//All include headers//
#include "AmmoBox.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h" 
#include "MainCharacter.h"

// Sets default values
AAmmoBox::AAmmoBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//Creates subobjects for the different components in the editor.
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	AmmoBoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ammo Box Mesh"));
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Box"));
	
	//Set Default Values for the components.
	SetRootComponent(Root);
	AmmoBoxMesh->SetupAttachment(Root);
	TriggerBox->SetupAttachment(AmmoBoxMesh);
	TriggerBox->SetBoxExtent(FVector(4.0f, 10.0f, 5.0f));
	TriggerBox->SetRelativeLocation(FVector(16.0f, -27.0f, 5.0f));
	TriggerBox->SetCollisionProfileName("Trigger");
}

// Called when the game starts or when spawned
void AAmmoBox::BeginPlay()
{
	Super::BeginPlay();
	OnActorHit.AddDynamic(this, &AAmmoBox::OnHit);
}

// Called every frame
void AAmmoBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAmmoBox::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor)
	{
		//If the other Actor class is a AMainCharacter and has player tag.
		if (OtherActor->GetClass()->IsChildOf(AMainCharacter::StaticClass()) && OtherActor->ActorHasTag("Player"))
		{
			if (Cast<AMainCharacter>(OtherActor)->MaxAmmunition >= 120)
			{
				UE_LOG(LogTemp, Warning, TEXT("Ammo are full can't take more."));
			}
			else
			{
				Cast<AMainCharacter>(OtherActor)->AmmoAdd();
				Destroy();
			}
		}
	}
}


