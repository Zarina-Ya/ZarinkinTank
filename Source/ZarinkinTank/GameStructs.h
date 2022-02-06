#pragma once
#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "GameStructs.generated.h"

UENUM(BlueprintType)
enum class ECannonType : uint8 {
	Fireprojectile = 0 UMETA(DisplayName = "Use Projectile"),
	Firetrace = 1 UMETA(DisplayName = "Use Trace")

};
