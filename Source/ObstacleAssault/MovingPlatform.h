// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class OBSTACLEASSAULT_API AMovingPlatform : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMovingPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Platform settings")
	FVector moveVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Platform settings")
	FRotator rotationVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Platform settings")
	float distanceLimit;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Platform settings")
	float distanceTraveled;

private:

	void MovePlatform(float DeltaTime);

	void RotatePlatform(float DeltaTime);

	bool IsOvershooting() const;

	float GetDistanceTraveled() const;

	FVector startLocation;
};