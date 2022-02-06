// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
class ATankPawn;
UCLASS()
class ZARINKINTANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
		ATankPawn* TankPawn;
	UPROPERTY()
		FVector MousePose;
public:
	ATankPlayerController();

	FVector GetMousePose(){return MousePose;}
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaTime) override;
	void MoveForward(float AxisValue);
	void RotateRight(float AxisValue);
};
