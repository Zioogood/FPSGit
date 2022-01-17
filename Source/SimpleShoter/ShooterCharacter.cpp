// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"

#include "Gun.h"
#include "Components/CapsuleComponent.h"
#include "SimpleShoterGameModeBase.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	for(TSubclassOf<AGun> Gunzz: GunClass)
	{
	Gun=GetWorld()->SpawnActor<AGun>(Gunzz);

	GetMesh()->HideBoneByName(TEXT("weapon_r"),EPhysBodyOp::PBO_None);

	 Gun->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,TEXT("WeaponSocket"));
	 Gun->SetOwner(this);
	}
	Healt = MaxHealth;
	
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"),this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRightLeft"),this,&AShooterCharacter::MoveRightLeft);
	PlayerInputComponent->BindAxis(TEXT("LookUp"),this, &AShooterCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("LookAround"),this,&AShooterCharacter::LookAround);
	PlayerInputComponent->BindAction(TEXT("Jump"),EInputEvent::IE_Pressed,this,&ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Shoot"),EInputEvent::IE_Pressed,this,&AShooterCharacter::Shoot);

}

float AShooterCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float DamageApplied = Super::TakeDamage(DamageAmount,DamageEvent,EventInstigator,DamageCauser);
	DamageApplied=FMath::Min(Healt,DamageApplied);
	Healt -= DamageApplied;
	UE_LOG(LogTemp,Warning,TEXT("Healt left %f"),Healt);

	if(IsDead())
	{

		ASimpleShoterGameModeBase* GameMode=GetWorld()->GetAuthGameMode<ASimpleShoterGameModeBase>();
		if(GameMode!=nullptr)
		{
			GameMode->CharacterKilled(this);
		}
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	return DamageApplied;
}

bool AShooterCharacter::IsDead()const 
{
	return Healt <= 0;
}
void AShooterCharacter::MoveForward(float AxisValue)
{

	AddMovementInput(GetActorForwardVector()* AxisValue);
}

void AShooterCharacter::MoveRightLeft(float AxisValue)
{
	AddMovementInput(GetActorRightVector()* AxisValue);
}

void AShooterCharacter::LookUp(float AxisValue)
{
	AddControllerPitchInput(AxisValue * RateLook * GetWorld()->GetDeltaSeconds());
}
void AShooterCharacter::LookAround(float AxisValue)
{
	AddControllerYawInput(AxisValue * RateLook * GetWorld()->GetDeltaSeconds());
}
void AShooterCharacter::Shoot()
{
	Gun->PullTrriger();
}

float AShooterCharacter::GetHealthPercent()const
{
	return Healt / MaxHealth; 
}