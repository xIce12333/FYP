// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Skeleton//SkeletonController.h"

// Sets default values
ASkeletonController::ASkeletonController()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}


void ASkeletonController::Attack()
{

	Super::Attack();
}

