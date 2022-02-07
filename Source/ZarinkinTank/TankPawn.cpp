// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPawn.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Math/UnrealMathUtility.h"
#include "ZarinkinTank.h"
#include <Runtime/Engine/Classes/Kismet/KismetMathLibrary.h>
#include "Cannon.h"

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

	CannonSetupPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Setup Point"));
	CannonSetupPoint->AttachToComponent(TurretMesh, FAttachmentTransformRules::KeepRelativeTransform);// устанавливает положение относительно предыдущего родител€
}

void ATankPawn::MoveForward(float AxisValue)
{
	TargetForwardAxisValue = AxisValue;
}



void ATankPawn::RotateRight(float AxisValue)
{
	TargetRotateAxisValue = AxisValue;
}

void ATankPawn::Fire()
{
	if (Cannon) {
		Cannon->Fire();
	}
	
}

// Called when the game starts or when spawned
void ATankPawn::BeginPlay()
{
	Super::BeginPlay();

	TankController = Cast< ATankPlayerController>(GetController());
	SetupCannon();//создание пушки 
}

void ATankPawn::SetupCannon()
{
	if (Cannon) {
		Cannon->Destroy();
		Cannon = nullptr;
	}
	FActorSpawnParameters Params;// структура параментров необходима€ дл€ метода SpawnActor
	Params.Instigator = this;// который несет ответственность за ущерб, нанесенный порожденным јктером.
	Params.Owner = this;//јктер, который породил этого јктера.

	Cannon = GetWorld()->SpawnActor<ACannon>(CannonClass, Params);
	Cannon->AttachToComponent(CannonSetupPoint, FAttachmentTransformRules::SnapToTargetNotIncludingScale);// прикрепл€етс€ на указанное место , но не повтор€ет размером родител€
}

// Called every frame
void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Tank Movement 
	FVector currentLocation = GetActorLocation();// получим текущее положение актора в мире
	FVector forwardVector = GetActorForwardVector();// ѕолучим направление танка вперед в виде вектора
	FVector movePosition = currentLocation + forwardVector * TargetForwardAxisValue * MoveSpeed * DeltaTime;// ѕ–ибавл€ем к нашей текущей позиции смещение 
	SetActorLocation(movePosition, true);

	// Tank Rotation 
	CurrentRotateAxisValue = FMath::Lerp(CurrentRotateAxisValue, TargetRotateAxisValue, RotationSmootheness);
	UE_LOG(LogCustom, Verbose, TEXT("CurrentRotateAxisValue = %f, TargetRotateAxisValue = %f"), CurrentRotateAxisValue, TargetRotateAxisValue);
	//CurrentRotateAxisValue = Math::Lerp( )
	FRotator currentRotation = GetActorRotation();// изначальеое положение 
	float YawRotation = CurrentRotateAxisValue * RotationSpeed * DeltaTime;// расчет поворота 
	YawRotation += currentRotation.Yaw;// прибавл€ем к новым рассчетам страое положение 
	FRotator newRotation = FRotator(0.f, YawRotation, 0.f);
	SetActorRotation(newRotation);
	
	//Turret Rotation
	if (TankController) {
		FVector MousePose = TankController->GetMousePose();// получаем из контроллера положение мыши // Ќаправление нам не нужно, поэтому мы в локальную переменную mouseDirection получаем значение и его больше не используем.

		FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), MousePose);// дл€ того, чтобы посчитать поворот до позциии мыши 
		FRotator CurrentRotation = TurretMesh->GetComponentRotation();
		TargetRotation.Pitch = CurrentRotation.Pitch;// ќ—таетс€ неизменным так как мы вращем только на оси Z
		TargetRotation.Roll = CurrentRotation.Roll;
		TurretMesh->SetWorldRotation(FMath::Lerp(CurrentRotation, TargetRotation, TurretRotationSmootheness));
	}
	


}



