#include "StatusWidget.h"
#include "Components/ProgressBar.h"

void UStatusWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UStatusWidget::UpdateHealthBar(float Current, float Max)
{
	if (HealthBar && Max > 0.f)
	{
		HealthBar->SetPercent(Current / Max);
	}
}

void UStatusWidget::UpdateStaminaBar(float Current, float Max)
{
	if (StaminaBar && Max > 0.f)
	{
		StaminaBar->SetPercent(Current / Max);
	}
}
