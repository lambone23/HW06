// DisappearingPlatform.cpp
#include "DisappearingPlatform.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h" 
#include "TimerManager.h"
#include "GameFramework/Character.h" // 플레이어 감지를 위해

ADisappearingPlatform::ADisappearingPlatform()
{
	PrimaryActorTick.bCanEverTick = false;

	// StaticMesh 컴포넌트 생성 및 루트로 설정
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    SetRootComponent(StaticMeshComp);

    // Collision 컴포넌트 생성 및 세팅
    CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
    CollisionComp->SetupAttachment(RootComponent);

    // 오버랩 이벤트 감지 설정
    CollisionComp->SetGenerateOverlapEvents(true);
    CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    CollisionComp->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Overlap);

    // 기본 사라짐 지연 시간
    DisappearDelay = 2.0f;
    ReappearDelay = 1.0f;
}

void ADisappearingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
    // 오버랩 이벤트 바인딩
    CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ADisappearingPlatform::OnPlatformBeginOverlap);
}

void ADisappearingPlatform::OnPlatformBeginOverlap(
    UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    // 플레이어만 감지
    if (OtherActor && OtherActor->IsA<ACharacter>())
    {
        // 이미 타이머가 작동 중이면 다시 설정하지 않음
        if (!GetWorld()->GetTimerManager().IsTimerActive(DisappearTimerHandle))
        {
            GetWorld()->GetTimerManager().SetTimer(
                DisappearTimerHandle,
                this,
                &ADisappearingPlatform::DisappearPlatform,
                DisappearDelay,
                false
            );
        }
    }
}

void ADisappearingPlatform::DisappearPlatform()
{
    // 발판 숨기기 및 충돌 비활성화
    StaticMeshComp->SetVisibility(false);
    StaticMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    CollisionComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    // 일정 시간 뒤 다시 나타나도록 예약
    GetWorld()->GetTimerManager().SetTimer(
        ReappearTimerHandle,
        this,
        &ADisappearingPlatform::ReappearPlatform,
        ReappearDelay,
        false
    );
}

void ADisappearingPlatform::ReappearPlatform()
{
    // 발판 다시 보이기 및 충돌 활성화
    StaticMeshComp->SetVisibility(true);
    StaticMeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

    // 타이머 초기화
    GetWorld()->GetTimerManager().ClearTimer(DisappearTimerHandle);
    GetWorld()->GetTimerManager().ClearTimer(ReappearTimerHandle);
}
