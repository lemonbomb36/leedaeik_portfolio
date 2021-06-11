// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyGameModeBase.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "thrownweapon_c_version.generated.h"

UCLASS()
class PPROJECT_API Athrownweapon_c_version : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Athrownweapon_c_version();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void blueprint_actor_spawn(const TCHAR* Filename, FVector location, FRotator rotation);
	float bulletspawnlocation = 300.0f;
};
