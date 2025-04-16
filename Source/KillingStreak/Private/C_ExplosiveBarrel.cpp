#include "C_ExplosiveBarrel.h"
#include "Components/BoxComponent.h"
#include "C_HealthComponent.h"

AC_ExplosiveBarrel::AC_ExplosiveBarrel()
{
	PrimaryActorTick.bCanEverTick = true;

	ExplosiveBarrelMesh = CreateDefaultSubobject<UStaticMeshComponent>("BarrelMesh");
	ExplosiveBarrelMesh->SetupAttachment(GetRootComponent());
	BarrelCollider = CreateDefaultSubobject<UBoxComponent>(" BarrelCollider");
	BarrelCollider->SetupAttachment(GetRootComponent());
	BarrelHealth = CreateDefaultSubobject<UC_HealthComponent>("BarrelHealth");
}

void AC_ExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
}

