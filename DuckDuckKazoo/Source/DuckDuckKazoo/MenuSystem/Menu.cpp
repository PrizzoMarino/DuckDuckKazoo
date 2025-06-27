// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"

bool UMenu::Initialize()
{
    bool Success = Super::Initialize();
    if (!Success) return false;

    if (!ensure(Singleplayer != nullptr)) { return false; }
    Singleplayer->OnClicked.AddDynamic(this, &UMenu::startSingleplayer);

    if (!ensure(LAN != nullptr)) { return false; }
    LAN->OnClicked.AddDynamic(this, &UMenu::startLAN);

    if (!ensure(Multiplayer != nullptr)) { return false; }
    Multiplayer->OnClicked.AddDynamic(this, &UMenu::startMultiplayer);

    if (!ensure(Quit != nullptr)) { return false; }
    Quit->OnClicked.AddDynamic(this, &UMenu::startQuit);

    return true;
}


void UMenu::startSingleplayer() {
    UE_LOG(LogTemp, Warning, TEXT("Singleplayer button was clicked."));

    if (MenuGameInstance)
    {
        MenuGameInstance->HostSingleplayer();

    }
}

void UMenu::startLAN()
{
    UE_LOG(LogTemp, Warning, TEXT("Opening LAN Menu."));

    if (!LANWidgetClass) {
        UE_LOG(LogTemp, Error, TEXT("LANWidgetClass not assigned."));
        return;
    }

    LANWidget = CreateWidget<UUserWidget>(GetWorld(), LANWidgetClass);
    if (!LANWidget) {
        UE_LOG(LogTemp, Error, TEXT("Failed to create LANWidget."));
        return;
    }

    RemoveFromParent();
    LANWidget->AddToViewport();

    APlayerController* PC = GetWorld()->GetFirstPlayerController();
    if (PC) {
        FInputModeUIOnly InputMode;
        InputMode.SetWidgetToFocus(LANWidget->TakeWidget());
        InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
        PC->SetInputMode(InputMode);
        PC->bShowMouseCursor = true;
    }
}

void UMenu::startMultiplayer()
{
    UE_LOG(LogTemp, Warning, TEXT("Multiplayer button clicked."));
}

void UMenu::startQuit()
{
    UE_LOG(LogTemp, Warning, TEXT("Quitting Game."));

    UWorld* World = GetWorld();
    if (!World) return;

    APlayerController* PC = World->GetFirstPlayerController();
    if (PC)
    {
        PC->ConsoleCommand("quit");
    }
}

void UMenu::Setup() {
    if (!ensure(GetWorld())) return;

    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (!ensure(PlayerController)) return;

    FInputModeUIOnly InputMode;
    InputMode.SetWidgetToFocus(this->TakeWidget());
    InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

    PlayerController->SetInputMode(InputMode);
    PlayerController->bShowMouseCursor = true;

    UE_LOG(LogTemp, Log, TEXT("Menu input setup complete."));
}

void UMenu::NativeDestruct() {
    Super::NativeDestruct();

    UWorld* World = GetWorld();
    if (!World)
    {
        UE_LOG(LogTemp, Warning, TEXT("World is null inside native."))
            return;
    }

    APlayerController* PlayerController = World->GetFirstPlayerController();
    if (!PlayerController)
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerController is null inside native."));
        return;
    }

    FInputModeGameOnly InputMode;
    PlayerController->SetInputMode(InputMode);
    PlayerController->bShowMouseCursor = false;
    UE_LOG(LogTemp, Log, TEXT("Main Menu and cursor gone."))
}

void UMenu::SetMenuGameInstance(UMyGameInstance* GameInstance)
{
    MenuGameInstance = GameInstance;
}