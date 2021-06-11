// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterSpawnSystem_C_version.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
AMonsterSpawnSystem_C_version::AMonsterSpawnSystem_C_version()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}
//블루프린트 액터소환
void AMonsterSpawnSystem_C_version::blueprint_actor_spawn(const TCHAR* Filename, FVector location)
{
	UObject* SpawnActor = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, Filename));

	UBlueprint* GeneratedBP = Cast<UBlueprint>(SpawnActor);
	if (!SpawnActor)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CANT FIND OBJECT TO SPAWN")));
		return;
	}

	UClass* SpawnClass = SpawnActor->StaticClass();
	if (SpawnClass == NULL)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CLASS == NULL")));
		return;
	}
	// 5000 -500 93
	UWorld* World = GetWorld();
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	World->SpawnActor<AActor>(GeneratedBP->GeneratedClass, location, GetActorRotation(), SpawnParams);
}

// Called when the game starts or when spawned
void AMonsterSpawnSystem_C_version::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMonsterSpawnSystem_C_version::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//몬스터 스폰위치 값(랜덤)
	int randomint = FMath::RandRange(0,12); 
	int randomint2 = FMath::RandRange(0, 12);

	AMyGameModeBase* modebase = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	if (modebase->mapsetchekcing_for_monsterspawn == true)
	{

		//근접몬스터 소환
		if (modebase->enemy1_count<3 )
		{
			FVector location = modebase->enemylocation[randomint];
			const TCHAR* Filename = TEXT("/Game/monster/bpEnemyCharacter.bpEnemyCharacter"); 
			//const TCHAR* Filename = TEXT("/Game/monster/enemy-character.enemy-character");
			blueprint_actor_spawn(Filename, location);
			++modebase->enemy1_count;
		}

		//원거리몬스터 소환
		if (modebase->enemy2_count<3 )
		{
			FVector location = modebase->enemylocation[randomint2];
			const TCHAR* Filename = TEXT("/Game/monster/enemy-character2.enemy-character2"); blueprint_actor_spawn(Filename, location);
			++modebase->enemy2_count;
		}



	}


}