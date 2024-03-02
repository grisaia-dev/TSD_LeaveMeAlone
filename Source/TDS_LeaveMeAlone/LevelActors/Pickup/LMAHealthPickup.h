// Make by Jatex. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LMAHealthPickup.generated.h"

class USphereComponent;
class ALMACharacter;

UCLASS()
class TDS_LEAVEMEALONE_API ALMAHealthPickup : public AActor {
	
public:	
	// Sets default values for this actor's properties
	ALMAHealthPickup();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Pickup") TObjectPtr<USphereComponent> SphereComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup") float RespawnTime = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "5", ClampMax = "100")) float HealthFromPickup = 100.f;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
private:
	bool GivePickup(ALMACharacter* Character);
	void PickupWasTaken();
	void RespawnPickup();


	GENERATED_BODY()
};
