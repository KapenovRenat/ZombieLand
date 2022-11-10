// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/ZL_HealthtComponent.h"
#include "GameFramework/Character.h"
#include "Weapon/ZLWeapon.h"
#include "ZL_Character.generated.h"

class AZLWeapon;

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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UZL_HealthtComponent* HealthComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UTextRenderComponent* HealthTextComponent;

	UFUNCTION(BlueprintCallable, Category="Movement")
	float GetMovementDirection() const;

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	TSubclassOf<AZLWeapon> WeaponClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category="Animation")
	UAnimMontage* DeathAnim;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUp(float AxisValue);
	void TurnArround(float AxisValue);
	void RotateForMouse(float DeltaTime);
	void OnDeath();
	void OnHealthChanged(float Health);
	void SpawnWeapon();
};
