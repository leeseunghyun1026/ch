#include "CoinItem.h"
#include "MyGameState.h"

ACoinItem::ACoinItem()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACoinItem::ActivateItem(AActor *Activator)
{
    if (Activator && Activator->ActorHasTag("Player"))
    {
        if (UWorld *World = GetWorld())
        {
            if (AMyGameState *MyGameState =
                    World->GetGameState<AMyGameState>())
            {
                MyGameState->AddScore(PointValue);
                MyGameState->OnCoinCollected();
            }
        }
     }
            DestroyItem();
}

