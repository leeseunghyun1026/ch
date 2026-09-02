#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
struct FInputActionValue;
UCLASS()
class CH_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()


public:	
	AMyCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* CameraComponent;
	
	virtual void SetupPlayerInputComponent(
        class UInputComponent *PlayerInputComponent) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
    float MaxHealth;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
    float Health;



	UFUNCTION()
    void Move(const FInputActionValue &value);
	UFUNCTION()
    void Look(const FInputActionValue &value);
    UFUNCTION()
    void StartJump(const FInputActionValue &value);
    UFUNCTION()
    void StartSprint(const FInputActionValue &value);
	UFUNCTION()
    void EndSprint(const FInputActionValue &value);

    UFUNCTION()
    float GetHealth() const;
    UFUNCTION()
    void AddHealth(float Amount);
    void OnDeath();
    virtual float TakeDamage(float DamageAmount,
                             struct FDamageEvent const &DamageEvent,
                             AController *EventInstigator,
                             AActor *DamageCauser) override;
};
