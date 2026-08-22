#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "ElementType.h"
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
    float BaseDamage = 0.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
    float ResonanceCost = 0.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
    float StaminaCost = 0.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
    float Cooldown = 0.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
    float StaggerDamage = 0.0f;
};

UENUM(BlueprintType)
enum class EElementMobility : uint8
{
    None        UMETA(DisplayName = "None"),
    Dash        UMETA(DisplayName = "Dash"),
    Leap        UMETA(DisplayName = "Leap"),
    Glide       UMETA(DisplayName = "Glide"),
    Teleport    UMETA(DisplayName = "Teleport"),
    Burrow      UMETA(DisplayName = "Burrow"),
    Pull        UMETA(DisplayName = "Pull")
};

UENUM(BlueprintType)
enum class EElementControl : uint8
{
    None        UMETA(DisplayName = "None"),
    Knockback   UMETA(DisplayName = "Knockback"),
    Root        UMETA(DisplayName = "Root"),
    Slow        UMETA(DisplayName = "Slow"),
    Stun        UMETA(DisplayName = "Stun"),
    Blind       UMETA(DisplayName = "Blind"),
    Lift        UMETA(DisplayName = "Lift"),
    Magnetize   UMETA(DisplayName = "Magnetize")
};

USTRUCT(BlueprintType)
struct ECHOOFELEMENTS_API FElementAbilityData
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
    FName AbilityId = NAME_None;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
    FText DisplayName;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability", meta = (MultiLine = true))
    FText Description;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability", meta = (ClampMin = "0.0"))
    float BaseDamage = 0.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability", meta = (ClampMin = "0.0"))
    float Cooldown = 0.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability", meta = (ClampMin = "0.0"))
    float ResonanceCost = 0.0f;
};

USTRUCT(BlueprintType)
struct ECHOOFELEMENTS_API FElementInteractionData
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interaction")
    EElementType TargetElement = EElementType::Fire;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interaction", meta = (Categories = "Reaction"))
    FGameplayTag ReactionTag;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interaction")
    float AffinityMultiplier = 1.0f;
};

UCLASS(BlueprintType)
class ECHOOFELEMENTS_API UElementDataAsset : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    virtual FPrimaryAssetId GetPrimaryAssetId() const override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Element")
    EElementType ElementType = EElementType::Fire;

    /** Legacy tag retained for existing Gameplay Ability assets. */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Element", meta = (Categories = "Element"))
    FGameplayTag ElementTag;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Element")
    FGameplayTagContainer AppliedStatusTags;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Element")
    FName ElementId = NAME_None;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Element")
    FText DisplayName;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Element", meta = (MultiLine = true))
    FText Description;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Element")
    FLinearColor PrimaryColor = FLinearColor::White;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Element")
    FLinearColor SecondaryColor = FLinearColor::Black;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Element")
    TObjectPtr<UTexture2D> Icon = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Element")
    EElementMobility Mobility = EElementMobility::None;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Element")
    EElementControl Control = EElementControl::None;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
    FElementAbilityData BasicAbility;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
    FElementAbilityNumbers BasicNumbers;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
    FElementAbilityData MobilityAbility;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
    FElementAbilityData ControlAbility;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
    FElementAbilityData UltimateAbility;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interactions")
    TArray<FElementInteractionData> Interactions;
};
