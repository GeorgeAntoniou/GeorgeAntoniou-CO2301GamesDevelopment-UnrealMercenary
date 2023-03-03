//All include headers//
#include "BTTask_FindRandomLocation.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) 
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	
	UE_LOG(LogTemp, Warning, TEXT("Starting Finding Random Location BT Task."));
	//Checks If AI owner is null return failed.
	if (OwnerComp.GetAIOwner() == nullptr) 
	{
		return EBTNodeResult::Failed;
	}
	//Get Reference to Enemy Character.
	AActor* AIActor = OwnerComp.GetAIOwner()->GetPawn();
	//Sets different Values for finding Random Location in the Level.
	float RandomRadius = 8000.0f;
	FNavLocation RandomLocation;
	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
	NavSys->GetRandomReachablePointInRadius(AIActor->GetActorLocation(), RandomRadius, RandomLocation);
	//Sets RandomPosition Blackboard Value.
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("RandomPosition"),RandomLocation);
	UE_LOG(LogTemp, Warning, TEXT("Ended Finding Random Location BT Task."));

	return EBTNodeResult::Succeeded;
}
