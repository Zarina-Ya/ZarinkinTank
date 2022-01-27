// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPawn.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

ATankPawn::ATankPawn()
{
 	// ”становка на пользовани€ метода Tick
	PrimaryActorTick.bCanEverTick = true;
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tank Body"));
	RootComponent = BodyMesh;

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Body"));
	TurretMesh->SetupAttachment(BodyMesh); // ѕрив€зали созданный компонент TurretMesh к BodyMesh.

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(BodyMesh);
	SpringArm->bDoCollisionTest = false; // ≈сли значение равно true, выполните тест на столкновение с помощью ProbeChannel и ProbeSize, чтобы предотвратить обрезание камеры на уровень.
	SpringArm->bInheritPitch = false;// ќтключаем так как камера будет на 90 градусов
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

	FVector currentLocation = GetActorLocation();// получим текущее положение актора в мире
	FVector forwardVector = GetActorForwardVector();// ѕолучим направление танка вперед в виде вектора
	FVector movePosition = currentLocation + forwardVector * MoveSpeed * TargetForwardAxisValue * DeltaTime;// ѕ–ибавл€ем к нашей текущей позиции смещение 
	SetActorLocation(movePosition, true);

	FVector currentLocationForRight = GetActorLocation();// получим текущее положение актора в мире
	FVector rightVector = GetActorRightVector();// получим напровление танка в сторону
	FVector moveRightPosition = currentLocationForRight + rightVector * MoveSpeed * TargetRightAxisValue * DeltaTime;
	SetActorLocation(moveRightPosition, true);
}



