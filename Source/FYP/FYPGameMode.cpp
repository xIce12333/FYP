// Copyright Epic Games, Inc. All Rights Reserved.

#include "FYPGameMode.h"
#include "FYPCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFYPGameMode::AFYPGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
