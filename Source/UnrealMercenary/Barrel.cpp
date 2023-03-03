//All include headers//
#include "Barrel.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Explosion.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ABarrel::ABarrel()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    //Creates subobjects for the different components in the editor.
    BarrelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Barrel Mesh"));
    ForceComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("Force Component"));

    //Set Default Values for the components.
    BarrelMesh->SetupAttachment(RootComponent);
    BarrelMesh->SetSimulatePhysics(true);
    ForceComp->SetupAttachment(BarrelMesh);
}
//A explode function for the Barrel.
void ABarrel::Explode()
{
    //Applies Impulse,RadialDamage and spawns an instance of the Explosion class.
    ForceComp->FireImpulse();
    UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), ExplosionRadius, UDamageType::StaticClass(), Characters, this, GetInstigatorController(), false, ECC_Visibility);
    Destroy();
    GetWorld()->SpawnActor<AExplosion>(ExplosionClass, this->GetActorLocation(), this->GetActorRotation());
}

// Called when the game starts or when spawned
void ABarrel::BeginPlay()
{
    Super::BeginPlay();
    BarrelMesh->AddImpulse(GetActorUpVector() * ForceAmount * BarrelMesh->GetMass());
}

void ABarrel::Tick(float DeltaTime)
{
    BarrelMesh->AddForce(GetActorUpVector() * ForceAmount * BarrelMesh->GetMass());
    BarrelMesh->AddTorqueInRadians(FVector(0.0f, 0.0f, 5.0f) * 1000.0f * BarrelMesh->GetMass());
}
