// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Komachi/MiraiKomachi.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMiraiKomachi::AMiraiKomachi()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);

	Weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh(), "WeaponSocket");
}

// Called when the game starts or when spawned
void AMiraiKomachi::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = KomachiState.WalkSpeed;
	
}

// Called every frame
void AMiraiKomachi::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(KomachiState. bIsRolling)
	{
		GetCharacterMovement()->Velocity = KomachiState.RollVec * 800;
	}

	
}

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
}

void AMiraiKomachi::MoveForward(const float Axis)		
{
	if(!KomachiState.bCanMove) return;
	FRotator Rotation = Controller->GetControlRotation();
	FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
	FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction, Axis);
	
}

void AMiraiKomachi::MoveRight(const float Axis)
{
	if(!KomachiState.bCanMove) return;
	FRotator Rotation = Controller->GetControlRotation();
	FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
	FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(Direction, Axis);
}

void AMiraiKomachi::ToRunSpeed()
{
	if(!KomachiState.bCanMove) return;
	if (!KomachiState.bIsStrafing)
		GetCharacterMovement()->MaxWalkSpeed = KomachiState.RunSpeed;
}

void AMiraiKomachi::ToWalkSpeed()
{
	if(!KomachiState.bCanMove) return;
	if (!KomachiState.bIsStrafing)
		GetCharacterMovement()->MaxWalkSpeed = KomachiState.WalkSpeed;
}

void AMiraiKomachi::ToggleStrafe()
{
	GetCharacterMovement()->MaxWalkSpeed = KomachiState.StrafeSpeed;
	KomachiState.bIsStrafing = !KomachiState.bIsStrafing;
	if(KomachiState.bIsStrafing)
	{

	}
	if(!KomachiState.bCanMove) return;
	bUseControllerRotationYaw = !bUseControllerRotationYaw;
	if (!KomachiState.bIsStrafing)
		ToWalkSpeed();
	
}

void AMiraiKomachi::Roll()
{
	if(!KomachiState.bCanMove) return;
	PlayAnimMontage(KomachiState.M_Roll, 1.5);
}


