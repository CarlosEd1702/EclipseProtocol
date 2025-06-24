// InteractionComponent.h
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ECLIPSEPROTOCOL_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInteractionComponent();
	
	UFUNCTION(BlueprintCallable)
	void TryInteract();

	UPROPERTY(EditAnywhere, Category = "Interact")
	float TraceDistance = 250.f;
};
