#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ElementType.h"
#include "ReactionDataAsset.h"
#include "ElementLibrary.generated.h"

UCLASS()
class ECHOOFELEMENTS_API UElementLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintPure, Category = "Elements")
    static bool IsValidElement(EElementType Element);

    UFUNCTION(BlueprintPure, Category = "Elements")
    static FName GetElementId(EElementType Element);

    UFUNCTION(BlueprintPure, Category = "Elements")
    static FText GetElementDisplayName(EElementType Element);

    UFUNCTION(BlueprintPure, Category = "Elements")
    static TArray<EElementType> GetAllElements();

    UFUNCTION(BlueprintPure, Category = "Elements|Reactions")
    static bool AreElementsCompatible(EElementType First, EElementType Second);

    UFUNCTION(BlueprintPure, Category = "Elements|Reactions")
    static bool FindReaction(const UReactionDataAsset* ReactionData, EElementType First, EElementType Second, FReactionDefinition& OutReaction);

    UFUNCTION(BlueprintPure, Category = "Elements|Reactions")
    static FName MakeReactionId(EElementType First, EElementType Second);
};
