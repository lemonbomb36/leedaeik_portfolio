// Fill out your copyright notice in the Description page of Project Settings.


#include "Field_water_C_version.h"
#include "playerCharacter.h" // 캐릭터 접촉

// Sets default values
AField_water_C_version::AField_water_C_version()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	gaheringbox = CreateDefaultSubobject<UBoxComponent>(TEXT("gaheringbox"));
	gaheringbox->InitBoxExtent(FVector(32.0f, 32.0f, 32.0f));
	gaheringbox->SetupAttachment(Root);
	gaheringbox->OnComponentBeginOverlap.AddDynamic(this, &AField_water_C_version::boxOverlapBegin);
	gaheringbox->OnComponentEndOverlap.AddDynamic(this, &AField_water_C_version::boxOverlapEnd);

	//tick on/off
	playersensor = CreateDefaultSubobject<UBoxComponent>(TEXT("playersensor"));
	playersensor->InitBoxExtent(FVector(32.0f, 32.0f, 32.0f));
	playersensor->SetupAttachment(Root);
	playersensor->OnComponentBeginOverlap.AddDynamic(this, &AField_water_C_version::playerarrive);
	playersensor->OnComponentEndOverlap.AddDynamic(this, &AField_water_C_version::playerleft);

	spawnlocation = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("spawnlocation"));
	spawnlocation->SetupAttachment(Root);

	mainobject_location = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mainobject_location"));
	mainobject_location->SetupAttachment(Root);

}

// Called when the game starts or when spawned
void AField_water_C_version::BeginPlay()
{
	Super::BeginPlay();
	AMyGameModeBase* modebase = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	modebase->enemylocation.Add(FVector(spawnlocation->GetComponentLocation()));
	modebase->mainobjectlocation.Add(FVector(mainobject_location->GetComponentLocation()));
}

// Called every frame
void AField_water_C_version::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AplayerCharacter* pcharacter = Cast<AplayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (Branch_Gate == true)
	{
		if (farming_available_range && pcharacter->E_press)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("cooltime start")));
			Branch_Gate = false;
			Gathering_cooltime_on = true;
			CountdownTime_gatheringcooltime = 10;
			GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &AField_water_C_version::gatheringcooltimer, 1.0f, true);

		}

	}
}


//채집박스로 들어가면
void AField_water_C_version::boxOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AplayerCharacter* pcharacter = Cast<AplayerCharacter>(OtherActor);
	AMyGameModeBase* modebase = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	if (pcharacter != nullptr)
	{
		Playeronlava = true;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("on range")));
		farming_available_range = true;
		if (Gathering_cooltime_on == false)
		{
			modebase->farming_available = "liquid";
		}
		else
		{
			modebase->farming_available = "";
		}
	}
}
//채집박스에서 나가면
void AField_water_C_version::boxOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AplayerCharacter* pcharacter = Cast<AplayerCharacter>(OtherActor);
	AMyGameModeBase* modebase = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	if (pcharacter != nullptr)
	{
		Playeronlava = false;
		farming_available_range = false;
		modebase->farming_available = "";
	}
}
//tick 발동
void AField_water_C_version::playerarrive(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AplayerCharacter* pcharacter = Cast<AplayerCharacter>(OtherActor);
	if (pcharacter != nullptr)
	{
		PrimaryActorTick.SetTickFunctionEnable(true);

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("playeronwater")));

	}

}
//tick 꺼짐
void AField_water_C_version::playerleft(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AplayerCharacter* pcharacter = Cast<AplayerCharacter>(OtherActor);
	if (pcharacter != nullptr)
	{
		PrimaryActorTick.SetTickFunctionEnable(false);

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("playerbyewater")));

	}

}


void AField_water_C_version::gatheringcooltimer()
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