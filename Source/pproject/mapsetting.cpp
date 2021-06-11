// Fill out your copyright notice in the Description page of Project Settings.

#include <array>
#include <algorithm> // shuffle
#include "math.h" // randrange
#include "mapsetting.h"


// Sets default values
Amapsetting::Amapsetting()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void Amapsetting::BeginPlay()
{
	Super::BeginPlay();

	int loopvar = 0; int loopvar2 = 0; int mainobject_count = 4;
	FVector location = FVector(0, 0, 0);	float location_x; float location_y;
	FRotator rotation = FRotator(0, 0, 0);
	const TCHAR* Filename = TEXT("");
	AMyGameModeBase* modebase = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	TArray<FString> fieldlist_mapsetting = modebase->fieldlist;
	//¼ÅÇÃ
	int loopi = 0;
	int temprand = 0;
	FString temp = "";
	for (loopi = 0; loopi < 16; loopi++)
	{
		temprand = FMath::RandRange(0, 15);
		temp = fieldlist_mapsetting[loopi];
		fieldlist_mapsetting[loopi] = fieldlist_mapsetting[temprand];
		fieldlist_mapsetting[temprand] = temp;
	}
	//



	for (loopvar = 0; loopvar < 16; loopvar++)
	{
		location_x = ((loopvar / 4) * 4000) - 8310;
		location_y = ((loopvar % 4) * (-4000)) + 4730;
		location = FVector(location_x, location_y, 0);
		rotation = FRotator(0,(FMath::RandRange(0, 3) * 90),0); 
		
		if(fieldlist_mapsetting[loopvar] == FString("lava"))
		{
			Filename = TEXT("/Game/GroundObject/bpField_Lava.bpField_Lava");
			blueprint_actor_spawn(Filename, location, rotation);
		
		}
		else if(fieldlist_mapsetting[loopvar] == FString("rockmaze"))
		{
			Filename = TEXT("/Game/GroundObject/bpfield_rock.bpfield_rock");
			blueprint_actor_spawn(Filename, location, rotation);
			
		}
		else if (fieldlist_mapsetting[loopvar] == FString("hill"))
		{
			Filename = TEXT("/Game/GroundObject/bpField_Hill.bpField_Hill");
			blueprint_actor_spawn(Filename, location, rotation);
			
		}
		else if (fieldlist_mapsetting[loopvar] == FString("water"))
		{
			Filename = TEXT("/Game/GroundObject/bpField_water.bpField_water");
			blueprint_actor_spawn(Filename, location, rotation);
			
		}
		else if (fieldlist_mapsetting[loopvar] == FString("forest")) 
		{
			Filename = TEXT("/Game/GroundObject/bpField_Forest.bpField_Forest");
			blueprint_actor_spawn(Filename, location, rotation);
			
		}
		else if (fieldlist_mapsetting[loopvar] == FString("flat"))
		{
			Filename = TEXT("/Game/GroundObject/bpField_Grassland.bpField_Grassland");
			blueprint_actor_spawn(Filename, location, rotation);
			
		}
	
	}

	modebase->mapsetchekcing_for_monsterspawn = true;
	Filename = TEXT("/Game/monster/bpMonsterSpawnSystem.bpMonsterSpawnSystem");
	blueprint_actor_spawn(Filename, location, rotation);


	//¼ÅÇÃ
	TArray<FVector> mainobjectlocation_mapsetting = modebase->mainobjectlocation;
	temprand = 0; loopi = 0;
	FVector temp2 = FVector(0, 0, 0);

	
	for (loopi = 0; loopi < 16; loopi++)
	{
		temprand = FMath::RandRange(0, 15);
		temp2 = mainobjectlocation_mapsetting[loopi];
		mainobjectlocation_mapsetting[loopi] = mainobjectlocation_mapsetting[temprand];
		mainobjectlocation_mapsetting[temprand] = temp2;
	}
	//

	for (loopvar2 = 0; loopvar2 < mainobject_count; loopvar2++)
	{
	Filename = TEXT("/Game/GroundObject/bpmainobject.bpmainobject");
	location = mainobjectlocation_mapsetting[loopvar2];
	blueprint_actor_spawn(Filename, location, rotation);
	}

	Destroy();
}

// Called every frame
void Amapsetting::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void Amapsetting::blueprint_actor_spawn(const TCHAR* Filename, FVector location, FRotator rotation)
{
	//const TCHAR* Filename = TEXT("");
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

	UWorld* World = GetWorld();
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	World->SpawnActor<AActor>(GeneratedBP->GeneratedClass, location, rotation, SpawnParams);
}

