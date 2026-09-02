#include "HealingItem.h"
#include "MyCharacter.h"
AHealingItem::AHealingItem()
{
	HealAmount = 30;
    ItemType = "HealingItem";
}

void AHealingItem::ActivateItem(AActor* Activator)
{
    if (Activator && Activator->ActorHasTag("Player"))
    {

        if (AMyCharacter* MyCharacter = Cast<AMyCharacter>(Activator))
        {
            MyCharacter->AddHealth(HealAmount);
        }
        DestroyItem();
    }
}