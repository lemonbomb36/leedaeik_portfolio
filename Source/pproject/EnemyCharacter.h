// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyGameModeBase.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class PPROJECT_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, Category = "collision")
		class UBoxComponent* charactercollision;
	UPROPERTY(EditAnywhere, Category = "enemyattack")
		class USphereComponent* enemyattack;

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int monster_hp = 4;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool damagedelay0 = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool damagedelay1 = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool damagedelay2 = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool rushcooltime = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool rushcooltimegate = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool dagmaged_for_animation = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool attack = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool attack_range = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool damage_delay_to_player = false;


private:
	FTimerHandle CountdownTimerHandle; FTimerHandle CountdownTimerHandle2;
	int CountdownTime = 0; float CountdownTime2 = 0;

	UFUNCTION()
		void speedupcountdown();
	UFUNCTION()
		void speedupcountdown2();
	UFUNCTION()
		void attackspeed();
	int timer = 0;
	int rushcooltimegate2 = 0;

	UFUNCTION()
		void attackOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
