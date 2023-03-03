//All include headers//
#include "Explosion.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AExplosion::AExplosion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Creates subobjects for the different components in the editor.
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	ExplosionParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Explosion Particle System"));

	//Set Default Values for the components.
	SetRootComponent(Root);
	ExplosionParticle->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AExplosion::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AExplosion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

