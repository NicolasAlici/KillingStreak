#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "C_FPSCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class KILLINGSTREAK_API AC_FPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AC_FPSCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVars")
	double NormalHeight;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVelocities")
	double WalkSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVelocities")
	double SprintSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVelocities")
	double DashSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerActions")
	bool isWalking;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerActions")
	bool isSprinting;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerActions")
	bool isDashing;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerActions")
	bool isSliding;;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerCan?")
	bool CanDash;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerCan?")
	bool CanSlide;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DashVars")
	double DImpulse;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DashVars")
	double DFriction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DashVars")
	double DCooldown;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DashVars")
	FTimerHandle DCooldownTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SlideVars")
	FTimerHandle SlideTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SlideVars")
	double SlideCooldown;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SlideVars")
	double SlideHeight;
	
private:
	UPROPERTY(EditAnywhere)
	class UCameraComponent* PlayerCam;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* CurrentWeapon;
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* PlayerMesh;
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = "InputVars")
	UInputMappingContext* PlayerInputContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InputVars")
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InputVars")
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InputVars")
	UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InputVars")
	UInputAction* DashAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InputVars")
	UInputAction* SprintAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InputVars")
	UInputAction* SlideAction;
	
	UFUNCTION(Category = "InputFuncs") 
	void Move(const FInputActionValue& Value);
	UFUNCTION(Category = "InputFuncs") 
	void Look(const FInputActionValue& Value);
	UFUNCTION(Category = "InputFuncs") 
	void Dash(const FInputActionValue& Value);
	UFUNCTION(Category = "InputFuncs") 
	void ResetDash();
	UFUNCTION(Category = "InputFuncs") 
	void Sprint();
	UFUNCTION(Category = "InputFuncs")
	void StopSprint();
	UFUNCTION(Category = "InputFuncs") 
	void Slide();
	UFUNCTION(Category = "InputFuncs") 
	void ResetSlide();
	
};
