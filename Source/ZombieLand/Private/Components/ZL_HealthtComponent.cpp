// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ZL_HealthtComponent.h"

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

	AActor* ComponentOwner = GetOwner();

	if (ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UZL_HealthtComponent::OnAnyDamageHandler);
	}
}

void UZL_HealthtComponent::OnAnyDamageHandler(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	Health -= Damage;
}

