#pragma once
//All include headers//
#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

UCLASS()
class UNREALMERCENARY_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaTime) override;
	void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

protected:
	virtual void BeginPlay() override;
	
public:
	void StartFire();

private:
	AActor* LookoutPoint;
	AActor* ChooseWaypoint();
	void Patrol();

	UPROPERTY()
		TArray<AActor*> Waypoints;

	UPROPERTY(EditAnywhere)
		UBehaviorTree* EnemyAIBehaviorTree;
};
