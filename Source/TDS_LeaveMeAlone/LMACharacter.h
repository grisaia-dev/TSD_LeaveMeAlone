// Make by Jatex. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LMACharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class ULMAHealthComponent;

UCLASS()
class TDS_LEAVEMEALONE_API ALMACharacter : public ACharacter {
public:
	// Sets default values for this character's properties
	ALMACharacter();

#pragma region Stamina
	void StartSprint();
	void StopSprint();
#pragma endregion

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components") TObjectPtr<USpringArmComponent> SpringArmComponent = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components") TObjectPtr<UCameraComponent> CameraComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player|Health") TObjectPtr<ULMAHealthComponent> HealthComponent = nullptr;

	// The normal walk speed of the character
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Movement", meta = (ClampMin = "0", ClampMax = "300")) float NormalMaxWalkSpeed = 300.f;
	// The sprinting speed of the character
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Movement", meta = (ClampMin = "500", ClampMax = "600")) float SprintMaxWalkSpeed = 500.f;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void RotationOnCursor();
	void UpdateStamina();

	// Stamina
	static constexpr float MaxStamina = 100.f;
	static constexpr float SprintCost = 0.3f;
	static constexpr float StaminaRecovery = 0.2f;
	float CurrentStamina = MaxStamina;
	bool bHasStamina = false;
	bool bIsSprint = false;

	static constexpr float ArmLenght = 1400.f;
	static constexpr float ArmRotateY = -75.f;
	static constexpr float CameraFOV = 55.f;

	// To get reference to the PlayerController
	UPROPERTY() TObjectPtr<APlayerController> PC = nullptr;

	GENERATED_BODY()

};
