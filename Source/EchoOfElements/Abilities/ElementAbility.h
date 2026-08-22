#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayTagContainer.h"
#include "Elements/ElementDataAsset.h"
#include "ElementAbility.generated.h"

UCLASS(Abstract)
class ECHOOFELEMENTS_API UElementAbility : public UGameplayAbility
{
    GENERATED_BODY()

public:
    UElementAbility();

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Element Ability")
    EElementAbilityType AbilityType = EElementAbilityType::Basic;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Element Ability")
    TObjectPtr<const UElementDataAsset> ElementData;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Element Ability", meta = (Categories = "Element"))
    FGameplayTag ElementTag;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Element Ability")
    FElementAbilityNumbers Numbers;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Element Ability", meta = (Categories = "Ability.Cooldown"))
    FGameplayTag CooldownTag;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Element Ability", meta = (Categories = "Ability.Block"))
    FGameplayTagContainer BlockedAbilityTags;

    UFUNCTION(BlueprintPure, Category = "Element Ability")
    EElementAbilityType GetElementAbilityType() const { return AbilityType; }

    UFUNCTION(BlueprintPure, Category = "Element Ability")
    FGameplayTag GetElementTag() const;

    UFUNCTION(BlueprintCallable, Category = "Element Ability")
    bool CommitElementAbility(float DamageMultiplier = 1.f);

protected:
    virtual bool CommitAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, FGameplayTagContainer* OptionalRelevantTags = nullptr) override;
    virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

    UFUNCTION(BlueprintNativeEvent, Category = "Element Ability")
    void K2_OnElementAbilityEnded(bool bWasCancelled);
};
