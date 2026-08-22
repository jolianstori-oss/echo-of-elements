#pragma once

#include "CoreMinimal.h"
#include "ElementType.generated.h"

/** The complete elemental taxonomy used by Echo of Elements. */
UENUM(BlueprintType)
enum class EElementType : uint8
{
    Fire       UMETA(DisplayName = "Fire"),
    Water      UMETA(DisplayName = "Water"),
    Earth      UMETA(DisplayName = "Earth"),
    Stone      UMETA(DisplayName = "Stone"),
    Wind       UMETA(DisplayName = "Wind"),
    Lightning  UMETA(DisplayName = "Lightning"),
    Ice        UMETA(DisplayName = "Ice"),
    Nature     UMETA(DisplayName = "Nature"),
    Sand       UMETA(DisplayName = "Sand"),
    Metal      UMETA(DisplayName = "Metal"),
    Light      UMETA(DisplayName = "Light"),
    Gravity    UMETA(DisplayName = "Gravity")
};

namespace EchoElements
{
    inline constexpr int32 ElementCount = 12;
}
