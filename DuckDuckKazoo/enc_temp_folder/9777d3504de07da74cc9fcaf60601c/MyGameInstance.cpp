// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "MenuSystem/MainMenu.h"
#include "UObject/ConstructorHelpers.h"

UMyGameInstance::UMyGameInstance() {
	UE_LOG(LogTemp, Warning, TEXT("UMyGameInstance has been called."));
	ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/HUDs/WBP_MainMenu"));

	if (MenuBPClass.Succeeded())
	{
		WidgetClass = MenuBPClass.Class;
		UE_LOG(LogTemp, Log, TEXT("Successfully loaded Widget class."));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load Widget class."));
	}
}

void UMyGameInstance::Init() {
	Super::Init();
	UE_LOG(LogTemp, Warning, TEXT("Initializating of UMyGameInstance."));

	if (WidgetClass && GetWorld())
	{
		MainMenuWidget = CreateWidget<UMainMenu>(GetWorld(), WidgetClass);
		if (MainMenuWidget)
		{
			MainMenuWidget->SetMenuGameInstance(this);
			MainMenuWidget->AddToViewport();

			UE_LOG(LogTemp, Log, TEXT("Main menu widget created and added to viewport."));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to create main menu widget."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("WidgetClass is null or GetWorld() failed."));
	}


}

void UMyGameInstance::Host() {

    if (GEngine)
	    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Game hosting starting up."));

    UWorld* World = GetWorld();

    if (!ensure(World != nullptr)) { return; };

    World->ServerTravel("/Game/Map/Game?listen");

}

void UMyGameInstance::Join(const FString& IPAddress)
{
    if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan,
            FString::Printf(TEXT("Attempting to join IP: %s"), *IPAddress));

    APlayerController* Controller = GetFirstLocalPlayerController();

    if (!ensure(Controller != nullptr)) return;

    Controller->ClientTravel(*IPAddress, ETravelType::TRAVEL_Absolute);
}

void UMyGameInstance::MainMenu()
{
	UWorld* World = GetWorld();
	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get PlayerController."));
	}

	if (WidgetClass && World)
	{
		if (!MainMenuWidget)
		{
			MainMenuWidget = CreateWidget<UMainMenu>(World, WidgetClass);
		}

		if (MainMenuWidget)
		{
			MainMenuWidget->AddToViewport();
			MainMenuWidget->Setup();

			UE_LOG(LogTemp, Log, TEXT("Main menu loaded and added to viewport."));
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("Failed to load main menu widget."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("WidgetClass or GetWorld() is null."));
	}


}