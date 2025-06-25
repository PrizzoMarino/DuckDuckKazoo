// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"

UMyGameInstance::UMyGameInstance()
{
    UE_LOG(LogTemp, Warning, TEXT("UMyGameInstance Constructor Called"));
}

void UMyGameInstance::Init()
{
    Super::Init();

    UE_LOG(LogTemp, Warning, TEXT("UMyGameInstance Init Called"));
}

void UMyGameInstance::Host() {

    if (GEngine)
	    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Game hosting starting up."));

    UWorld* World = GetWorld();

    if (!ensure(World != nullptr)) { return; };

    World->ServerTravel("/Game/Maps/lobby?listen");

}

void UMyGameInstance::Join(const FString& IPAddress) {

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Joining requested server."));

	APlayerController* Controller = GetFirstLocalPlayerController();

	if (!ensure(Controller != nullptr)) { return; };

	Controller->ClientTravel(*IPAddress, ETravelType::TRAVEL_Absolute);
}

