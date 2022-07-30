// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/ProjectileBase.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Hitbox"));
	RootComponent = HitBox;
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	HitBox->OnComponentBeginOverlap.AddDynamic(this, &AProjectileBase::HitBoxOnBeginOverlap);
	AActor* PlayerActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	Player = Cast<AMiraiKomachi>(PlayerActor);
	if (GetOwner())
	{
		Direction = GetOwner()->GetActorForwardVector().GetSafeNormal();
	}
	
}


// Called every frame
void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimeElapsed += DeltaTime;
	
	if (TimeElapsed > SurvivalTime)
		this->Destroy();

	const FVector LocalMove = Direction * DeltaTime * LaunchSpeed;

	AddActorLocalOffset(LocalMove, true);
	
}

void AProjectileBase::HitBoxOnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Weapon") || OtherActor->ActorHasTag("Player"))
	{
		if (Player->bIsGuarding)
			HandleGuarded();
		else
		{
			Player->ApplyDamage(Damage);
			this->Destroy();
		}
	}
	else if (OtherActor->ActorHasTag("Enemy"))
	{
		return;
	}
	this->Destroy();
}

void AProjectileBase::HandleGuarded()
{
	Direction = Player->GetActorForwardVector().GetSafeNormal();
	TimeElapsed = 0;
}
