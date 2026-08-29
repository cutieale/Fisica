#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsAnimationComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PHYSICS_API UPhysicsAnimationComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	USkeletalMeshComponent* m_Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	UCurveFloat* m_pCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	float m_fBlendDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	FName m_sOverrideAnimatedBoneName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	TArray<FName> m_tBreakableBones;

protected:
	float m_fBlendTimer = 0;
	FName m_sAnimatedBoneName;
	bool m_bEnabled = true;
	TArray<FName> m_tBrokenBones;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	// Sets default values for this component's properties
	UPhysicsAnimationComponent();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void TakePointDamage(AActor* DamagedActor, float Damage, class AController* InstigatedBy, FVector HitLocation, class UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const class UDamageType* DamageType, AActor* DamageCauser);

	UFUNCTION(BlueprintCallable)
	void EndComponent();

	void CustomSetAllBodiesBelowPhysicsBlendWeight(const FName& InBoneName, float PhysicsBlendWeight, bool bSkipCustomPhysicsType = false, bool bIncludeSelf = true);

};
