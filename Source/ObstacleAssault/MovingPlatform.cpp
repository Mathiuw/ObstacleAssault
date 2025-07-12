// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	startLocation = GetActorLocation();

	UE_LOG(LogTemp, Display, TEXT("Start location set"));

	//DEBUG
	float boxSize = 25;

	DrawDebugBox(GetWorld(), GetActorLocation(), FVector(boxSize, boxSize, boxSize), FColor::Red, true, -1, 0, 3);

	if (distanceLimit > 0)
	{
		FVector desiredPosition = GetActorLocation() + moveVelocity.GetSafeNormal() * distanceLimit;

		//Draw trajectory line
		DrawDebugLine(GetWorld(), GetActorLocation(), desiredPosition, FColor::Red, true, -1, 0, 3);
		//Draw location cubes
		DrawDebugBox(GetWorld(), desiredPosition, FVector(boxSize, boxSize, boxSize), FColor::Red, true, -1, 0, 3);
	}
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
}

//Move platform foward and invert if gone too far
void AMovingPlatform::MovePlatform(float DeltaTime)
{
	if (IsOvershooting())
	{
		FVector moveDirection = moveVelocity.GetSafeNormal();

		startLocation = startLocation + moveDirection * distanceLimit;
		SetActorLocation(startLocation);

		moveVelocity = -moveVelocity;
	}
	else
	{
		distanceTraveled = GetDistanceTraveled();

		AddActorLocalOffset(moveVelocity * DeltaTime);
	}
}

//Rotate the platform
void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	AddActorLocalRotation(rotationVelocity * DeltaTime);
}

//Check if the platform surpassed the limit
bool AMovingPlatform::IsOvershooting() const
{
	return GetDistanceTraveled() > distanceLimit;
}

//Return the distance that the platform has moved
float AMovingPlatform::GetDistanceTraveled() const
{
	return FVector::Distance(GetActorLocation(), startLocation);
}