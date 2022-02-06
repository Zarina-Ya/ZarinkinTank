// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPawn.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Math/UnrealMathUtility.h"
#include "ZarinkinTank.h"

ATankPawn::ATankPawn()
{
 	// ��������� �� ����������� ������ Tick
	PrimaryActorTick.bCanEverTick = true;
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tank Body"));
	RootComponent = BodyMesh;

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Body"));
	TurretMesh->SetupAttachment(BodyMesh); // ��������� ��������� ��������� TurretMesh � BodyMesh.

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(BodyMesh);
	SpringArm->bDoCollisionTest = false; // ���� �������� ����� true, ��������� ���� �� ������������ � ������� ProbeChannel � ProbeSize, ����� ������������� ��������� ������ �� �������.
	SpringArm->bInheritPitch = false;// ��������� ��� ��� ������ ����� �� 90 ��������
	SpringArm->bInheritRoll = false;
	SpringArm->bInheritYaw = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);


}

void ATankPawn::MoveForward(float AxisValue)
{
	TargetForwardAxisValue = AxisValue;
}



void ATankPawn::RotateRight(float AxisValue)
{
	TargetRotateAxisValue = AxisValue;
}

// Called when the game starts or when spawned
void ATankPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector currentLocation = GetActorLocation();// ������� ������� ��������� ������ � ����
	FVector forwardVector = GetActorForwardVector();// ������� ����������� ����� ������ � ���� �������
	FVector movePosition = currentLocation + forwardVector * TargetForwardAxisValue * MoveSpeed * DeltaTime;// ���������� � ����� ������� ������� �������� 
	SetActorLocation(movePosition, true);

	CurrentRotateAxisValue = FMath::Lerp(CurrentRotateAxisValue, TargetRotateAxisValue, RotationSmootheness);


	UE_LOG(LogCustom, Verbose, TEXT("CurrentRotateAxisValue = %f, TargetRotateAxisValue = %f"), CurrentRotateAxisValue, TargetRotateAxisValue);
	//CurrentRotateAxisValue = Math::Lerp( )
	FRotator currentRotation = GetActorRotation();// ����������� ��������� 
	float YawRotation = CurrentRotateAxisValue * RotationSpeed * DeltaTime;// ������ �������� 
	YawRotation += currentRotation.Yaw;// ���������� � ����� ��������� ������ ��������� 

	FRotator newRotation = FRotator(0.f, YawRotation, 0.f);

	SetActorRotation(newRotation);
	
	//CurrentRotateAxisValue = FMath::Lerp(CurrentRotateAxisValue, TargetRotateAxisValue, RotationSmootheness);
}



