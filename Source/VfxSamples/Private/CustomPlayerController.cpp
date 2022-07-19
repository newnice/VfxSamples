// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomPlayerController.h"
#include "HitReceivedComponent.h"


void ACustomPlayerController::Shoot()
{
	FHitResult Result;
	if (GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Result))
	{
		const auto BoneName = Result.BoneName;
		if(!Result.Actor.IsValid() || !BoneName.IsValid())
			return;

		const auto HitComponent = Cast<UHitReceivedComponent>(Result.Actor.Get()->GetComponentByClass(UHitReceivedComponent::StaticClass()));
		if (HitComponent)
		{	
			HitComponent->AddBoneHit(BoneName, Result.ImpactPoint);
		}
	}
}

void ACustomPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("Shoot", IE_Pressed, this, &ACustomPlayerController::Shoot);
}

ACustomPlayerController::ACustomPlayerController()
{
	bShowMouseCursor = true;
}
