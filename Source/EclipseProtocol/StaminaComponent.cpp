// StaminaComponent.cpp
#include "StaminaComponent.h"

#include "Engine/World.h"

UStaminaComponent::UStaminaComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UStaminaComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentStamina = MaxStamina;
	OnStaminaChanged.Broadcast(CurrentStamina, MaxStamina);
	
	// Start regen timer
	GetWorld()->GetTimerManager().SetTimer(RegenTimerHandle, this, &UStaminaComponent::HandleRegenTick, 0.1f, true);
}

void UStaminaComponent::ConsumeStamina(float Amount)
{
	CurrentStamina = FMath::Clamp(CurrentStamina - Amount, 0.f, MaxStamina);
	OnStaminaChanged.Broadcast(CurrentStamina, MaxStamina);

	// Pausar Regeneracion
	GetWorld()->GetTimerManager().ClearTimer(RegenTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(RegenDelayHandle);

	//Reanudar despues del delay
	GetWorld()->GetTimerManager().SetTimer(RegenDelayHandle, this, &UStaminaComponent::StartRegen, RegenDelay, false);
}

void UStaminaComponent::RegenerateStamina(float Amount)
{
	CurrentStamina = FMath::Clamp(CurrentStamina + Amount, 0.f, MaxStamina);
	OnStaminaChanged.Broadcast(CurrentStamina, MaxStamina);
}

void UStaminaComponent::SetCanRegenStamina(bool bEnabled)
{
	bCanRegenStamina = bEnabled;
}

void UStaminaComponent::HandleRegenTick()
{
	if (bCanRegenStamina && CurrentStamina < MaxStamina)
	{
		RegenerateStamina(RegenRate);
	}
}

void UStaminaComponent::StartRegen()
{
	SetCanRegenStamina(true);
	GetWorld()->GetTimerManager().SetTimer(RegenTimerHandle, this, &UStaminaComponent::HandleRegenTick, 0.1f, true);
}
