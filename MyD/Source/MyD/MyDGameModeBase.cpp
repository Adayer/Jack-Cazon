// Copyright Epic Games, Inc. All Rights Reserved.


#include "MyDGameModeBase.h"
#include "MyController.h"


AMyDGameModeBase::AMyDGameModeBase()
{
	PlayerControllerClass = AMyController::StaticClass();
}

