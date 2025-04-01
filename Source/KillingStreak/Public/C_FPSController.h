#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "C_FPSController.generated.h"

/**
 * 
 */
UCLASS()
class KILLINGSTREAK_API AC_FPSController : public APlayerController
{
	GENERATED_BODY()

public:
	AC_FPSController();

protected:
	virtual void BeginPlay() override;
};
