//All include headers//
#include "UnrealMercenaryGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Called when the game starts or when spawned
void AUnrealMercenaryGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	StartGame();
}

//A function that returns the number of seconds that have passed.
int AUnrealMercenaryGameModeBase::GetTimePassed()
{
	GameSecondsPassed = GetWorld()->TimeSeconds;
	if (GameSecondsPassed < GameDuration) {
		return GameSecondsPassed;
	}
	else
	{
		/*GameOverTimeUp();*/
		GameSecondsPassed = GameDuration;
		return GameSecondsPassed;
	}

}
//A function that returns the number of seconds that the game duration is.
int AUnrealMercenaryGameModeBase::GetGameDuration()
{
	return GameDuration;
}

//A function that is called when the game starts that sets a timer for the game duration.
void AUnrealMercenaryGameModeBase::StartGame()
{
	UE_LOG(LogTemp, Warning, TEXT("Game Started."));
	GetWorld()->GetTimerManager().SetTimer(EndGameTimer, this, &AUnrealMercenaryGameModeBase::TimeUp, GameDuration, false);
}

//A function that is called when time's up and opens LoseLevelTimeUp level.
void AUnrealMercenaryGameModeBase::GameOverTimeUp()
{
	UE_LOG(LogTemp, Warning, TEXT("Game Over Run out of time."));
	UGameplayStatics::OpenLevel(GetWorld(), "LoseLevelTimeUp");
}

//A function that is called when player dies and opens LoseLevelPlayerDied level.
void AUnrealMercenaryGameModeBase::GameOverPlayerDied()
{
	UE_LOG(LogTemp, Warning, TEXT("Game Over. Player Died"));
	UGameplayStatics::OpenLevel(GetWorld(), "LoseLevelPlayerDied");
}

//A function that is called when player wins and opens WinLevel level.
void AUnrealMercenaryGameModeBase::GameOverPlayerWon()
{
	UE_LOG(LogTemp, Warning, TEXT("Game Over. Player killed everyone."));
	UGameplayStatics::OpenLevel(GetWorld(), "WinLevel");
}

//A function that is called when timer is up and calls GameOverTimeUp function.
void AUnrealMercenaryGameModeBase::TimeUp()
{
	GameOverTimeUp();
}