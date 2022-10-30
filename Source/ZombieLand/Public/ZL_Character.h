// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "ZL_Character.generated.h"

UCLASS()
class ZOMBIELAND_API AZL_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AZL_Character();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* MainCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USpringArmComponent* SpringArmComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpeedMove = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RotateSpeedInterp = 1.0f;

	UFUNCTION(BlueprintCallable, Category="Movement")
	float GetMovementDirection() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUp(float AxisValue);
	void TurnArround(float AxisValue);
	void RotateForMouse(float deltaTime);
};