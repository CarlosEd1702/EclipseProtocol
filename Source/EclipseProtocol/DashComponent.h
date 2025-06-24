#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DashComponent.generated.h"

class UStaminaComponent;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ECLIPSEPROTOCOL_API UDashComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UDashComponent();

	UFUNCTION(BlueprintCallable, Category = "Dash")
	void TryDash();

	UPROPERTY(EditDefaultsOnly, Category = "Dash")
	float StaminaCost = 20.f;

	UPROPERTY(EditDefaultsOnly, Category = "Dash")
	float DashDistance = 600.f;

	UPROPERTY(EditDefaultsOnly, Category = "Dash")
	float DashCooldown = 1.f;

	UPROPERTY(EditDefaultsOnly, Category = "Dash")
	float DashDuration = 0.1f;

protected:
	virtual void BeginPlay() override;

private:
	bool bCanDash = true;

	UStaminaComponent* StaminaComp;

	FVector DashStart;
	FVector DashEnd;
	float ElapsedTime = 0.f;

	FTimerHandle DashTickHandle;
	FTimerHandle CooldownHandle;

	void PerformDash();
	void TickDash();
	void ResetDash();
};
