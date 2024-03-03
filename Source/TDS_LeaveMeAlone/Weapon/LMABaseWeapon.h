// Make by Jatex. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LMABaseWeapon.generated.h"

class ALMACharacter;

UCLASS()
class TDS_LEAVEMEALONE_API ALMABaseWeapon : public AActor {
public:	
	ALMABaseWeapon();

	void StartFire();
	void StopFire();

	virtual void Tick(float DeltaTime) override; // Update every tick
protected:
	virtual void BeginPlay() override; // When Game Start's

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon") TObjectPtr<USkeletalMeshComponent> WeaponComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon") float TraceDistance = 800.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon") float FireRate = 1.f;

private:
	void Shoot();

	FTimerHandle TimerHandle;

	UPROPERTY() ALMACharacter* PlayerCharacter = nullptr;

	GENERATED_BODY()
};
