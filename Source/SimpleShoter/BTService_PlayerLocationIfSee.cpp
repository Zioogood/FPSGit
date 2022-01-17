// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocationIfSee.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "AIController.h"

UBTService_PlayerLocationIfSee::UBTService_PlayerLocationIfSee()
{
    NodeName = "Update Pleyer Location If See";

}

 void UBTService_PlayerLocationIfSee::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
 {
     Super::TickNode(OwnerComp,NodeMemory,DeltaSeconds);
    
    ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(),0);
    if(PlayerCharacter == nullptr)
    {
        return;
    }

    if(OwnerComp.GetAIOwner()==nullptr)
    {
        return;
    }
    if(OwnerComp.GetAIOwner()->LineOfSightTo(PlayerCharacter))
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(),PlayerCharacter);
    }
    else
    {
        OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
    }
 }