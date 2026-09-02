#include "SpawnVolume.h"
#include "Components/BoxComponent.h"

ASpawnVolume::ASpawnVolume()
{
    PrimaryActorTick.bCanEverTick = true;

    SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
    SetRootComponent(SceneComp);

    SpawningBoxComp =
        CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningComp"));
    SpawningBoxComp->SetupAttachment(SceneComp);
}

FVector ASpawnVolume::GetRandomPointVolume() const
{
    FVector BoxExtent = SpawningBoxComp->GetScaledBoxExtent();
    FVector BoxOrigin = SpawningBoxComp->GetComponentLocation();

    return BoxOrigin + FVector(FMath::FRandRange(-BoxExtent.X, BoxExtent.X),
                               FMath::FRandRange(-BoxExtent.Y, BoxExtent.Y),
                               FMath::FRandRange(-BoxExtent.Z, BoxExtent.Z));
}

AActor* ASpawnVolume::SpawnItem(TSubclassOf<AActor> ItemClass)
{
    if (!ItemClass)
        return nullptr;

   AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ItemClass, GetRandomPointVolume(),
                                   FRotator::ZeroRotator);
    return SpawnedActor;
}

AActor* ASpawnVolume::SpawnRandomItem()
{
    if (FItemSpawnRow* SelectedRow = GetRandomItem())
    {
        if (UClass* ActualClass = SelectedRow->ItemClass.Get())
        {
            return SpawnItem(ActualClass);
        }
    }
    return nullptr;
}

FItemSpawnRow *ASpawnVolume::GetRandomItem() const
{
    if (!ItemTable)
        return nullptr;

    TArray<FItemSpawnRow *> AllRows;
    static const FString ContextString(TEXT("IteamSpawnContext"));
    ItemTable->GetAllRows(ContextString, AllRows);

    if (AllRows.IsEmpty())
        return nullptr;

    float TotalChance = 0.0f;
    for (const FItemSpawnRow *Row : AllRows)
    {
        if (Row)
        {
            TotalChance += Row->SpawnChance;
        }
    }

    const float RandValue = FMath::FRandRange(0.0f, TotalChance);
    float AccumlateChance = 0.0f;
    for (FItemSpawnRow *Row : AllRows)
    {
        AccumlateChance += Row->SpawnChance;
        if (RandValue <= AccumlateChance)
        {
            return Row;
        }
    }
    return nullptr;
}