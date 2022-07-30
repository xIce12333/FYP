// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/GameManager.h"

#include "Kismet/GameplayStatics.h"


void AGameManager::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<AMiraiKomachi>(UGameplayStatics::GetActorOfClass(GetWorld(), AMiraiKomachi::StaticClass()));
	if (!Player) return;
	Player->PlayerDied.AddDynamic(this, &AGameManager::OnPlayerDied);
	Player->GamePause.AddDynamic(this, &AGameManager::OnPauseButtonPressed);
}

void AGameManager::OnPlayerDied()
{
	ShowDiedMenu();
	if (!Player) return;
	Cast<APlayerController>(Player->GetController())->bShowMouseCursor = true;
}

void AGameManager::OnPauseButtonPressed()
{
	ShowPauseMenu();
	Cast<APlayerController>(Player->GetController())->bShowMouseCursor = true;
}
