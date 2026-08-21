#include "Abilities/ElementAbility.h"

#include "AbilitySystemComponent.h"

UElementAbility::UElementAbility()
{
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
    NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
    ReplicationPolicy = EGameplayAbilityReplicationPolicy::ReplicateNo;
}

FGameplayTag UElementAbility::GetElementTag() const
{
    return ElementTag.IsValid() ? ElementTag : (ElementData ? ElementData->ElementTag : FGameplayTag());
}

bool UElementAbility::CommitElementAbility(float DamageMultiplier)
{
    if (DamageMultiplier <= 0.f)
    {
        return false;
    }

    return CommitAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo);
}

bool UElementAbility::CommitAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, FGameplayTagContainer* OptionalRelevantTags)
{
    if (!ActorInfo || !ActorInfo->AbilitySystemComponent.IsValid())
    {
        return false;
    }

    return Super::CommitAbility(Handle, ActorInfo, ActivationInfo, OptionalRelevantTags);
}

void UElementAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
    K2_OnElementAbilityEnded(bWasCancelled);
    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UElementAbility::K2_OnElementAbilityEnded_Implementation(bool bWasCancelled)
{
}
