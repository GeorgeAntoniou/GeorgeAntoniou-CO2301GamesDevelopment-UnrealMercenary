//All include headers//
#include "MyBTTask_FireWeapon.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "DrawDebugHelpers.h"
#include "MainCharacter.h"
#include "EnemyAIController.h"

EBTNodeResult::Type UMyBTTask_FireWeapon::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	UE_LOG(LogTemp, Warning, TEXT("Starting Shooting BT Task."));
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	//Checks If AI owner or player character is null return failed.
	if (OwnerComp.GetAIOwner() == nullptr || PlayerPawn==nullptr) 
	{
		return EBTNodeResult::Failed;
	}
	else
	{
		//Gets A reference to the AI controller ,calls The AEnemyAIController.cpp StartFire Function and returns succeeded.
		AEnemyAIController* EnemyControllerRef = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
		EnemyControllerRef->StartFire();
		return EBTNodeResult::Succeeded;
	}
}
