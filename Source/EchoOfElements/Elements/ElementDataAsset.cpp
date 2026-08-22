#include "Elements/ElementDataAsset.h"

FPrimaryAssetId UElementDataAsset::GetPrimaryAssetId() const
{
    const FName AssetName = ElementId.IsNone() ? GetFName() : ElementId;
    return FPrimaryAssetId(FPrimaryAssetType(TEXT("Element")), AssetName);
}
