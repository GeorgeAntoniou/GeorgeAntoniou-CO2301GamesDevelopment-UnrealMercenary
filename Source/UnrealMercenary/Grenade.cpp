//All include headers//
#include "Grenade.h"
#include "Components/SphereComponent.h"
#include "MainCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Particles/ParticleSystem.h"
#include "EnemyAIController.h"
#include "CustomCharacterController.h"
#include "Explosion.h"

// Sets default values
AGrenade::AGrenade()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Creates subobjects for the different components in the editor.
	GrenadeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Grenade Mesh"));
	SphereBox = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ForceComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("Force Component"));

	//Set Default Values for the components.
	SetRootComponent(GrenadeMesh);
	GrenadeMesh->SetSimulatePhysics(true);
	GrenadeMesh->SetNotifyRigidBodyCollision(true);
	ProjectileMovement->MaxSpeed = MovementSpeed;
	ProjectileMovement->InitialSpeed = MovementSpeed;
	InitialLifeSpan = 10.0f;
	ForceComp->SetupAttachment(GrenadeMesh);
}

// Called when the game starts or when spawned
void AGrenade::BeginPlay()
{
	Super::BeginPlay();
	OnActorHit.AddDynamic(this, &AGrenade::OnHit);
}

//A explode function for the Barrel.
void AGrenade::Explode()
{
	GrenadeMesh->AddImpulse(GetActorUpVector() * ForceAmount * GrenadeMesh->GetMass());
	GrenadeMesh->AddForce(GetActorUpVector() * ForceAmount * GrenadeMesh->GetMass());
	GrenadeMesh->AddTorqueInRadians(FVector(0.0f, 0.0f, 5.0f) * 1000.0f * GrenadeMesh->GetMass());
	ForceComp->FireImpulse();
	GetWorld()->SpawnActor<AExplosion>(ExplosionClass, this->GetActorLocation(), this->GetActorRotation());
	Destroy();
}

//A function that is called when the Grenade Actor is colliding with another actor.
void AGrenade::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor)
	{
		//If the other Actor class is a AMainCharacter.
		if (OtherActor->GetClass()->IsChildOf(AMainCharacter::StaticClass()))
		{

			UGameplayStatics::PlaySoundAtLocation(GetWorld(), ExplosionSound, GetActorLocation(), 1.0f, 1.0f, 0.0f);
			UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *Hit.GetActor()->GetName());
			AActor* ProjectileOwner = GetOwner();
			if (ProjectileOwner)
			{
				FVector Location = SelfActor->GetActorLocation();
				AController* OwnerController = GetInstigatorController();
				Explode();
				UGameplayStatics::ApplyDamage(OtherActor, Damage, ProjectileOwner->GetInstigatorController(), this, UDamageType::StaticClass());
			}
		}
	}
}

