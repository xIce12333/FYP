// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Komachi/MiraiKomachi.h"

#include "EnemyBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMiraiKomachi::AMiraiKomachi()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CurrentHealth = MaxHealth;
	GetCharacterMovement()->bOrientRotationToMovement = true;
//	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);

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
//	PlayerInputComponent->BindAxis("Attack", this, &AMiraiKomachi::Attack);

	PlayerInputComponent->BindAction("ChangeMoveSpeed", IE_Pressed, this, &AMiraiKomachi::ToRunSpeed);
	PlayerInputComponent->BindAction("ChangeMoveSpeed", IE_Released, this, &AMiraiKomachi::ToWalkSpeed);
	PlayerInputComponent->BindAction("Roll", IE_Pressed, this, &AMiraiKomachi::Roll);
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
	if(!bCanMove) return;
	bUseControllerRotationYaw = !bUseControllerRotationYaw;
	if (!bTargetLocked)
		ToWalkSpeed();
}

void AMiraiKomachi::Roll()
{
	if(!bCanMove) return;
	PlayAnimMontage(M_Roll, 1.5);
}

#pragma endregion Input_and_Movement

#pragma region Attack
void AMiraiKomachi::Attack(FVector StickValue)
{

	if (!bCanAttack || !WeaponEquipped || StickValue.Size() < 0.5) return;

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

	for (auto It = M_Attack.CreateConstIterator(); It; ++It)
	{
		int Id = It.GetId().AsInteger();
		if (Id == 4)
			PlayAnimMontage(*It);
	}
}
#pragma endregion Attack

float AMiraiKomachi::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	CurrentHealth = FMath::Clamp(CurrentHealth - DamageAmount, 0.0f, MaxHealth);
	bCanMove = false;
	if (CurrentHealth <= 0)
		bIsDead = true;
	
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser); 
}

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
	if (bCanDealDamage)
	{
		AEnemyBase* Enemy = Cast<AEnemyBase>(OtherActor);
		if (Enemy)
		{
			bCanDealDamage = false;
			UE_LOG(LogTemp, Warning, TEXT("Hit!"));
			Enemy->ApplyDamage(WeaponEquipped->DamageAmount);
		}

	}
}

void AMiraiKomachi::ApplyDamage(float DamageAmount)
{
	if (bIsDead) return;
	CurrentHealth = FMath::Clamp(CurrentHealth - DamageAmount, 0.0f, MaxHealth);
	bCanMove = false;
	if (CurrentHealth <= 0)
	{
		bIsDead = true;
		if (GetCurrentMontage()) StopAnimMontage();
	}
	else
	{
		if (M_Hurt) PlayAnimMontage(M_Hurt);
	}
		
}
