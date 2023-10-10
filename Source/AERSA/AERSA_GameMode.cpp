// Fill out your copyright notice in the Description page of Project Settings.


#include "AERSA_GameMode.h"
#include "AERSA_Character.h"
#include "UObject/ConstructorHelpers.h"

AAERSA_GameMode::AAERSA_GameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_AERSACharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
}
