#pragma once

#include "CoreMinimal.h"
#include "C_HealthComponent.h"
#include "C_PlayerHealthComponent.generated.h"

/**
 * 
 */
UCLASS()
class KILLINGSTREAK_API UC_PlayerHealthComponent : public UC_HealthComponent
{
	GENERATED_BODY()

public:
	virtual void HealUp(float HealAmount) override;
	
};
