#pragma once

#include "CoreMinimal.h"
#include "ElementAbility.h"
#include "AbsorbAbility.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAbsorbResultSignature, bool, bPerfectAbsorb);

UCLASS()
class ECHOOFELEMENTS_API UAbsorbAbility : public UElementAbility
{
    GENERATED_BODY()

public:
    UAbsorbAbility();

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Absorb")
    float AbsorbRange = 500.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Absorb")
    float PerfectAbsorbWindow = 0.20f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Absorb", meta = (Categories = "State"))
    FGameplayTag AbsorbWindowTag;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Absorb", meta = (Categories = "State"))
    FGameplayTag InvulnerableTag;

    UPROPERTY(BlueprintAssignable, Category = "Absorb")
    FAbsorbResultSignature OnAbsorbResult;

    UFUNCTION(BlueprintCallable, Category = "Absorb")
    void BeginPerfectAbsorbWindow();

    UFUNCTION(BlueprintCallable, Category = "Absorb")
    bool TryPerfectAbsorb();

    UFUNCTION(BlueprintPure, Category = "Absorb")
    bool IsPerfectAbsorbWindowOpen() const { return bPerfectWindowOpen; }

protected:
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
    virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

private:
    void ClosePerfectAbsorbWindow();

    FTimerHandle PerfectWindowTimerHandle;
    bool bPerfectWindowOpen = false;
};
