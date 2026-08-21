#include "BossIgnar.h"
#include "CharacterDataAsset.h"

ABossIgnar::ABossIgnar()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ABossIgnar::BeginPlay()
{
    Super::BeginPlay();
    CombatPhase = EIgnarCombatPhase::PhaseOne;
}

float ABossIgnar::GetPhaseHealthPercent() const
{
    return GetHealthPercent();
}

float ABossIgnar::TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    if (CombatPhase == EIgnarCombatPhase::Defeated || bAbsorbWindowOpen)
    {
        return 0.0f;
    }

    float PhaseAdjustedDamage = DamageAmount;
    if (CombatPhase == EIgnarCombatPhase::PhaseTwo)
    {
        PhaseAdjustedDamage /= PhaseTwoDamageMultiplier;
    }
    else if (CombatPhase == EIgnarCombatPhase::PhaseThree)
    {
        PhaseAdjustedDamage /= PhaseThreeDamageMultiplier;
    }

    const float AppliedDamage = Super::TakeDamage(PhaseAdjustedDamage, DamageEvent, EventInstigator, DamageCauser);
    if (!bIsDead)
    {
        UpdateCombatPhase();
    }
    return AppliedDamage;
}

void ABossIgnar::UpdateCombatPhase()
{
    const float HealthPercent = GetHealthPercent();
    if (HealthPercent <= 0.0f)
    {
        SetCombatPhase(EIgnarCombatPhase::Defeated);
    }
    else if (HealthPercent <= PhaseThreeHealthThreshold)
    {
        SetCombatPhase(EIgnarCombatPhase::PhaseThree);
    }
    else if (HealthPercent <= PhaseTwoHealthThreshold)
    {
        SetCombatPhase(EIgnarCombatPhase::PhaseTwo);
    }
}

void ABossIgnar::SetCombatPhase(EIgnarCombatPhase NewPhase)
{
    if (CombatPhase == NewPhase)
    {
        return;
    }

    CombatPhase = NewPhase;
    OnPhaseChanged.Broadcast(CombatPhase);
}

void ABossIgnar::StartTelegraph(FName AttackId, float Duration)
{
    if (CombatPhase == EIgnarCombatPhase::Defeated || AttackId.IsNone())
    {
        return;
    }

    ActiveTelegraphAttack = AttackId;
    OnTelegraphStarted.Broadcast(ActiveTelegraphAttack);
    GetWorldTimerManager().SetTimer(TelegraphTimerHandle, this, &ABossIgnar::FinishTelegraph, FMath::Max(0.05f, Duration), false);
}

void ABossIgnar::FinishTelegraph()
{
    ActiveTelegraphAttack = NAME_None;
}

void ABossIgnar::OpenAbsorbWindow(float Duration)
{
    if (CombatPhase == EIgnarCombatPhase::Defeated)
    {
        return;
    }

    bAbsorbWindowOpen = true;
    GetWorldTimerManager().SetTimer(AbsorbWindowTimerHandle, this, &ABossIgnar::CloseAbsorbWindow, FMath::Max(0.05f, Duration), false);
}

void ABossIgnar::CloseAbsorbWindow()
{
    bAbsorbWindowOpen = false;
}
