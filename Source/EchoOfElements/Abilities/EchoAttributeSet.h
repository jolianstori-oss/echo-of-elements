#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "EchoAttributeSet.generated.h"

/** GAS attributes owned by Echo of Elements actors. */
UCLASS()
class ECHOOFELEMENTS_API UEchoAttributeSet : public UAttributeSet
{
    GENERATED_BODY()

public:
    UEchoAttributeSet();

    UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Health)
    FGameplayAttributeData Health;
    ATTRIBUTE_ACCESSORS(UEchoAttributeSet, Health)

    UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_MaxHealth)
    FGameplayAttributeData MaxHealth;
    ATTRIBUTE_ACCESSORS(UEchoAttributeSet, MaxHealth)

    UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Stamina)
    FGameplayAttributeData Stamina;
    ATTRIBUTE_ACCESSORS(UEchoAttributeSet, Stamina)

    UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_MaxStamina)
    FGameplayAttributeData MaxStamina;
    ATTRIBUTE_ACCESSORS(UEchoAttributeSet, MaxStamina)

    UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Resonance)
    FGameplayAttributeData Resonance;
    ATTRIBUTE_ACCESSORS(UEchoAttributeSet, Resonance)

    UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_MaxResonance)
    FGameplayAttributeData MaxResonance;
    ATTRIBUTE_ACCESSORS(UEchoAttributeSet, MaxResonance)

    UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_StaggerResistance)
    FGameplayAttributeData StaggerResistance;
    ATTRIBUTE_ACCESSORS(UEchoAttributeSet, StaggerResistance)

    UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_KineticPower)
    FGameplayAttributeData KineticPower;
    ATTRIBUTE_ACCESSORS(UEchoAttributeSet, KineticPower)

    UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Defense)
    FGameplayAttributeData Defense;
    ATTRIBUTE_ACCESSORS(UEchoAttributeSet, Defense)

    UPROPERTY(BlueprintReadOnly, Category = "Elemental Buildup", ReplicatedUsing = OnRep_BuildupFire)
    FGameplayAttributeData BuildupFire;
    ATTRIBUTE_ACCESSORS(UEchoAttributeSet, BuildupFire)

    UPROPERTY(BlueprintReadOnly, Category = "Elemental Buildup", ReplicatedUsing = OnRep_BuildupWater)
    FGameplayAttributeData BuildupWater;
    ATTRIBUTE_ACCESSORS(UEchoAttributeSet, BuildupWater)

    UPROPERTY(BlueprintReadOnly, Category = "Elemental Buildup", ReplicatedUsing = OnRep_BuildupEarth)
    FGameplayAttributeData BuildupEarth;
    ATTRIBUTE_ACCESSORS(UEchoAttributeSet, BuildupEarth)

    UPROPERTY(BlueprintReadOnly, Category = "Elemental Buildup", ReplicatedUsing = OnRep_BuildupStone)
    FGameplayAttributeData BuildupStone;
    ATTRIBUTE_ACCESSORS(UEchoAttributeSet, BuildupStone)

    UPROPERTY(BlueprintReadOnly, Category = "Elemental Buildup", ReplicatedUsing = OnRep_BuildupWind)
    FGameplayAttributeData BuildupWind;
    ATTRIBUTE_ACCESSORS(UEchoAttributeSet, BuildupWind)

    UPROPERTY(BlueprintReadOnly, Category = "Elemental Buildup", ReplicatedUsing = OnRep_BuildupLightning)
    FGameplayAttributeData BuildupLightning;
    ATTRIBUTE_ACCESSORS(UEchoAttributeSet, BuildupLightning)

    UPROPERTY(BlueprintReadOnly, Category = "Elemental Buildup", ReplicatedUsing = OnRep_BuildupIce)
    FGameplayAttributeData BuildupIce;
    ATTRIBUTE_ACCESSORS(UEchoAttributeSet, BuildupIce)

    UPROPERTY(BlueprintReadOnly, Category = "Elemental Buildup", ReplicatedUsing = OnRep_BuildupNature)
    FGameplayAttributeData BuildupNature;
    ATTRIBUTE_ACCESSORS(UEchoAttributeSet, BuildupNature)

    UPROPERTY(BlueprintReadOnly, Category = "Elemental Buildup", ReplicatedUsing = OnRep_BuildupSand)
    FGameplayAttributeData BuildupSand;
    ATTRIBUTE_ACCESSORS(UEchoAttributeSet, BuildupSand)

    UPROPERTY(BlueprintReadOnly, Category = "Elemental Buildup", ReplicatedUsing = OnRep_BuildupMetal)
    FGameplayAttributeData BuildupMetal;
    ATTRIBUTE_ACCESSORS(UEchoAttributeSet, BuildupMetal)

    UPROPERTY(BlueprintReadOnly, Category = "Elemental Buildup", ReplicatedUsing = OnRep_BuildupLight)
    FGameplayAttributeData BuildupLight;
    ATTRIBUTE_ACCESSORS(UEchoAttributeSet, BuildupLight)

    UPROPERTY(BlueprintReadOnly, Category = "Elemental Buildup", ReplicatedUsing = OnRep_BuildupGravity)
    FGameplayAttributeData BuildupGravity;
    ATTRIBUTE_ACCESSORS(UEchoAttributeSet, BuildupGravity)

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
    virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

protected:
    UFUNCTION() void OnRep_Health(const FGameplayAttributeData& OldValue) const;
    UFUNCTION() void OnRep_MaxHealth(const FGameplayAttributeData& OldValue) const;
    UFUNCTION() void OnRep_Stamina(const FGameplayAttributeData& OldValue) const;
    UFUNCTION() void OnRep_MaxStamina(const FGameplayAttributeData& OldValue) const;
    UFUNCTION() void OnRep_Resonance(const FGameplayAttributeData& OldValue) const;
    UFUNCTION() void OnRep_MaxResonance(const FGameplayAttributeData& OldValue) const;
    UFUNCTION() void OnRep_StaggerResistance(const FGameplayAttributeData& OldValue) const;
    UFUNCTION() void OnRep_KineticPower(const FGameplayAttributeData& OldValue) const;
    UFUNCTION() void OnRep_Defense(const FGameplayAttributeData& OldValue) const;
    UFUNCTION() void OnRep_BuildupFire(const FGameplayAttributeData& OldValue) const;
    UFUNCTION() void OnRep_BuildupWater(const FGameplayAttributeData& OldValue) const;
    UFUNCTION() void OnRep_BuildupEarth(const FGameplayAttributeData& OldValue) const;
    UFUNCTION() void OnRep_BuildupStone(const FGameplayAttributeData& OldValue) const;
    UFUNCTION() void OnRep_BuildupWind(const FGameplayAttributeData& OldValue) const;
    UFUNCTION() void OnRep_BuildupLightning(const FGameplayAttributeData& OldValue) const;
    UFUNCTION() void OnRep_BuildupIce(const FGameplayAttributeData& OldValue) const;
    UFUNCTION() void OnRep_BuildupNature(const FGameplayAttributeData& OldValue) const;
    UFUNCTION() void OnRep_BuildupSand(const FGameplayAttributeData& OldValue) const;
    UFUNCTION() void OnRep_BuildupMetal(const FGameplayAttributeData& OldValue) const;
    UFUNCTION() void OnRep_BuildupLight(const FGameplayAttributeData& OldValue) const;
    UFUNCTION() void OnRep_BuildupGravity(const FGameplayAttributeData& OldValue) const;
};
