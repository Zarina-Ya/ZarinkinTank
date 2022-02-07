// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"
#include "Components/SceneComponent.h"
#include "Components/ArrowComponent.h"
#include "TimerManager.h"

//class USceneComponent;
// Sets default values
ACannon::ACannon()
{
	PrimaryActorTick.bCanEverTick = false;// отрисовка каждый кадр не нужна 
	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));// благодаря данному компаненту у данного актора появляется трансорм = ( Location , Rotation , Scale  )

	RootComponent = Root;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cannon Mesh"));
	Mesh->SetupAttachment(RootComponent);

	ProjectileSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(Mesh);



}

// Called when the game starts or when spawned
void ACannon::BeginPlay()
{
	Super::BeginPlay();
	bReadyToFire = true;
}

void ACannon::EndPlay(const EEndPlayReason::Type EndPlayReason)// необходимо для того , чтобы в случае смерти актора , таймер не продолжал работать
{
	Super::EndPlay(EndPlayReason);
	GetWorld()->GetTimerManager().ClearTimer(RealoadTimerHendle);
}

void ACannon::Fire()
{
	if (!bReadyToFire) { return; }// если мы еще перезарежаемся
	bReadyToFire = false;
	
	if (Type == ECannonType::Fireprojectile) {
		GEngine->AddOnScreenDebugMessage(10, 1.f, FColor::Green, TEXT("Fire - projectile"));// 10 - Уникальный ключ для предотвращения многократного добавления одного и того же сообщения.
	}
	else {
		GEngine->AddOnScreenDebugMessage(10, 1.f, FColor::Green, TEXT("Fire - trace"));// 10 - Уникальный ключ для предотвращения многократного добавления одного и того же сообщения.

	}

	GetWorld()->GetTimerManager().SetTimer(RealoadTimerHendle, this, &ACannon::Reload, 1.f/FireRate, false);

	//GetWorld - получаем информацию о мире 
	// GetTimerManager - получаем доступ ко всем функциям таймера
	
}

void ACannon::Reload()
{
	bReadyToFire = true;
}

bool ACannon::IsReadyToFire()
{
	return bReadyToFire;
}



