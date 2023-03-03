#pragma once
//All include headers//
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Barrel.generated.h"

class URadialForceComponent;
class UParticleSystemComponent;
class AExplosion;
UCLASS()
class UNREALMERCENARY_API ABarrel : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ABarrel();
    void Explode();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;
    
    UPROPERTY(EditAnywhere)
        URadialForceComponent* ForceComp;

private:
    TArray<AActor*> Characters;

    UPROPERTY(EditAnywhere)
        UStaticMeshComponent* BarrelMesh;

    UPROPERTY(EditAnywhere)
        float ForceAmount = 1200.f;

    UPROPERTY(EditAnywhere)
        float TorqueAmount = 10.f;

    UPROPERTY(EditAnywhere)
        float ExplosionRadius = 500.f;

    UPROPERTY(VisibleAnywhere)
        float Damage = 30.f;

    UPROPERTY(EditAnywhere)
        TSubclassOf<AExplosion> ExplosionClass;
};