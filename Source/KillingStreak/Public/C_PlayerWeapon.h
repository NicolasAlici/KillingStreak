#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_PlayerWeapon.generated.h"

UCLASS()
class KILLINGSTREAK_API AC_PlayerWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AC_PlayerWeapon();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponVars")
	int32 MaxAmmo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponVars")
	double ShootRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponVars")
	double TimeBtwShots;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponVars")
	double DamageAmount;

	UPROPERTY(EditAnywhere, Category = "WeaponSounds")
	USoundBase* ShootSound;
	UPROPERTY(EditAnywhere, Category = "WeaponSounds")
	USoundBase* ReloadSound;
	
	UFUNCTION(BlueprintCallable, Category  = "WeaponFuncs")
	void ShootGun();
	UFUNCTION(BlueprintCallable, Category  = "WeaponFuncs")
	void ReloadGun();
	
private:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* WeaponMesh;
	
protected:
	virtual void BeginPlay() override;

	int32 CurrentAmmo;
	double LastShotTime;
	FTimerHandle DelaytBtwShots;

	UAudioComponent* ShootAudioComp;
	UAudioComponent* ReloadAudioComp;
	
	bool CanShoot();
	bool CanReload();

	void ShootRaycast();
};
