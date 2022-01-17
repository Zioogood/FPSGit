// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"

#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterCharacter.h"

void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();

    if(AIBehavior != nullptr)
    {
        RunBehaviorTree(AIBehavior);
        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"),GetPawn()->GetActorLocation());
    }
}

void AShooterAIController::Tick(float DeltaSecods)
{
    Super::Tick(DeltaSecods);
}

bool AShooterAIController::IsDead() const
{
    AShooterCharacter* ControlledCharacter=Cast<AShooterCharacter>(GetCharacter());
    if(ControlledCharacter!=nullptr)
    {
       return ControlledCharacter->IsDead();
    }
    return true;
}