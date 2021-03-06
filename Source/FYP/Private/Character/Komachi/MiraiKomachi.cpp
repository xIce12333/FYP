// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Komachi/MiraiKomachi.h"
#include "Kismet/GameplayStatics.h"
#include "Pickable/Weapon.h"
#include "Character/BaseClass/EnemyBase.h"

// Sets default values
AMiraiKomachi::AMiraiKomachi()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	EnemyDetectionCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Enemy Detection Collider"));
	EnemyDetectionCollider->SetupAttachment(RootComponent);
	EnemyDetectionCollider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	EnemyDetectionCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn,
		ECollisionResponse::ECR_Overlap);
	EnemyDetectionCollider->SetSphereRadius(TargetLockDistance);
	Tags.Add("Player");
}

// Called when the game starts or when spawned
void AMiraiKomachi::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bCanAttack = true;
	bIsRolling = false;
	bIsGuarding = false;
	bCanGuard = true;
	bIsInvulnerable = false;
	bCanRoll = true;
	bCanPickItem = true;
	StopGuard();
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	EnemyDetectionCollider->OnComponentBeginOverlap.AddDynamic(this, &AMiraiKomachi::OnEnemyDetectionBeginOverlap);
	EnemyDetectionCollider->OnComponentEndOverlap.AddDynamic(this, &AMiraiKomachi::OnEnemyDetectionEndOverlap);
}

// Called every frame
void AMiraiKomachi::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

#pragma region Input_and_Movement
// Called to bind functionality to input
void AMiraiKomachi::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("CameraRight", this, &AMiraiKomachi::CameraRight);
	PlayerInputComponent->BindAxis("CameraUp", this, &AMiraiKomachi::CameraUp);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMiraiKomachi::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMiraiKomachi::MoveRight);
	
	PlayerInputComponent->BindAction("ChangeMoveSpeed", IE_Pressed, this, &AMiraiKomachi::ToRunSpeed);
	PlayerInputComponent->BindAction("ChangeMoveSpeed", IE_Released, this, &AMiraiKomachi::ToWalkSpeed);
	PlayerInputComponent->BindAction("Roll", IE_Pressed, this, &AMiraiKomachi::Roll);
	PlayerInputComponent->BindAction("Guard", IE_Pressed, this, &AMiraiKomachi::ToggleGuard);
	PlayerInputComponent->BindAction("Guard", IE_Released, this, &AMiraiKomachi::ToggleGuard);
	PlayerInputComponent->BindAction("Strafe", IE_Pressed, this, &AMiraiKomachi::ToggleStrafe);
	PlayerInputComponent->BindAction("CycleLeft", IE_Pressed, this, &AMiraiKomachi::CycleLeft);
	PlayerInputComponent->BindAction("CycleRight", IE_Pressed, this, &AMiraiKomachi::CycleRight);
	PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &AMiraiKomachi::SendPauseGame);
	
}


void AMiraiKomachi::MoveForward(const float Axis)		
{
	if(!bCanMove) return;
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction, Axis);
	
	
}

void AMiraiKomachi::MoveRight(const float Axis)
{
	if(!bCanMove) return;
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(Direction, Axis);
}

void AMiraiKomachi::ToRunSpeed()
{
	if(!bCanMove || bTargetLocked) return;
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}

void AMiraiKomachi::ToWalkSpeed()
{
	if(!bCanMove || bTargetLocked) return;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}


void AMiraiKomachi::ToggleStrafe()
{
	if (!WeaponEquipped) return;
	if (NearbyEnemies.Num() == 0)
	{
		TargetEnemy = nullptr;
		bTargetLocked = false;
		bUseControllerRotationYaw = false;
		return;
	}
	bTargetLocked = !bTargetLocked;
	bUseControllerRotationYaw = !bUseControllerRotationYaw;
	if (bTargetLocked)
	{
		GetCharacterMovement()->MaxWalkSpeed = StrafeSpeed;
		TargetEnemy = FindNearestEnemy();
		AEnemyBase* Enemy = Cast<AEnemyBase>(TargetEnemy);
		if (Enemy)
		{
			Enemy->SetCrosshair(true);
		}
	}
	else
	{
		AEnemyBase* Enemy = Cast<AEnemyBase>(TargetEnemy);
		if (Enemy)
		{
			Enemy->SetCrosshair(false);
		}
		ToWalkSpeed();
	}
	
}

AActor* AMiraiKomachi::FindNearestEnemy()
{
	AActor* SuitableTarget = nullptr;
	float NearestDistance = INFINITY;
	for(const auto& NearEnemy : NearbyEnemies)
	{
		const float Distance = FVector::Dist(GetActorLocation(), NearEnemy->GetActorLocation());
		if (Distance < NearestDistance)
		{
			NearestDistance = Distance;
			SuitableTarget = NearEnemy;
		}
	}
	return SuitableTarget;
}

void AMiraiKomachi::CycleLeft()
{
	if (!bTargetLocked) return;
	CycleEnemy(false);
}

void AMiraiKomachi::CycleRight()
{
	if (!bTargetLocked) return;
	CycleEnemy(true);
}

void AMiraiKomachi::CycleEnemy(bool bRight)
{
	if (!TargetEnemy) return;
	AActor* SuitableTarget = nullptr;
	const FVector CameraLocation = Cast<APlayerController>(GetController())->PlayerCameraManager->GetCameraLocation();

	const FRotator TargetDirection = (TargetEnemy->GetActorLocation() - CameraLocation).ToOrientationRotator();

	float BestYawDifference = INFINITY;

	for (const auto& NearEnemy : NearbyEnemies)
	{
		if (NearEnemy == TargetEnemy)
			continue;

		FVector NearEnemyDirection = NearEnemy->GetActorLocation() - CameraLocation;
		const FRotator Difference = UKismetMathLibrary::NormalizedDeltaRotator(NearEnemyDirection.ToOrientationRotator(), TargetDirection);

		if ((bRight && Difference.Yaw <= 0.0f) || (!bRight && Difference.Yaw >= 0.0f))
			continue;
		
		const float YawDifference = FMath::Abs(Difference.Yaw);
		if (YawDifference < BestYawDifference)
		{
			BestYawDifference = YawDifference;
			SuitableTarget = NearEnemy;
		}
	}

	if (!SuitableTarget) return;
	
	if (TargetEnemy == SuitableTarget) return;
	AEnemyBase* Enemy = Cast<AEnemyBase>(TargetEnemy);
	if (Enemy) Enemy->SetCrosshair(false);
	TargetEnemy = SuitableTarget;
	Enemy = Cast<AEnemyBase>(TargetEnemy);
	if (Enemy) Enemy->SetCrosshair(true);
}

void AMiraiKomachi::CameraRight(const float Axis)
{
	if (bTargetLocked) return;
	AddControllerYawInput(Axis * 0.5);
}

void AMiraiKomachi::CameraUp(const float Axis)
{
	if (bTargetLocked) return;
	AddControllerPitchInput(Axis * 0.5);
}


void AMiraiKomachi::ToggleGuard()
{
	bGuardPressed = !bGuardPressed;
}

void AMiraiKomachi::Roll()
{
	if(!bCanRoll || !bCanMove) return;
	PlayAnimMontage(M_Roll, 1.5);
}

#pragma endregion Input_and_Movement

#pragma region Attack
void AMiraiKomachi::Attack(FVector StickValue)
{
	if (!bCanAttack || !WeaponEquipped || !bTargetLocked ||StickValue.Size() < 0.5) return;
	StickValue = StickValue.GetSafeNormal(); // Normalize magnitude to 1
	StickValue.Y = -StickValue.Y;		// original y-axis is -1 when pointing upward 
	float Angle = UKismetMathLibrary::Acos(FVector::DotProduct(StickValue, FVector(1, 0, 0)));
	Angle = Angle * 180 / PI;		// radian to degree
	if (StickValue.Y > 0)		// 1st or 2nd quadrant
		{
		if (Angle <= 22.5)	MeleeE();
		else if (Angle <= 67.5)	MeleeNE();
		else if (Angle <= 112.5) MeleeN();
		else if (Angle <= 157.5) MeleeNW();
		else MeleeW();
		}
	else                // 3rd or 4th quadrant
		{
		if (Angle <= 22.5)	MeleeE();
		else if (Angle <= 67.5)	MeleeSE();
		else if (Angle <= 112.5) MeleeS();
		else if (Angle <= 157.5) MeleeSW();
		else MeleeW();
		}
}

void AMiraiKomachi::MeleeN()
{
	UE_LOG(LogTemp, Warning, TEXT("N"));
	
}

void AMiraiKomachi::MeleeE()
{
	UE_LOG(LogTemp, Warning, TEXT("E"));

	if (bGuardPressed && M_GuardRight)
	{
		bGuardE = true;
		PlayAnimMontage(M_GuardRight);
	}
	else if (bCanAttack && M_MeleeE)
	{
		PlayAnimMontage(M_MeleeE);
	}
}

void AMiraiKomachi::MeleeS()
{
	UE_LOG(LogTemp, Warning, TEXT("S"));
}

void AMiraiKomachi::MeleeW()
{
	UE_LOG(LogTemp, Warning, TEXT("W"));

	if (bGuardPressed && M_GuardLeft)
	{
		bGuardW = true;
		PlayAnimMontage(M_GuardLeft);
	}
	else if (bCanAttack && M_MeleeW)
	{
		PlayAnimMontage(M_MeleeW);
	}

}

void AMiraiKomachi::MeleeNE()
{
	UE_LOG(LogTemp, Warning, TEXT("NE"));

	if (bGuardPressed && M_GuardRight)
	{
		bGuardNE = true;
		PlayAnimMontage(M_GuardRight);
	}
	else if (bCanAttack && M_MeleeNE)
	{
		PlayAnimMontage(M_MeleeNE);
	}

}

void AMiraiKomachi::MeleeNW()
{
	UE_LOG(LogTemp, Warning, TEXT("NW"));

	if (bGuardPressed && M_GuardLeft)
	{
		bGuardNW = true;
		PlayAnimMontage(M_GuardLeft);
	}
	else if (bCanAttack && M_MeleeNW)
	{
		PlayAnimMontage(M_MeleeNW);
	}
}

void AMiraiKomachi::MeleeSE()
{
	UE_LOG(LogTemp, Warning, TEXT("SE"));

	if (bGuardPressed && M_GuardRight)
	{
		bGuardSE = true;
		PlayAnimMontage(M_GuardRight);
	}
	else if (bCanAttack && M_MeleeSE)
	{
		PlayAnimMontage(M_MeleeSE);
	}

}

void AMiraiKomachi::MeleeSW()
{
	UE_LOG(LogTemp, Warning, TEXT("SW"));

	if (bGuardPressed && M_GuardLeft)
	{
		bGuardSW = true;
		PlayAnimMontage(M_GuardLeft);
	}
	else if (bCanAttack && M_MeleeSW)
	{
		PlayAnimMontage(M_MeleeSW);
	}
}

void AMiraiKomachi::OnEnemyDetectionBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AEnemyBase>(OtherActor) && !NearbyEnemies.Contains(OtherActor))
	{
		NearbyEnemies.Add(OtherActor);
	}
		
}

void AMiraiKomachi::OnEnemyDetectionEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<AEnemyBase>(OtherActor) && NearbyEnemies.Contains(OtherActor))
	{
		NearbyEnemies.Remove(OtherActor);
		if (NearbyEnemies.Num() == 0)
			ToggleStrafe();
	}
	
}

#pragma endregion Attack

void AMiraiKomachi::PickUpItem()
{
	if (!ItemPicking) return;
	ItemPicking->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, 
		TEXT("WeaponSocketBottom"));

	if (WeaponEquipped) return;
	AWeapon* Weapon = Cast<AWeapon>(ItemPicking);
	if (!Weapon) return;
	WeaponEquipped = Weapon;
	WeaponEquipped->AttackHitBox->OnComponentBeginOverlap.AddDynamic(this, &AMiraiKomachi::WeaponHitBoxOnBeginOverlap);
	ItemPicking = nullptr;
}

void AMiraiKomachi::WeaponHitBoxOnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AEnemyBase* Enemy = Cast<AEnemyBase>(OtherActor);
	if (Enemy && !HitEnemies.Contains(OtherActor) && bCanDealDamage)
	{
		HitEnemies.Add(OtherActor);
		const float MinDamage = WeaponEquipped->DamageAmount * 0.9;
		const float MaxDamage = WeaponEquipped->DamageAmount * 1.1;
		Enemy->ApplyDamage(static_cast<int>(FMath::RandRange(MinDamage, MaxDamage)));
	}

}

void AMiraiKomachi::ApplyDamage(float DamageAmount)
{
	if (bIsDead || bIsInvulnerable) return;
	bCanMove = false;
	CurrentHealth = FMath::Clamp(CurrentHealth - DamageAmount, 0.0f, MaxHealth);
	CurrentDamage = DamageAmount;
	GenerateDamageText();
	if (CurrentHealth <= 0)
	{
		bIsDead = true;
		if (GetCurrentMontage()) StopAnimMontage();
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		this->DisableInput(PlayerController);
	}
	else
	{
		if (GetCurrentMontage()) StopAnimMontage();
		if (M_Hurt) PlayAnimMontage(M_Hurt);
	}
		
}

void AMiraiKomachi::StopGuard()
{
	bGuardE = false;
	bGuardW = false;
	bGuardNE = false;
	bGuardNW = false;
	bGuardSE = false;
	bGuardSW = false;
}


bool AMiraiKomachi::CheckGuardSuccessful(const AEnemyBase* Enemy) const
{
	if (!bIsGuarding) return false;
	if (Enemy->MeleeE && bGuardE) return true;
	else if (Enemy->MeleeW && bGuardW) return true;
	else if (Enemy->MeleeNE && bGuardSE) return true;
	else if (Enemy->MeleeNW && bGuardSW) return true;
	else if (Enemy->MeleeSE && bGuardNE) return true;
	else if (Enemy->MeleeSW && bGuardNW) return true;
	return false;
}

void AMiraiKomachi::GuardSuccessful()
{
	if (bGuardE || bGuardNE || bGuardSE)
		PlayAnimMontage(M_GuardRightSuccessful);
	else if (bGuardW || bGuardNW || bGuardSW)
		PlayAnimMontage(M_GuardLeftSuccessful);
	CameraShake();
}
