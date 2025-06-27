// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class DUCKDUCKKAZOO_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
    UMyGameInstance();

    virtual void Init() override;

    UFUNCTION(Exec)
    void Host();

    UFUNCTION(Exec)
    void Join(const FString& IPAddress);

	UFUNCTION(Exec, BlueprintCallable, Category = "Menu")
	void MainMenu();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> WidgetClass;


private:
	UPROPERTY()
	class UMainMenu* MainMenuWidget;
};
