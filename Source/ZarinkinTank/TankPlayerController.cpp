// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "GameFramework/PlayerController.h"
#include "TankPawn.h"
ATankPlayerController::ATankPlayerController()
{
}

void ATankPlayerController::SetupInputComponent()// для обработки inputов
{
	Super::SetupInputComponent();
	InputComponent->BindAxis("MoveForward", this, &ATankPlayerController::MoveForward);// Привязывает функцию делегата к оси, определенной в параметрах проекта. Возвращаемая ссылка гарантированно действительна только до тех пор, пока не будет связана другая ось.
    // связываем команду «‎MoveForward» с методом MoveForward класса ATankPlayerController

	InputComponent->BindAxis("MoveRight", this, &ATankPlayerController::MoveRight);

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

void ATankPlayerController::MoveRight(float AxisValue)
{
	TankPawn->MoveRight(AxisValue);
}
