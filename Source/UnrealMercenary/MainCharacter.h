#pragma once
//All include headers//
#include "Grenade.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class USceneCaptureComponent2D;
class USceneComponent;
class AEnemyAIController;
class ACustomCharacterController;
class UAnimMontage;
class USkeletalMeshComponent;
class UAnimInstance;
class AWeapon;
class AExplosion;
UCLASS()
class UNREALMERCENARY_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	AEnemyAIController* EnemyControllerRef;
	ACustomCharacterController* CustomControllerRef;
	AWeapon* WeaponRef;

	void MoveForward(float Axis);
	void MoveStrafe(float Axis);
	void Turn(float Axis);
	void LookUp(float Axis);
	void Sprint();
	void StopSprinting();
	void Crouching();
	void StopCrouching();
	void Fire();
	void FireGrenade();
	void Reloading();
	void RefillStamina();
	void HandleSprinting();

	UFUNCTION(BlueprintPure)
		int AmmoAdd();

	UFUNCTION()
		int RemainingEnemiesCount();

	UFUNCTION(BlueprintPure)
		float HealthAdd();

	UFUNCTION()
		virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

		UPROPERTY(EditAnywhere)
		float Damage=20.0f;
	
	UPROPERTY(EditAnywhere)
		float Stamina = 80.f;

	UPROPERTY(EditAnywhere)
		float TurnRate = 45.0f;

	UPROPERTY(EditAnywhere)
		float LookupRate = 45.0f;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		int RemainingEnemies;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		float Health = 100.0f;

	UPROPERTY(BlueprintReadWrite)
		bool PlayerCanCrouch=false;

	UPROPERTY(EditAnywhere)
		int CurrentAmmunitionMagazine = 20;

	UPROPERTY(EditAnywhere)
		int MaxAmmunitionMagazine = 20;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		int MaxAmmunition = 120;

	UPROPERTY(BlueprintReadWrite)
		int GrenadeCount = 5;

private:
	TArray<AActor*> Enemies;
	UAnimInstance* AnimInstance;

	UPROPERTY(EditAnywhere)
		USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere)
		UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
		USpringArmComponent* MapArm;

	UPROPERTY(EditAnywhere)
		USceneCaptureComponent2D* MapCamera;

	UPROPERTY(VisibleAnywhere)
		USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditAnywhere)
		USoundBase* GunFireSound;

	UPROPERTY(EditAnywhere)
		USoundBase* EmptyGunSound;

	UPROPERTY(VisibleAnywhere)
		USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(VisibleAnywhere)
		USceneComponent* WeaponParticleSpawnPoint;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AGrenade> GrenadeClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AWeapon> WeaponClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AExplosion> FireParticleClass;

	UPROPERTY(EditAnywhere)
		UAnimMontage* FireAnimation;

	//UPROPERTY(EditAnywhere)
	//	UAnimMontage* DeathAnimation;

	UPROPERTY(EditAnywhere)
		UAnimMontage* ReloadAnimation;

	UPROPERTY()
	bool PlayerCanShoot = true;

	UPROPERTY()
		bool PlayerIsSprinting = false;

	UPROPERTY()
		float KillAnimDelay = 5.f;

		FTimerHandle RegenerateStamina;
		FTimerHandle LowerStamina;
};
