// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/GameInstanceController.h"

#include "Kismet/GameplayStatics.h"

void UGameInstanceController::RetryGame()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

void UGameInstanceController::QuitGame()
{
	// empty for now
}
