// Make by Jatex. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "LMAPlayerController.generated.h"

class UEnhancedInputComponent;
class ALMACharacter;
class UInputMappingContext;
class ULMAWeaponComponent;

UCLASS(Abstract)
class TDS_LEAVEMEALONE_API ALMAPlayerController : public APlayerController {
public:

	// The Input Action to map to movement
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Movement") TObjectPtr<UInputAction> ActionMove = nullptr;

	// The Input Action to map to movement sprint
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Movement") TObjectPtr<UInputAction> ActionSprint = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Action") TObjectPtr<UInputAction> ActionFire = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Action") TObjectPtr<UInputAction> ActionReload = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Movement") TObjectPtr<UInputMappingContext> InputMappingContent = nullptr;

	UFUNCTION() ALMACharacter* GetPlayerCharacter() const { return PlayerCharacter; }

protected:
	void HandleMove(const FInputActionValue& InputActionValue);
	void HandleStartSprint();
	void HandleStopSprint();
	void HandleStartFire();
	void HandleStopFire();
	void HandleReload();

	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;

	virtual void BeginSpectatingState() override;

	virtual void BeginPlay() override;

private:
	// Used to store a reference to the InputComponent cast to an EnhancedInputComponent
	UPROPERTY() TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent = nullptr;

	// Used to store a reference to the Pawn we are controlling
	UPROPERTY() TObjectPtr<ALMACharacter> PlayerCharacter = nullptr;

	UPROPERTY() TObjectPtr<ULMAWeaponComponent> WeaponComponent = nullptr;

	GENERATED_BODY()
};
