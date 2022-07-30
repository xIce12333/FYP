// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Komachi/MiraiKomachi.h"
#include "GameFramework/GameModeBase.h"
#include "GameManager.generated.h"

/**
 * 
 */
UCLASS()
class FYP_API AGameManager : public AGameModeBase
{
	GENERATED_BODY()
private:
	UFUNCTION()
		void OnPlayerDied();

	UFUNCTION()
		void OnPauseButtonPressed();

	virtual void BeginPlay() override;
	AMiraiKomachi* Player;
protected:
	UFUNCTION(BlueprintImplementableEvent)
		void ShowDiedMenu();
	UFUNCTION(BlueprintImplementableEvent)
		void ShowPauseMenu();

};
