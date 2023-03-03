//All include headers//
#include "BTService_LineOfSight.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"

void UBTService_LineOfSight::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) 
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	//Gets A reference on the Enemy Controller,Player Character and Enemy Character.
	AAIController* EnemyAIController = OwnerComp.GetAIOwner();
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	APawn* EnemyPawn = EnemyAIController->GetPawn();
	//Checks if Enemy has Line of Sight with Player.
	if (EnemyAIController->LineOfSightTo(PlayerPawn))
	{

						//Dot Product Calculation//
		FVector EnemyPawnForwardVector = EnemyPawn->GetActorForwardVector();
		FVector PlayerLocation = PlayerPawn->GetActorLocation();
		FVector EnemyPawnLocation = EnemyPawn->GetActorLocation();
		FVector EnemyToPlayerVector = PlayerLocation - EnemyPawnLocation;
		//Checks If Enemy is infront of the player.//
		if (FVector::DotProduct(EnemyToPlayerVector, EnemyPawnForwardVector) > 0.f)
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), true);
		}
		else
		{
			OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
		}
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
	}
}