// Fill out your copyright notice in the Description page of Project Settings.


#include "field_rock_c_version.h"
#include "playerCharacter.h" // 캐릭터 접촉

// Sets default values
Afield_rock_c_version::Afield_rock_c_version()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	
	//아이템 채집판정박스
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	gaheringbox = CreateDefaultSubobject<UBoxComponent>(TEXT("gaheringbox"));
	gaheringbox->InitBoxExtent(FVector(32.0f, 32.0f, 32.0f));
	gaheringbox->SetupAttachment(Root);
	gaheringbox->OnComponentBeginOverlap.AddDynamic(this, &Afield_rock_c_version::boxOverlapBegin);
	gaheringbox->OnComponentEndOverlap.AddDynamic(this, &Afield_rock_c_version::boxOverlapEnd);
	
	//tick on/off
	playersensor = CreateDefaultSubobject<UBoxComponent>(TEXT("playersensor"));
	playersensor->InitBoxExtent(FVector(32.0f, 32.0f, 32.0f));
	playersensor->SetupAttachment(Root);
	playersensor->OnComponentBeginOverlap.AddDynamic(this, &Afield_rock_c_version::playerarrive);
	playersensor->OnComponentEndOverlap.AddDynamic(this, &Afield_rock_c_version::playerleft);
	
	spawnlocation2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("spawnlocation2"));
	spawnlocation2->SetupAttachment(Root);

	mainobject_location2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mainobject_location2"));
	mainobject_location2->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void Afield_rock_c_version::BeginPlay()
{
	Super::BeginPlay();
	AMyGameModeBase* modebase = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	modebase->enemylocation.Add(FVector(spawnlocation2->GetComponentLocation()));
	modebase->mainobjectlocation.Add(FVector(mainobject_location2->GetComponentLocation()));
}

// Called every frame 플레이어가 범위에 없으면 작동안함
void Afield_rock_c_version::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//아이템 채집 쿨타임
	AplayerCharacter* pcharacter = Cast<AplayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (Branch_Gate == true)
	{
		if (farming_available_range && pcharacter->E_press)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("cooltime start")));
			Branch_Gate = false;
			Gathering_cooltime_on = true;
			CountdownTime_gatheringcooltime = 10; 
			GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &Afield_rock_c_version::gatheringcooltimer, 1.0f, true);

		}

	}

	
}

//채집박스로 들어가면
void Afield_rock_c_version::boxOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AplayerCharacter* pcharacter = Cast<AplayerCharacter>(OtherActor);
	AMyGameModeBase* modebase = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	if (pcharacter != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("on range")));
		farming_available_range = true;
		if (Gathering_cooltime_on == false)
		{
			modebase->farming_available = "Mb";
		}
		else
		{
			modebase->farming_available = "";
		}
	}
}
//채집박스에서 나가면
void Afield_rock_c_version::boxOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AplayerCharacter* pcharacter = Cast<AplayerCharacter>(OtherActor);
	AMyGameModeBase* modebase = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	if (pcharacter != nullptr)
	{
		farming_available_range = false;
		modebase->farming_available = "";
	}
}
//tick 발동
void Afield_rock_c_version::playerarrive(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AplayerCharacter* pcharacter = Cast<AplayerCharacter>(OtherActor);
	if (pcharacter != nullptr)
	{
		PrimaryActorTick.SetTickFunctionEnable(true);
	
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("playeronrock")));
		
	}

}
//tick 꺼짐
void Afield_rock_c_version::playerleft(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AplayerCharacter* pcharacter = Cast<AplayerCharacter>(OtherActor);
	if (pcharacter != nullptr)
	{
		PrimaryActorTick.SetTickFunctionEnable(false);
		
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("playerbyerock")));
		
	}

}


void Afield_rock_c_version::gatheringcooltimer()
{
	--CountdownTime_gatheringcooltime;
	if (CountdownTime_gatheringcooltime <= 0)
	{
		// 카운트다운이 완료되면 타이머를 중지
		GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
		Gathering_cooltime_on = false;
		Branch_Gate = true;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("cooltime off")));
	}

}
