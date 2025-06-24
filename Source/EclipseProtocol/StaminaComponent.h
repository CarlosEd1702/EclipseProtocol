// StaminaComponent.h
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StaminaComponent.generated.h"

struct FTimerHandle;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStaminaChanged, float, Current, float, Max);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ECLIPSEPROTOCOL_API UStaminaComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UStaminaComponent();

	UFUNCTION(BlueprintCallable)
	void ConsumeStamina(float Amount);
	
	UFUNCTION(BlueprintCallable)
	void RegenerateStamina(float Amount);
	
	UFUNCTION(BlueprintCallable)
	float GetStamina() const { return CurrentStamina; }
	
	UFUNCTION(BlueprintCallable)
	float GetMaxStamina() const { return MaxStamina; }

	/** Si es false, no se regenera la estamina automáticamente */
	UPROPERTY(BlueprintReadWrite, Category = "Stamina")
	bool bCanRegenStamina = true;

	UPROPERTY(BlueprintAssignable)
	FOnStaminaChanged OnStaminaChanged;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stamina")
	FTimerHandle  RegenTimerHandle;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stamina")
	FTimerHandle RegenDelayHandle;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stamina")
	float RegenDelay = 1.5f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stamina")
	float RegenRate = 2.5f;

	UFUNCTION(BlueprintCallable, Category = "Stamina")
	void SetCanRegenStamina(bool bEnabled);
	
	UFUNCTION(BlueprintCallable)
	void HandleRegenTick();
	
	UFUNCTION()
	void StartRegen();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Stamina")
	float MaxStamina = 100.f;

	UPROPERTY(BlueprintReadOnly, Category = "Stamina")
	float CurrentStamina;
};
