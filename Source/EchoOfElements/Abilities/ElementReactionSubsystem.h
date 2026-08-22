#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "GameplayTagContainer.h"
#include "Elements/ElementReactionData.h"
#include "ElementReactionSubsystem.generated.h"

USTRUCT(BlueprintType)
struct ECHOOFELEMENTS_API FResolvedElementReaction
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    bool bFound = false;

    UPROPERTY(BlueprintReadOnly)
    FGameplayTag ElementA;

    UPROPERTY(BlueprintReadOnly)
    FGameplayTag ElementB;

    UPROPERTY(BlueprintReadOnly)
    FGameplayTag ReactionTag;

    UPROPERTY(BlueprintReadOnly)
    float DamageMultiplier = 1.f;

    UPROPERTY(BlueprintReadOnly)
    float StaggerMultiplier = 1.f;

    UPROPERTY(BlueprintReadOnly)
    float BuildupRequired = 100.f;

    UPROPERTY(BlueprintReadOnly)
    float Duration = 0.f;
};

UCLASS()
class ECHOOFELEMENTS_API UElementReactionSubsystem : public UWorldSubsystem
{
    GENERATED_BODY()

public:
    virtual void Deinitialize() override;

    UFUNCTION(BlueprintCallable, Category = "Elements|Reactions")
    void LoadReactionData(const UElementReactionDataAsset* ReactionData);

    UFUNCTION(BlueprintPure, Category = "Elements|Reactions")
    bool FindReaction(FGameplayTag ElementA, FGameplayTag ElementB, FElementReactionDefinition& OutReaction) const;

    UFUNCTION(BlueprintPure, Category = "Elements|Reactions")
    FResolvedElementReaction ResolveReaction(FGameplayTag ElementA, FGameplayTag ElementB) const;

    UFUNCTION(BlueprintPure, Category = "Elements|Reactions")
    static FGameplayTag MakeCanonicalPairTag(FGameplayTag ElementA, FGameplayTag ElementB);

private:
    static FName MakePairKey(FGameplayTag ElementA, FGameplayTag ElementB);

    TMap<FName, FElementReactionDefinition> ReactionByPair;
};
