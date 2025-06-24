// SprintComponent.h
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SprintComponent.generated.h"

class UStaminaComponent;
class ACharacter;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ECLIPSEPROTOCOL_API USprintComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USprintComponent();

	UFUNCTION(BlueprintCallable)
	void StartSprinting();

	UFUNCTION(BlueprintCallable)
	void StopSprinting();

	// Configurables desde el editor
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sprint")
	float SprintSpeed = 850.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sprint")
	float WalkSpeed = 500.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sprint")
	float StaminaCostPerTick = 5.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sprint")
	float TickRate = 0.1f;

protected:
	virtual void BeginPlay() override;

private:
	bool bIsSprinting = false;

	UPROPERTY()
	ACharacter* OwnerCharacter;

	UPROPERTY()
	UStaminaComponent* StaminaComp;

	FTimerHandle SprintTickHandle;

	UFUNCTION()
	void ConsumeStaminaTick();
};
