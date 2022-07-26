// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CustomPlayerController.generated.h"

UCLASS()
class VFXSAMPLES_API ACustomPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	void Shoot();
	virtual void SetupInputComponent() override;
public:
	ACustomPlayerController();
};
