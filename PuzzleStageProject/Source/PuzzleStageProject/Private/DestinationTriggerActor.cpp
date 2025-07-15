// DestinationTriggerActor.cpp
#include "DestinationTriggerActor.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Character.h"  // 플레이어 캐릭터 판별용

ADestinationTriggerActor::ADestinationTriggerActor()
{
    PrimaryActorTick.bCanEverTick = false;

    // 트리거 박스 컴포넌트 생성 및 루트 컴포넌트로 설정
    TriggerZone = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerZone"));
    SetRootComponent(TriggerZone);

    // Overlap 이벤트를 받도록 설정
    TriggerZone->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    TriggerZone->SetCollisionResponseToAllChannels(ECR_Ignore);
    TriggerZone->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

    // 텍스트 렌더 컴포넌트 생성 및 트리거박스 자식으로 붙임
    ArrivalText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ArrivalText"));
    ArrivalText->SetupAttachment(RootComponent);

    // 초기에는 텍스트 숨김
    ArrivalText->SetHiddenInGame(true);
    ArrivalText->SetHorizontalAlignment(EHTA_Center);
    ArrivalText->SetText(FText::FromString(TEXT("Arrived!")));
}

void ADestinationTriggerActor::BeginPlay()
{
	Super::BeginPlay();
	
    // Overlap 이벤트 바인딩
    if (TriggerZone)
    {
        TriggerZone->OnComponentBeginOverlap.AddDynamic(this, &ADestinationTriggerActor::OnOverlapBegin);
        TriggerZone->OnComponentEndOverlap.AddDynamic(this, &ADestinationTriggerActor::OnOverlapEnd);
    }
}

void ADestinationTriggerActor::OnOverlapBegin(
    UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    if (!OtherActor) return;

    // 플레이어 캐릭터가 들어왔는지 체크
    if (OtherActor->IsA(ACharacter::StaticClass()))
    {
        // 텍스트 보이게 하기
        ArrivalText->SetHiddenInGame(false);
    }
}

void ADestinationTriggerActor::OnOverlapEnd(
    UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex)
{
    if (!OtherActor) return;

    // 플레이어 캐릭터가 나갔는지 체크
    if (OtherActor->IsA(ACharacter::StaticClass()))
    {
        // 텍스트 숨기기
        ArrivalText->SetHiddenInGame(true);
    }
}
