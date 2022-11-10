// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ZL_HealthtComponent.h"

#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UZL_HealthtComponent::UZL_HealthtComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UZL_HealthtComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	OnHealthChanged.Broadcast(Health);

	AActor* ComponentOwner = GetOwner();

	if (ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UZL_HealthtComponent::OnAnyDamageHandler);
	}
}

void UZL_HealthtComponent::OnAnyDamageHandler(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f || isDeadh() || !GetWorld()) return;
	Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(Health);
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	
	if (isDeadh())
	{
		OnDeath.Broadcast();
	} else if (AutoHeal)
	{
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UZL_HealthtComponent::HealUpdate, DelayHeal, true, PauseHeal);
	}
	// LOG
	// FString LOGString = "Damage + " + FString::SanitizeFloat(Damage);
	// UKismetSystemLibrary::PrintString(GetWorld(), *LOGString, true, false, FLinearColor::Red, 1.0f);
}

void UZL_HealthtComponent::HealUpdate()
{
	Health = FMath::Min(Health + HealStep, MaxHealth);
	OnHealthChanged.Broadcast(Health);

	if (Health == MaxHealth && GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	}
}

