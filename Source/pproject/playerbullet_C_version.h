// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "playerbullet_C_version.generated.h"

UCLASS()
class PPROJECT_API Aplayerbullet_C_version : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Aplayerbullet_C_version();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int damage = 1;

};
