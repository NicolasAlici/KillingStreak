#include "C_FPSCharacter.h"
#include "C_FPSController.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AC_FPSCharacter::AC_FPSCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	PlayerCam = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCam"));
	PlayerCam->SetupAttachment(GetRootComponent());
	PlayerMesh = CreateDefaultSubobject<USkeletalMeshComponent>("PlayerMesh");
	PlayerMesh->SetupAttachment(PlayerCam);
	CurrentWeapon = CreateDefaultSubobject<UChildActorComponent>("PlayerGun");
	CurrentWeapon->SetupAttachment(PlayerCam);
}

void AC_FPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitValues();
}

void AC_FPSCharacter::InitValues()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	CanDash = true;
	CanSlide = true;
}


void AC_FPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	const AC_FPSController* ControllerRef = Cast<AC_FPSController>(Controller);
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(ControllerRef->GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(PlayerInputContext, 0);
	}

	UEnhancedInputComponent* FPSInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (FPSInputComponent)
	{
		//Moving
		FPSInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AC_FPSCharacter::Move);
		//Looking
		FPSInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this,  &AC_FPSCharacter::Look);
		//Dashing
		FPSInputComponent->BindAction(DashAction, ETriggerEvent::Triggered, this, &AC_FPSCharacter::Dash);
		//Sprinting
		FPSInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &AC_FPSCharacter::Sprint);
		FPSInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AC_FPSCharacter::StopSprint);
		//Sliding
		FPSInputComponent->BindAction(SlideAction, ETriggerEvent::Triggered, this, &AC_FPSCharacter::Slide);
		//Jumping
		FPSInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		FPSInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AC_FPSCharacter::StopJumping);
		//Shooting
		
	}
}

void AC_FPSCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	isWalking = true;
	AddMovementInput(GetActorForwardVector(), MovementVector.Y);
	AddMovementInput(GetActorRightVector(), MovementVector.X);
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, "Walking");
	}
}

void AC_FPSCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookVector = Value.Get<FVector2D>();
	AddControllerYawInput(LookVector.X);
	AddControllerPitchInput(LookVector.Y);
}

void AC_FPSCharacter::Dash(const FInputActionValue& Value)
{
	if (isSprinting && CanDash)
	{
		isDashing = true;
		CanDash = false;
		const FVector Dash = GetCharacterMovement()->GetLastInputVector();
		if (GetCharacterMovement()->Velocity != FVector::ZeroVector)
		{
			GetCharacterMovement()->FallingLateralFriction = DFriction;
			LaunchCharacter(Dash * DImpulse * DashSpeed, true, false);
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(3, 5.f, FColor::Blue, "Dash");
			}
		}
		GetWorld()->GetTimerManager().SetTimer(DCooldownTimer, this, &AC_FPSCharacter::ResetDash, DCooldown, false);
	}
}

void AC_FPSCharacter::ResetDash()
{
	CanDash = true;
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(3, 5.f, FColor::Blue, "Dash Reseted");
	}
}

void AC_FPSCharacter::Sprint()
{
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	isSprinting = true;
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(2, 5.f, FColor::Yellow, "Sprinting");
	}
}

void AC_FPSCharacter::StopSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	isSprinting = false;
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(2, 5.f, FColor::Orange, "isnt Sprinting");
	}
}

void AC_FPSCharacter::Slide()
{
	if (isSprinting && GetCharacterMovement()->IsFalling() == false && CanSlide)
	{
		CanSlide = false;
		isSliding = true;
		GetCapsuleComponent()->SetCapsuleHalfHeight(SlideHeight, true);
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(4, 5.f, FColor::Orange, "Slide");
		}
	}
	GetWorld()->GetTimerManager().SetTimer(SlideTimer, this, &AC_FPSCharacter::ResetSlide, SlideCooldown, false);
}

void AC_FPSCharacter::ResetSlide()
{
	CanSlide = true;
	isSliding = false;
	GetCapsuleComponent()->SetCapsuleHalfHeight(NormalHeight, true);
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(4, 5.f, FColor::Orange, "SlideRest");
	}
}

