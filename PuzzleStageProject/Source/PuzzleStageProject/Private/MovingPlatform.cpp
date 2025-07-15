// MovingPlatform.cpp
#include "MovingPlatform.h"
#include "Components/StaticMeshComponent.h"

AMovingPlatform::AMovingPlatform()
{
    // Tick 사용 설정
	PrimaryActorTick.bCanEverTick = true;

    // StaticMesh 컴포넌트 생성 및 루트로 설정
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    SetRootComponent(StaticMeshComp);

    MoveSpeed = 200.f;                      // 기본 이동 속도
    MaxRange = 300.f;                       // 최대 이동 거리
    MoveDirection = FVector(1.f, 0.f, 0.f); // 이동 방향 벡터 (기본값: X+ 방향)
    bMovingForward = true;                  // 초기 이동 방향은 정방향 (true)
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

    // 현재 위치를 시작 위치로 기록
	StartLocation = GetActorLocation();

    // 이동 방향: 액터의 앞 방향 (Forward Vector)
    if (MoveDirection.IsNearlyZero())
    {
        MoveDirection = GetActorForwardVector();
    }
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    // 현재 위치
    FVector CurrentLocation = GetActorLocation();

    // 한 프레임 동안 이동할 거리 계산 (프레임 독립적)
    FVector Delta = MoveDirection * MoveSpeed * DeltaTime;

    // 시작 위치와의 거리 계산
    float DistanceMoved = FVector::Dist(StartLocation, CurrentLocation);

    // 이동 범위 초과 시 방향 반전 + 시작점 갱신
    if (DistanceMoved >= MaxRange)
    {
        bMovingForward = !bMovingForward;
        StartLocation = CurrentLocation;
    }

    // 정방향 또는 역방향으로 이동
    FVector MoveStep = bMovingForward ? Delta : -Delta;
    AddActorWorldOffset(MoveStep, false);  // Sweep = true (충돌 감지)
}
