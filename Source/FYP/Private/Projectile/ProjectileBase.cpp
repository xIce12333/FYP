// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/ProjectileBase.h"

#include "Character/BaseClass/EnemyBase.h"
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
			HandleGuarded();	// Player guard the attack
		else
		{
			const float MinDamage = Damage * 0.9;
			const float MaxDamage = Damage * 1.1;
			Player->ApplyDamage(static_cast<int>(FMath::RandRange(MinDamage, MaxDamage)));
			Destroy();
		}
	}
	else if (OtherActor->ActorHasTag("Enemy"))
	{
		if (OtherActor == GetOwner())
		{
			AEnemyBase* OwnerEnemy = Cast<AEnemyBase>(OtherActor);
			if (!OwnerEnemy) return;
			OwnerEnemy->HandleBeingGuarded(); // The projectile hits back the enemy
		}
		else
		{
			return;				// The projectile should pass through other enemy
		}
	}
	Destroy();
}

void AProjectileBase::HandleGuarded()
{
	Direction = Player->GetActorForwardVector().GetSafeNormal();
	TimeElapsed = 0;
}
