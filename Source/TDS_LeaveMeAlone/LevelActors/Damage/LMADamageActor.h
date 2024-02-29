// Make by Jatex. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LMADamageActor.generated.h"

class USphereComponent;

UCLASS()
class TDS_LEAVEMEALONE_API ALMADamageActor : public AActor {
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALMADamageActor();


	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components") TObjectPtr<USphereComponent> SphereComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components") TObjectPtr<UStaticMeshComponent> StaticMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage") float Damage = 5.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage") float SphereRadius = 100.f;
private:	

};
