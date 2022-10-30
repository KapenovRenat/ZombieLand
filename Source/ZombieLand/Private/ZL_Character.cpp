// Fill out your copyright notice in the Description page of Project Settings.


#include "ZL_Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AZL_Character::AZL_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));

	//Attach the Spring Arm to the Character's Skeletal Mesh Component
	SpringArmComp->SetupAttachment(GetRootComponent()); 

	//Attach the Camera to the SpringArmComponent
	MainCamera->SetupAttachment(SpringArmComp);

	//Setting default properties of the SpringArmComp
	SpringArmComp->bUsePawnControlRotation = false;
	SpringArmComp->bEnableCameraLag = false;
	SpringArmComp->TargetArmLength = 500.0f;
}

float AZL_Character::GetMovementDirection() const
{
	const auto VelocityNormal = GetVelocity().GetSafeNormal();
	const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
	const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);

	return FMath::RadiansToDegrees(AngleBetween) * FMath::Sign(CrossProduct.Z);
}

// Called when the game starts or when spawned
void AZL_Character::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AZL_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RotateForMouse(DeltaTime);
}

// Called to bind functionality to input
void AZL_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("Move", this, &AZL_Character::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AZL_Character::MoveRight);
	InputComponent->BindAxis("MouseX", this, &AZL_Character::TurnArround);
	InputComponent->BindAxis("MouseY", this, &AZL_Character::LookUp);
	InputComponent->BindAction("Jump", IE_Pressed, this, &AZL_Character::Jump);
}

void AZL_Character::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector(), AxisValue);
}

void AZL_Character::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector(), AxisValue);
}

void AZL_Character::LookUp(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}

void AZL_Character::TurnArround(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

void AZL_Character::RotateForMouse(float deltaTime)
{
	FVector MouseLocation, MouseDirection;
	GetWorld()->GetFirstPlayerController()->DeprojectMousePositionToWorld(MouseLocation, MouseDirection);
	float ArmLength = SpringArmComp->TargetArmLength + 2000.0f;
	FVector MultiplayDirectionAndArmLength = MouseDirection * ArmLength;
	FVector LineTraceEnd = MultiplayDirectionAndArmLength + MouseLocation;
	FHitResult OutHit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	
	if (GetWorld()->LineTraceSingleByChannel(OutHit, MouseLocation, LineTraceEnd, ECollisionChannel::ECC_Visibility, Params, FCollisionResponseParams::DefaultResponseParam))
	{
		FRotator PlayerRot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), OutHit.Location);
		// FRotator InterpRot = FMath::RInterpTo(GetActorRotation(), PlayerRot, deltaTime, RotateSpeedInterp);
		FRotator NewPlayerRot = FRotator::ZeroRotator;
		NewPlayerRot.Roll = GetActorRotation().Roll;
		NewPlayerRot.Pitch = GetActorRotation().Pitch;
		NewPlayerRot.Yaw = PlayerRot.Yaw;

		// FString HealthStr = "Yaw = " + FString::SanitizeFloat(InterpRot.Yaw) + " Pitch = " + FString::SanitizeFloat(InterpRot.Pitch) + " Roll = " + FString::SanitizeFloat(InterpRot.Roll);
		// UKismetSystemLibrary::PrintString(GetWorld(), HealthStr, true, false, FLinearColor::Red, 1.0f);
		
		SetActorRotation(NewPlayerRot, ETeleportType::None);
		DrawDebugLine(GetWorld(), MouseLocation, LineTraceEnd, FColor::Red, true, 5.0f, 0, 0.0f);
	}
}

