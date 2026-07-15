// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/ProjectileWeaponComponent.h"
#include "PhysicsCharacter.h"
#include "PhysicsProjectile.h"
#include "Camera/CameraComponent.h"

void UProjectileWeaponComponent::Fire()
{
	Super::Fire();
	FVector vCharView = Character->FirstPersonCameraComponent->GetComponentRotation().Vector(); //dispara dir cam	
	FVector vStart = Character->FirstPersonCameraComponent->GetComponentLocation();
	float fRange = 100000.f; //rango arma
	FVector vEnd = vStart + vCharView * 100000.f; //dispara hasta rango
	FVector vSpawnLocation = GetOwner()->GetActorLocation() + GetComponentRotation().RotateVector(MuzzleOffset); //desde arma
	FHitResult oHitResult;


	if (GetWorld()->LineTraceSingleByChannel(oHitResult, vStart, vEnd, ECC_Visibility))
	{
		DrawDebugLine(GetWorld(), vSpawnLocation, vEnd, FColor::Green, false, 1.f);
		FVector vSpawnDir = (oHitResult.ImpactPoint - vSpawnLocation).GetSafeNormal();	
		//oHitResult.GetComponent()->AddImpulse(vCharView * 100000.f);
		FActorSpawnParameters oSpawnParams;
		oSpawnParams.Owner = GetOwner();
		//oSpawnParams.Instigator = GetInstigator();
		oSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		APhysicsProjectile* pProjectile = GetWorld()->SpawnActor<APhysicsProjectile>(m_ProjectileClass, vSpawnLocation, vSpawnDir.Rotation(), oSpawnParams);
		if (pProjectile)
		{
			pProjectile->m_OwnerWeapon = this;
		}
	}
	else
	{
		oHitResult.ImpactPoint = vEnd;
		DrawDebugLine(GetWorld(), vSpawnLocation, vEnd, FColor::Green, false, 1.f);
		FVector vSpawnDir = (vEnd - vSpawnLocation).GetSafeNormal();
		//oHitResult.GetComponent()->AddImpulse(vCharView * 100000.f);
		FActorSpawnParameters oSpawnParams;
		oSpawnParams.Owner = GetOwner();
		//oSpawnParams.Instigator = GetInstigator();
		oSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		APhysicsProjectile* pProjectile = GetWorld()->SpawnActor<APhysicsProjectile>(m_ProjectileClass, vSpawnLocation, vSpawnDir.Rotation(), oSpawnParams);
		if (pProjectile)
		{
			pProjectile->m_OwnerWeapon = this;
		}
	}
}

