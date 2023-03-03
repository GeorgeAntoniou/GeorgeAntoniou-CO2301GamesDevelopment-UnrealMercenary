#pragma once
//All include headers//
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

class ABarrel;
class AEnemyAIController;
class ACustomCharacterController;
UCLASS()
class UNREALMERCENARY_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
public:
	AEnemyAIController* EnemyControllerRef;
	ACustomCharacterController* PlayerControllerRef;
	void Fire();

	UPROPERTY(EditAnywhere)
		float Damage = 20.f;

private:

	UPROPERTY(VisibleAnywhere)
		USceneComponent* Root;

	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent* WeaponMesh;
};
