#include "MyGameInstance.h"

void UMyGameInstance :: Init()
{
    Super::Init();

    CurrentWaveIndex = 0;
    CurrentLevelIndex = 0;
    MaxWaves = 3;
}