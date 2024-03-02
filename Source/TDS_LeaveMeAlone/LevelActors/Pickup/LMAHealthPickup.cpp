// Make by Jatex. All Right Reserved.


#include "LMAHealthPickup.h"
#include "Components/SphereComponent.h"
#include "../../LMACharacter.h"
#include "../../Components/LMAHealthComponent.h"

// Sets default values
ALMAHealthPickup::ALMAHealthPickup() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SetRootComponent(SphereComponent);
}

// Called when the game starts or when spawned
void ALMAHealthPickup::BeginPlay() {
	Super::BeginPlay();
	checkf(SphereComponent, TEXT("Unable reference to USphereCompoonent"));

}

// Called every frame
void ALMAHealthPickup::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void ALMAHealthPickup::PickupWasTaken() {
	SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	GetRootComponent()->SetVisibility(false, true);
	FTimerHandle RespawnTimerHandle;
	GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ALMAHealthPickup::RespawnPickup, RespawnTime);
}

void ALMAHealthPickup::RespawnPickup() {
	SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	GetRootComponent()->SetVisibility(true, true);
}

bool ALMAHealthPickup::GivePickup(ALMACharacter* Character) {
	const auto HealthComponent = Character->GetHealthComponent();
	if (!HealthComponent) return false;
	return HealthComponent->AddHealth(HealthFromPickup);
}

void ALMAHealthPickup::NotifyActorBeginOverlap(AActor* OtherActor) {
	Super::NotifyActorBeginOverlap(OtherActor);
	const auto Character = Cast<ALMACharacter>(OtherActor);
	checkf(Character, TEXT("Cast failed"));
	if (GivePickup(Character)) { PickupWasTaken(); }
}