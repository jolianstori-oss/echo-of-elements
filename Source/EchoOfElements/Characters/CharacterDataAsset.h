#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "CharacterDataAsset.generated.h"

class ACharacter;
class UAnimMontage;
class USkeletalMesh;

UENUM(BlueprintType)
enum class ECharacterRole : uint8
{
    Hero,
    Enemy,
    Boss
};

UENUM(BlueprintType)
enum class EEnemyArchetype : uint8
{
    None,
    Melee,
    Ranged,
    WeakPointHunter,
    Boss
};

USTRUCT(BlueprintType)
struct FCharacterResourceDefaults
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Resources", meta = (ClampMin = "0.0"))
    float MaxHealth = 1000.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Resources", meta = (ClampMin = "0.0"))
    float MaxResonance = 100.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Resources", meta = (ClampMin = "0.0"))
    float MaxStamina = 100.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Resources", meta = (ClampMin = "0.0"))
    float AttackPower = 100.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Resources", meta = (ClampMin = "0.0"))
    float Defense = 0.0f;
};

UCLASS(BlueprintType)
class ECHOOFELEMENTS_API UCharacterDataAsset : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    virtual FPrimaryAssetId GetPrimaryAssetId() const override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Identity")
    FName CharacterId;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Identity")
    FText DisplayName;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Identity")
    ECharacterRole Role = ECharacterRole::Enemy;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Identity")
    EEnemyArchetype AIArchetype = EEnemyArchetype::None;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
    FCharacterResourceDefaults Resources;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats", meta = (ClampMin = "0.01"))
    float MoveSpeedMultiplier = 1.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats", meta = (ClampMin = "0.0"))
    float PreferredRange = 250.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Element")
    FGameplayTagContainer PrimaryElementTags;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
    FGameplayTagContainer WeaknessTags;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Presentation")
    TObjectPtr<USkeletalMesh> CharacterMesh;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Presentation")
    TArray<TObjectPtr<UAnimMontage>> AttackMontages;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
    float AggroRange = 1500.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
    float AttackRange = 180.0f;
};
