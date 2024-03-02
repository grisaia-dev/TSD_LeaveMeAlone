// Make by Jatex. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LMAHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TDS_LEAVEMEALONE_API ULMAHealthComponent : public UActorComponent {

public:	
	// Sets default values for this component's properties
	ULMAHealthComponent();

	UFUNCTION(BlueprintCallable) float GetHealth() const { return Health; }

	UFUNCTION(BlueprintCallable) bool IsDead() const;

	bool AddHealth(float NewHealth);

	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	FOnDeath OnDeath;
	FOnHealthChanged OnHealthChanged;
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player|Health") float MaxHealth = 100.f;

	// Called when the game starts
	virtual void BeginPlay() override;

private:
	float Health = 0.f;

	// For Delegates with damage
	UFUNCTION() void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UPROPERTY() TObjectPtr<AActor> OwnerComponent = nullptr;

	bool IsHealthFull() const;

	GENERATED_BODY()
};
