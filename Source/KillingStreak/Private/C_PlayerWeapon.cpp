#include "C_PlayerWeapon.h"

#include "C_FPSController.h"
#include "Components/AudioComponent.h"

AC_PlayerWeapon::AC_PlayerWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
	
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>("WeaponSM");
	WeaponMesh->SetupAttachment(GetRootComponent());

	ShootAudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("ShootSound"));
	ShootAudioComp->SetupAttachment(WeaponMesh);
	ReloadAudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("ReloadSound"));
	ReloadAudioComp->SetupAttachment(WeaponMesh);
}


void AC_PlayerWeapon::BeginPlay()
{
	Super::BeginPlay();
	ReloadGun();

	if (ShootSound)
	{
		ShootAudioComp->SetSound(ShootSound);
	}

	if (ReloadSound)
	{
		ReloadAudioComp->SetSound(ReloadSound);
	}
}

void AC_PlayerWeapon::ShootGun()
{
	if (CanShoot())
	{
		CurrentAmmo--;
		ShootRaycast();
		LastShotTime = GetWorld()->GetTimeSeconds();
		ShootAudioComp->Play();
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Blue, "Shooting");
		}
	}
}

void AC_PlayerWeapon::ReloadGun()
{
	if (CanReload())
	{
		CurrentAmmo = MaxAmmo;
		ReloadAudioComp->Play();
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(6, 5.f, FColor::Purple, "Reload");
		}
	}
}

void AC_PlayerWeapon::ShootRaycast()
{
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(GetOwner());
		
	FHitResult ShootHit;
	FVector StartShootRaycast = WeaponMesh->GetSocketLocation("Barrel");
	FVector ForwardDirection = WeaponMesh->GetSocketRotation("Barrel").Vector();
	FVector EndShootRaycast = (ForwardDirection * ShootRange) + StartShootRaycast;

	GetWorld()->LineTraceSingleByChannel(ShootHit, StartShootRaycast, EndShootRaycast, ECC_Pawn, Params);
	DrawDebugLine(GetWorld(), StartShootRaycast, EndShootRaycast, FColor::Blue, false, 3.f, 5, 5.f);
		
}


bool AC_PlayerWeapon::CanShoot()
{
	const double CurrentTime = GetWorld()->GetTimeSeconds();
	return CurrentAmmo > 0 && (LastShotTime == 0.0f || (CurrentTime - LastShotTime) >= TimeBtwShots);
}

bool AC_PlayerWeapon::CanReload()
{
	return CurrentAmmo < MaxAmmo;
}



