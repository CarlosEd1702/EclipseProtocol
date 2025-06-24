// InteractionComponent.cpp
#include "InteractionComponent.h"
#include "InteractableInterface.h"
#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"

UInteractionComponent::UInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInteractionComponent::TryInteract()
{
	AActor* Owner = GetOwner();
	if (!Owner) return;

	FVector Start = Owner->GetActorLocation();
	FVector End = Start + Owner->GetActorForwardVector() * TraceDistance;

	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(Owner);

	GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params);

	if (AActor* HitActor = Hit.GetActor())
	{
		if (HitActor->Implements<UInteractableInterface>())
		{
			IInteractableInterface::Execute_Interact(HitActor, Owner);
		}
	}

	// Visual debug
	DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1.5f, 0, 2.f);
}
