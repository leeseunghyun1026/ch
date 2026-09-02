#include "MyGameState.h"
#include "CoinItem.h"
#include "Kismet/GameplayStatics.h"
#include "MyGameInstance.h"
#include "SpawnVolume.h"
#include "MyPlayerController.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"

AMyGameState::AMyGameState()
{
    Score = 0;
    SpawnedCoinCount = 0;
    WaveTimeArray = {
        {18.0f, 22.0f, 25.0f}, {25.0f, 30.0f, 35.0f}, {35.0f, 40.0f, 45.0f}};
    WaveScoreRequirement = {{200, 300,400}, {500, 600, 700}, {800, 900, 1000}};
    LevelMapNames = {TEXT("IntermediateLevel"), TEXT("AdvancedLevel")};
}

int32 AMyGameState::GetScore() const
{
    return Score;
}

void AMyGameState::AddScore(int32 Amount)
{
    Score += Amount;
}

void AMyGameState::StartWave()
{
    if (APlayerController *PlayerController =
            GetWorld()->GetFirstPlayerController())
    {
        if (AMyPlayerController *MyPlayerController =
                Cast<AMyPlayerController>(PlayerController))
        {
            MyPlayerController->ShowGameHUD();
        }
    }


    SpawnedCoinCount = 0;
    Score = 0;

    TArray<AActor *> FoundVolumes;
    UGameplayStatics::GetAllActorsOfClass(
        GetWorld(), ASpawnVolume::StaticClass(), FoundVolumes);

    const int32 ItemToSpawn = 40;

    for (int32 i = 0; i < ItemToSpawn; i++)
    {
        if (FoundVolumes.Num() > 0)
        {
            if (ASpawnVolume *SpawnVolume = Cast<ASpawnVolume>(FoundVolumes[0]))
            {

                AActor *SpawnedActor = SpawnVolume->SpawnRandomItem();
                if (SpawnedActor && SpawnedActor->IsA(ACoinItem::StaticClass()))
                {
                    SpawnedCoinCount++;
                }
            }
        }
    }

    if (UMyGameInstance *MyGameInstance =
            GetWorld()->GetGameInstance<UMyGameInstance>())
    {
        GetWorld()->GetTimerManager().SetTimer(
            WaveTimerHandle, this, &AMyGameState::OnGameOver,
            WaveTimeArray[MyGameInstance->CurrentLevelIndex]
                         [MyGameInstance->CurrentWaveIndex],
            false);
        GEngine->AddOnScreenDebugMessage(
            -1, 5.0f, FColor::Magenta,
            FString::Printf(TEXT("%d레벨 %d번째 웨이브 시작!!"),
                            MyGameInstance->CurrentLevelIndex + 1,
                            MyGameInstance->CurrentWaveIndex + 1));
    }
}

void AMyGameState::EndWave()
{
    GetWorld()->GetTimerManager().ClearTimer(WaveTimerHandle);
    if (UMyGameInstance *MyGameInstance =
            GetWorld()->GetGameInstance<UMyGameInstance>())
    {
        MyGameInstance->CurrentWaveIndex++;
        if (MyGameInstance->CurrentWaveIndex >= MyGameInstance->MaxWaves)
        {
            MyGameInstance->CurrentWaveIndex = 0;
            if (LevelMapNames.IsValidIndex(MyGameInstance->CurrentLevelIndex))
            {
                const FName NextLevelName =
                    LevelMapNames[MyGameInstance->CurrentLevelIndex];
                MyGameInstance->CurrentLevelIndex++;
                UGameplayStatics::OpenLevel(GetWorld(),NextLevelName);
            }
            else
            {
                OnGameOver();
            }
        }
          else
        {
            StartWave();
        }
    }
}

void AMyGameState::OnCoinCollected()
{

    if (UMyGameInstance *MyGameInstance =
            GetWorld()->GetGameInstance<UMyGameInstance>())
    {
        if (Score >= WaveScoreRequirement[MyGameInstance->CurrentLevelIndex]
                                         [MyGameInstance->CurrentWaveIndex])
        {
            EndWave();
        }
    }
}
void AMyGameState::BeginPlay()
{
    Super::BeginPlay();
    UpdateHUD();
    StartWave();

    GetWorld()->GetTimerManager().SetTimer(
        HUDUpdateTimerHandle, this, &AMyGameState::UpdateHUD, 0.1f, true);
}

void AMyGameState::UpdateHUD()
{
    UMyGameInstance *MyGameInstance =
        GetWorld()->GetGameInstance<UMyGameInstance>();

    if (!MyGameInstance)
        return;

    APlayerController *PlayerController =
        GetWorld()->GetFirstPlayerController();
    if (!PlayerController)
        return;

    AMyPlayerController *MyPlayerController =
        Cast<AMyPlayerController>(PlayerController);
    if (!MyPlayerController)
        return;

    UUserWidget *HUDWidget = MyPlayerController->GetHUDWidget();
    if (!HUDWidget)
        return;

    float RemainingTIme =
        GetWorld()->GetTimerManager().GetTimerRemaining(WaveTimerHandle);

    if (UTextBlock* TimeText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("TimeValue"))))
    {
        TimeText->SetText(FText::FromString(
            FString::Printf(TEXT("Time: %.f"), RemainingTIme)));
    }

    if (UTextBlock *ScoreText =
            Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("ScoreValue"))))
    {
        ScoreText->SetText(FText::FromString(
            FString::Printf(TEXT("Score: %d"), Score)));
    }

    if (UTextBlock *LevelWaveText =
            Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("LevelWave"))))
    {
        LevelWaveText->SetText(FText::FromString(FString::Printf(
            TEXT("Level %d Wave %d"), MyGameInstance->CurrentLevelIndex+1,
            MyGameInstance->CurrentWaveIndex+1)));
    }
}



    void AMyGameState::OnGameOver()
{
        if (APlayerController *PlayerController =
                GetWorld()->GetFirstPlayerController())
        {
            if (AMyPlayerController *MyPlayerController =
                    Cast<AMyPlayerController>(PlayerController))
            {
                MyPlayerController->ShowMainMenu(true);
            }
        }
    }