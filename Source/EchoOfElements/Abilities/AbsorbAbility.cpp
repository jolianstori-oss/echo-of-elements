#include "Abilities/AbsorbAbility.h"

#include "AbilitySystemComponent.h"
#include "TimerManager.h"

UAbsorbAbility::UAbsorbAbility()
{
    AbilityType = EElementAbilityType::Control;
    NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
    AbsorbWindowTag = FGameplayTag::RequestGameplayTag(TEXT("State.AbsorbWindow"));
    InvulnerableTag = FGameplayTag::RequestGameplayTag(TEXT("State.Invulnerable"));
}

void UAbsorbAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
    {
        EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
        return;
    }

    BeginPerfectAbsorbWindow();
}

void UAbsorbAbility::BeginPerfectAbsorbWindow()
{
    if (bPerfectWindowOpen)
    {
        return;
    }

    bPerfectWindowOpen = true;
    if (UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo())
    {
        ASC->AddLooseGameplayTag(AbsorbWindowTag);
    }

    if (UWorld* World = GetWorld())
    {
        World->GetTimerManager().SetTimer(PerfectWindowTimerHandle, this, &ThisClass::ClosePerfectAbsorbWindow, FMath::Max(0.f, PerfectAbsorbWindow), false);
    }
}

bool UAbsorbAbility::TryPerfectAbsorb()
{
    if (!bPerfectWindowOpen || !GetAbilitySystemComponentFromActorInfo())
    {
        OnAbsorbResult.Broadcast(false);
        return false;
    }

    bPerfectWindowOpen = false;
    if (UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo())
    {
        ASC->RemoveLooseGameplayTag(AbsorbWindowTag);
    }
    if (UWorld* World = GetWorld())
    {
        World->GetTimerManager().ClearTimer(PerfectWindowTimerHandle);
    }

    OnAbsorbResult.Broadcast(true);
    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
    return true;
}

void UAbsorbAbility::ClosePerfectAbsorbWindow()
{
    if (!bPerfectWindowOpen)
    {
        return;
    }

    bPerfectWindowOpen = false;
    if (UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo())
    {
        ASC->RemoveLooseGameplayTag(AbsorbWindowTag);
    }
    OnAbsorbResult.Broadcast(false);
    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}

void UAbsorbAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
    if (UWorld* World = GetWorld())
    {
        World->GetTimerManager().ClearTimer(PerfectWindowTimerHandle);
    }
    if (UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo())
    {
        ASC->RemoveLooseGameplayTag(AbsorbWindowTag);
    }
    bPerfectWindowOpen = false;
    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
