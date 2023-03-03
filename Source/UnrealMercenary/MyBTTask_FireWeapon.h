#pragma once
//All include headers//
#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "MyBTTask_FireWeapon.generated.h"

UCLASS()
class UNREALMERCENARY_API UMyBTTask_FireWeapon : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	bool CanShout;
};
