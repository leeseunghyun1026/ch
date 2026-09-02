#include "MyPlayerController.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "UObject/ConstructorHelpers.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "MyGameState.h"
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"
AMyPlayerController::AMyPlayerController()
    : IMC_Default(nullptr), IA_Move(nullptr), IA_Look(nullptr),
      IA_Jump(nullptr), IA_Sprint(nullptr), HUDWidgetClass(nullptr),
      HUDWidgetInstance(nullptr), MainMenuWidgetClass(nullptr),
      MainMenuWidgetInstance(nullptr)
{
    static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMCFinder(
        TEXT("/Game/Inputs/IMC_Default.IMC_Default"));
    if (IMCFinder.Succeeded())
    {
        IMC_Default = IMCFinder.Object;
    }

    static ConstructorHelpers::FObjectFinder<UInputAction> MoveFinder(
        TEXT("/Game/Inputs/IA_Move.IA_Move"));
    if (MoveFinder.Succeeded())
    {
        IA_Move = MoveFinder.Object;
    }

    static ConstructorHelpers::FObjectFinder<UInputAction> JumpFinder(
        TEXT("/Game/Inputs/IA_Jump.IA_Jump"));
    if (JumpFinder.Succeeded())
    {
        IA_Jump = JumpFinder.Object;
    }

    static ConstructorHelpers::FObjectFinder<UInputAction> LookFinder(
        TEXT("/Game/Inputs/IA_Look.IA_Look"));
    if (LookFinder.Succeeded())
    {
        IA_Look = LookFinder.Object;
    }

    static ConstructorHelpers::FObjectFinder<UInputAction> SprintFinder(
        TEXT("/Game/Inputs/IA_Sprint.IA_Sprint"));
    if (SprintFinder.Succeeded())
    {
        IA_Sprint = SprintFinder.Object;

    }
   /* static ConstructorHelpers::FClassFinder<UUserWidget> HUDObj(
        TEXT("/Game/Blueprint/HUD/WBP_HUD"));
    if (HUDObj.Succeeded())
        {
        HUDWidgetClass = HUDObj.Class;
    }*/
       /* static ConstructorHelpers::FClassFinder<UUserWidget> MainMenuObj(
            TEXT("/Game/Blueprint/HUD/WBP_MainMenu"));
    if (MainMenuObj.Succeeded())
        {
        MainMenuWidgetClass = MainMenuObj.Class;
        }*/
}

void AMyPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
            LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
        {
            if (IMC_Default)
            {
                Subsystem->AddMappingContext(IMC_Default, 0);
            }
        }
    }
    FString CurrenMapName = GetWorld()->GetMapName();
    if (CurrenMapName.Contains("MenuLevel"))
    {
       
        ShowMainMenu(false);
    }
}

UUserWidget* AMyPlayerController::GetHUDWidget() const
{
    return HUDWidgetInstance;
}
void AMyPlayerController::ShowMainMenu(bool bIsRestart)
{
    if (HUDWidgetInstance)
    {
        HUDWidgetInstance->RemoveFromParent();
        HUDWidgetInstance=nullptr;
    }
    if (MainMenuWidgetInstance)
    {
        MainMenuWidgetInstance->RemoveFromParent();
        MainMenuWidgetInstance=nullptr;
    }
    if (MainMenuWidgetClass)
    {
        MainMenuWidgetInstance =
            CreateWidget<UUserWidget>(this, MainMenuWidgetClass);
        if (MainMenuWidgetInstance)
        {
          
            MainMenuWidgetInstance->AddToViewport();
            bShowMouseCursor = true;
            SetInputMode(FInputModeUIOnly());
        }
        if (UTextBlock* ButtonText = Cast<UTextBlock>(MainMenuWidgetInstance->GetWidgetFromName(TEXT("StartButtonText"))))
        {
            if (bIsRestart)
            {
                ButtonText->SetText(FText::FromString(TEXT("Restart")));
            }
            else
            {
                ButtonText->SetText(FText::FromString(TEXT("Start")));

            }
        }
    }
}
void AMyPlayerController::ShowGameHUD()
{
    if (HUDWidgetInstance)
    {
        HUDWidgetInstance->RemoveFromParent();
        HUDWidgetInstance = nullptr;
    }
    if (MainMenuWidgetInstance)
    {
        MainMenuWidgetInstance->RemoveFromParent();
        MainMenuWidgetInstance = nullptr;
    }
    if (HUDWidgetClass)
    {
        HUDWidgetInstance = CreateWidget<UUserWidget>(this, HUDWidgetClass);
        if (HUDWidgetInstance)
        {
            HUDWidgetInstance->AddToViewport();
            bShowMouseCursor = false;
            SetInputMode(FInputModeGameOnly());
        }
        AMyGameState *MyGameState =
            GetWorld() ? GetWorld()->GetGameState<AMyGameState>() : nullptr;
        if (MyGameState)
        {
            MyGameState->UpdateHUD();
        }
    }
}
void AMyPlayerController::StartGame()
{
    GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor :: Black,
                                     FString::Printf(TEXT("Here")));
    if (UMyGameInstance *MyGameInstance =
            Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(this)))
    {
        MyGameInstance->CurrentLevelIndex = 0;
       
    }
    UGameplayStatics::OpenLevel(GetWorld(),FName("BasicLevel"));
}