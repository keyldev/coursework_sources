#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "hungerCharacter.generated.h"

class UInputComponent;

UCLASS(config=Game)
class AhungerCharacter : public ACharacter
{
	GENERATED_BODY()

	// павн 
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	class USkeletalMeshComponent* Mesh1P;

	// оружие 
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* FP_Gun;


	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* FP_MuzzleLocation;

	
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* VR_Gun;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* VR_MuzzleLocation;

	// камера 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UMotionControllerComponent* R_MotionController;

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UMotionControllerComponent* L_MotionController;

public:
	AhungerCharacter();

protected:
	virtual void BeginPlay();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProperty)const override;

public:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector GunOffset;

	
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class AhungerProjectile> ProjectileClass;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	class USoundBase* FireSound;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FireAnimation;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	uint32 bUsingMotionControllers : 1;
public:
	UPROPERTY(ReplicatedUsing = OnRep_Killer, BlueprintReadOnly, Category = Gameplay)
		AhungerCharacter* Killer;
	
	UFUNCTION()
		void OnRep_Killer();
	UFUNCTION(BlueprintImplementableEvent)
		void ShowDeathScreen();
protected:
	

	UFUNCTION(Server, Reliable)
		void ServerOnFire();
		void ServerOnFire_Implementation();

	
	void OnFire();
	void StartFire();
	void ClientFire();
	
	void OnResetVR();

	
	void MoveForward(float Val);

	
	void MoveRight(float Val);

	
	void TurnAtRate(float Rate);

	
	void LookUpAtRate(float Rate);

	struct TouchData
	{
		TouchData() { bIsPressed = false;Location=FVector::ZeroVector;}
		bool bIsPressed;
		ETouchIndex::Type FingerIndex;
		FVector Location;
		bool bMoved;
	};
	void BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location);
	TouchData	TouchItem;
	
protected:
	
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	
	bool EnableTouchscreenMovement(UInputComponent* InputComponent);

public:
	
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

};

