#include "MineItem.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
AMineItem::AMineItem()
{
    ExplosionRadius = 200.0f;
    ExplosionDamage = 50;
    ExplosionDelay = 1.0f;
    ItemType = "MineItem";

    ExplosionCollision =
        CreateDefaultSubobject<USphereComponent>(TEXT("ExplosionCollision"));
    ExplosionCollision->InitSphereRadius(ExplosionRadius);
    ExplosionCollision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
    ExplosionCollision->SetupAttachment(SceneComp);
}

void AMineItem::ActivateItem(AActor* Activator)
{
    GetWorld()->GetTimerManager().SetTimer(ExplosionTimerHandle, this,
                                           &AMineItem::Explode, ExplosionDelay);
}

void AMineItem::Explode()
{
    TArray<AActor *> OverlappingActors;
    ExplosionCollision->GetOverlappingActors(OverlappingActors);

    for (AActor *Actor : OverlappingActors)
        if (Actor && Actor->ActorHasTag("Player"))
        {
            UGameplayStatics ::ApplyDamage(Actor, ExplosionDamage, nullptr,
                                           this, UDamageType::StaticClass());
        }
    DestroyItem();
}