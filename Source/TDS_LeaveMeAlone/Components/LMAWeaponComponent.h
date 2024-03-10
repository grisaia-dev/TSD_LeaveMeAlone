// Make by Jatex. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LMAWeaponComponent.generated.h"

class ALMABaseWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TDS_LEAVEMEALONE_API ULMAWeaponComponent : public UActorComponent {
public:	
	ULMAWeaponComponent(); // Sets default values for this component's properties
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override; // Called every frame

	void SpawnWeapon();

#pragma region Fire
	void StartFire();
	void StopFire();
#pragma endregion

	void Reload();
	bool CanReload() const;

protected:
	virtual void BeginPlay() override; // Called when the game starts

	void InitAnimNotify();
	void OnNotifyReloadFinished(USkeletalMeshComponent* SkeletalMesh);

	void OnClipIsEmpty(bool Ammo);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon") TSubclassOf<ALMABaseWeapon> WeaponClass;
	UPROPERTY() ALMABaseWeapon* Weapon = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	UAnimMontage* ReloadMontage = nullptr;
	bool AnimReloading = false;

	GENERATED_BODY()
};
