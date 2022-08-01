// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/MagicBall.h"

#include "Kismet/GameplayStatics.h"

void AMagicBall::BeginPlay()
{
	Super::BeginPlay();
}

void AMagicBall::Tick(float DeltaSeconds)
{
	FaceCamera();
	
}

void AMagicBall::FaceCamera()
{
	APlayerCameraManager* Camera = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	if (!Camera) return;
	
}
