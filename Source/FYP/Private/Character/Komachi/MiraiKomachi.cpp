// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Komachi/MiraiKomachi.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AMiraiKomachi::AMiraiKomachi()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
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
	AdjustMovementSpeed();
}

// Called to bind functionality to input
void AMiraiKomachi::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMiraiKomachi::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMiraiKomachi::MoveRight);
}

void AMiraiKomachi::MoveForward(float Axis)
{
	FRotator Rotation = Controller->GetControlRotation();
	FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
	FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction, Axis);
	
}

void AMiraiKomachi::MoveRight(float Axis)
{
	FRotator Rotation = Controller->GetControlRotation();
	FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
	FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(Direction, Axis);
}

void AMiraiKomachi::AdjustMovementSpeed()
{
	FKey Key = "K";
	bool pressed = UGameplayStatics::GetPlayerController(GetWorld(), 0)->WasInputKeyJustPressed(Key);
	bool released = UGameplayStatics::GetPlayerController(GetWorld(), 0)->WasInputKeyJustReleased(Key);
	if (pressed)
		GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
	else if (released)
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
//	UE_LOG(LogTemp, Warning, TEXT("speed: %f"), GetCharacterMovement()->MaxWalkSpeed);
	
}

