// Make by Jatex. All Right Reserved.


#include "LMAWeaponComponent.h"
#include "../Weapon/LMABaseWeapon.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
ULMAWeaponComponent::ULMAWeaponComponent() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void ULMAWeaponComponent::BeginPlay() {
	Super::BeginPlay();
	SpawnWeapon();
}


// Called every frame
void ULMAWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void ULMAWeaponComponent::SpawnWeapon() {
	Weapon = GetWorld()->SpawnActor<ALMABaseWeapon>(WeaponClass);
	if (Weapon) {
		const auto Character = Cast<ACharacter>(GetOwner());
		if (Character) {
			FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
			Weapon->AttachToComponent(Character->GetMesh(), AttachmentRules, "r_weapon_socket");
		}
	}
}