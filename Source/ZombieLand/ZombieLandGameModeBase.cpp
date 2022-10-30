// Copyright Epic Games, Inc. All Rights Reserved.


#include "ZombieLandGameModeBase.h"
#include "ZL_Character.h"
#include "ZL_PlayerController.h"

AZombieLandGameModeBase::AZombieLandGameModeBase() {
	DefaultPawnClass = AZL_Character::StaticClass();
	PlayerControllerClass = AZL_PlayerController::StaticClass();
}
