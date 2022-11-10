// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ZL_HealthtComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ZOMBIELAND_API UZL_HealthtComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UZL_HealthtComponent();
	
	float GetHealth() const {return Health;}
	
	UFUNCTION(BlueprintCallable)
	bool isDeadh() const {return Health <= 0.0f;}

	FOnDeath OnDeath;
	FOnHealthChanged OnHealthChanged;
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float MaxHealth = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Heal")
	bool AutoHeal = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Heal")
	float DelayHeal = 0.2f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Heal")
	float PauseHeal = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Heal")
	float HealStep = 5.0f;

	FTimerHandle TimerHandle;
	
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	float Health = 0.0f;
	
	UFUNCTION()
	void OnAnyDamageHandler(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	void HealUpdate();
};
