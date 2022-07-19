// Fill out your copyright notice in the Description page of Project Settings.


#include "HitReceivedComponent.h"

#include "BpFuncLibrary.h"
#include "Kismet/KismetMathLibrary.h"

UHitReceivedComponent::UHitReceivedComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UHitReceivedComponent::BeginPlay()
{
	Super::BeginPlay();

	auto Owner = GetOwner();
	if (Owner)
	{
		OwnerSM = Cast<USkeletalMeshComponent>(Owner->GetComponentByClass(USkeletalMeshComponent::StaticClass()));
	}
}

void UHitReceivedComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (ExpirationTime > 0)
	{
		TArray<FHitData> HitsToRemove;
		const auto CurrentTime = GetWorld()->GetTimeSeconds();
		for (auto& HitData : HitBones)
		{
			if (HitData.HitTime + ExpirationTime < CurrentTime)
			{
				HitsToRemove.Add(HitData);
			}
		}
		for (auto& Hit : HitsToRemove)
		{
			HitBones.Remove(Hit);
			HitRemoved.Broadcast(Hit);
		}
	}
}

void UHitReceivedComponent::AddBoneHit(const FName& BoneName, FVector ImpactPoint)
{
	const auto CurrentTime = GetWorld()->GetTimeSeconds();
	FVector LocalImpact = FVector::ZeroVector;
	if (OwnerSM.IsValid())
	{
		const FTransform BoneTransform = UBpFuncLibrary::GetBoneTransform(OwnerSM.Get(), BoneName);
		LocalImpact = UKismetMathLibrary::InverseTransformLocation(BoneTransform, ImpactPoint);
	}

	if (MaxHitCount > 0 && HitBones.Num() == MaxHitCount)
	{
		const auto HitToRemove = HitBones[0];
		HitBones.RemoveAt(0);
		HitRemoved.Broadcast(HitToRemove);
	}
	const auto Hit = FHitData{BoneName, LocalImpact, CurrentTime};
	HitBones.Add(Hit);

	HitAdded.Broadcast(Hit);
}
