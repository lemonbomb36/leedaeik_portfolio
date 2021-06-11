// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "playerCharacter.h" // 캐릭터 접촉

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//플레이어 공격판정
	enemyattack = CreateDefaultSubobject<USphereComponent>(TEXT("enemyattack"));
	enemyattack->InitSphereRadius(32.0);
	enemyattack->SetupAttachment(GetMesh(), "hand_r");
	enemyattack->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCharacter::attackOverlapBegin);


}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	AMyGameModeBase* modebase = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	Super::Tick(DeltaTime);
	//1 몬스터 체력 떨어지면 사망
	if (monster_hp <= 0)
	{
		--(modebase->enemy1_count);
		AEnemyCharacter::Destroy();
	}
	//2 부스트 쿨타임
	if (rushcooltime && rushcooltimegate)
	{
		rushcooltimegate = false;
	
		CountdownTime = 2; GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &AEnemyCharacter::speedupcountdown, 1.0f, true);


	}
	//3 공격속도 조절
	if (attack)
	{
		GetWorldTimerManager().SetTimer(CountdownTimerHandle2, this, &AEnemyCharacter::attackspeed, 1.0f, true);
		attack = false;
	}
}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
//몬스터 부스트 뒷처리1
void AEnemyCharacter::speedupcountdown()
{
	--CountdownTime;
	if (CountdownTime < 0)
	{
		// 카운트다운이 완료
		UCharacterMovementComponent* MovementPtr = Cast<UCharacterMovementComponent>(GetCharacterMovement());
		GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
		MovementPtr->MaxWalkSpeed = MovementPtr->MaxWalkSpeed - 400.0f;
		CountdownTime = 5; GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &AEnemyCharacter::speedupcountdown2, 1.0f, true);
	}


}
//몬스터 부스트 뒷처리2
void AEnemyCharacter::speedupcountdown2()
{
	--CountdownTime;
	if (CountdownTime < 0)
	{
		// 카운트다운이 완료
		GetWorldTimerManager().ClearTimer(CountdownTimerHandle);

		rushcooltime = false;
		rushcooltimegate = true;

	}


}
//공격속도 조절
void AEnemyCharacter::attackspeed()
{
	--CountdownTime2;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("count! %d"), CountdownTime));
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString(TEXT("attack!")));
	if (CountdownTime < 0)
	{
		// 카운트다운 완료
		GetWorldTimerManager().ClearTimer(CountdownTimerHandle2);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString(TEXT("ready!")));
		CountdownTime2 = 0.45f;
	}
	
}

//근접공격데미지 판정
void AEnemyCharacter::attackOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AplayerCharacter* pcharacter = Cast<AplayerCharacter>(OtherActor);
	AMyGameModeBase* modebase = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (pcharacter != nullptr)
	{
		if (damage_delay_to_player == false)
		{
			damage_delay_to_player = true;
			--(modebase->character_health);
			damage_delay_to_player = false;
			
		}
	}
}