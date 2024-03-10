// Make by Jatex. All Right Reserved.
#include "LMABaseWeapon.h"
#include "../LMACharacter.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeapon, All, All);

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

	PlayerCharacter = Cast<ALMACharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	checkf(PlayerCharacter, TEXT("Get reference to the PlayerCharacter"));

	CurrentAmmoWeapon.Bullets = AmmoWeapon.Bullets;
}

// Called every frame
void ALMABaseWeapon::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::White, *(FString::Printf(TEXT("Ammo: %i"), CurrentAmmoWeapon.Bullets)));
}

void ALMABaseWeapon::StartFire() {
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ALMABaseWeapon::Shoot, FireRate, true, 0.f);
}

void ALMABaseWeapon::StopFire() {
	GetWorldTimerManager().ClearTimer(TimerHandle);
}

void ALMABaseWeapon::Shoot() {
	if (PlayerCharacter->GetIsSprint() || PlayerCharacter->IsDead()) { StopFire(); return; }
	const FTransform SocketTransform = WeaponComponent->GetSocketTransform("Fire");
	const FVector TraceStart = SocketTransform.GetLocation();
	const FVector ShootDirection = SocketTransform.GetRotation().GetForwardVector();
	const FVector TraceEnd = TraceStart + ShootDirection * TraceDistance;
	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Black, false, 1.f, 0, 2.f);

	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility);

	if (HitResult.bBlockingHit) {
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 5.f, 24, FColor::Red, false, 1.0f);
	}
	DecrementBulltes();
}

void ALMABaseWeapon::ChangeClip() { CurrentAmmoWeapon.Bullets = AmmoWeapon.Bullets; }

bool ALMABaseWeapon::IsCurrentClipEmpty() const { return CurrentAmmoWeapon.Bullets == 0; }
bool ALMABaseWeapon::IsCurrentClipFull() const { return CurrentAmmoWeapon.Bullets == 30; }

void ALMABaseWeapon::DecrementBulltes() {
	CurrentAmmoWeapon.Bullets = FMath::Clamp(CurrentAmmoWeapon.Bullets - 1, 0, 30);
	OnClipIsEmpty.Broadcast(IsCurrentClipEmpty());
}