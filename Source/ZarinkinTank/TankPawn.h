// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankPawn.generated.h"

class UStaticMeshComponent;
class UCameraComponent;
class USpringArmComponent;
UCLASS()
class ZARINKINTANK_API ATankPawn : public APawn
{
	GENERATED_BODY()

protected:

	/// <summary>
	/// VisibleDefaultsOnly - будет виден только при настройки класса ( «Значения по умолчанию» в данном контексте означают, что это свойство будет отображаться в классах Blueprint )
	/// Это фактически способ сделать свойство видимым, но доступным только для чтения.
	/// BrueprintReadWrite - возможность чтения и редактирования значения в блупринтах 
	/// Category - задает котегорию компонента( удобно для поиска в движке )
	/// EditDefaultsOnly - Указывает, что это свойство может быть изменено окнами свойств, но только на архетипах. Этот спецификатор несовместим с любым из "видимых" спецификаторов.
	/// </summary>
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* BodyMesh;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = " Components")
		UStaticMeshComponent* TurretMesh;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UCameraComponent* Camera;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		USpringArmComponent* SpringArm;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
		float MoveSpeed = 100.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
		float RotationSpeed = 100.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
		float RotationSmootheness = 0.1f;// 10% необходимо для интерполяции -- гладкость поворотов

	
	float TargetForwardAxisValue = 0.f;
	float TargetRotateAxisValue = 0.f;
	float CurrentRotateAxisValue = 0.f;// переменная для сглаживания 
public:
	// Конструктор нашего объекта и Инициализация
	ATankPawn();

	UFUNCTION()
		void MoveForward(float AxisValue);

	UFUNCTION()
		void RotateRight(float AxisValue);

protected:
	//  начало работы 
	virtual void BeginPlay() override;

public:	
	// Отрисовка в самой игре 
	virtual void Tick(float DeltaTime) override;


};
