// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun_c_version.h"
#include <Runtime\Engine\Classes\Kismet\KismetMathLibrary.h>

int32* usedbullet;
float bulletspawnlocation=300.0f;

// Sets default values
AGun_c_version::AGun_c_version()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


// Called when the game starts or when spawned
void AGun_c_version::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("gun!")));
}

// Called every frame 총알이 발사되는과정
void AGun_c_version::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AMyGameModeBase* modebase = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	//attack 이벤트바인딩
	if (modebase->player_attack == true) // 공격버튼명령 들어옴
 	{
		modebase->player_attack = false;
		if ((modebase->inventory.Contains(FString("bullet"))) == true)
		{

			MakeNoise(1.0f, NULL, FVector(0.0f, 0.0f, 0.0f), 400.0f, FName("player"));
			//총알발사
			const TCHAR* Filename = TEXT("/Game/weapon/bpplayerbullet.bpplayerbullet");
			FVector location = modebase->character_location + (bulletspawnlocation * (UKismetMathLibrary::GetForwardVector(modebase->character_rotation)));
			FRotator rotation = modebase->character_rotation;
			blueprint_actor_spawn(Filename, location, rotation);

			//인벤토리에서 총알 소모 반영
			usedbullet = modebase->inventory.Find(FString("bullet"));
			if ( (*usedbullet)-1 > 0 )
			{
				modebase->inventory.Add(FString("bullet"), ((*usedbullet)-1));
			}
			else // 총알이 아예 0이 될 경우
			{
				modebase->inventory.Remove(FString("bullet"));
			}

		}
	}
}

//블루프린트 액터 소환
void AGun_c_version::blueprint_actor_spawn(const TCHAR* Filename, FVector location, FRotator rotation)
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

