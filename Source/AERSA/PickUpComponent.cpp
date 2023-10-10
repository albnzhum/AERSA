// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUpComponent.h"

UPickUpComponent::UPickUpComponent()
{
	SphereRadius = 32.f;
}

void UPickUpComponent::BeginPlay()
{
	Super::BeginPlay();
	OnComponentBeginOverlap.AddDynamic(this, &UPickUpComponent::OnSphereBeginOverlap);
}

void UPickUpComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AAERSA_Character* Character = Cast<AAERSA_Character>(OtherActor);
	if (Character != nullptr)
	{
		OnPickUp.Broadcast(Character);
		OnComponentBeginOverlap.RemoveAll(this);
	}
}
