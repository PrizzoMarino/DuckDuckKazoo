// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../MyGameInstance.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class DUCKDUCKKAZOO_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual bool Initialize();
	virtual void NativeDestruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* HostButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* JoinButton;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* Screens;

	UPROPERTY(meta = (BindWidget))
	class UWidget* Menu;

	UPROPERTY(meta = (BindWidget))
	class UWidget* JoinScreen;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* InputIP;

	UPROPERTY(meta = (BindWidget))
	class UButton* JoinConfirm;

	UPROPERTY(meta = (BindWidget))
	class UButton* CancelButton;

	UFUNCTION()
	void HostGame();

	UFUNCTION()
	void JoinGame();

	UFUNCTION()
	void OpenJoinScreen();

	UFUNCTION()
	void CancelJoin();

private:
	UMyGameInstance* MenuGameInstance;

public:
	void SetMenuGameInstance(UMyGameInstance* GameInstance);

	void Setup();
};
