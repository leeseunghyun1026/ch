#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemSpawnRow.h"
#include "SpawnVolume.generated.h"


class UBoxComponent;
UCLASS()
class CH_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpawnVolume();
  UFUNCTION()
  FVector GetRandomPointVolume() const;

  UFUNCTION()
  AActor* SpawnItem(TSubclassOf<AActor> ItemClass);
  FItemSpawnRow *GetRandomItem() const;
  AActor *SpawnRandomItem();

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Spawn")
    USceneComponent *SceneComp;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawn")
    UBoxComponent *SpawningBoxComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
    UDataTable * ItemTable;
};
