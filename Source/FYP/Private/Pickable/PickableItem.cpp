// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickable/PickableItem.h"

#include "Components/BillboardComponent.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
APickableItem::APickableItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	PickUpIcon = CreateDefaultSubobject<UBillboardComponent>(TEXT("PickUpIcon"));
}

// Called when the game starts or when spawned
void APickableItem::BeginPlay()
{
	Super::BeginPlay();

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &APickableItem::OnOverlapBegin);
	SphereCollision->OnComponentEndOverlap.AddDynamic(this, &APickableItem::OnOverlapEnd);
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PickUpIcon->SetVisibility(false);
	UInputSettings::UInputSettings::GetInputSettings()->GetActionMappingByName("PickUp", ActionMapping);
	AActor* PlayerActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerActor)
	{
		Player = Cast<AMiraiKomachi>(PlayerActor);
	}
}

void APickableItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bIsPicked) return;
	if (!OtherActor->ActorHasTag("Player")) return;
	PickUpIcon->SetVisibility(true);
	bCanPick = true;
	
}

void APickableItem::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	if (bIsPicked) return;
	if (!OtherActor->ActorHasTag("Player")) return;
	PickUpIcon->SetVisibility(false);
	bCanPick = false;
} 

// Called every frame
void APickableItem::Tick(float DeltaTime)
{
	if (!bCanPick || !PlayerController) return;

	for (auto Action : ActionMapping)
	{
		if (PlayerController->WasInputKeyJustPressed(Action.Key))
		{
			GetPicked();
		}
	}
}

void APickableItem::GetPicked()
{
	bIsPicked = true;
	// Empty for now because inventory system is not implemented
}


