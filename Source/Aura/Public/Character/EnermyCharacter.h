

#pragma once
#include "CoreMinimal.h"
#include "AuraBaseCharacter.h"
#include "Interface/LightingInterface.h"
#include "EnermyCharacter.generated.h"


UCLASS()
class AURA_API AEnermyCharacter : public AAuraBaseCharacter, public ILightingInterface
{
	GENERATED_BODY()

public:
	AEnermyCharacter();
	

	//~ Begin ILightingInterface
	virtual void HighLightActor() override;
	virtual void UnHighLightActor() override;
	//~ End ILightingInterface
protected:
	virtual void BeginPlay() override;
	
};
