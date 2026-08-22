#include "Elements/ElementLibrary.h"

namespace
{
    const TCHAR* ToElementString(EElementType Element)
    {
        switch (Element)
        {
        case EElementType::Fire:      return TEXT("Fire");
        case EElementType::Water:     return TEXT("Water");
        case EElementType::Earth:     return TEXT("Earth");
        case EElementType::Stone:     return TEXT("Stone");
        case EElementType::Wind:      return TEXT("Wind");
        case EElementType::Lightning: return TEXT("Lightning");
        case EElementType::Ice:       return TEXT("Ice");
        case EElementType::Nature:    return TEXT("Nature");
        case EElementType::Sand:      return TEXT("Sand");
        case EElementType::Metal:     return TEXT("Metal");
        case EElementType::Light:     return TEXT("Light");
        case EElementType::Gravity:   return TEXT("Gravity");
        default:                      return TEXT("None");
        }
    }
}

bool UElementLibrary::IsValidElement(EElementType Element)
{
    return static_cast<uint8>(Element) < static_cast<uint8>(EElementType::Gravity) + 1;
}

FName UElementLibrary::GetElementId(EElementType Element)
{
    return IsValidElement(Element) ? FName(ToElementString(Element)) : NAME_None;
}

FText UElementLibrary::GetElementDisplayName(EElementType Element)
{
    return IsValidElement(Element) ? FText::FromString(ToElementString(Element)) : FText::GetEmpty();
}

TArray<EElementType> UElementLibrary::GetAllElements()
{
    return {
        EElementType::Fire, EElementType::Water, EElementType::Earth, EElementType::Stone,
        EElementType::Wind, EElementType::Lightning, EElementType::Ice, EElementType::Nature,
        EElementType::Sand, EElementType::Metal, EElementType::Light, EElementType::Gravity
    };
}

bool UElementLibrary::AreElementsCompatible(EElementType First, EElementType Second)
{
    return IsValidElement(First) && IsValidElement(Second) && First != Second;
}

bool UElementLibrary::FindReaction(const UReactionDataAsset* ReactionData, EElementType First, EElementType Second, FReactionDefinition& OutReaction)
{
    OutReaction = FReactionDefinition();
    if (!ReactionData || !AreElementsCompatible(First, Second))
    {
        return false;
    }

    const FReactionDefinition* Found = ReactionData->FindReaction(First, Second);
    if (!Found)
    {
        return false;
    }

    OutReaction = *Found;
    return true;
}

FName UElementLibrary::MakeReactionId(EElementType First, EElementType Second)
{
    if (!AreElementsCompatible(First, Second))
    {
        return NAME_None;
    }

    const FString FirstName = ToElementString(First);
    const FString SecondName = ToElementString(Second);
    return FirstName < SecondName
        ? FName(FString::Printf(TEXT("%s_%s"), *FirstName, *SecondName))
        : FName(FString::Printf(TEXT("%s_%s"), *SecondName, *FirstName));
}
