// Make by Jatex. All Right Reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LMACharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class ULMAHealthComponent;
class ULMAWeaponComponent;

UCLASS()
class TDS_LEAVEMEALONE_API ALMACharacter : public ACharacter {
public:
	// Sets default values for this character's properties
	ALMACharacter();

#pragma region Stamina
	// for enhanced input to start sprint
	void StartSprint();
	// for enhanced input to end sprint
	void StopSprint();
	bool GetIsSprint() const { return bIsSprint; }
#pragma endregion

	bool IsDead() const;

	UFUNCTION() ULMAHealthComponent* GetHealthComponent() const { return HealthComponent; }

	UFUNCTION() ULMAWeaponComponent* GetWeaponComponent() const { return WeaponComponent; }

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components") TObjectPtr<USpringArmComponent> SpringArmComponent = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components") TObjectPtr<UCameraComponent> CameraComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player|Health") TObjectPtr<ULMAHealthComponent> HealthComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Player|Animations") TObjectPtr<UAnimMontage> DeathMontage = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Movement", meta = (ClampMin = "0", ClampMax = "300")) float NormalMaxWalkSpeed = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Movement", meta = (ClampMin = "500", ClampMax = "600")) float SprintMaxWalkSpeed = 500.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player|Weapon") ULMAWeaponComponent* WeaponComponent = nullptr;

	virtual void BeginPlay() override; // Called when the game starts or when spawned
private:
	void RotationOnCursor(); // Character mesh see on Cursor

	void UpdateStamina(); // Update stamina variables

	// Stamina
	static constexpr float MaxStamina = 100.f;
	static constexpr float SprintCost = 0.3f;
	static constexpr float StaminaRecovery = 0.2f;
	float CurrentStamina = MaxStamina;
	bool bHasStamina = false;
	bool bIsSprint = false;

	// For Camera
	static constexpr float ArmLenght = 1400.f;
	static constexpr float ArmRotateY = -75.f;
	static constexpr float CameraFOV = 55.f;

	void OnDeath();
	void OnHealthChanged(float NewHealth);

	UPROPERTY() TObjectPtr<APlayerController> PC = nullptr; // To get reference to the PlayerController
	UPROPERTY() TObjectPtr<UCharacterMovementComponent> PlayerMovement = nullptr; // To get reference to the Character Movement

	GENERATED_BODY()

};
