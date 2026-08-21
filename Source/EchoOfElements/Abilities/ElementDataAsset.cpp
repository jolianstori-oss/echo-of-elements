#include "Abilities/ElementDataAsset.h"

FPrimaryAssetId UElementDataAsset::GetPrimaryAssetId() const
{
    return FPrimaryAssetId(FPrimaryAssetType(TEXT("Element")), GetFName());
}
