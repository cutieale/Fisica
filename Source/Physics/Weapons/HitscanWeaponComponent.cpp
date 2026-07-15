// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/HitscanWeaponComponent.h"
#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/GameplayStatics.h>
#include "PhysicsCharacter.h"
#include "PhysicsWeaponComponent.h"

void UHitscanWeaponComponent::Fire()
{
	Super::Fire();

	FVector vCharView = Character->FirstPersonCameraComponent->GetComponentRotation().Vector(); //dispara dir cam			
	FVector vStart = Character->FirstPersonCameraComponent->GetComponentLocation();//dispara desde cam
	float fRange = 100000.f; //rango arma
	FVector vEnd = vStart + vCharView * fRange; //dispara hasta rango

	if(GetWorld()->LineTraceSingleByChannel(m_HitResult, vStart, vEnd, ECC_Visibility))
	{
		// DrawDebugSphere(GetWorld(), m_HitResult.Location, 10.f, 12, FColor::Green, false, 1.f);
		m_HitResult.GetComponent()->AddImpulse(vCharView * 100000.f);
		
	}
}
