#pragma once
//All include headers//
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HealthKit.generated.h"

class UBoxComponent;
UCLASS()
class UNREALMERCENARY_API AHealthKit : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHealthKit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

private:
	UPROPERTY(VisibleAnywhere)
		USceneComponent* Root;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* HealthKitMesh;

	UPROPERTY(EditAnywhere)
		UBoxComponent* TriggerBox;
};
