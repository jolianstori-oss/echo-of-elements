#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "ElementDataAsset.generated.h"

UENUM(BlueprintType)
enum class EElementAbilityType : uint8
{
    Basic,
    Mobility,
    Control,
    Ultimate
};

USTRUCT(BlueprintType)
struct ECHOOFELEMENTS_API FElementAbilityNumbers
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
    float BaseDamage = 0.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
    float ResonanceCost = 0.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
    float StaminaCost = 0.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
    float Cooldown = 0.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
    float StaggerDamage = 0.f;
};

UCLASS(BlueprintType)
class ECHOOFELEMENTS_API UElementDataAsset : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    virtual FPrimaryAssetId GetPrimaryAssetId() const override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Element", meta = (Categories = "Element"))
    FGameplayTag ElementTag;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Element")
    FText DisplayName;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Element")
    TObjectPtr<UTexture2D> Icon = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Element")
    FLinearColor PrimaryColor = FLinearColor::White;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Element")
    FGameplayTagContainer AppliedStatusTags;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Element")
    FElementAbilityNumbers BasicNumbers;
};

USTRUCT(BlueprintType)
struct ECHOOFELEMENTS_API FElementReactionDefinition
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "Element"))
    FGameplayTag ElementA;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "Element"))
    FGameplayTag ElementB;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "Reaction"))
    FGameplayTag ReactionTag;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float DamageMultiplier = 1.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float StaggerMultiplier = 1.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float BuildupRequired = 100.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float Duration = 0.f;
};

UCLASS(BlueprintType)
class ECHOOFELEMENTS_API UElementReactionDataAsset : public UDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Reactions")
    TArray<FElementReactionDefinition> Reactions;
};
