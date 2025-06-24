#include "EclipseProtocolCharacter.h"
#include "DashComponent.h"
#include "SprintComponent.h"
#include "StaminaComponent.h"
#include "HealthComponent.h"
#include "InteractionComponent.h"
#include "StatusWidget.h"
#include "InputActionValue.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

AEclipseProtocolCharacter::AEclipseProtocolCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>(TEXT("InteractionComponent"));
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	StaminaComponent = CreateDefaultSubobject<UStaminaComponent>(TEXT("StaminaComponent"));
	DashComponent = CreateDefaultSubobject<UDashComponent>(TEXT("DashComponent"));
	SprintComponent = CreateDefaultSubobject<USprintComponent>(TEXT("SprintComponent"));
}

void AEclipseProtocolCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EIC->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EIC->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AEclipseProtocolCharacter::Move);
		EIC->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &AEclipseProtocolCharacter::Look);
		EIC->BindAction(LookAction, ETriggerEvent::Triggered, this, &AEclipseProtocolCharacter::Look);
		if (SprintComponent)
		{
			EIC->BindAction(SprintAction, ETriggerEvent::Started, SprintComponent, &USprintComponent::StartSprinting);
			EIC->BindAction(SprintAction, ETriggerEvent::Completed, SprintComponent, &USprintComponent::StopSprinting);
		}
		if(InteractionComponent)
		{
			EIC->BindAction(InteractionInput, ETriggerEvent::Triggered, this, &AEclipseProtocolCharacter::TryInteract);

		}
		if(DashComponent)
		{
			EIC->BindAction(DashInput, ETriggerEvent::Triggered, this, &AEclipseProtocolCharacter::PerformDash);
		}
	}
}

void AEclipseProtocolCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (StatusWidgetClass)
	{
		StatusWidgetInstance = CreateWidget<UStatusWidget>(GetWorld(), StatusWidgetClass);
		if (StatusWidgetInstance)
		{
			StatusWidgetInstance->AddToViewport();

			if (HealthComponent)
			{
				HealthComponent->OnHealthChanged.AddDynamic(StatusWidgetInstance, &UStatusWidget::UpdateHealthBar);
				StatusWidgetInstance->UpdateHealthBar(HealthComponent->GetHealth(), HealthComponent->GetMaxHealth());
			}

			if (StaminaComponent)
			{
				StaminaComponent->OnStaminaChanged.AddDynamic(StatusWidgetInstance, &UStatusWidget::UpdateStaminaBar);
				StatusWidgetInstance->UpdateStaminaBar(StaminaComponent->GetStamina(), StaminaComponent->GetMaxStamina());
			}
		}
	}
}

void AEclipseProtocolCharacter::Move(const FInputActionValue& Value)
{
	FVector2D Input = Value.Get<FVector2D>();
	DoMove(Input.X, Input.Y);
}

void AEclipseProtocolCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookInput = Value.Get<FVector2D>();
	DoLook(LookInput.X, LookInput.Y);
}

void AEclipseProtocolCharacter::DoMove(float Right, float Forward)
{
	if (!Controller) return;

	const FRotator YawRot(0.f, Controller->GetControlRotation().Yaw, 0.f);
	const FVector ForwardDir = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);
	const FVector RightDir = FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDir, Forward);
	AddMovementInput(RightDir, Right);
}

void AEclipseProtocolCharacter::DoLook(float Yaw, float Pitch)
{
	AddControllerYawInput(Yaw);
	AddControllerPitchInput(Pitch);
}

void AEclipseProtocolCharacter::DoJumpStart() { Jump(); }
void AEclipseProtocolCharacter::DoJumpEnd()   { StopJumping(); }

void AEclipseProtocolCharacter::TryInteract()
{
	if (InteractionComponent)
	{
		InteractionComponent->TryInteract();
	}
}

void AEclipseProtocolCharacter::PerformDash()
{
	if (DashComponent && StaminaComponent)
	{
		StaminaComponent->SetCanRegenStamina(false);
		DashComponent->TryDash();
	}
}
