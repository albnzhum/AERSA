// Fill out your copyright notice in the Description page of Project Settings.


#include "AERSA_Character.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Inventory/Item.h"

// Sets default values
AAERSA_Character::AAERSA_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(40.0f, 95.0f);

	TurnRate = 45.0f;
	LookUpRate = 45.0f;

	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	FirstPersonCamera-> SetupAttachment(GetCapsuleComponent());
	FirstPersonCamera->AddRelativeLocation(FVector(-39.65f, 1.75f, 64.0f));
	FirstPersonCamera->bUsePawnControlRotation = true;

	HandsMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Character Mesh"));

	HandsMesh->SetOnlyOwnerSee(true);
	HandsMesh->SetupAttachment(FirstPersonCamera);
	HandsMesh->bCastDynamicShadow = false;
	HandsMesh->CastShadow = false;
	HandsMesh->AddRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	HandsMesh->AddRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun"));
	GunMesh->SetOnlyOwnerSee(true);
	GunMesh->bCastDynamicShadow = false;
	GunMesh->CastShadow = false;

	MuzzleLocation= CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle Loccation"));
	MuzzleLocation->SetupAttachment(GunMesh);
	MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	GunOffset = FVector(100.0f, 0.0f, 10.0f);
	

}

// Called when the game starts or when spawned
void AAERSA_Character::BeginPlay()
{
	Super::BeginPlay();

	GunMesh->AttachToComponent(HandsMesh,
		FAttachmentTransformRules::SnapToTargetNotIncludingScale,
		TEXT("GripPoint"));
	
}

// Called every frame
void AAERSA_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	InteractCheck();

}

// Called to bind functionality to input
void AAERSA_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Fire",IE_Pressed, this, &AAERSA_Character::OnFire);

	PlayerInputComponent->BindAxis("MoveForward", this, &AAERSA_Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AAERSA_Character::MoveRight);
	
	PlayerInputComponent->BindAxis("Turn", this, &AAERSA_Character::TurnAtPate);
	PlayerInputComponent->BindAxis("LookUp", this, &AAERSA_Character::LookAtPate);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AAERSA_Character::Interact);

}

void AAERSA_Character::OnFire()
{
	
}

void AAERSA_Character::MoveForward(float value)
{
	if(value != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), value);
	}
}

void AAERSA_Character::MoveRight(float value)
{
	if(value != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), value);
	}
}

void AAERSA_Character::TurnAtPate(float rate)
{
	AddControllerYawInput(rate * TurnRate * GetWorld()->GetDeltaSeconds());
}

void AAERSA_Character::LookAtPate(float rate)
{
	AddControllerPitchInput(rate * LookUpRate * GetWorld()->GetDeltaSeconds());
}

void AAERSA_Character::Interact()
{
	if (Cast<AItem>(InteractHitResult.GetActor()))
	{
		UE_LOG(LogTemp, Warning, TEXT("123"))
	}
}

void AAERSA_Character::InteractCheck()
{
	Cast<APlayerController>(GetController())->GetPlayerViewPoint(ViewVector, ViewRotation);
	FVector VecDirection = ViewRotation.Vector() * 1000.f;
	FVector InteractEnd = ViewVector + VecDirection;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	GetWorld()->LineTraceSingleByChannel(InteractHitResult, ViewVector, InteractEnd, ECollisionChannel::ECC_GameTraceChannel1, QueryParams);
}


