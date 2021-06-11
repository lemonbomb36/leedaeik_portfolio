// Fill out your copyright notice in the Description page of Project Settings.


#include "Rule_C_version.h"

bool gate_for_branch_once = true;


// Sets default values
ARule_C_version::ARule_C_version()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

//블루프린트 액터소환
void ARule_C_version::blueprint_actor_spawn(const TCHAR* Filename)
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
	World->SpawnActor<AActor>(GeneratedBP->GeneratedClass, GetActorLocation(), GetActorRotation(), SpawnParams);
}

//리셋액터
void ARule_C_version::Gamereset()
{
	//FVector Location(0.0f, 0.0f, 0.0f);		FRotator Rotation(0.0f, 0.0f, 0.0f);	FActorSpawnParameters SpawnInfo;
	const TCHAR* Filename = TEXT("/Game/player/gamereset.gamereset"); blueprint_actor_spawn(Filename);
}

// Called when the game starts or when spawned
void ARule_C_version::BeginPlay()
{
	Super::BeginPlay();	

	//플레이어에게 총알 10개 부여
	AMyGameModeBase* modebase = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	modebase->inventory.Add(FString("Bullet"), int32(10));
}

// Called every frame, 게임규칙
void ARule_C_version::Tick(float DeltaTime)
{
	
	AMyGameModeBase* modebase = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	Super::Tick(DeltaTime);


	//플레이어 체력 0되면 겜오버
	if (modebase->character_health <= 0)
	{
		if(gate_for_branch_once==true)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("characterhealth = 4")));
			gate_for_branch_once = false;
			FStringClassReference MyWidgetClassRef(TEXT("/Game/UI/Lose_screen.Lose_screen_C"));
			if (UClass* MyWidgetClass = MyWidgetClassRef.TryLoadClass<UUserWidget>())
			{
				UUserWidget* MyWidget = CreateWidget<UUserWidget>(GetWorld(), MyWidgetClass);
				MyWidget->AddToViewport();
				modebase->mainmenuswitch = true; gate_for_branch_once = true;
				Gamereset();
			}
		}
	}
	
	//메인 오브젝트 다 수집하면 승리
	if (modebase->inventory.Find(FString("Mainobject")) != NULL) // 널값 체크 안하면 에러나고 엔진 아예꺼짐. 특히 얘는 아예 데이터 없음에서 시작되므로
	{
		if (*modebase->inventory.Find(FString("Mainobject")) >= 4)
		{
			if (gate_for_branch_once == true)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("mainobject >= 4")));
				gate_for_branch_once = false;
				FStringClassReference MyWidgetClassRef(TEXT("/Game/UI/Win_screen.Win_screen_C"));
				if (UClass* MyWidgetClass = MyWidgetClassRef.TryLoadClass<UUserWidget>())
				{
					UUserWidget* MyWidget = CreateWidget<UUserWidget>(GetWorld(), MyWidgetClass);
					MyWidget->AddToViewport();
					modebase->mainmenuswitch = true; gate_for_branch_once = true;
					Gamereset();
				}
			}
		}

	}
	
}
