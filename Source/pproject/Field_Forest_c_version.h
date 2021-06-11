// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyGameModeBase.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h" // FVector GetComponentLocation() const
#include "Field_Forest_c_version.generated.h"

UCLASS()
class PPROJECT_API AField_Forest_c_version : public AActor
{
	GENERATED_BODY()
	UPROPERTY()
		USceneComponent* Root;
	UPROPERTY(EditAnywhere, Category = "gaheringbox")
		class UBoxComponent* gaheringbox;
	UPROPERTY(EditAnywhere, Category = "playersensor")
		class UBoxComponent* playersensor;
	UPROPERTY(EditAnywhere, Category = "spawnlocation2")
		class UStaticMeshComponent* spawnlocation2;
	UPROPERTY(EditAnywhere, Category = "mainobject_location2")
		class UStaticMeshComponent* mainobject_location2;
public:	
	// Sets default values for this actor's properties
	AField_Forest_c_version();

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


	UFUNCTION()
		void boxOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void playerarrive(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void boxOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
		void playerleft(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
