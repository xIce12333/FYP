// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Komachi/MiraiKomachi.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMiraiKomachi::AMiraiKomachi()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CurrentHealth = MaxHealth;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bCanAttack = true;
	bIsRolling = false;
	bIsGuarding = false;
	bCanGuard = true;
	bIsInvulnerable = false;
	bCanRoll = true;
	StopGuard();
}

// Called when the game starts or when spawned
void AMiraiKomachi::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	
}

// Called every frame
void AMiraiKomachi::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if(bIsRolling)
	{
		GetCharacterMovement()->Velocity = RollVec * 600;
	}
}

#pragma region Input_and_Movement
// Called to bind functionality to input
void AMiraiKomachi::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMiraiKomachi::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMiraiKomachi::MoveRight);

	PlayerInputComponent->BindAction("ChangeMoveSpeed", IE_Pressed, this, &AMiraiKomachi::ToRunSpeed);
	PlayerInputComponent->BindAction("ChangeMoveSpeed", IE_Released, this, &AMiraiKomachi::ToWalkSpeed);
	PlayerInputComponent->BindAction("Roll", IE_Pressed, this, &AMiraiKomachi::Roll);
	PlayerInputComponent->BindAction("Guard", IE_Pressed, this, &AMiraiKomachi::ToggleGuard);
	PlayerInputComponent->BindAction("Guard", IE_Released, this, &AMiraiKomachi::ToggleGuard);
	
}


void AMiraiKomachi::MoveForward(const float Axis)		
{
	if(!bCanMove) return;
	FRotator Rotation = Controller->GetControlRotation();
	FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
	FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction, Axis);
	
}

void AMiraiKomachi::MoveRight(const float Axis)
{
	if(!bCanMove) return;
	FRotator Rotation = Controller->GetControlRotation();
	FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
	FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(Direction, Axis);
}

void AMiraiKomachi::ToRunSpeed()
{
	if(!bCanMove) return;
	if (!bTargetLocked)
		GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}

void AMiraiKomachi::ToWalkSpeed()
{
	if(!bCanMove) return;
	if (!bTargetLocked)
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}


void AMiraiKomachi::ToggleStrafe()
{
	GetCharacterMovement()->MaxWalkSpeed = StrafeSpeed;
	bTargetLocked = !bTargetLocked;
	bUseControllerRotationYaw = !bUseControllerRotationYaw;
	if (!bTargetLocked)
		ToWalkSpeed();
}

void AMiraiKomachi::ToggleGuard()
{
	bGuardPressed = !bGuardPressed;
}

void AMiraiKomachi::Roll()
{
	if(!bCanRoll) return;
	PlayAnimMontage(M_Roll, 1.5);
}

#pragma endregion Input_and_Movement

#pragma region Attack
void AMiraiKomachi::Attack(FVector StickValue)
{
	if (!bCanAttack || !WeaponEquipped ||StickValue.Size() < 0.5) return;
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

	if (bGuardPressed && M_Guard)
	{
		bGuardE = true;
		PlayAnimMontage(M_Guard);
		return;
	}
	if (!bCanAttack) return;
	for (auto It = M_Attack.CreateConstIterator(); It; ++It)
	{
		int Id = It.GetId().AsInteger();
		if (Id == 0)
			PlayAnimMontage(*It);
	}
}

void AMiraiKomachi::MeleeS()
{
	UE_LOG(LogTemp, Warning, TEXT("S"));
}

void AMiraiKomachi::MeleeW()
{
	UE_LOG(LogTemp, Warning, TEXT("W"));

	if (bGuardPressed && M_Guard)
	{
		bGuardW = true;
		PlayAnimMontage(M_Guard);
		return;
	}
	if (!bCanAttack) return;
	for (auto It = M_Attack.CreateConstIterator(); It; ++It)
	{
		int Id = It.GetId().AsInteger();
		if (Id == 5)
			PlayAnimMontage(*It);
	}
}

void AMiraiKomachi::MeleeNE()
{
	UE_LOG(LogTemp, Warning, TEXT("NE"));

	if (bGuardPressed && M_Guard)
	{
		bGuardNE = true;
		PlayAnimMontage(M_Guard);
		return;
	}
	if (!bCanAttack) return;
	for (auto It = M_Attack.CreateConstIterator(); It; ++It)
	{
		int Id = It.GetId().AsInteger();
		if (Id == 1)
			PlayAnimMontage(*It);
	}
}

void AMiraiKomachi::MeleeNW()
{
	UE_LOG(LogTemp, Warning, TEXT("NW"));

	if (bGuardPressed && M_Guard)
	{
		bGuardNW = true;
		PlayAnimMontage(M_Guard);
		return;
	}
	if (!bCanAttack) return;
	for (auto It = M_Attack.CreateConstIterator(); It; ++It)
	{
		int Id = It.GetId().AsInteger();
		if (Id == 2)
			PlayAnimMontage(*It);
	}
}

void AMiraiKomachi::MeleeSE()
{
	UE_LOG(LogTemp, Warning, TEXT("SE"));

	if (bGuardPressed && M_Guard)
	{
		bGuardSE = true;
		PlayAnimMontage(M_Guard);
		return;
	}
	if (!bCanAttack) return;
	for (auto It = M_Attack.CreateConstIterator(); It; ++It)
	{
		int Id = It.GetId().AsInteger();
		if (Id == 3)
			PlayAnimMontage(*It);
	}
}

void AMiraiKomachi::MeleeSW()
{
	UE_LOG(LogTemp, Warning, TEXT("SW"));

	if (bGuardPressed && M_Guard)
	{
		bGuardSW = true;
		PlayAnimMontage(M_Guard);
		return;
	}
	if (!bCanAttack) return;
	for (auto It = M_Attack.CreateConstIterator(); It; ++It)
	{
		int Id = It.GetId().AsInteger();
		if (Id == 4)
			PlayAnimMontage(*It);
	}
}

#pragma endregion Attack

void AMiraiKomachi::EquipWeapon(AWeapon* Weapon)
{
	if (WeaponEquipped) return;

	Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, 
		TEXT("WeaponSocketBottom"));

	WeaponEquipped = Weapon;
	WeaponEquipped->AttackHitBox->OnComponentBeginOverlap.AddDynamic(this, &AMiraiKomachi::WeaponHitBoxOnBeginOverlap);
}

void AMiraiKomachi::WeaponHitBoxOnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AEnemyBase* Enemy = Cast<AEnemyBase>(OtherActor);
	if (bCanDealDamage)
	{
		if (Enemy)
		{
			bCanDealDamage = false;
			const float MinDamage = WeaponEquipped->DamageAmount * 0.9;
			const float MaxDamage = WeaponEquipped->DamageAmount * 1.1;
			Enemy->ApplyDamage(static_cast<int>(FMath::RandRange(MinDamage, MaxDamage)));
		}
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
	if (M_GuardSuccessful)
		PlayAnimMontage(M_GuardSuccessful);
}
