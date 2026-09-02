#include "BigCoinItem.h"

ABigCoinItem::ABigCoinItem()
{
    PointValue = 100;
    ItemType = "BigCoinItem";
}

void ABigCoinItem::ActivateItem(AActor* Activator)
{
    Super::ActivateItem(Activator);
}