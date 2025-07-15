#include "ColorDisappearingPlatform.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "TimerManager.h"

AColorDisappearingPlatform::AColorDisappearingPlatform()
{
    // Tick()을 사용하므로 활성화
    PrimaryActorTick.bCanEverTick = true;

    // StaticMeshComponent 생성 및 루트 컴포넌트로 설정
    StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
    SetRootComponent(StaticMeshComp);

    // 기본값 설정
    VisibleDuration = 5.0f;   // 5초 동안 보임
    InvisibleDuration = 2.0f; // 2초 동안 사라짐
    bIsVisible = true;        // 현재 발판이 보이는 상태인지 여부
}

void AColorDisappearingPlatform::BeginPlay()
{
    Super::BeginPlay();

    // StaticMesh의 머티리얼을 동적으로 제어하기 위해 DynamicMaterial 생성
    if (StaticMeshComp && StaticMeshComp->GetMaterial(0))
    {
        DynamicMaterial = UMaterialInstanceDynamic::Create(StaticMeshComp->GetMaterial(0), this);
        StaticMeshComp->SetMaterial(0, DynamicMaterial);

        ChangeColor(); // 색상 변경
    }

    // 주기적으로 발판의 가시성 토글 함수를 호출하도록 타이머 시작
    GetWorldTimerManager().SetTimer(VisibilityTimerHandle, this, &AColorDisappearingPlatform::ToggleVisibility, VisibleDuration, false);
}

void AColorDisappearingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AColorDisappearingPlatform::ToggleVisibility()
{
    if (!StaticMeshComp) return;

    bIsVisible = !bIsVisible;

    // 발판의 가시성 설정
    StaticMeshComp->SetVisibility(bIsVisible);
    StaticMeshComp->SetCollisionEnabled(bIsVisible ? ECollisionEnabled::QueryAndPhysics : ECollisionEnabled::NoCollision);

    if (bIsVisible)
    {
        // 보이게 된 직후 색상 변경
        ChangeColor();

        // 다시 일정 시간 후 숨김 처리 예약
        GetWorldTimerManager().SetTimer(VisibilityTimerHandle, this, &AColorDisappearingPlatform::ToggleVisibility, VisibleDuration, false);
    }
    else
    {
        // 숨겨진 상태에서 다시 일정 시간 후 보임 처리 예약
        GetWorldTimerManager().SetTimer(VisibilityTimerHandle, this, &AColorDisappearingPlatform::ToggleVisibility, InvisibleDuration, false);
    }
}

void AColorDisappearingPlatform::ChangeColor()
{
    if (!DynamicMaterial) return;

    // 0~1 사이의 랜덤 RGB 값 생성
    FLinearColor NewColor = FLinearColor::MakeRandomColor();

    // 머티리얼 파라미터 이름
    DynamicMaterial->SetVectorParameterValue(FName("BaseColor"), NewColor);
}
