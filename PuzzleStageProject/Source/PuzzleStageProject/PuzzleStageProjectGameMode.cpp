// Copyright Epic Games, Inc. All Rights Reserved.

#include "PuzzleStageProjectGameMode.h"
#include "PuzzleStageProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

APuzzleStageProjectGameMode::APuzzleStageProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
