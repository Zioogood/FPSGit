// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SimpleShoterGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOTER_API ASimpleShoterGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	virtual void CharacterKilled(ACharacter* CharacterKilled);
};
