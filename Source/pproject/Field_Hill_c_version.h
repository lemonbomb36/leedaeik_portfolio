// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyGameModeBase.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h" // FVector GetComponentLocation() const
#include "Field_Hill_c_version.generated.h"

UCLASS()
class PPROJECT_API AField_Hill_c_version : public AActor
{
	GENERATED_BODY()
	UPROPERTY()
		USceneComponent* Root;
	UPROPERTY(EditAnywhere, Category = "spawnlocation")
		class UStaticMeshComponent* spawnlocation;
	UPROPERTY(EditAnywhere, Category = "mainobject_location")
		class UStaticMeshComponent* mainobject_location;
public:	
	// Sets default values for this actor's properties
	AField_Hill_c_version();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
