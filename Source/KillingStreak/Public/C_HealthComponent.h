#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "C_HealthComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KILLINGSTREAK_API UC_HealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UC_HealthComponent();

	UFUNCTION(BlueprintCallable, Category="Health")
	virtual void TakeDamage(float DamageAmount);
	UFUNCTION(BlueprintCallable, Category="Health")
	virtual void Die();
	UFUNCTION(BlueprintCallable, Category="Health")
	double GetHealth() const {return CurrentHealth;}
	UFUNCTION(BlueprintCallable, Category="Health")
	virtual void HealUp(float HealAmount);
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	double MaxHealth;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	double CurrentHealth;
};
