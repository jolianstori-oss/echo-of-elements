#include "CharacterDataAsset.h"

FPrimaryAssetId UCharacterDataAsset::GetPrimaryAssetId() const
{
    return FPrimaryAssetId(TEXT("Character"), GetFName());
}
