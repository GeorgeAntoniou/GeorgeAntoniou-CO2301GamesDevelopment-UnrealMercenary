//All include headers//
#include "EnemyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/TargetPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MainCharacter.h"

void AEnemyAIController::BeginPlay() 
{
	Super::BeginPlay();
	//A reference to the main player.
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	//Checks if the Enemy Behavior tree is not null and runs it.
	if (EnemyAIBehaviorTree != nullptr) 
	{         
		RunBehaviorTree(EnemyAIBehaviorTree);
	}
	//Sets blackboard values of player location and home position respectively.
	GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
	GetBlackboardComponent()->SetValueAsVector(TEXT("HomePosition"), GetPawn()->GetActorLocation());
}

void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
//A Function to choose a random Waypoint.
AActor* AEnemyAIController::ChooseWaypoint() 
{
	int index = FMath::RandRange(0, Waypoints.Num() - 1);
	return Waypoints[index];
}
//A Function to Move Actor to a random Waypoint.
void AEnemyAIController::Patrol() 
{
	MoveToActor(ChooseWaypoint());
}
//A Function to Move Actor to a random Waypoint.
void AEnemyAIController::StartFire()
{
	//A reference to main player and enemy players.
	APawn* MainPlayer = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	AMainCharacter* EnemyPawn = Cast<AMainCharacter>(GetPawn());
	//If not null this Calls the fire function from the MainCharacter.cpp 
	if (EnemyPawn)
	{
		SetFocus(MainPlayer);
		EnemyPawn->Fire();
	}
}

void AEnemyAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
}