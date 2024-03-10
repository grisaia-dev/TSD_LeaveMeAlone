// Make by Jatex. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LMABaseWeapon.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnClipIsEmpty, bool)

class ALMACharacter;

USTRUCT(BlueprintType) struct FAmmoWeapon {
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon") int32 Bullets;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon") int32 Clips;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon") bool Infinite;
};

UCLASS()
class TDS_LEAVEMEALONE_API ALMABaseWeapon : public AActor {
public:	
	ALMABaseWeapon();

	void StartFire();
	void StopFire();

	void ChangeClip();
	bool IsCurrentClipEmpty() const;
	bool IsCurrentClipFull() const;

	FOnClipIsEmpty OnClipIsEmpty;

	virtual void Tick(float DeltaTime) override; // Update every tick
protected:
	virtual void BeginPlay() override; // When Game Start's

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon") TObjectPtr<USkeletalMeshComponent> WeaponComponent = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon") float TraceDistance = 800.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon") float FireRate = 1.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon") FAmmoWeapon AmmoWeapon { 30, 0, true };

	void DecrementBulltes();
private:
	void Shoot();

	FAmmoWeapon CurrentAmmoWeapon;

	FTimerHandle TimerHandle;
	UPROPERTY() ALMACharacter* PlayerCharacter = nullptr;

	GENERATED_BODY()
};
