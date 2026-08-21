#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

UENUM(BlueprintType)
enum class EEnemyAIState : uint8
{
    Patrol,
    Chase,
    Telegraph,
    Attack
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEnemyAIStateChangedSignature, EEnemyAIState, NewState);

UCLASS(Blueprintable)
class ECHOOFELEMENTS_API AEnemyAIController : public AAIController
{
    GENERATED_BODY()

public:
    AEnemyAIController();

    virtual void OnPossess(APawn* InPawn) override;
    virtual void OnUnPossess() override;

    UFUNCTION(BlueprintCallable, Category = "AI")
    void SetTargetActor(AActor* NewTarget);

    UFUNCTION(BlueprintPure, Category = "AI")
    EEnemyAIState GetAIState() const { return AIState; }

    UFUNCTION(BlueprintPure, Category = "AI")
    AActor* GetTargetActor() const { return TargetActor.Get(); }

    UFUNCTION(BlueprintCallable, Category = "AI")
    void BeginTelegraph(float Duration);

    UPROPERTY(BlueprintAssignable, Category = "AI|Events")
    FEnemyAIStateChangedSignature OnAIStateChanged;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI|Tuning")
    float DetectionRadius = 1500.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI|Tuning")
    float AttackRadius = 180.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI|Tuning")
    float AttackCooldown = 1.5f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI|Tuning")
    float PatrolRadius = 600.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI|Tuning")
    float TelegraphDuration = 0.8f;

    UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "AI|State")
    EEnemyAIState AIState = EEnemyAIState::Patrol;

    TWeakObjectPtr<AActor> TargetActor;
    FTimerHandle ThinkTimerHandle;
    FTimerHandle TelegraphTimerHandle;
    FVector PatrolOrigin = FVector::ZeroVector;
    FVector CurrentPatrolPoint = FVector::ZeroVector;
    double LastAttackTime = -BIG_NUMBER;

    virtual void Tick(float DeltaSeconds) override;
    virtual void BeginPlay() override;

    UFUNCTION(BlueprintNativeEvent, Category = "AI")
    void ExecuteAttack();
    virtual void ExecuteAttack_Implementation();

    UFUNCTION(BlueprintNativeEvent, Category = "AI")
    void OnTelegraphStarted();
    virtual void OnTelegraphStarted_Implementation();

    void Think();
    void SelectTarget();
    void MoveToPatrolPoint();
    void SetAIState(EEnemyAIState NewState);
    void FinishTelegraph();
};
