// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyGameModeBase.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Components/PrimitiveComponent.h"
#include "enemy_bullet_c_version.h" // 플레이어 총알피격
#include "GameFramework/CharacterMovementComponent.h"
#include "playerCharacter.generated.h"

UCLASS()
class PPROJECT_API AplayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AplayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 전후 이동 처리
	UFUNCTION()
		void MoveForward(float Value);

	// 좌우 이동 처리
	UFUNCTION()
		void MoveRight(float Value);

	// 키를 누르면 점프 플래그를 설정합니다.
	UFUNCTION()
		void StartJump();

	// 키를 떼면 점프 플래그를 지웁니다.
	UFUNCTION()
		void StopJump();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool E_press = false;

private:
	void blueprint_actor_spawn(const TCHAR* Filename);

	FTimerHandle CountdownTimerHandle;
	bool flamegate = true;
	int CountdownTime = 1;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
