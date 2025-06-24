#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EclipseProtocolCharacter.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

class USpringArmComponent;
class UCameraComponent;
class UInputAction;
class UInteractionComponent;
class UHealthComponent;
class UStaminaComponent;
class UDashComponent;
class USprintComponent;
class UStatusWidget;
struct FInputActionValue;

UCLASS(abstract)
class AEclipseProtocolCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input") UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input") UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input") UInputAction* LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input") UInputAction* MouseLookAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input") UInputAction* SprintAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input") UInputAction* InteractionInput;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input") UInputAction* DashInput;

public:
	AEclipseProtocolCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UInteractionComponent* InteractionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaminaComponent* StaminaComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UDashComponent* DashComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USprintComponent* SprintComponent;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UStatusWidget> StatusWidgetClass;

	UStatusWidget* StatusWidgetInstance;

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void BeginPlay();

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

public:
	void TryInteract();
	void PerformDash();

	UFUNCTION(BlueprintCallable) void DoMove(float Right, float Forward);
	UFUNCTION(BlueprintCallable) void DoLook(float Yaw, float Pitch);
	UFUNCTION(BlueprintCallable) void DoJumpStart();
	UFUNCTION(BlueprintCallable) void DoJumpEnd();

	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
