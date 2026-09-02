#include "MyCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "MyPlayerController.h"

AMyCharacter::AMyCharacter()
{

	PrimaryActorTick.bCanEverTick = false;

	SpringArmComponent =
		CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 300.0f;
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent =
		CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->bUsePawnControlRotation = false;

	GetCharacterMovement()->MaxWalkSpeed = 300.0f;

	MaxHealth = 100.0f;
	Health = MaxHealth;
}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (AMyPlayerController* PlayerController = Cast<AMyPlayerController>(GetController()))
		{
			if (PlayerController->IA_Move)
			{
                EnhancedInput->BindAction(PlayerController->IA_Move,
                                          ETriggerEvent::Triggered, this,
                                          &AMyCharacter::Move);
			}


			if (PlayerController->IA_Look)
			{
                EnhancedInput->BindAction(PlayerController->IA_Look,
                                          ETriggerEvent::Triggered, this,
                                          &AMyCharacter:: Look);
			}

			if (PlayerController->IA_Jump)
			{
                EnhancedInput->BindAction(PlayerController->IA_Jump,
                                          ETriggerEvent::Triggered, this,
                                          &AMyCharacter::StartJump);
			}

			if (PlayerController->IA_Sprint)
			{
                EnhancedInput->BindAction(PlayerController->IA_Sprint,
                                          ETriggerEvent::Triggered, this,
                                          &AMyCharacter::StartSprint);

				EnhancedInput->BindAction(PlayerController->IA_Sprint,
                                          ETriggerEvent::Completed, this,
                                          &AMyCharacter::EndSprint);
			}

		}
	}
}


void AMyCharacter::Move(const FInputActionValue &value)
{
    const FVector2D MoveInput = value.Get<FVector2D>();
    if (!FMath::IsNearlyZero(MoveInput.X))
        {
        AddMovementInput(GetActorForwardVector(), MoveInput.X);
        }
	if (!FMath::IsNearlyZero(MoveInput.Y))
	{
        AddMovementInput(GetActorRightVector(), MoveInput.Y);
		}
}

void AMyCharacter::Look(const FInputActionValue &value)
{
    const FVector2D LookInput = value.Get<FVector2D>();
    
	AddControllerYawInput(LookInput.X);
    AddControllerPitchInput(LookInput.Y);
}

void AMyCharacter::StartJump(const FInputActionValue &value)
{
    if (value.Get<bool>())
    {
        Jump();
    }
}

void AMyCharacter::StartSprint(const FInputActionValue &value)
{
	if (GetCharacterMovement())
	{
        GetCharacterMovement()->MaxWalkSpeed = 1200.0f;
	}
}

void AMyCharacter::EndSprint(const FInputActionValue &value)
{
	if (GetCharacterMovement())
	{
        GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	}
}


void AMyCharacter::AddHealth(float Amount)
{
    Health = FMath::Clamp(Health + Amount, 0.0f, MaxHealth);
    GEngine->AddOnScreenDebugMessage(
        -1, 3.0f, FColor::Cyan, FString ::Printf(TEXT("체력회복 : %f"), Health));
}


float AMyCharacter::TakeDamage(float DamageAmount,
	struct FDamageEvent const& DamageEvent,
	AController* EventInstigator,
	AActor* DamageCauser)
{
    float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent,
                                           EventInstigator, DamageCauser);

	Health = FMath::Clamp(Health - ActualDamage, 0.0f, MaxHealth);
	
	if (Health <= 0.0f)
	{
        OnDeath();
	}
    return ActualDamage;

}

void AMyCharacter::OnDeath()
{
    UE_LOG(LogTemp, Warning, TEXT("죽음"));
}

float AMyCharacter::GetHealth() const
{
    return Health;
}