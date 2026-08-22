#include "Elements/ReactionDataAsset.h"

namespace
{
    FReactionDefinition MakeReaction(
        const TCHAR* Id,
        EElementType A,
        EElementType B,
        const TCHAR* Name,
        const TCHAR* Description,
        EReactionEffect Effect,
        float DamageMultiplier,
        float Duration,
        float BuildupRequired)
    {
        FReactionDefinition Result;
        Result.ReactionId = FName(Id);
        Result.ElementA = A;
        Result.ElementB = B;
        Result.DisplayName = FText::FromString(Name);
        Result.Description = FText::FromString(Description);
        Result.Effect = Effect;
        Result.DamageMultiplier = DamageMultiplier;
        Result.Duration = Duration;
        Result.BuildupRequired = BuildupRequired;
        return Result;
    }
}

static TArray<FReactionDefinition> BuildDefaultReactionTable();

UReactionDataAsset::UReactionDataAsset()
    : Reactions(BuildDefaultReactionTable())
{
}

const FReactionDefinition* UReactionDataAsset::FindReaction(EElementType First, EElementType Second) const
{
    return Reactions.FindByPredicate([First, Second](const FReactionDefinition& Reaction)
    {
        return (Reaction.ElementA == First && Reaction.ElementB == Second)
            || (Reaction.ElementA == Second && Reaction.ElementB == First);
    });
}

// Recommended starter table. Designers can override this list in a UReactionDataAsset.
static TArray<FReactionDefinition> BuildDefaultReactionTable()
{
    return {
        MakeReaction(TEXT("Inferno"), EElementType::Fire, EElementType::Wind, TEXT("Inferno"), TEXT("A violent expanding flame that deals burst damage."), EReactionEffect::BurstDamage, 2.00f, 0.0f, 100.0f),
        MakeReaction(TEXT("Steam"), EElementType::Fire, EElementType::Water, TEXT("Steam"), TEXT("Scalding vapor obscures vision and deals damage over time."), EReactionEffect::Blind, 1.25f, 4.0f, 100.0f),
        MakeReaction(TEXT("Magma"), EElementType::Fire, EElementType::Earth, TEXT("Magma"), TEXT("Molten ground burns targets and breaks armor."), EReactionEffect::ArmorBreak, 1.75f, 5.0f, 100.0f),
        MakeReaction(TEXT("Shatter"), EElementType::Water, EElementType::Ice, TEXT("Shatter"), TEXT("Frozen targets fracture under a heavy burst."), EReactionEffect::BurstDamage, 2.25f, 0.0f, 100.0f),
        MakeReaction(TEXT("Overgrowth"), EElementType::Water, EElementType::Nature, TEXT("Overgrowth"), TEXT("Vines root the target and spread healing flora."), EReactionEffect::Root, 1.15f, 4.0f, 100.0f),
        MakeReaction(TEXT("Quicksand"), EElementType::Earth, EElementType::Sand, TEXT("Quicksand"), TEXT("The ground gives way, slowing and trapping enemies."), EReactionEffect::Root, 1.10f, 5.0f, 100.0f),
        MakeReaction(TEXT("Fortify"), EElementType::Earth, EElementType::Stone, TEXT("Fortify"), TEXT("Stone reinforces the earth, granting a protective shield."), EReactionEffect::Shield, 1.00f, 6.0f, 100.0f),
        MakeReaction(TEXT("Cyclone"), EElementType::Wind, EElementType::Lightning, TEXT("Cyclone"), TEXT("A charged vortex pulls enemies toward its center."), EReactionEffect::Pull, 1.60f, 3.0f, 100.0f),
        MakeReaction(TEXT("Blizzard"), EElementType::Wind, EElementType::Ice, TEXT("Blizzard"), TEXT("Freezing wind slows enemies in a wide area."), EReactionEffect::Slow, 1.45f, 6.0f, 100.0f),
        MakeReaction(TEXT("Stormglass"), EElementType::Lightning, EElementType::Sand, TEXT("Stormglass"), TEXT("Lightning vitrifies sand into a sharp, stunning field."), EReactionEffect::Stun, 1.80f, 2.0f, 100.0f),
        MakeReaction(TEXT("Electrolysis"), EElementType::Lightning, EElementType::Water, TEXT("Electrolysis"), TEXT("Electricity chains through wet targets."), EReactionEffect::DamageOverTime, 1.65f, 5.0f, 100.0f),
        MakeReaction(TEXT("Conductive Bloom"), EElementType::Lightning, EElementType::Nature, TEXT("Conductive Bloom"), TEXT("Living roots carry a stunning electrical pulse."), EReactionEffect::Stun, 1.50f, 2.5f, 100.0f),
        MakeReaction(TEXT("Frostbite"), EElementType::Ice, EElementType::Metal, TEXT("Frostbite"), TEXT("Cold makes metal brittle and reduces defenses."), EReactionEffect::ArmorBreak, 1.55f, 5.0f, 100.0f),
        MakeReaction(TEXT("Rust"), EElementType::Water, EElementType::Metal, TEXT("Rust"), TEXT("Water corrodes metal, weakening armor over time."), EReactionEffect::ArmorBreak, 1.35f, 8.0f, 100.0f),
        MakeReaction(TEXT("Magnetize"), EElementType::Metal, EElementType::Lightning, TEXT("Magnetize"), TEXT("A magnetic surge pulls metal-bearing targets together."), EReactionEffect::Pull, 1.40f, 3.0f, 100.0f),
        MakeReaction(TEXT("Radiance"), EElementType::Light, EElementType::Nature, TEXT("Radiance"), TEXT("Life amplified by light creates a restorative shield."), EReactionEffect::Shield, 1.10f, 7.0f, 100.0f),
        MakeReaction(TEXT("Eclipse"), EElementType::Light, EElementType::Gravity, TEXT("Eclipse"), TEXT("Gravity bends light into a blinding singularity."), EReactionEffect::Blind, 1.90f, 4.0f, 100.0f),
        MakeReaction(TEXT("Singularity"), EElementType::Gravity, EElementType::Stone, TEXT("Singularity"), TEXT("Dense stone collapses inward, lifting and crushing targets."), EReactionEffect::Lift, 2.10f, 2.0f, 100.0f)
    };
}
