#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

UCLASS()
class CH_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
	public:
    virtual void Init() override;

	UPROPERTY(BlueprintReadOnly, Category = "Level")
	int32 CurrentWaveIndex;

	UPROPERTY(BlueprintReadOnly, Category = "Level")
    int32 CurrentLevelIndex;

	UPROPERTY(BlueprintReadOnly, Category = "Level")
    int32 MaxWaves;
};
