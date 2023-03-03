#pragma once
//All include headers//
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grenade.generated.h"

class UProjectileMovementComponent;
class USphereComponent;
class URadialForceComponent;
class UParticleSystem;
class AEnemyAIController;
class AExplosion;
UCLASS()
class UNREALMERCENARY_API AGrenade : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrenade();

	AEnemyAIController* ControllerRef;
	UFUNCTION()
		void Explode();

	UFUNCTION()
		void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* GrenadeMesh;

	UPROPERTY(VisibleAnywhere)
		UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditAnywhere)
		USphereComponent* SphereBox;

	UPROPERTY(EditAnywhere)
		URadialForceComponent* ForceComp;

	UPROPERTY(EditAnywhere)
		USoundBase* ExplosionSound;

	UPROPERTY(EditAnywhere)
		float MovementSpeed = 1000.0f;

	UPROPERTY(EditAnywhere)
		float Damage = 40.f;

	UPROPERTY(EditAnywhere)
		float ForceAmount = 1200.0f;

	UPROPERTY(EditAnywhere)
		float TorqueAmount = 10.0f;

	UPROPERTY(EditAnywhere)
		float ExplosionRadius = 150.0f;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AExplosion> ExplosionClass;
	
};
