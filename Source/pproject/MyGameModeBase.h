 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Math/RandomStream.h"
#include "Containers/Array.h"
#include "CoreMinimal.h"
#include <Map>
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"



/**
 *
 */
UCLASS()
class PPROJECT_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	// 게임 내 공유값

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int enemy_character1_deadcount = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int enemy_character2_deadcount = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FRandomStream randomvalue; //randomvalue.Initialize(0);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float character_speed = 700;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float character_default_speed = 700;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float character_health = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float character_health_max = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector character_location = FVector(0, 0, 0);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FRotator character_rotation = FRotator(0, 0, 0); // control rotation
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool player_attack = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FString> fieldlist = { "lava","lava", "rockmaze", "rockmaze", "rockmaze", "hill", "water", "water", "water", "forest", "forest", "forest", "forest", "flat", "flat", "flat" };
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool mapsetchekcing_for_monsterspawn = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FVector> enemylocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TMap<FString, int32> inventory; // 처음총알은 플레이어가 Rule_C_version.cpp가 선언
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString inventory_temporary;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FTransform blank_actor_transform;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString farming_available = "None";
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FVector> mainobjectlocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool mainobjectget = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int mainobjectgetcounting = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int enemy1_count = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int enemy2_count = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool inventory_is_opened = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int monsterspawnnumber = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float character_on_flame_time = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool mainmenuswitch = false;

};
