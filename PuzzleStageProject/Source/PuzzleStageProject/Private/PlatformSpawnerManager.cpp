// PlatformSpawnerManager.cpp
#include "PlatformSpawnerManager.h"
#include "Kismet/GameplayStatics.h"
#include "PlatformSpawnPoint.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "MovingPlatform.h"
#include "RotatingPlatform.h"
#include "DisappearingPlatform.h"

APlatformSpawnerManager::APlatformSpawnerManager()
{
	PrimaryActorTick.bCanEverTick = false;

	NumPlatformsPerSpawnPoint = 7; // 한 스폰 포인트 당 생성할 발판 수
}

void APlatformSpawnerManager::BeginPlay()
{
	Super::BeginPlay();
	SpawnPlatforms();
}

void APlatformSpawnerManager::SpawnPlatforms()
{
	// 맵 내 존재하는 모든 APlatformSpawnPoint 액터들을 찾아 FoundActors 배열에 저장
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlatformSpawnPoint::StaticClass(), FoundActors);

	// 기존 SpawnPoints 배열 초기화(이전 데이터 제거)
	SpawnPoints.Empty();

	// FoundActors 배열을 순회하면서 APlatformSpawnPoint 타입만 골라 SpawnPoints 배열에 추가
	for (AActor* Actor : FoundActors)
	{
		if (APlatformSpawnPoint* SpawnPoint = Cast<APlatformSpawnPoint>(Actor))
		{// SpawnPoint로 캐스팅하고 유효한 SpawnPoint만 SpawnPoints에 저장
			SpawnPoints.Add(SpawnPoint);
		}
	}

	// 각 SpawnPoint마다 발판을 지정 개수(NumPlatformsPerSpawnPoint)만큼 스폰
	for (APlatformSpawnPoint* SpawnPoint : SpawnPoints)
	{
		SpawnPlatformsAtPoint(SpawnPoint, NumPlatformsPerSpawnPoint);
	}
}

void APlatformSpawnerManager::SpawnPlatformsAtPoint(APlatformSpawnPoint* SpawnPoint, int32 NumToSpawn)
{
	// 유효성 검사: 스폰 포인트가 유효하지 않거나, 스폰할 발판 클래스가 설정되지 않은 경우 실행 중단
	if (!SpawnPoint || PlatformTypesToSpawn.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid"));
		return;
	}

	// SpawnPoint에 부착된 BoxComponent (스폰 영역) 가져오기
	if (UBoxComponent* SpawnBox = SpawnPoint->GetSpawnBox())
	{
		// 박스 중심 위치와 범위 정보 가져오기
		const FVector Origin = SpawnBox->GetComponentLocation();// 박스의 중심 좌표
		const FVector Extent = SpawnBox->GetScaledBoxExtent();	// 박스의 반지름 (X,Y,Z 방향 범위)

		// 지정된 개수만큼 발판 생성
		for (int32 i = 0; i < NumToSpawn; ++i)
		{
			// 스폰 영역 내 무작위 위치 선정
			const FVector SpawnLocation = UKismetMathLibrary::RandomPointInBoundingBox(Origin, Extent);

			// 기본 회전값 설정 (기본은 회전 없음)
			const FRotator SpawnRotation = FRotator::ZeroRotator;

			// 발판 클래스 목록 중 하나를 무작위로 선택
			int32 Index = FMath::RandRange(0, PlatformTypesToSpawn.Num() - 1);
			TSubclassOf<AActor> SelectedPlatformClass = PlatformTypesToSpawn[Index];
			if (!SelectedPlatformClass) continue; // 유효하지 않은 클래스일 경우 스킵

			// 선택된 위치와 회전으로 발판 액터 스폰
			AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(SelectedPlatformClass, SpawnLocation, SpawnRotation);

			// 발판이 정상적으로 스폰되었으면, 속성 초기화 함수 호출
			if (SpawnedActor)
			{
				SetupPlatformProperties(SpawnedActor);
			}
		}
	}
	else
	{// 박스 컴포넌트가 없을 경우 경고 출력
		UE_LOG(LogTemp, Warning, TEXT("no SpawnBox!"));
	}
}

void APlatformSpawnerManager::SetupPlatformProperties(AActor* SpawnedActor)
{
	if (!SpawnedActor) return;

	// AMovingPlatform인 경우: 속도 및 이동 범위 설정
	AMovingPlatform* MovingPlatform = Cast<AMovingPlatform>(SpawnedActor);
	if (MovingPlatform)
	{
		MovingPlatform->MoveSpeed = FMath::RandRange(50.f, 150.f);	// 이동 속도
		MovingPlatform->MaxRange = FMath::RandRange(100.f, 300.f);	// 최대 이동 범위
		
		// 기본 방향 (X축 기준)
		FVector BaseDirection = FVector::ForwardVector; // = FVector(1, 0, 0)

		// 약간의 랜덤 회전 적용
		FRotator RandomRot = FRotator(
			FMath::RandRange(-10.f, 10.f),  // Pitch: 위아래로 살짝
			FMath::RandRange(-20.f, 20.f),  // Yaw: 좌우로 적당히 흔들기
			0.f								// Roll은 생략 (플랫폼은 기울어지지 않음)
		);
		FVector FinalDirection = RandomRot.RotateVector(BaseDirection);
		FinalDirection.Normalize(); // 단위 벡터로 정규화

		MovingPlatform->MoveDirection = FinalDirection;

		return;
	}

	// ARotatingPlatform인 경우: 회전 속도 설정
	ARotatingPlatform* RotatingPlatform = Cast<ARotatingPlatform>(SpawnedActor);
	if (RotatingPlatform)
	{
		const float RandomYawSpeed = FMath::RandRange(30.f, 90.f);
		RotatingPlatform->RotationSpeed = FRotator(0.f, RandomYawSpeed, 0.f); // 초당 회전 속도
		return;
	}

	// ADisappearingPlatform인 경우: 사라지는 시간 설정
	ADisappearingPlatform* DisappearingPlatform = Cast<ADisappearingPlatform>(SpawnedActor);
	if (DisappearingPlatform)
	{
		DisappearingPlatform->DisappearDelay = FMath::RandRange(1.f, 3.f); // 딜레이 시간
		return;
	}
}
