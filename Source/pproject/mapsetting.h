// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyGameModeBase.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "mapsetting.generated.h"

UCLASS()
class PPROJECT_API Amapsetting : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Amapsetting();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	void blueprint_actor_spawn(const TCHAR* Filename, FVector location, FRotator rotation);

};
