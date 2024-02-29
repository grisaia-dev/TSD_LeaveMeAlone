// Make by Jatex. All Right Reserved.


#include "LMACharacter.h"
#include "Components/LMAHealthComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ALMACharacter::ALMACharacter() {
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->SetUsingAbsoluteRotation(true);
	SpringArmComponent->SetRelativeRotation(FRotator(ArmRotateY, 0.f, 0.f));
	SpringArmComponent->TargetArmLength = ArmLenght;
	SpringArmComponent->bDoCollisionTest = false;
	SpringArmComponent->bEnableCameraLag = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->SetFieldOfView(CameraFOV);
	CameraComponent->bUsePawnControlRotation = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	HealthComponent = CreateDefaultSubobject<ULMAHealthComponent>("HealthComponent");
}

// Called when the game starts or when spawned
void ALMACharacter::BeginPlay() {
	Super::BeginPlay();
	PlayerMovement = GetCharacterMovement();
	checkf(PlayerMovement, TEXT("Unable CharacterMovement"));

	PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	checkf(PC, TEXT("Unable to get reference to PlayerController"));

	PlayerMovement->MaxWalkSpeed = NormalMaxWalkSpeed;

	checkf(HealthComponent, TEXT("Create HealthComponent finished bad"));
	HealthComponent->OnDeath.AddUObject(this, &ALMACharacter::OnDeath);
	HealthComponent->OnHealthChanged.AddUObject(this, &ALMACharacter::OnHealthChanged);

	checkf(DeathMontage, TEXT("Check DeathMontage!"));
}


// Called every frame
void ALMACharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	if (!HealthComponent->IsDead()) {
		RotationOnCursor();
		UpdateStamina();
	}

	// temporary displey debug info
	GEngine->AddOnScreenDebugMessage(2, 0.5f, FColor::Green, *(FString::Printf(TEXT("Health - Current: %f"), HealthComponent->GetHealth())));
	GEngine->AddOnScreenDebugMessage(1, 0.5f, FColor::Silver, *(FString::Printf(TEXT("Stamina - Current: %f"), CurrentStamina)));
}

// Called to bind functionality to input
//void ALMACharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) { Super::SetupPlayerInputComponent(PlayerInputComponent); }

void ALMACharacter::RotationOnCursor() {
	if (PC) {
		FHitResult ResultHit;
		PC->GetHitResultUnderCursor(ECC_GameTraceChannel1, true, ResultHit);
		float FindRotatorResultZ = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), ResultHit.Location).Yaw;
		SetActorRotation(FQuat(FRotator(0.f, FindRotatorResultZ, 0.f)));
	}
}

void ALMACharacter::StartSprint() {
	if (bHasStamina) {
		PlayerMovement->MaxWalkSpeed = SprintMaxWalkSpeed;
		if (GetVelocity().Size() >= 0.4f) {
			bIsSprint = true;
		} else {
			bIsSprint = false;
		}
	} 
}
void ALMACharacter::StopSprint() {
	PlayerMovement->MaxWalkSpeed = NormalMaxWalkSpeed;
	bIsSprint = false;
}
void ALMACharacter::UpdateStamina() {
	if (bIsSprint) { CurrentStamina = FMath::Clamp(CurrentStamina - SprintCost, 0.f, MaxStamina); }
	if (!bIsSprint && CurrentStamina < MaxStamina) { CurrentStamina =  FMath::Clamp(CurrentStamina + StaminaRecovery, 0.f, MaxStamina); }
	if (CurrentStamina <= 0) {
		bHasStamina = false;
		StopSprint();
	} else if (CurrentStamina >= 50.f) { bHasStamina = true; }
}

void ALMACharacter::OnHealthChanged(float NewHealth) {
	GEngine->AddOnScreenDebugMessage(4, 0.5f, FColor::Green, *(FString::Printf(TEXT("i'm here"))));
}

void ALMACharacter::OnDeath() {
	PlayerMovement->DisableMovement();
	PlayAnimMontage(DeathMontage);
	SetLifeSpan(5.f);
	if (PC) {
		PC->ChangeState(NAME_Spectating);
	}
}