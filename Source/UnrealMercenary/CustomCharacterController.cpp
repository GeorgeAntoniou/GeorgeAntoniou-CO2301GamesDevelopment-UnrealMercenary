//All include headers//
#include "CustomCharacterController.h"
#include "MainCharacter.h"
#include "Blueprint/UserWidget.h" 
#include "Kismet/GameplayStatics.h"
#include "UnrealMercenaryGameModeBase.h"

void ACustomCharacterController::BeginPlay()
{
	Super::BeginPlay();
	//Gets Reference to the player character and game mode.
	ControlledCharacter = Cast<AMainCharacter>(GetPawn());
	GameModeRef = Cast< AUnrealMercenaryGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	//Creates all the below widgets.
	MinimapWidget = CreateWidget(this, MinimapHUDClass);
	HealthWidget = CreateWidget(this, HealthHUDClass);
	ExtraInfoWidget = CreateWidget(this, ExtraInfoHUDClass);
	AmmoCountersWidget = CreateWidget(this, AmmoCountersHUDClass);
	TimerWidget = CreateWidget(this, TimerHUDClass);
	KillCounterWidget = CreateWidget(this, KillCounterHUDClass);
	CrosshairWidget = CreateWidget(this, CrosshairHUDClass);
	PauseWidget = CreateWidget(this, PauseMenuHUDClass);
	//Checks if they are not null and adds to viewport.
	if (MinimapHUDClass) 
	{
		MinimapWidget->AddToViewport();
	}
	if (HealthHUDClass)
	{
		HealthWidget->AddToViewport();
	}
	if (ExtraInfoHUDClass)
	{
		ExtraInfoWidget->AddToViewport();
	}
	if (AmmoCountersHUDClass)
	{
		AmmoCountersWidget->AddToViewport();
	}
	if (TimerHUDClass)
	{
		TimerWidget->AddToViewport();
	}
	if (KillCounterHUDClass)
	{
		KillCounterWidget->AddToViewport();
	}
	if (CrosshairHUDClass)
	{
		CrosshairWidget->AddToViewport();
	}
}
//Setup Input Component.
void ACustomCharacterController::SetupInputComponent()
{
	Super::SetupInputComponent();
	check(InputComponent);
	//Binds all axis/actions.
	InputComponent->BindAxis("ForwardMovement", this, &ACustomCharacterController::CallForward);
	InputComponent->BindAxis("StrafeMovement", this, &ACustomCharacterController::CallStrafe);
	InputComponent->BindAxis("Turning", this, &ACustomCharacterController::CallTurn);
	InputComponent->BindAxis("LookUp", this, &ACustomCharacterController::CallLookUp);

	InputComponent->BindAction("Firing", EInputEvent::IE_Pressed, this, &ACustomCharacterController::CallFire);
	InputComponent->BindAction("ThrowingGrenade", EInputEvent::IE_Pressed, this, &ACustomCharacterController::CallThrowingGrenade);
	InputComponent->BindAction("Jumping", EInputEvent::IE_Pressed, this, &ACustomCharacterController::CallJump);
	InputComponent->BindAction("Jumping", EInputEvent::IE_Released, this, &ACustomCharacterController::CallStopJump);
	InputComponent->BindAction("Sprinting", EInputEvent::IE_Pressed, this, &ACustomCharacterController::CallSprinting);
	InputComponent->BindAction("Sprinting", EInputEvent::IE_Released, this, &ACustomCharacterController::CallStopSprinting);
	InputComponent->BindAction("Crouching", EInputEvent::IE_Pressed, this, &ACustomCharacterController::CallCrouching);
	InputComponent->BindAction("Crouching", EInputEvent::IE_Released, this, &ACustomCharacterController::CallStopCrouching);
	InputComponent->BindAction("Reloading", EInputEvent::IE_Released, this, &ACustomCharacterController::CallReloading);
	InputComponent->BindAction("Pause", EInputEvent::IE_Pressed, this, &ACustomCharacterController::PauseGame);
}

void ACustomCharacterController::CallForward(float Value)
{
	if (ControlledCharacter) 
	{
		ControlledCharacter->MoveForward(Value);
	}
}

void ACustomCharacterController::CallStrafe(float Value)
{
	if (ControlledCharacter) 
	{
		ControlledCharacter->MoveStrafe(Value);
	}
}

void ACustomCharacterController::CallTurn(float Value)
{
	if (ControlledCharacter) 
	{
		ControlledCharacter->Turn(Value);
	}
}

void ACustomCharacterController::CallLookUp(float Value)
{
	if (ControlledCharacter) 
	{
		ControlledCharacter->LookUp(Value);
	}
}

void ACustomCharacterController::CallFire()
{
	if (ControlledCharacter) 
	{
		ControlledCharacter->Fire();
	}
}

void ACustomCharacterController::CallThrowingGrenade()
{
	if (ControlledCharacter) 
	{
		ControlledCharacter->FireGrenade();
	}
}

void ACustomCharacterController::CallJump()
{
	if (ControlledCharacter) 
	{
		ControlledCharacter->Jump();
	}
}

void ACustomCharacterController::CallStopJump()
{
	if (ControlledCharacter) 
	{
		ControlledCharacter->StopJumping();
	}
}

void ACustomCharacterController::CallSprinting()
{
	if (ControlledCharacter) 
	{
		ControlledCharacter->Sprint();
	}
}

void ACustomCharacterController::CallStopSprinting()
{
	if (ControlledCharacter) 
	{
		ControlledCharacter->StopSprinting();
	}
}

void ACustomCharacterController::CallCrouching()
{
	if (ControlledCharacter) 
	{
		ControlledCharacter->Crouching();
	}
}

void ACustomCharacterController::CallStopCrouching()
{
	if (ControlledCharacter)
	{
		ControlledCharacter->StopCrouching();
	}
}

void ACustomCharacterController::CallReloading()
{
	if (ControlledCharacter) 
	{
		ControlledCharacter->Reloading();
	}
}

void ACustomCharacterController::PauseGame()
{
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	if (PauseMenuHUDClass)
	{
		PauseWidget->AddToViewport();
		APlayerController* Controller = UGameplayStatics::GetPlayerController(ControlledCharacter, 0);
		Controller->SetShowMouseCursor(true);
	}
}

float ACustomCharacterController::GetHealth()
{
	if (ControlledCharacter->Health <= 0.f)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Died."));
		GameModeRef->GameOverPlayerDied();
	}
	return ControlledCharacter->Health;
}

float ACustomCharacterController::GetHealthPercentage()
{
	return ControlledCharacter->Health/100.0f;
}

float ACustomCharacterController::GetStamina()
{
	return ControlledCharacter->Stamina;
}

 float ACustomCharacterController::GetStaminaPercentage()
{
	return ControlledCharacter->Stamina/100.0f;
}



int ACustomCharacterController::GetCurrentAmmunitionMagazine()
{
	return ControlledCharacter->CurrentAmmunitionMagazine;
}

int ACustomCharacterController::GetMaxAmmunition()
{
	return ControlledCharacter->MaxAmmunition;
}

int ACustomCharacterController::GetGrenadeCounter()
{
	return ControlledCharacter->GrenadeCount;
}

int ACustomCharacterController::GetRemainingEnemiesCounter()
{
	if (ControlledCharacter->RemainingEnemiesCount() <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("All enemies are dead. Game Won!"));
		GameModeRef->GameOverPlayerWon();
	}
	return ControlledCharacter->RemainingEnemiesCount();
}