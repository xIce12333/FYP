// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Komachi/MiraiKomachi.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AMiraiKomachi::AMiraiKomachi()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

/*	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false; */
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
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
//	UE_LOG(LogTemp, Warning, TEXT("IS FALLING: %s"), GetCharacterMovement()->IsFalling()? TEXT("true"): TEXT("false"));
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
	PlayerInputComponent->BindAction("Strafe", IE_Pressed, this, &AMiraiKomachi::ToggleStrafe);
}

void AMiraiKomachi::MoveForward(const float Axis)		
{
	FRotator Rotation = Controller->GetControlRotation();
	FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
	FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction, Axis);
	
}

void AMiraiKomachi::MoveRight(const float Axis)
{
	FRotator Rotation = Controller->GetControlRotation();
	FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
	FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(Direction, Axis);
}

void AMiraiKomachi::ToRunSpeed()
{
	if (!KomachiState.bIsStrafing)
		GetCharacterMovement()->MaxWalkSpeed = KomachiState.RunSpeed;
}

void AMiraiKomachi::ToWalkSpeed()
{
	if (!KomachiState.bIsStrafing)
		GetCharacterMovement()->MaxWalkSpeed = KomachiState.WalkSpeed;
}

void AMiraiKomachi::ToggleStrafe()
{
	GetCharacterMovement()->MaxWalkSpeed = KomachiState.StrafeSpeed;
	KomachiState.bIsStrafing = !KomachiState.bIsStrafing;
	bUseControllerRotationYaw = !bUseControllerRotationYaw;
	if (!KomachiState.bIsStrafing)
		ToWalkSpeed();
}


