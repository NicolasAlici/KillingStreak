#include "C_PlayerHealthComponent.h"

void UC_PlayerHealthComponent::HealUp(float HealAmount)
{
	if (CurrentHealth <= 0.0f || HealAmount <= 0.0f)
		return;

	CurrentHealth = FMath::Clamp(CurrentHealth + HealAmount, 0.0f, MaxHealth);
}