// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyGameModeBase.h"
#include "GameFramework/Actor.h"
#include "Rule_C_version.generated.h"

UCLASS()
class PPROJECT_API ARule_C_version : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARule_C_version();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void Gamereset();
	void blueprint_actor_spawn(const TCHAR* Filename);
};
