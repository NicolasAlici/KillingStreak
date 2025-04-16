#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_ExplosiveBarrel.generated.h"

class UC_HealthComponent;
class UBoxComponent;

UCLASS()
class KILLINGSTREAK_API AC_ExplosiveBarrel : public AActor
{
	GENERATED_BODY()
	
public:	
	AC_ExplosiveBarrel();

private:
	UPROPERTY(EditANywhere)
	UStaticMeshComponent* ExplosiveBarrelMesh;
	UPROPERTY(VisibleAnywhere)
	UC_HealthComponent* BarrelHealth;
	UPROPERTY(EditAnywhere)
	UBoxComponent* BarrelCollider;
	
protected:
	virtual void BeginPlay() override;
};
