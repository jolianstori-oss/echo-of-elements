#include "Abilities/ElementReactionSubsystem.h"

void UElementReactionSubsystem::Deinitialize()
{
    ReactionByPair.Reset();
    Super::Deinitialize();
}

void UElementReactionSubsystem::LoadReactionData(const UElementReactionDataAsset* ReactionData)
{
    ReactionByPair.Reset();
    if (!ReactionData)
    {
        return;
    }

    for (const FElementReactionDefinition& Definition : ReactionData->Reactions)
    {
        if (Definition.ElementA.IsValid() && Definition.ElementB.IsValid() && Definition.ReactionTag.IsValid())
        {
            ReactionByPair.Add(MakePairKey(Definition.ElementA, Definition.ElementB), Definition);
        }
    }
}

bool UElementReactionSubsystem::FindReaction(FGameplayTag ElementA, FGameplayTag ElementB, FElementReactionDefinition& OutReaction) const
{
    const FElementReactionDefinition* Found = ReactionByPair.Find(MakePairKey(ElementA, ElementB));
    if (!Found)
    {
        OutReaction = FElementReactionDefinition();
        return false;
    }

    OutReaction = *Found;
    return true;
}

FResolvedElementReaction UElementReactionSubsystem::ResolveReaction(FGameplayTag ElementA, FGameplayTag ElementB) const
{
    FResolvedElementReaction Result;
    FElementReactionDefinition Definition;
    if (!FindReaction(ElementA, ElementB, Definition))
    {
        return Result;
    }

    Result.bFound = true;
    Result.ElementA = Definition.ElementA;
    Result.ElementB = Definition.ElementB;
    Result.ReactionTag = Definition.ReactionTag;
    Result.DamageMultiplier = Definition.DamageMultiplier;
    Result.StaggerMultiplier = Definition.StaggerMultiplier;
    Result.BuildupRequired = Definition.BuildupRequired;
    Result.Duration = Definition.Duration;
    return Result;
}

FGameplayTag UElementReactionSubsystem::MakeCanonicalPairTag(FGameplayTag ElementA, FGameplayTag ElementB)
{
    if (!ElementA.IsValid() || !ElementB.IsValid())
    {
        return FGameplayTag();
    }

    const FString A = ElementA.GetTagName().ToString();
    const FString B = ElementB.GetTagName().ToString();
    const FString Pair = A <= B ? FString::Printf(TEXT("Reaction.Pair.%s.%s"), *A, *B) : FString::Printf(TEXT("Reaction.Pair.%s.%s"), *B, *A);
    return FGameplayTag::RequestGameplayTag(FName(*Pair), false);
}

FName UElementReactionSubsystem::MakePairKey(FGameplayTag ElementA, FGameplayTag ElementB)
{
    if (!ElementA.IsValid() || !ElementB.IsValid())
    {
        return NAME_None;
    }

    const FString A = ElementA.GetTagName().ToString();
    const FString B = ElementB.GetTagName().ToString();
    return FName(A <= B ? FString::Printf(TEXT("%s|%s"), *A, *B) : FString::Printf(TEXT("%s|%s"), *B, *A));
}
