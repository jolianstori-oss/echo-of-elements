#include "CharacterBase.h"
#include "CharacterDataAsset.h"
#include "Kismet/GameplayStatics.h"

ACharacterBase::ACharacterBase()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ACharacterBase::BeginPlay()
{
    Super::BeginPlay();

    if (CharacterData)
    {
        Health = CharacterData->Resources.MaxHealth;
        Resonance = CharacterData->Resources.MaxResonance;
        Stamina = CharacterData->Resources.MaxStamina;
        ActiveElementTags = CharacterData->PrimaryElementTags;
        GetCharacterMovement()->MaxWalkSpeed *= CharacterData->MoveSpeedMultiplier;
    }
}

void ACharacterBase::SetCharacterData(UCharacterDataAsset* InCharacterData)
{
    if (!InCharacterData || HasActorBegunPlay())
    {
        return;
    }

    CharacterData = InCharacterData;
}

float ACharacterBase::GetHealthPercent() const
{
    const float MaxHealth = CharacterData ? CharacterData->Resources.MaxHealth : 0.0f;
    return MaxHealth > 0.0f ? FMath::Clamp(Health / MaxHealth, 0.0f, 1.0f) : 0.0f;
}

void ACharacterBase::RestoreHealth(float Amount)
{
    if (bIsDead || Amount <= 0.0f)
    {
        return;
    }

    const float MaxHealth = CharacterData ? CharacterData->Resources.MaxHealth : Health;
    Health = FMath::Min(Health + Amount, MaxHealth);
    BroadcastResourceChanged();
}

bool ACharacterBase::ConsumeResonance(float Amount)
{
    if (Amount < 0.0f || Resonance < Amount)
    {
        return false;
    }

    Resonance -= Amount;
    BroadcastResourceChanged();
    return true;
}

float ACharacterBase::TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    if (bIsDead || DamageAmount <= 0.0f)
    {
        return 0.0f;
    }

    const float Defense = CharacterData ? CharacterData->Resources.Defense : 0.0f;
    const float AppliedDamage = FMath::Max(0.0f, DamageAmount - Defense);
    Health = FMath::Max(0.0f, Health - AppliedDamage);
    BroadcastResourceChanged();

    if (Health <= 0.0f)
    {
        HandleDeath(EventInstigator, DamageCauser);
    }

    return AppliedDamage;
}

void ACharacterBase::DealCharacterDamage(AActor* Target, float DamageAmount, TSubclassOf<UDamageType> DamageType)
{
    if (Target && DamageAmount > 0.0f && !bIsDead)
    {
        UGameplayStatics::ApplyDamage(Target, DamageAmount, GetController(), this, DamageType);
    }
}

void ACharacterBase::HandleDeath(AController* EventInstigator, AActor* DamageCauser)
{
    if (bIsDead)
    {
        return;
    }

    bIsDead = true;
    GetCharacterMovement()->DisableMovement();
    OnCharacterDeath.Broadcast(this);
    SetLifeSpan(5.0f);
}

void ACharacterBase::BroadcastResourceChanged()
{
    OnResourceChanged.Broadcast(this);
}
