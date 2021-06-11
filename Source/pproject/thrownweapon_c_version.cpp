// Fill out your copyright notice in the Description page of Project Settings.


#include "thrownweapon_c_version.h"
#include <Runtime\Engine\Classes\Kismet\KismetMathLibrary.h>



// Sets default values
Athrownweapon_c_version::Athrownweapon_c_version()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void Athrownweapon_c_version::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Athrownweapon_c_version::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	

	AMyGameModeBase* modebase = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	//attack 이벤트바인딩
	if (modebase->player_attack == true)
	{
		modebase->player_attack = false;
		if ((modebase->inventory.Contains(FString("bomb"))) == true)
		{
			//투척이벤트
			const TCHAR* Filename = TEXT("/Game/weapon/Bomb.Bomb");
			FVector location = modebase->character_location + (bulletspawnlocation * (UKismetMathLibrary::GetForwardVector(modebase->character_rotation)));
			FRotator rotation = modebase->character_rotation;
			blueprint_actor_spawn(Filename, location, rotation);

			//인벤토리 반영
			int* usedbullet = modebase->inventory.Find(FString("bomb"));
			if ((*usedbullet) - 1 > 0)
			{
				modebase->inventory.Add(FString("bomb"), ((*usedbullet) - 1));
			}
			else
			{
				modebase->inventory.Remove(FString("bomb"));
			}

		}
	}

	
}

void Athrownweapon_c_version::blueprint_actor_spawn(const TCHAR* Filename, FVector location, FRotator rotation)
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