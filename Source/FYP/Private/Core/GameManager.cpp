// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/GameManager.h"

#include "Kismet/GameplayStatics.h"


void AGameManager::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<AMiraiKomachi>(UGameplayStatics::GetActorOfClass(GetWorld(), AMiraiKomachi::StaticClass()));
	if (!Player) return;
	Player->PlayerDied.AddDynamic(this, &AGameManager::OnPlayerDied);
}

void AGameManager::OnPlayerDied()
{
	ShowDiedMenu();
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.0002f);	// can't set to zero
	if (!Player) return;
	Cast<APlayerController>(Player->GetController())->bShowMouseCursor = true;
}