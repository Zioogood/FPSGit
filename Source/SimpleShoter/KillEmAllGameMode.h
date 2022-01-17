// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SimpleShoterGameModeBase.h"
#include "KillEmAllGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOTER_API AKillEmAllGameMode : public ASimpleShoterGameModeBase
{
	GENERATED_BODY()
public:
	virtual void CharacterKilled(ACharacter* CharacterKilled)override;

private:

	void EndGame(bool bIsPlayerWinner);
};
