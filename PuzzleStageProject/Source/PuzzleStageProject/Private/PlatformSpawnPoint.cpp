// PlatformSpawnPoint.cpp
#include "PlatformSpawnPoint.h"
#include "Components/BoxComponent.h"

APlatformSpawnPoint::APlatformSpawnPoint()
{
	PrimaryActorTick.bCanEverTick = false;

	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	RootComponent = RootSceneComponent;

	// 박스 콜리전 컴포넌트 생성 및 루트에 부착
	SpawnAreaBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnAreaBox"));
	SpawnAreaBox->SetupAttachment(RootComponent);

	// 스폰 영역 기본 크기 설정 (에디터에서 수정 가능)
	SpawnAreaBox->SetBoxExtent(FVector(200.f, 200.f, 100.f)); // 기본 사이즈 설정

	// 콜리전은 시각화 전용 (충돌 X)
	SpawnAreaBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// 편집 및 시각화를 위해 HiddenInGame 비활성화
	SpawnAreaBox->bHiddenInGame = false;
}

void APlatformSpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
}
