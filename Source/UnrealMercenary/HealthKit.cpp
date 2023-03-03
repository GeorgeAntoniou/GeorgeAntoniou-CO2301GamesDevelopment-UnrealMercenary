//All include headers//
#include "HealthKit.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MainCharacter.h"

// Sets default values
AHealthKit::AHealthKit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Creates subobjects for the different components in the editor.
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	HealthKitMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ammo Box Mesh"));
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Box"));

	//Set Default Values for the components.
	SetRootComponent(Root);
	HealthKitMesh->SetupAttachment(Root);
	TriggerBox->SetupAttachment(HealthKitMesh);
	TriggerBox->SetBoxExtent(FVector(80.0f, 110.0f, 20.0f));
	TriggerBox->SetRelativeLocation(FVector(6.0f, 3.0f, 4.0f));
	TriggerBox->SetCollisionProfileName("Trigger");
}

// Called when the game starts or when spawned
void AHealthKit::BeginPlay()
{
	Super::BeginPlay();
	OnActorHit.AddDynamic(this, &AHealthKit::OnHit);
}

// Called every frame
void AHealthKit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHealthKit::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor)
	{
		//If the other Actor class is a AMainCharacter and has player tag.
		if (OtherActor->GetClass()->IsChildOf(AMainCharacter::StaticClass()) && OtherActor->ActorHasTag("Player"))
		{
			if (Cast<AMainCharacter>(OtherActor)->Health >= 100)
			{
				UE_LOG(LogTemp, Warning, TEXT("Health is full and player can't heal."));
			}
			else
			{
				Cast<AMainCharacter>(OtherActor)->HealthAdd();
				Destroy();
			}
		}
	}
}

