#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Vector"
#include "MyGameState.generated.h"

UCLASS()
class CH_API AMyGameState : public AGameState
{
	GENERATED_BODY()


	public:
    AMyGameState();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Score")
	int32 Score;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Score")
    int32 SpawnedCoinCount;
  

    std::vector<std::vector<float>> WaveTimeArray;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Score")
    TArray<FName> LevelMapNames;

    std::vector<std::vector<int32>> WaveScoreRequirement;

	FTimerHandle WaveTimerHandle;
    FTimerHandle HUDUpdateTimerHandle;
	UFUNCTION(BlueprintPure, Category = "Score")
	int32 GetScore() const;

    UFUNCTION(BlueprintCallable, Category = "Score")
    void AddScore(int32 Amount);

    UFUNCTION(BlueprintCallable, Category = "Level")
    void OnGameOver();

    void StartWave();
    void EndWave();
    void OnCoinCollected();
    void UpdateHUD();

    virtual void BeginPlay() override;
	

};
