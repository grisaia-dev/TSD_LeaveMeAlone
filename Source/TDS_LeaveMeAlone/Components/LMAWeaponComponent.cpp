// Make by Jatex. All Right Reserved.


#include "LMAWeaponComponent.h"
#include "../Weapon/LMABaseWeapon.h"
#include "GameFramework/Character.h"
#include "Engine/TimerHandle.h"
#include "../LMACharacter.h"
#include "../Animations/LMAReloadFinishedAnimNotify.h"

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
	InitAnimNotify();
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
			Weapon->OnClipIsEmpty.AddUObject(this, &ULMAWeaponComponent::OnClipIsEmpty);
		}
	}
}

void ULMAWeaponComponent::StartFire() {
	if (Weapon && !AnimReloading)
		Weapon->StartFire();
}

void ULMAWeaponComponent::StopFire() {
	Weapon->StopFire();
}

void ULMAWeaponComponent::InitAnimNotify() {
	if (!ReloadMontage) return;
	const auto NotifiesEvents = ReloadMontage->Notifies;
	for (auto NotifyEvent : NotifiesEvents) {
		auto ReloadFinish = Cast<ULMAReloadFinishedAnimNotify>(NotifyEvent.Notify);
		if (ReloadFinish) {
			ReloadFinish->OnNotifyReloadFinished.AddUObject(this, &ULMAWeaponComponent::OnNotifyReloadFinished);
			break;
		}
	}
}

void ULMAWeaponComponent::OnNotifyReloadFinished(USkeletalMeshComponent* SkeletalMesh) {
	const auto Character = Cast<ACharacter>(GetOwner());
	if (Character->GetMesh() == SkeletalMesh) { 
		AnimReloading = false;
		Weapon->ChangeClip();
	}
}

bool ULMAWeaponComponent::CanReload() const {
	return !AnimReloading && !Weapon->IsCurrentClipFull();
}

void ULMAWeaponComponent::OnClipIsEmpty(bool Ammo) {
	if (Ammo) {
		Reload();
		GEngine->AddOnScreenDebugMessage(3, 2.0f, FColor::Silver, FString::Printf(TEXT("Reload?: %i"), Ammo));
	}
}

void ULMAWeaponComponent::Reload() {
	if (!CanReload()) return;
	StopFire();
	AnimReloading = true;
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	Character->PlayAnimMontage(ReloadMontage);
}