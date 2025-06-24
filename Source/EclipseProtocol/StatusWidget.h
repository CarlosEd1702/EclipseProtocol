#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StatusWidget.generated.h"

class UProgressBar;

/**
 * Widget que muestra solo la barra de stamina
 */
UCLASS()
class ECLIPSEPROTOCOL_API UStatusWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	/** Llamar desde Blueprint cuando cambia la salud */
	UFUNCTION(BlueprintCallable, Category = "Status")
	void UpdateHealthBar(float Current, float Max);
	
	/** Llamar desde Blueprint cuando cambia la estamina */
	UFUNCTION(BlueprintCallable, Category = "Status")
	void UpdateStaminaBar(float Current, float Max);

protected:
	virtual void NativeConstruct() override;
	
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
	UProgressBar* HealthBar;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
	UProgressBar* StaminaBar;
};
