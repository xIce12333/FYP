// Fill out your copyright notice in the Description page of Project Settings.


#include "SkeletonController.h"

// Sets default values
ASkeletonController::ASkeletonController()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASkeletonController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkeletonController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASkeletonController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

