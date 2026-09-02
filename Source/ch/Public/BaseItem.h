#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemInterface.h"
#include "BaseItem.generated.h"


class USphereComponent;

UCLASS()
class CH_API ABaseItem : public AActor, public IItemInterface
{
    GENERATED_BODY()

  public:
    ABaseItem();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FName ItemType;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
    USceneComponent *SceneComp;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
    USphereComponent *SphereComp;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
    UStaticMeshComponent *StaticMeshComp;
    virtual void OnItemOverlap(UPrimitiveComponent *OverlappedComp,
                               AActor *OtherActor,
                               UPrimitiveComponent *OtherComp,
                               int32 OtherBodyIndex, bool bFromSweep,
                               const FHitResult &SweepResult) override;
    virtual void OnItemEndOverlap(UPrimitiveComponent *OverlappedComp,
                                  AActor *OtherActor,
                                  UPrimitiveComponent *OtherComp,
                                  int32 OtherBodyIndex) override;
    virtual void ActivateItem(AActor *Activator) override;
    virtual FName GetItemType() const override;
    virtual void DestroyItem();
};
