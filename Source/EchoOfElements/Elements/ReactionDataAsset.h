#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ElementType.h"
#include "ReactionDataAsset.generated.h"

UENUM(BlueprintType)
enum class EReactionEffect : uint8
{
    DamageOverTime UMETA(DisplayName = "Damage Over Time"),
    BurstDamage    UMETA(DisplayName = "Burst Damage"),
    Knockback      UMETA(DisplayName = "Knockback"),
    Root           UMETA(DisplayName = "Root"),
    Slow           UMETA(DisplayName = "Slow"),
    Stun           UMETA(DisplayName = "Stun"),
    Blind          UMETA(DisplayName = "Blind"),
    ArmorBreak     UMETA(DisplayName = "Armor Break"),
    Pull           UMETA(DisplayName = "Pull"),
    Lift           UMETA(DisplayName = "Lift"),
    Shield         UMETA(DisplayName = "Shield")
};

USTRUCT(BlueprintType)
struct ECHOOFELEMENTS_API FReactionDefinition
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Reaction")
    FName ReactionId = NAME_None;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Reaction")
    EElementType ElementA = EElementType::Fire;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Reaction")
    EElementType ElementB = EElementType::Water;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Reaction")
    FText DisplayName;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Reaction", meta = (MultiLine = true))
    FText Description;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Reaction")
    EReactionEffect Effect = EReactionEffect::BurstDamage;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Reaction", meta = (ClampMin = "0.0"))
    float DamageMultiplier = 1.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Reaction", meta = (ClampMin = "0.0"))
    float Duration = 0.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Reaction", meta = (ClampMin = "0.0"))
    float BuildupRequired = 100.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Reaction")
    bool bConsumesAppliedElements = true;
};

UCLASS(BlueprintType)
class ECHOOFELEMENTS_API UReactionDataAsset : public UDataAsset
{
    GENERATED_BODY()

public:
    UReactionDataAsset();

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Reactions")
    TArray<FReactionDefinition> Reactions;

    const FReactionDefinition* FindReaction(EElementType First, EElementType Second) const;
};
