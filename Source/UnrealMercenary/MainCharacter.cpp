//All include headers//
#include "MainCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Kismet/GameplayStatics.h"
#include "CustomCharacterController.h"
#include "EnemyAIController.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"
#include "Weapon.h"
#include "DrawDebugHelpers.h"
#include "Explosion.h"
#include "Grenade.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Creates subobjects for the different components in the editor.
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	MapArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Map Spring Arm"));
	MapCamera = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Map Camera"));
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	WeaponParticleSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Particle Spawn Point"));

	//Set Default Values for the components.
	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);
	MapArm->SetupAttachment(RootComponent);
	MapCamera->SetupAttachment(MapArm);
	ProjectileSpawnPoint->SetupAttachment(RootComponent);
	WeaponParticleSpawnPoint->SetupAttachment(RootComponent);
	SpringArm->bEnableCameraLag = true;
	SpringArm->TargetArmLength = 300.0f;
	MapArm->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));
	ProjectileSpawnPoint->SetRelativeLocation(FVector(40.0f, 0.0f, 60.0f));
	ProjectileSpawnPoint->SetRelativeRotation(FRotator(0.0f, 20.0f, 0.0f));
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Casts the enemy controller and weapon.
	EnemyControllerRef = Cast<AEnemyAIController>(GetController());
	WeaponRef = Cast<AWeapon>(GetOwner());

	//Spawns an instance of the weapon and sets the character as the owner of the weapon.
	const FVector ActorLocation = GetActorLocation();
	const FRotator ActorRotation = GetActorRotation();
	WeaponRef = GetWorld()->SpawnActor<AWeapon>(WeaponClass, ActorLocation, ActorRotation);
	WeaponRef->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("gunSocket"));
	WeaponRef->SetOwner(this);

	//Gets an AnimInstance of the character.
	AnimInstance = this->GetMesh()->GetAnimInstance();

	GetWorld()->GetTimerManager().SetTimer(LowerStamina, this, &AMainCharacter::HandleSprinting, 1.0f, true);
	GetWorld()->GetTimerManager().SetTimer(RegenerateStamina, this, &AMainCharacter::RefillStamina, 1.0f, true);
}

//Functions for the character movement.
void AMainCharacter::MoveForward(float Axis)
{
	if (Axis != 0.0f)
	{
		AddMovementInput(GetActorForwardVector() * Axis);
	}
}

void AMainCharacter::MoveStrafe(float Axis)
{
	if (Axis != 0.0f)
	{
		AddMovementInput(GetActorRightVector() * Axis);
	}
}

void AMainCharacter::Turn(float Axis)
{
	if (Axis != 0.0f)
	{
		AddControllerYawInput(Axis * TurnRate * GetWorld()->GetDeltaSeconds());
	}
}

void AMainCharacter::LookUp(float Axis)
{
	if (Axis != 0.0f)
	{
		AddControllerPitchInput(Axis * LookupRate * GetWorld()->GetDeltaSeconds());
	}
}

void AMainCharacter::Sprint()
{
	if (Stamina > 0) 
	{
		PlayerIsSprinting = true;
		GetCharacterMovement()->MaxWalkSpeed = 800.0f;
	}
	else 
	{
		StopSprinting();
	}
}

void AMainCharacter::StopSprinting()
{
	PlayerIsSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
}
void AMainCharacter::Crouching()
{
	PlayerCanCrouch = true;
}
void AMainCharacter::StopCrouching()
{
	PlayerCanCrouch = false;
}
//End of Movement Functions.

//Fire Function for the character.
void AMainCharacter::Fire()
{
	if (Health > 0)
	{
		if (PlayerCanShoot && CurrentAmmunitionMagazine > 0)
		{
			if (GunFireSound)
			{
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), GunFireSound, GetActorLocation(), 1.0f, 1.0f, 0.0f);
			}
			if (FireParticleClass)
			{
				const FVector GunBarrelLocation = ProjectileSpawnPoint->GetComponentLocation();
				const FRotator GunBarrelRotation = ProjectileSpawnPoint->GetComponentRotation();
				//GetWorld()->SpawnActor<AExplosion>(FireParticleClass, WeaponParticleSpawnPoint->GetComponentLocation(), WeaponParticleSpawnPoint->GetComponentRotation()); 
				GetWorld()->SpawnActor<AExplosion>(FireParticleClass, GunBarrelLocation, GunBarrelRotation);
			}
			CurrentAmmunitionMagazine--;
			WeaponRef->Fire();
			if (Cast<ACustomCharacterController>(GetController()))
			{
				if (AnimInstance)
				{
					if (FireAnimation)
					{
						AnimInstance->Montage_Play(FireAnimation, 1.0f);
					}
				}
			}
		}
		else 
		{
			if (EmptyGunSound) 
			{
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), EmptyGunSound, GetActorLocation(), 1.0f, 1.0f, 0.0f);
			}
		}

	}
}

//Function for adding Ammo.
int AMainCharacter::AmmoAdd()
{
	if (MaxAmmunition >= 100)
	{
		MaxAmmunition = 120;
	}
	else
	{
		MaxAmmunition += 20;
	}
	return MaxAmmunition;
}

//Function that return health after healing.
float AMainCharacter::HealthAdd()
{
	if (Health >= 80)
	{
		Health = 100;
	}
	else
	{
		Health += 20;
	}
	return Health;
}

//Function that return the number of remaining enemies.
int AMainCharacter::RemainingEnemiesCount()
{
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), AMainCharacter::StaticClass(), "Enemy", Enemies);
	return Enemies.Num();
}

//Fire Function for the grenades.
void AMainCharacter::FireGrenade()
{
	if (GrenadeCount > 0 && GrenadeClass) //checks teabag projectile has been set in the editor
	{
		GrenadeCount--;
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;
		UE_LOG(LogTemp, Warning, TEXT("Grenade Fired."));
		const FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
		const FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();
		AGrenade* TempGrenade = GetWorld()->SpawnActor<AGrenade>(GrenadeClass, SpawnLocation, SpawnRotation);
		TempGrenade->SetOwner(this);
	}
}

void AMainCharacter::Reloading()
{
	PlayerCanShoot = false;

	if (CurrentAmmunitionMagazine == MaxAmmunitionMagazine)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player can't reload because Ammo is full."));
		PlayerCanShoot = true;
	}
	if (ReloadAnimation)
	{
		AnimInstance->Montage_Play(ReloadAnimation, 1.0f);
	}
	int AmmunitionToAddToMag = MaxAmmunitionMagazine - CurrentAmmunitionMagazine;

	if (MaxAmmunition != 0)
	{
		CurrentAmmunitionMagazine += AmmunitionToAddToMag;
		MaxAmmunition -= AmmunitionToAddToMag;
	}

	else if (AmmunitionToAddToMag >= MaxAmmunition)
	{
		AmmunitionToAddToMag = MaxAmmunition;
		CurrentAmmunitionMagazine += AmmunitionToAddToMag;
		MaxAmmunition = 0;
	}
	PlayerCanShoot = true;
}

void AMainCharacter::RefillStamina()
{
	if (!PlayerIsSprinting && Stamina<100)
	{

		if (Stamina + 1.0f < 100.f)
		{
			Stamina = Stamina + 1.0f;
		}
		else
		{
			Stamina = 100.f;
		}
		UE_LOG(LogTemp, Warning, TEXT("PlayerStamina : %f"), Stamina);
	}
	else 
	{
		/*UE_LOG(LogTemp, Warning, TEXT("PlayerStamina Can't be regenerated because he is still sprinting."));*/
	}
}

void AMainCharacter::HandleSprinting()
{
	if (PlayerIsSprinting) 
	{
		--Stamina;
		UE_LOG(LogTemp, Warning, TEXT("PlayerStamina : %f"), Stamina);
	}
}

//Function for taking damage for the character either player character or enemy.
float AMainCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (Health - DamageAmount > 0)
	{
		if (Cast<ACustomCharacterController>(GetController()))
		{
			Health -= DamageAmount;
			UE_LOG(LogTemp, Warning, TEXT("Player Health : %f"), Health);
		}
		if (Cast<AEnemyAIController>(GetController()))
		{
			Health -= DamageAmount;
			UE_LOG(LogTemp, Warning, TEXT("Enemy Health : %f"), Health);
		}
	}
	else
	{
		Health = 0;
		if (Cast<AEnemyAIController>(EnemyControllerRef))
		{
			Destroy();
			WeaponRef->Destroy();
			UE_LOG(LogTemp, Warning, TEXT("Enemy Dead."));
		}
	}
	return Health;
}
