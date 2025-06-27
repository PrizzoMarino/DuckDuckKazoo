// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../MyGameInstance.h"
#include "Menu.generated.h"

/**
 * 
 */
UCLASS()
class DUCKDUCKKAZOO_API UMenu : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual bool Initialize() override;
	virtual void NativeDestruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* Singleplayer;

	UPROPERTY(meta = (BindWidget))
	class UButton* LAN;

	UPROPERTY(meta = (BindWidget))
	class UButton* Multiplayer;

	UPROPERTY(meta = (BindWidget))
	class UButton* Quit;

	UFUNCTION()
	void startSingleplayer();

	UFUNCTION()
	void startLAN();

	UFUNCTION()
	void startMultiplayer ();

	UFUNCTION()
	void startQuit();

	UMyGameInstance* MenuGameInstance;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> LANWidgetClass;

	UPROPERTY()
	class UUserWidget* LANWidget;

public:

	void SetMenuGameInstance(UMyGameInstance* GameInstance);
	void Setup();

};
