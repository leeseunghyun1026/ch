#pragma once

#include "CoinItem.h"
#include "CoreMinimal.h"
#include "SmallCoinItem.generated.h"
UCLASS()
class CH_API ASmallCoinItem : public ACoinItem
{
    GENERATED_BODY()
    ASmallCoinItem();

    virtual void ActivateItem(AActor *Activator) override;
};
