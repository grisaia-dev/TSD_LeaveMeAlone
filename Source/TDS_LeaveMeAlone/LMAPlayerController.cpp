// Make by Jatex. All Right Reserved.


#include "LMAPlayerController.h"
#include "LMACharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/LMAWeaponComponent.h"


void ALMAPlayerController::BeginPlay() {
    Super::BeginPlay();
    SetInputMode(FInputModeGameOnly());
    bShowMouseCursor =true;
}

void ALMAPlayerController::HandleMove(const FInputActionValue& InputActionValue) {
    // Value is a Vector2D
    const FVector2D Movementvector = InputActionValue.Get<FVector2D>();

    // Add movement to the Player's Character Pawn
    if (PlayerCharacter) {
        PlayerCharacter->AddMovementInput(PlayerCharacter->GetActorForwardVector(), Movementvector.Y);
        PlayerCharacter->AddMovementInput(PlayerCharacter->GetActorRightVector(), Movementvector.X);
    }
}

void ALMAPlayerController::HandleStartSprint() {
    // Value is a bool (Value not used here) Just pressed is true not pressed is false
    if (PlayerCharacter) { PlayerCharacter->StartSprint(); }
}
void ALMAPlayerController::HandleStopSprint() {
    if (PlayerCharacter) { PlayerCharacter->StopSprint(); }
}

void ALMAPlayerController::HandleStartFire() {
    if (PlayerCharacter && WeaponComponent) {
        if (!PlayerCharacter->GetIsSprint())
            WeaponComponent->StartFire();
    }
}

void ALMAPlayerController::HandleStopFire() {
    if (PlayerCharacter && WeaponComponent) {
        WeaponComponent->StopFire();
    }
}

void ALMAPlayerController::OnPossess(APawn* aPawn) {
    Super::OnPossess(aPawn);

    // Store a reference to the Player's Pawn
    PlayerCharacter = Cast<ALMACharacter>(aPawn);
    checkf(PlayerCharacter, TEXT("ALMAPlayerController derived classes should only possess ALMACharacter derived pawns"));

    WeaponComponent = PlayerCharacter->GetWeaponComponent();
    checkf(WeaponComponent, TEXT("Unable to get reference to the weapon component"));

    // Get a reference to the EnhancedInputComponent
    EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
    checkf(EnhancedInputComponent, TEXT("Unable to get reference to the EnhancedInputComponent"));


    // Get the local player subsystem
    UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
    checkf(InputSubsystem, TEXT("Unable to get reference to the EnhancedInputLocalPlayerSubsystem"));

    // Wipe existing mapping and add our mapping
    checkf(InputMappingContent, TEXT("InputMappingContent was not specefied"));
    InputSubsystem->ClearAllMappings();
    InputSubsystem->AddMappingContext(InputMappingContent, 0);

    // Bind the input actions
    // Only attempt to bind if a valid value was provided
    if (ActionMove)
        EnhancedInputComponent->BindAction(ActionMove, ETriggerEvent::Triggered, this, &ALMAPlayerController::HandleMove);
    if (ActionSprint) {
        EnhancedInputComponent->BindAction(ActionSprint, ETriggerEvent::Triggered, this, &ALMAPlayerController::HandleStartSprint);
        EnhancedInputComponent->BindAction(ActionSprint, ETriggerEvent::Completed, this, &ALMAPlayerController::HandleStopSprint);
    }
    if (ActionFire) {
        EnhancedInputComponent->BindAction(ActionFire, ETriggerEvent::Triggered, this, &ALMAPlayerController::HandleStartFire);
        EnhancedInputComponent->BindAction(ActionFire, ETriggerEvent::Completed, this, &ALMAPlayerController::HandleStopFire);
    }

}

void ALMAPlayerController::OnUnPossess() {
    // Unbinding things here
    EnhancedInputComponent->ClearActionBindings();
    Super::OnUnPossess();
}

void ALMAPlayerController::BeginSpectatingState() {
    SetControlRotation(FRotator(-75.f, 0.f, 0.f));
    bShowMouseCursor = false;
    SetIgnoreLookInput(true);
    SetIgnoreMoveInput(true);
    Super::BeginSpectatingState();
}