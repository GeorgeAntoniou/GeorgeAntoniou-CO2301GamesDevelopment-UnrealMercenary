#pragma once
//All include headers//
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Explosion.generated.h"

class UParticleSystemComponent;
UCLASS()
class UNREALMERCENARY_API AExplosion : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExplosion();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
		USceneComponent* Root;

	UPROPERTY(EditAnywhere)
		UParticleSystemComponent* ExplosionParticle;
};
