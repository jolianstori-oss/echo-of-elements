#include "EnemyAIController.h"
#include "NavigationSystem.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

AEnemyAIController::AEnemyAIController()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AEnemyAIController::BeginPlay()
{
    Super::BeginPlay();
    GetWorldTimerManager().SetTimer(ThinkTimerHandle, this, &AEnemyAIController::Think, 0.2f, true);
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    PatrolOrigin = InPawn ? InPawn->GetActorLocation() : FVector::ZeroVector;
    MoveToPatrolPoint();
}

void AEnemyAIController::OnUnPossess()
{
    GetWorldTimerManager().ClearTimer(ThinkTimerHandle);
    GetWorldTimerManager().ClearTimer(TelegraphTimerHandle);
    Super::OnUnPossess();
}

void AEnemyAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    if (AIState == EEnemyAIState::Chase && TargetActor.IsValid())
    {
        MoveToActor(TargetActor.Get(), AttackRadius * 0.75f);
    }
}

void AEnemyAIController::SetTargetActor(AActor* NewTarget)
{
    TargetActor = NewTarget;
    SetAIState(NewTarget ? EEnemyAIState::Chase : EEnemyAIState::Patrol);
}

void AEnemyAIController::Think()
{
    if (!GetPawn() || AIState == EEnemyAIState::Telegraph)
    {
        return;
    }

    if (!TargetActor.IsValid())
    {
        SelectTarget();
    }

    if (!TargetActor.IsValid())
    {
        SetAIState(EEnemyAIState::Patrol);
        MoveToPatrolPoint();
        return;
    }

    const float Distance = FVector::Dist(GetPawn()->GetActorLocation(), TargetActor->GetActorLocation());
    if (Distance > DetectionRadius)
    {
        TargetActor.Reset();
        SetAIState(EEnemyAIState::Patrol);
        return;
    }

    if (Distance <= AttackRadius && GetWorld()->GetTimeSeconds() >= LastAttackTime + AttackCooldown)
    {
        BeginTelegraph(TelegraphDuration);
    }
    else
    {
        SetAIState(EEnemyAIState::Chase);
    }
}

void AEnemyAIController::SelectTarget()
{
    APawn* Candidate = UGameplayStatics::GetPlayerPawn(this, 0);
    if (Candidate && FVector::Dist(GetPawn()->GetActorLocation(), Candidate->GetActorLocation()) <= DetectionRadius)
    {
        TargetActor = Candidate;
    }
}

void AEnemyAIController::MoveToPatrolPoint()
{
    if (!GetPawn() || AIState != EEnemyAIState::Patrol)
    {
        return;
    }

    UNavigationSystemV1* Navigation = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
    if (!Navigation)
    {
        return;
    }

    FNavLocation Candidate;
    if (Navigation->GetRandomReachablePointInRadius(PatrolOrigin, PatrolRadius, Candidate))
    {
        CurrentPatrolPoint = Candidate.Location;
        MoveToLocation(CurrentPatrolPoint, 50.0f);
    }
}

void AEnemyAIController::BeginTelegraph(float Duration)
{
    if (AIState == EEnemyAIState::Telegraph || !TargetActor.IsValid())
    {
        return;
    }

    StopMovement();
    SetAIState(EEnemyAIState::Telegraph);
    OnTelegraphStarted();
    GetWorldTimerManager().SetTimer(TelegraphTimerHandle, this, &AEnemyAIController::FinishTelegraph, FMath::Max(0.05f, Duration), false);
}

void AEnemyAIController::FinishTelegraph()
{
    if (TargetActor.IsValid())
    {
        SetAIState(EEnemyAIState::Attack);
        LastAttackTime = GetWorld()->GetTimeSeconds();
        ExecuteAttack();
    }
    SetAIState(TargetActor.IsValid() ? EEnemyAIState::Chase : EEnemyAIState::Patrol);
}

void AEnemyAIController::SetAIState(EEnemyAIState NewState)
{
    if (AIState != NewState)
    {
        AIState = NewState;
        OnAIStateChanged.Broadcast(AIState);
    }
}

void AEnemyAIController::ExecuteAttack_Implementation()
{
}

void AEnemyAIController::OnTelegraphStarted_Implementation()
{
}
