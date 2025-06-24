#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.h"
#include "InteractableActor.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UWidgetComponent;

UCLASS()
class ECLIPSEPROTOCOL_API AInteractableActor : public AActor, public IInteractableInterface
{
	GENERATED_BODY()

public:
	AInteractableActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "TriggerBox")
	UBoxComponent* TriggerBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interact")
	UWidgetComponent* InteractionWidget;

	// Solo la declaración
	virtual void Interact_Implementation(AActor* Interactor) override;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
