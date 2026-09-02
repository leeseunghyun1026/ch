#include "BaseItem.h"
#include "Components/SphereComponent.h"

ABaseItem::ABaseItem()
{
    PrimaryActorTick.bCanEverTick = true;

    SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
    SetRootComponent(SceneComp);

    SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
    SphereComp->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
    SphereComp->SetupAttachment(SceneComp);
    SphereComp->OnComponentBeginOverlap.AddDynamic(this,
                                                   &ABaseItem::OnItemOverlap);
    SphereComp->OnComponentEndOverlap.AddDynamic(this,
                                                 &ABaseItem::OnItemEndOverlap);

    StaticMeshComp =
        CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
    StaticMeshComp->SetupAttachment(SphereComp);
}

void ABaseItem::OnItemOverlap(UPrimitiveComponent* OverlappedComp,
                              AActor *OtherActor,
                              UPrimitiveComponent *OtherComp,
                              int32 OtherBodyIndex, bool bFromSweep,
                              const FHitResult &SweepResult)
{
    if (OtherActor && OtherActor->ActorHasTag("Player"))
    {
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan,
                                         FString::Printf(TEXT("Overlap")));
        ActivateItem(OtherActor);
    }
}

void ABaseItem::OnItemEndOverlap(UPrimitiveComponent* OverlappedComp,
                                 AActor* OtherActor,
                                 UPrimitiveComponent *OtherComp,
                                 int32 OtherBodyIndex)
{
}

void ABaseItem::ActivateItem(AActor *Activator)
{
}

FName ABaseItem::GetItemType() const
{
    return ItemType;
}

void ABaseItem::DestroyItem()
{
    Destroy();
}