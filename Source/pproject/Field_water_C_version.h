// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyGameModeBase.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h" // FVector GetComponentLocation() const
#include "Field_water_C_version.generated.h"

UCLASS()
class PPROJECT_API AField_water_C_version : public AActor
{
	GENERATED_BODY()
		UPROPERTY()
		USceneComponent* Root;
	UPROPERTY(EditAnywhere, Category = "gaheringbox")
		class UBoxComponent* gaheringbox;
	UPROPERTY(EditAnywhere, Category = "playersensor")
		class UBoxComponent* playersensor;
	UPROPERTY(EditAnywhere, Category = "spawnlocation")
		class UStaticMeshComponent* spawnlocation;
	UPROPERTY(EditAnywhere, Category = "mainobject_location")
		class UStaticMeshComponent* mainobject_location;
public:	
	// Sets default values for this actor's properties
	AField_water_C_version();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UFUNCTION()
		void gatheringcooltimer();

	bool Gathering_cooltime_on = false;
	bool farming_available_range = false;
	bool Branch_Gate = true;

	FTimerHandle CountdownTimerHandle;
	int CountdownTime_gatheringcooltime = 0;

	UPROPERTY(EditAnywhere)
		bool Playeronlava = false;

	UFUNCTION()
		void boxOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void playerarrive(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void boxOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
		void playerleft(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
