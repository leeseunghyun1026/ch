#pragma once

#include "BaseItem.h"
#include "CoreMinimal.h"
#include "MineItem.generated.h"

UCLASS()
class CH_API AMineItem : public ABaseItem
{
    GENERATED_BODY()

  public:
    AMineItem();

    UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "MineItem")
    USphereComponent *ExplosionCollision;

    UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "MineItem")
    float ExplosionRadius;

    UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "MineItem")
    float ExplosionDamage;

    UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "MineItem")
    float ExplosionDelay;

    virtual void ActivateItem(AActor *Activator) override;

    FTimerHandle ExplosionTimerHandle;

    void Explode();
};
