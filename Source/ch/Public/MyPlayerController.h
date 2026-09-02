#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"


class UInputMappingContext;
class UInputAction;

UCLASS()
class CH_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMyPlayerController();


	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Controller")
	UInputMappingContext* IMC_Default;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Controller")
	UInputAction* IA_Move;
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Controller")
	UInputAction* IA_Look;
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Controller")
	UInputAction* IA_Jump;
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Controller")
	UInputAction* IA_Sprint;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> HUDWidgetClass;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
    UUserWidget *HUDWidgetInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MENU")
    TSubclassOf<UUserWidget> MainMenuWidgetClass;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MENU")
    UUserWidget *MainMenuWidgetInstance;

	UFUNCTION(BlueprintPure, Category = "HUD")
    UUserWidget *GetHUDWidget() const;

	UFUNCTION(BlueprintCallable, Category = "HUD")

	void ShowGameHUD();
    UFUNCTION(BlueprintCallable, Category = "MENU")

	void ShowMainMenu(bool bIsRestart);
    UFUNCTION(BlueprintCallable, Category = "MENU")

    void StartGame();

	virtual void BeginPlay() override;




};
