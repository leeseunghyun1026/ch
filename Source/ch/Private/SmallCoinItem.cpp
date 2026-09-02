
#include "SmallCoinItem.h"

ASmallCoinItem::ASmallCoinItem()
{
    PointValue = 10;
    ItemType = "SmallCoinItem";
}

void ASmallCoinItem::ActivateItem(AActor *Activator)
{
    Super::ActivateItem(Activator);
}