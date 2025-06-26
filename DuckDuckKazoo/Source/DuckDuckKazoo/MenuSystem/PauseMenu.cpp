// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenu.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

bool UPauseMenu::Initialize() {
    bool Success = Super::Initialize();
    if (!Success) return false;

    if (ResumeButton) ResumeButton->OnClicked.AddDynamic(this, &UPauseMenu::ResumeGame);
    if (QuitButton) QuitButton->OnClicked.AddDynamic(this, &UPauseMenu::QuitGame);

    return true;
}

void UPauseMenu::ResumeGame() {
    RemoveFromParent();

    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (PlayerController) {
        PlayerController->SetInputMode(FInputModeGameOnly());
        PlayerController->bShowMouseCursor = false;
    }

    UGameplayStatics::SetGamePaused(GetWorld(), false);
}

void UPauseMenu::QuitGame() {
    UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}