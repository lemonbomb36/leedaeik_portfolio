// Fill out your copyright notice in the Description page of Project Settings.


#include "playerCharacter.h"


// Sets default values
AplayerCharacter::AplayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AplayerCharacter::OnOverlapBegin);

}

// Called when the game starts or when spawned
void AplayerCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame 작업용 정보기록
void AplayerCharacter::Tick(float DeltaTime)
{
	AMyGameModeBase* modebase = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	UCharacterMovementComponent* MovementPtr = Cast<UCharacterMovementComponent>(GetCharacterMovement());
	Super::Tick(DeltaTime);

	//1 이동속도 갱신
	MovementPtr->MaxWalkSpeed = modebase->character_speed;


	//2 캐릭터 위치와 각도기록. 투척무기 등에 사용
	modebase->character_location = GetActorLocation();
	modebase->character_rotation = GetControlRotation();

}

// Called to bind functionality to input
void AplayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{

	// 입력에 함수성 바인딩을 위해 호출됩니다.
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// "movement" 바인딩 구성
	PlayerInputComponent->BindAxis("MoveForward", this, &AplayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AplayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AplayerCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AplayerCharacter::AddControllerPitchInput);

	// "action" 바인딩을 구성합니다.
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AplayerCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AplayerCharacter::StopJump);

}

//전후이동
void AplayerCharacter::MoveForward(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

//좌우이동
void AplayerCharacter::MoveRight(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

//점프
void AplayerCharacter::StartJump()
{
	bPressedJump = true;
}
void AplayerCharacter::StopJump()
{
	bPressedJump = false;
}

//블루프린트 액터소환
void AplayerCharacter::blueprint_actor_spawn(const TCHAR* Filename)
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


//enemybullet 플레이어 피격
void AplayerCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	Aenemy_bullet_c_version* ebullet = Cast<Aenemy_bullet_c_version>(OtherActor);
	AMyGameModeBase* modebase = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (ebullet != nullptr)
		{
			ebullet->Destroy(); // 제 때 안 없애면 중복피격으로 2번 맞음
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("hit ough!")));
				--(modebase->character_health);
			
		}
	}
	
}

