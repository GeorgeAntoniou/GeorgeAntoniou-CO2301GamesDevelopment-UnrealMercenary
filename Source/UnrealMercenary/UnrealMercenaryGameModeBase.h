#pragma once
//All include headers//
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UnrealMercenaryGameModeBase.generated.h"

UCLASS()
class UNREALMERCENARY_API AUnrealMercenaryGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	FTimerHandle EndGameTimer;

	UFUNCTION(BlueprintCallable)
		int GetTimePassed();

	UFUNCTION(BlueprintCallable)
		int GetGameDuration();

	UFUNCTION()
		void StartGame();

	UFUNCTION()
		void GameOverTimeUp();

	UFUNCTION()
		void GameOverPlayerDied();

	UFUNCTION()
		void GameOverPlayerWon();

	UFUNCTION()
		void TimeUp();

	UPROPERTY(EditAnywhere)
		int GameDuration = 300.0f;

	UPROPERTY()
		int GameSecondsPassed = 0;
};
