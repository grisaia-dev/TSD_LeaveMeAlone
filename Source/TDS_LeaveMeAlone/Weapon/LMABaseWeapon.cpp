// Make by Jatex. All Right Reserved.


#include "LMABaseWeapon.h"

// Sets default values
ALMABaseWeapon::ALMABaseWeapon() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponComponent = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	SetRootComponent(WeaponComponent);
}

// Called when the game starts or when spawned
void ALMABaseWeapon::BeginPlay() {
	Super::BeginPlay();
	checkf(WeaponComponent, TEXT("Unable reference to WeaponComponent"));
}

// Called every frame
void ALMABaseWeapon::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

