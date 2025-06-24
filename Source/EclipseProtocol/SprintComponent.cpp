#include "SprintComponent.h"
#include "StaminaComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"

USprintComponent::USprintComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USprintComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (OwnerCharacter)
	{
		StaminaComp = OwnerCharacter->FindComponentByClass<UStaminaComponent>();
	}
}

void USprintComponent::StartSprinting()
{
	if (!OwnerCharacter || !StaminaComp) return;

	if (StaminaComp->GetStamina() <= StaminaCostPerTick)
	{
		StopSprinting();
		return;
	}

	bIsSprinting = true;
	OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	StaminaComp->SetCanRegenStamina(false);

	// Comenzar a consumir estamina
	GetWorld()->GetTimerManager().SetTimer(SprintTickHandle, this, &USprintComponent::ConsumeStaminaTick, TickRate, true);
}

void USprintComponent::StopSprinting()
{
	if (!OwnerCharacter || !StaminaComp) return;

	bIsSprinting = false;
	OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

	GetWorld()->GetTimerManager().ClearTimer(SprintTickHandle);
	StaminaComp->StartRegen();
}

void USprintComponent::ConsumeStaminaTick()
{
	if (!StaminaComp || !bIsSprinting) return;

	if (StaminaComp->GetStamina() <= StaminaCostPerTick)
	{
		StopSprinting();
		return;
	}

	StaminaComp->ConsumeStamina(StaminaCostPerTick);
}
