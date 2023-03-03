//All include headers//
#include "Weapon.h"
#include "CustomCharacterController.h"
#include "EnemyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "UObject/Class.h"
#include "MainCharacter.h"
#include "Barrel.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Creates subobjects for the different components in the editor.
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Mesh"));

	//Set Default Values for the components.
	SetRootComponent(Root);
	WeaponMesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//A Fire Function that checks if there is Raycast, applies damage to the actor who was hit and draws a debug line.
void AWeapon::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("Bullet fired."));
	float Range = 2000.f;
	float offset = 5.f;
	FVector WeaponLocation;
	FRotator WeaponRotation;
	FHitResult Hit;
	this->GetActorEyesViewPoint(WeaponLocation, WeaponRotation);
	WeaponLocation = WeaponLocation + offset;
	FVector End = WeaponLocation + WeaponRotation.Vector() * Range;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	bool isHit = GetWorld()->LineTraceSingleByChannel(Hit, WeaponLocation, End, ECC_Visibility, Params);
	DrawDebugLine(GetWorld(), WeaponLocation, End, FColor::Red, false, 1, 0, 1);
	AActor* HitActor = Hit.GetActor();
	if (Cast<AEnemyAIController>(EnemyControllerRef))
	{
		APawn* MainPlayer = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		//Cast<AEnemyAIController>(EnemyControllerRef)->SetFocus(MainPlayer);
	}
	
	if (isHit)
	{
		if (Hit.GetActor()) 
		{
			if (Hit.GetActor() != GetOwner())
			{
				UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *HitActor->GetName());
				UPrimitiveComponent* RootComp = Cast<UPrimitiveComponent>(Hit.GetActor()->GetRootComponent());
				if (Hit.GetActor()->GetClass()->IsChildOf(AMainCharacter::StaticClass()))
				{
					UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *HitActor->GetName());
					//Apply damage to the character
					UGameplayStatics::ApplyDamage(Hit.GetActor(), Damage, GetOwner()->GetInstigatorController(), this, UDamageType::StaticClass());
				}

				if (Cast<ABarrel>(Hit.GetActor()))
				{
					Cast<ABarrel>(Hit.GetActor())->Explode();
				}
			}
		}
	}
}
