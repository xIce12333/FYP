// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameInstanceController.generated.h"

/**
 * 
 */
UCLASS()
class FYP_API UGameInstanceController : public UGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
		void RetryGame();
	UFUNCTION(BlueprintCallable)
		void QuitGame();

protected:
	virtual void Init() override;
	virtual void Shutdown() override;
	virtual void StartGameInstance() override;

};
