// Make by Jatex. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LMAHealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TDS_LEAVEMEALONE_API ULMAHealthComponent : public UActorComponent {

public:	
	// Sets default values for this component's properties
	ULMAHealthComponent();

	UFUNCTION(BlueprintCallable) float GetHealth() const { return Health; }

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player|Health") float MaxHealth = 100.f;

	// Called when the game starts
	virtual void BeginPlay() override;

private:
	float Health = 0.f;

	GENERATED_BODY()
};
