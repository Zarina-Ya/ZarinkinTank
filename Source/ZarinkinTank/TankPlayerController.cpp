// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "GameFramework/PlayerController.h"
#include "TankPawn.h"
#include "ZarinkinTank.h"
#include "DrawDebughelpers.h"
ATankPlayerController::ATankPlayerController()
{
	bShowMouseCursor = true;
}

void ATankPlayerController::SetupInputComponent()// для обработки inputов
{
	Super::SetupInputComponent();
	InputComponent->BindAxis("MoveForward", this, &ATankPlayerController::MoveForward);// Привязывает функцию делегата к оси, определенной в параметрах проекта. Возвращаемая ссылка гарантированно действительна только до тех пор, пока не будет связана другая ось.
    // связываем команду «‎MoveForward» с методом MoveForward класса ATankPlayerController

	
	InputComponent->BindAxis("RotateRight", this, &ATankPlayerController::RotateRight);

	InputComponent->BindAction("Fire", IE_Pressed, this, &ATankPlayerController::Fire);
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector MouseDirection;
	DeprojectMousePositionToWorld(MousePose, MouseDirection);// MousePose-сохранит позицию  . MouseDirection - сохранит напрвление 
	UE_LOG(LogCustom, Verbose, TEXT("MousePose = %s, MouseDirection = %f"), *MousePose.ToString(), *MouseDirection.ToString());

	FVector PawnPose = TankPawn->GetActorLocation();
	MousePose.Z = PawnPose.Z;
	FVector Dir = MousePose - PawnPose;// направление от танка до мыши, получили напрвление кот нужно единичной длины , следовательно его нужно будет нормализовать 
	Dir.Normalize();
	MousePose = PawnPose + Dir * 1000.f; // напраление умноженное на некоторую константу , где бы у нас не находилась мышь , мы всегда будем удалены от танка на радиус = 1000
	DrawDebugLine(GetWorld(), PawnPose, MousePose, FColor::Green, false, 0.1f, 0.f, 0.5f);// GetWorld() - берем текущий мир , в котором мы находимся / PawnPose - начальная точка линиии . false - нужно ли стирать кажыдй кадр линию 
}


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();// получаем указатель на объект связанный с этим контроллером 

	TankPawn = Cast<ATankPawn>(GetPawn());// полученный указатель приводим к типу ATankPawn. Cast преобразоывывает в опреенный класс
}

void ATankPlayerController::MoveForward(float AxisValue)
{
	TankPawn->MoveForward(AxisValue);
}



void ATankPlayerController::RotateRight(float AxisValue)
{
	TankPawn->RotateRight(AxisValue);
}

void ATankPlayerController::Fire()
{
	TankPawn->Fire();
}
