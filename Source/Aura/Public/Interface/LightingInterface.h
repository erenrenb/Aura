

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LightingInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class ULightingInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AURA_API ILightingInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void HighLightActor();
	virtual void UnHighLightActor();
};
