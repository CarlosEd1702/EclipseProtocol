#include "DashComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "StaminaComponent.h"
#include "TimerManager.h"

UDashComponent::UDashComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UDashComponent::BeginPlay()
{
	Super::BeginPlay();

	if (AActor* Owner = GetOwner())
	{
		StaminaComp = Owner->FindComponentByClass<UStaminaComponent>();
	}
}

void UDashComponent::TryDash()
{
	if (!bCanDash || !StaminaComp) return;
	if (StaminaComp->GetStamina() < StaminaCost) return;

	StaminaComp->ConsumeStamina(StaminaCost);
	bCanDash = false;

	PerformDash();

	// Cooldown
	GetWorld()->GetTimerManager().SetTimer(CooldownHandle, this, &UDashComponent::ResetDash, DashCooldown, false);
	StaminaComp->StartRegen();
}

void UDashComponent::ResetDash()
{
	bCanDash = true;
}

void UDashComponent::PerformDash()
{
	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (!OwnerCharacter) return;

	DashStart = OwnerCharacter->GetActorLocation();
	FVector Forward = OwnerCharacter->GetActorForwardVector();
	DashEnd = DashStart + Forward * DashDistance;
	ElapsedTime = 0.f;

	// Bloquea movimiento
	OwnerCharacter->GetCharacterMovement()->DisableMovement();

	// Timer tick
	GetWorld()->GetTimerManager().SetTimer(DashTickHandle, this, &UDashComponent::TickDash, 0.01f, true);
}

void UDashComponent::TickDash()
{
	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (!OwnerCharacter) return;

	ElapsedTime += 0.01f;
	float Alpha = FMath::Clamp(ElapsedTime / DashDuration, 0.f, 1.f);
	FVector NewLocation = FMath::Lerp(DashStart, DashEnd, Alpha);

	OwnerCharacter->SetActorLocation(NewLocation, true);

	if (Alpha >= 1.f)
	{
		GetWorld()->GetTimerManager().ClearTimer(DashTickHandle);
		OwnerCharacter->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	}
}
