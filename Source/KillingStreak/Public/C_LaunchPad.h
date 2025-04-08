#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_LaunchPad.generated.h"

UCLASS()
class KILLINGSTREAK_API AC_LaunchPad : public AActor
{
	GENERATED_BODY()
	
public:	
	AC_LaunchPad();

private:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* LaunchPadMesh;
	
protected:
	virtual void BeginPlay() override;
};
