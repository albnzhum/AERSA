// Copyright Epic Games, Inc. All Rights Reserved.

#include "AERSAGameMode.h"
#include "AERSACharacter.h"
#include "UObject/ConstructorHelpers.h"

AAERSAGameMode::AAERSAGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_AERSACharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
