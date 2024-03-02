// Make by Jatex. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LMABaseWeapon.generated.h"

UCLASS()
class TDS_LEAVEMEALONE_API ALMABaseWeapon : public AActor {
public:	
	ALMABaseWeapon();

	virtual void Tick(float DeltaTime) override; // Update every tick
protected:
	virtual void BeginPlay() override; // When Game Start's

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon") TObjectPtr<USkeletalMeshComponent> WeaponComponent = nullptr;

private:	

	GENERATED_BODY()
};
