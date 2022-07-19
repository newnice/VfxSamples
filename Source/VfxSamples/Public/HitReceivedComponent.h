// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HitReceivedComponent.generated.h"

USTRUCT(BlueprintType)
struct VFXSAMPLES_API FHitData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FName BoneName;

	UPROPERTY(BlueprintReadOnly)
	FVector LocalImpactPoint;

	UPROPERTY(BlueprintReadOnly)
	float HitTime;

	friend uint32 GetTypeHash(const FHitData& HitData)
	{
		return HashCombine(HashCombine(GetTypeHash(HitData.BoneName), GetTypeHash(HitData.LocalImpactPoint)), GetTypeHash(HitData.HitTime));
	}

	friend bool operator==(const FHitData& HitData1, const FHitData& HitData2)
	{
		return HitData1.BoneName == HitData2.BoneName && HitData1.LocalImpactPoint == HitData2.LocalImpactPoint && HitData1.HitTime == HitData2.HitTime;
	}
};



DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBoneHitDelegate, FHitData, HitData);

UCLASS(ClassGroup=(Custom), Blueprintable)
class VFXSAMPLES_API UHitReceivedComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHitReceivedComponent();

	UPROPERTY(EditAnywhere)
	float ExpirationTime = 5;

	UPROPERTY(EditAnywhere)
	float MaxHitCount = 1;

	void AddBoneHit(const FName& BoneName, FVector ImpactPoint);
protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintReadOnly)
	TWeakObjectPtr<USkeletalMeshComponent> OwnerSM;

	UPROPERTY(BlueprintReadOnly)
	TArray<FHitData> HitBones;

	UPROPERTY(BlueprintAssignable)
	FBoneHitDelegate HitAdded;

	UPROPERTY(BlueprintAssignable)
	FBoneHitDelegate HitRemoved;
};
