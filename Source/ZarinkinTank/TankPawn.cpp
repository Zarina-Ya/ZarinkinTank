// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPawn.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

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

void ATankPawn::MoveRight(float AxisValue)
{
	TargetRightAxisValue = AxisValue;
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
	FVector movePosition = currentLocation + forwardVector * MoveSpeed * TargetForwardAxisValue * DeltaTime;// ���������� � ����� ������� ������� �������� 
	SetActorLocation(movePosition, true);

	FVector currentLocationForRight = GetActorLocation();// ������� ������� ��������� ������ � ����
	FVector rightVector = GetActorRightVector();// ������� ����������� ����� � �������
	FVector moveRightPosition = currentLocationForRight + rightVector * MoveSpeed * TargetRightAxisValue * DeltaTime;
	SetActorLocation(moveRightPosition, true);
}



