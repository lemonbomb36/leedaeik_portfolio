// Fill out your copyright notice in the Description page of Project Settings.


#include "Field_Hill_c_version.h"

// Sets default values
AField_Hill_c_version::AField_Hill_c_version()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	spawnlocation = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("spawnlocation"));
	spawnlocation->SetupAttachment(Root);

	mainobject_location = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mainobject_location"));
	mainobject_location->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AField_Hill_c_version::BeginPlay()
{
	Super::BeginPlay();
	AMyGameModeBase* modebase = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	modebase->enemylocation.Add(FVector(spawnlocation->GetComponentLocation()));
	modebase->mainobjectlocation.Add(FVector(mainobject_location->GetComponentLocation()));
}

// Called every frame
void AField_Hill_c_version::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

