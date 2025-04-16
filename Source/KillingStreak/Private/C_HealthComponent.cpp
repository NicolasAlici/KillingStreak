#include "C_HealthComponent.h"

UC_HealthComponent::UC_HealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UC_HealthComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
}

void UC_HealthComponent::TakeDamage(float DamageAmount)
{
	if (DamageAmount <= 0.0f || CurrentHealth <= 0.0f)
		return;

	CurrentHealth = FMath::Clamp(CurrentHealth - DamageAmount, 0.0f, MaxHealth);

	if (CurrentHealth <= 0.0f)
	{
		Die();
	}
}

void UC_HealthComponent::Die()
{
	if (AActor* Owner = GetOwner())
	{
		Owner->Destroy();
	}
}

void UC_HealthComponent::HealUp(float HealAmount)
{
	//Only for player
}


