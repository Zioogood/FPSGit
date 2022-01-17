// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "GameFramework/Character.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"

void AKillEmAllGameMode::CharacterKilled(ACharacter* CharacterKilled)
{
    Super::CharacterKilled(CharacterKilled);
    APlayerController* PlayerController = Cast<APlayerController>(CharacterKilled->GetController());
    if(PlayerController != nullptr)
        {
            EndGame(false);
        }
    for(AShooterAIController* AI:TActorRange<AShooterAIController>(GetWorld()))
        {
            if(!AI->IsDead())
                {
                    return;
                }
        }
    EndGame(true);
}

void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner)
{
   for( AController* Controller:TActorRange<AController>(GetWorld()))
        {
            bool bIsWinner=Controller->IsPlayerController() == bIsPlayerWinner;
            Controller->GameHasEnded(Controller->GetCharacter(),bIsWinner);
      
        }
}