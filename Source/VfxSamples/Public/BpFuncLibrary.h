// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BpFuncLibrary.generated.h"

/**
 * 
 */
UCLASS()
class VFXSAMPLES_API UBpFuncLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	static FTransform GetWorldSpaceTransform(FReferenceSkeleton RefSkel, int32 BoneIdx);
public:
	UFUNCTION(BlueprintCallable, Category = "BPLibrary")
	static FTransform GetRefPoseBoneTransform(USkeletalMeshComponent* SkelMesh, FName BoneName);

	UFUNCTION(BlueprintCallable, Category = "BPLibrary")
	static FTransform GetBoneTransform(USkeletalMeshComponent* SkelMesh, FName BoneName);
};
