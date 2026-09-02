#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "HealingItem.generated.h"

UCLASS()
class CH_API AHealingItem : public ABaseItem
{
	GENERATED_BODY()
	
public:
    AHealingItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HealingItem")
    float HealAmount;

	virtual void ActivateItem(AActor *Activator) override;

};
