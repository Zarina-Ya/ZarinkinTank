// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"
#include "Components/SceneComponent.h"
#include "Components/ArrowComponent.h"
#include "TimerManager.h"

//class USceneComponent;
// Sets default values
ACannon::ACannon()
{
	PrimaryActorTick.bCanEverTick = false;// ��������� ������ ���� �� ����� 
	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));// ��������� ������� ���������� � ������� ������ ���������� �������� = ( Location , Rotation , Scale  )

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

void ACannon::EndPlay(const EEndPlayReason::Type EndPlayReason)// ���������� ��� ���� , ����� � ������ ������ ������ , ������ �� ��������� ��������
{
	Super::EndPlay(EndPlayReason);
	GetWorld()->GetTimerManager().ClearTimer(RealoadTimerHendle);
}

void ACannon::Fire()
{
	if (!bReadyToFire) { return; }// ���� �� ��� ��������������
	bReadyToFire = false;
	
	if (Type == ECannonType::Fireprojectile) {
		GEngine->AddOnScreenDebugMessage(10, 1.f, FColor::Green, TEXT("Fire - projectile"));// 10 - ���������� ���� ��� �������������� ������������� ���������� ������ � ���� �� ���������.
	}
	else {
		GEngine->AddOnScreenDebugMessage(10, 1.f, FColor::Green, TEXT("Fire - trace"));// 10 - ���������� ���� ��� �������������� ������������� ���������� ������ � ���� �� ���������.

	}

	GetWorld()->GetTimerManager().SetTimer(RealoadTimerHendle, this, &ACannon::Reload, 1.f/FireRate, false);

	//GetWorld - �������� ���������� � ���� 
	// GetTimerManager - �������� ������ �� ���� �������� �������
	
}

void ACannon::Reload()
{
	bReadyToFire = true;
}

bool ACannon::IsReadyToFire()
{
	return bReadyToFire;
}



