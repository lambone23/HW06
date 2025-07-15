// RotatingPlatform.cpp
#include "RotatingPlatform.h"

ARotatingPlatform::ARotatingPlatform()
{
	// Tick() 함수를 매 프레임 호출하도록 설정
	PrimaryActorTick.bCanEverTick = true;

	// 컴포넌트 생성
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));

	// 루트 컴포넌트를 StaticMeshComp로 지정
	// 루트 컴포넌트는 액터의 위치, 회전, 스케일 기준점이 된다
	SetRootComponent(StaticMeshComp);

	// 기본 회전 속도 설정 (Yaw 방향으로 초당 180도)
	RotationSpeed = FRotator(0.f, 180.f, 0.f);

}

void ARotatingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARotatingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 회전 속도에 DeltaTime을 곱해 프레임 독립적인 회전값 계산
	FRotator DeltaRotation = RotationSpeed * DeltaTime;

	// 액터를 로컬 좌표계 기준으로 회전시킴
	AddActorLocalRotation(DeltaRotation);

}
