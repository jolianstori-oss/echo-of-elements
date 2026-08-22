#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "ElementReactionData.generated.h"

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
