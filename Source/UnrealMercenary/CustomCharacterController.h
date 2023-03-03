#pragma once
//All include headers//
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CustomCharacterController.generated.h"

class AMainCharacter;
class AUnrealMercenaryGameModeBase;
UCLASS()
class UNREALMERCENARY_API ACustomCharacterController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	AMainCharacter* ControlledCharacter;
	AUnrealMercenaryGameModeBase* GameModeRef;

	virtual void SetupInputComponent();
	virtual void CallForward(float Value);
	virtual void CallStrafe(float Value);
	virtual void CallTurn(float Value);
	virtual void CallLookUp(float Value);
	virtual void CallFire();
	virtual void CallThrowingGrenade();
	virtual void CallJump();
	virtual void CallStopJump();
	virtual void CallSprinting();
	virtual void CallStopSprinting();
	virtual void CallCrouching();
	virtual void CallStopCrouching();
	virtual void CallReloading();
	virtual void PauseGame();

	UFUNCTION(BlueprintPure)
		float GetHealth();

	UFUNCTION(BlueprintPure)
		float GetHealthPercentage();

	UFUNCTION(BlueprintPure)
		 float GetStaminaPercentage();

	UFUNCTION(BlueprintPure)
		 float GetStamina();

	UFUNCTION(BlueprintPure)
		int GetCurrentAmmunitionMagazine();

	UFUNCTION(BlueprintPure)
		int GetMaxAmmunition();

	UFUNCTION(BlueprintPure)
		int GetGrenadeCounter();

	UFUNCTION(BlueprintPure)
		int GetRemainingEnemiesCounter();

	UPROPERTY()
		float DeathDelay = 5.f;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> MinimapHUDClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> HealthHUDClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> ExtraInfoHUDClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> AmmoCountersHUDClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> TimerHUDClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> KillCounterHUDClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> CrosshairHUDClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> PauseMenuHUDClass;

	UPROPERTY()
		UUserWidget* MinimapWidget;

	UPROPERTY()
		UUserWidget* HealthWidget;

	UPROPERTY()
		UUserWidget* ExtraInfoWidget;

	UPROPERTY()
		UUserWidget* AmmoCountersWidget;

	UPROPERTY()
		UUserWidget* TimerWidget;

	UPROPERTY()
		UUserWidget* KillCounterWidget;

	UPROPERTY()
		UUserWidget* CrosshairWidget;

	UPROPERTY()
		UUserWidget* PauseWidget;
};
