// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components/Button.h"
#include "Components/Widget.h"
#include "Components/EditableTextBox.h"
#include "Components/WidgetSwitcher.h"

bool UMainMenu::Initialize()
{
    bool Success = Super::Initialize();
    if (!Success) return false;

    if (!ensure(HostButton != nullptr)) { return false; }
    HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostGame);

    if (!ensure(JoinButton != nullptr)) { return false; }
    JoinButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinScreen);

    if (!ensure(JoinConfirm != nullptr)) { return false; }
    JoinConfirm->OnClicked.AddDynamic(this, &UMainMenu::JoinGame);

    if (!ensure(CancelButton != nullptr)) { return false; }
    CancelButton->OnClicked.AddDynamic(this, &UMainMenu::CancelJoin);

    return true;
}

void UMainMenu::HostGame() {
    UE_LOG(LogTemp, Warning, TEXT("Host button was clicked."));

    if (MenuGameInstance)
    {
        MenuGameInstance->Host();

    }
}

void UMainMenu::OpenJoinScreen() {
    UE_LOG(LogTemp, Warning, TEXT("Join button was clicked."));

    if (Screens && JoinScreen) {
        Screens->SetActiveWidget(JoinScreen);
        UE_LOG(LogTemp, Log, TEXT("Screen switched."));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Switcher or JoinScreen is null."));
    }
}

void UMainMenu::JoinGame() {
    if (!InputIP) {
        UE_LOG(LogTemp, Warning, TEXT("Missing InputIP."));
        return;
    }

    FString IPAddress = InputIP->GetText().ToString();

    if (IPAddress.IsEmpty()) {
        UE_LOG(LogTemp, Warning, TEXT("IP Address input is empty."));
        return;
    }

    MenuGameInstance->Join(IPAddress);
    UE_LOG(LogTemp, Log, TEXT("Joining IP: %s"), *IPAddress);
}

void UMainMenu::CancelJoin() {
    if (Screens && Menu) {
        Screens->SetActiveWidget(Menu);
        UE_LOG(LogTemp, Log, TEXT("Cancelled join screen; switched back to menu."));
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("Screens or Menu is null in CancelJoin."));
    }
}


void UMainMenu::Setup() {
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

void UMainMenu::NativeDestruct() {
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