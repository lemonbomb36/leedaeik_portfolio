// Fill out your copyright notice in the Description page of Project Settings.


#include "mainobject_c_version.h"
#include "playerCharacter.h" // 캐릭터 접촉

// Sets default values
Amainobject_c_version::Amainobject_c_version()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//플레이어 접촉판정
	Sensor = CreateDefaultSubobject<UCapsuleComponent>(TEXT("capsule"));
	Sensor->InitCapsuleSize(55, 96.0f);
	Sensor->OnComponentBeginOverlap.AddDynamic(this, &Amainobject_c_version::OnOverlapBegin);
	Sensor->OnComponentEndOverlap.AddDynamic(this, &Amainobject_c_version::OnOverlapEnd);
	
}

// Called when the game starts or when spawned
void Amainobject_c_version::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame 수집되면 제거됨
void Amainobject_c_version::Tick(float DeltaTime)
{
	AMyGameModeBase* modebase = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	Super::Tick(DeltaTime);
	if (modebase->mainobjectget && contacting)
	{
		modebase->mainobjectget = false;
		Destroy();
	}
}

//플레이어 수집 접촉판정
void Amainobject_c_version::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AplayerCharacter* pcharacter = Cast<AplayerCharacter>(OtherActor);
	AMyGameModeBase* modebase = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (pcharacter != nullptr)
		{
			modebase->farming_available = FString("mainobject");
			contacting = true;
		}
	}
}

void Amainobject_c_version::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AplayerCharacter* pcharacter = Cast<AplayerCharacter>(OtherActor);
	AMyGameModeBase* modebase = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (pcharacter != nullptr)
		{
			modebase->farming_available = FString("");
			contacting = false;
		}
	}

}