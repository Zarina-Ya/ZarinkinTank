// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankPlayerController.h"
#include "Cannon.h"
#include "Components/ArrowComponent.h"
#include "TankPawn.generated.h"

class UStaticMeshComponent;
class UCameraComponent;
class USpringArmComponent;
class UArrowComponent;

UCLASS()
class ZARINKINTANK_API ATankPawn : public APawn
{
	GENERATED_BODY()

protected:

	/// <summary>
	/// VisibleDefaultsOnly - ����� ����� ������ ��� ��������� ������ ( ��������� �� ���������� � ������ ��������� ��������, ��� ��� �������� ����� ������������ � ������� Blueprint )
	/// ��� ���������� ������ ������� �������� �������, �� ��������� ������ ��� ������.
	/// BrueprintReadWrite - ����������� ������ � �������������� �������� � ���������� 
	/// Category - ������ ��������� ����������( ������ ��� ������ � ������ )
	/// EditDefaultsOnly - ���������, ��� ��� �������� ����� ���� �������� ������ �������, �� ������ �� ���������. ���� ������������ ����������� � ����� �� "�������" ��������������.
	/// </summary>
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* BodyMesh;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = " Components")
		UStaticMeshComponent* TurretMesh;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UCameraComponent* Camera;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UArrowComponent* CannonSetupPoint; // ������� ����� 
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Turret|Cannon")
		TSubclassOf<ACannon> CannonClass;// ���������� ��� ������������

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
		float MoveSpeed = 100.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
		float RotationSpeed = 100.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
		float RotationSmootheness = 0.1f;// 10% ���������� ��� ������������ -- ��������� ���������

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
		float TurretRotationSmootheness = 0.5f;

	
	float TargetForwardAxisValue = 0.f;
	float TargetRotateAxisValue = 0.f;
	float CurrentRotateAxisValue = 0.f;// ���������� ��� ����������� 
public:
	// ����������� ������ ������� � �������������
	ATankPawn();

	UFUNCTION()
		void MoveForward(float AxisValue);

	UFUNCTION()
		void RotateRight(float AxisValue);

	UFUNCTION()
		void Fire();// ���������� �� �����������


protected:
	//  ������ ������ 
	virtual void BeginPlay() override;

	void SetupCannon();// ��������� ����� ����� � ���������� ������.

public:	
	// ��������� � ����� ���� 
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
		ATankPlayerController* TankController;
	UPROPERTY()
		ACannon* Cannon;
};
