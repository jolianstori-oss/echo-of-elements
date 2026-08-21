#include "Abilities/EchoAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

UEchoAttributeSet::UEchoAttributeSet()
{
    InitHealth(100.f);
    InitMaxHealth(100.f);
    InitStamina(100.f);
    InitMaxStamina(100.f);
    InitResonance(0.f);
    InitMaxResonance(100.f);
    InitStaggerResistance(100.f);
    InitKineticPower(10.f);
    InitDefense(0.f);
}

void UEchoAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
#define ECHO_REPLICATE(AttributeName) \
    DOREPLIFETIME_CONDITION_NOTIFY(UEchoAttributeSet, AttributeName, COND_None, REPNOTIFY_Always)
    ECHO_REPLICATE(Health);
    ECHO_REPLICATE(MaxHealth);
    ECHO_REPLICATE(Stamina);
    ECHO_REPLICATE(MaxStamina);
    ECHO_REPLICATE(Resonance);
    ECHO_REPLICATE(MaxResonance);
    ECHO_REPLICATE(StaggerResistance);
    ECHO_REPLICATE(KineticPower);
    ECHO_REPLICATE(Defense);
    ECHO_REPLICATE(BuildupFire);
    ECHO_REPLICATE(BuildupWater);
    ECHO_REPLICATE(BuildupEarth);
    ECHO_REPLICATE(BuildupStone);
    ECHO_REPLICATE(BuildupWind);
    ECHO_REPLICATE(BuildupLightning);
    ECHO_REPLICATE(BuildupIce);
    ECHO_REPLICATE(BuildupNature);
    ECHO_REPLICATE(BuildupSand);
    ECHO_REPLICATE(BuildupMetal);
    ECHO_REPLICATE(BuildupLight);
    ECHO_REPLICATE(BuildupGravity);
#undef ECHO_REPLICATE
}

void UEchoAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
    Super::PreAttributeChange(Attribute, NewValue);
    if (Attribute == GetHealthAttribute()) NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
    else if (Attribute == GetStaminaAttribute()) NewValue = FMath::Clamp(NewValue, 0.f, GetMaxStamina());
    else if (Attribute == GetResonanceAttribute()) NewValue = FMath::Clamp(NewValue, 0.f, GetMaxResonance());
    else if (Attribute == GetStaggerResistanceAttribute()) NewValue = FMath::Max(0.f, NewValue);
    else if (Attribute == GetDefenseAttribute()) NewValue = FMath::Max(0.f, NewValue);
    else if (Attribute == GetKineticPowerAttribute()) NewValue = FMath::Max(0.f, NewValue);
    else if (Attribute == GetMaxHealthAttribute() || Attribute == GetMaxStaminaAttribute() || Attribute == GetMaxResonance()) NewValue = FMath::Max(0.f, NewValue);
    else NewValue = FMath::Max(0.f, NewValue);
}

void UEchoAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);
    if (Data.EvaluatedData.Attribute == GetHealthAttribute()) SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
    else if (Data.EvaluatedData.Attribute == GetStaminaAttribute()) SetStamina(FMath::Clamp(GetStamina(), 0.f, GetMaxStamina()));
    else if (Data.EvaluatedData.Attribute == GetResonanceAttribute()) SetResonance(FMath::Clamp(GetResonance(), 0.f, GetMaxResonance()));
}

#define ECHO_ONREP_IMPL(AttributeName) \
void UEchoAttributeSet::OnRep_##AttributeName(const FGameplayAttributeData& OldValue) const { GAMEPLAYATTRIBUTE_REPNOTIFY(UEchoAttributeSet, AttributeName, OldValue); }
ECHO_ONREP_IMPL(Health)
ECHO_ONREP_IMPL(MaxHealth)
ECHO_ONREP_IMPL(Stamina)
ECHO_ONREP_IMPL(MaxStamina)
ECHO_ONREP_IMPL(Resonance)
ECHO_ONREP_IMPL(MaxResonance)
ECHO_ONREP_IMPL(StaggerResistance)
ECHO_ONREP_IMPL(KineticPower)
ECHO_ONREP_IMPL(Defense)
ECHO_ONREP_IMPL(BuildupFire)
ECHO_ONREP_IMPL(BuildupWater)
ECHO_ONREP_IMPL(BuildupEarth)
ECHO_ONREP_IMPL(BuildupStone)
ECHO_ONREP_IMPL(BuildupWind)
ECHO_ONREP_IMPL(BuildupLightning)
ECHO_ONREP_IMPL(BuildupIce)
ECHO_ONREP_IMPL(BuildupNature)
ECHO_ONREP_IMPL(BuildupSand)
ECHO_ONREP_IMPL(BuildupMetal)
ECHO_ONREP_IMPL(BuildupLight)
ECHO_ONREP_IMPL(BuildupGravity)
#undef ECHO_ONREP_IMPL
