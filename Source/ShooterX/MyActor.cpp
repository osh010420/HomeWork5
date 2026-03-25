// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "Engine/Engine.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation(FVector(0, 50, 0));

	RunRandomMovementAndRotation();


}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyActor::Move(float Distance)
{
	FVector ForwardVector = GetActorForwardVector();
	FVector CurrentLocation = GetActorLocation();

	FVector NewLocation = CurrentLocation + (ForwardVector * Distance);

	SetActorLocation(NewLocation);

	PrintCurrentLocation();
}

void AMyActor::Turn(float Angle)
{
	FRotator CurrentRotation = GetActorRotation();

	CurrentRotation.Yaw += Angle;
	CurrentRotation.Pitch += Angle;
	CurrentRotation.Roll += Angle;


	SetActorRotation(CurrentRotation);
}

void AMyActor::RunRandomMovementAndRotation()
{
	for (int i = 0; i < 10; i++)
	{
		float RandomDistance = FMath::RandRange(100.0f, 300.0f);

		// 회전 각도 랜덤 설정 (예: -90 ~ 90)
		float RandomAngle = FMath::RandRange(-90.0f, 90.0f);

		// 로그
		UE_LOG(LogTemp, Warning, TEXT("Step %d"), i + 1);
		UE_LOG(LogTemp, Warning, TEXT("Move Distance: %f"), RandomDistance);
		UE_LOG(LogTemp, Warning, TEXT("Turn Angle: %f"), RandomAngle);

		// 회전 후 이동
		Turn(RandomAngle);
		Move(RandomDistance);
	}
}
void AMyActor::PrintCurrentLocation()
{
	FVector CurrentLocation = GetActorLocation();
	FRotator CurrentRotation = GetActorRotation();

	FString DebugMessage = FString::Printf(
		TEXT("Location -> X: %.2f, Y: %.2f, Z: %.2f | Rotation -> Pitch: %.2f, Yaw: %.2f, Roll: %.2f"),
		CurrentLocation.X,
		CurrentLocation.Y,
		CurrentLocation.Z,
		CurrentRotation.Pitch,
		CurrentRotation.Yaw,
		CurrentRotation.Roll
	);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, DebugMessage);
	}

	UE_LOG(LogTemp, Warning, TEXT("%s"), *DebugMessage);
}