#include "C_LaunchPad.h"

AC_LaunchPad::AC_LaunchPad()
{
	PrimaryActorTick.bCanEverTick = true;

	LaunchPadMesh = CreateDefaultSubobject<UStaticMeshComponent>("LaunchPadMesh");
	LaunchPadMesh->SetupAttachment(GetRootComponent());
}


void AC_LaunchPad::BeginPlay()
{
	Super::BeginPlay();
	
}


