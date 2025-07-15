// DestinationTriggerActor.h
// 플레이어가 종착지 트리거에 들어오면 텍스트를 표시하고, 벗어나면 숨기는 Actor 클래스
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestinationTriggerActor.generated.h"

UCLASS()
class PUZZLESTAGEPROJECT_API ADestinationTriggerActor : public AActor
{
	GENERATED_BODY()
	
public:
	ADestinationTriggerActor();

protected:
	virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, Category = "Destination|Component")
    class UBoxComponent* TriggerZone;           // 트리거 영역 (박스 콜리전)
    UPROPERTY(VisibleAnywhere, Category = "Destination|Component")
    class UTextRenderComponent* ArrivalText;    // 도착 메시지를 표시하는 텍스트 렌더 컴포넌트

    // 오버랩 감지 함수
    UFUNCTION()
    void OnOverlapBegin(
        UPrimitiveComponent* OverlappedComp,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult);

    // 트리거 이탈 시 호출
    UFUNCTION()
    void OnOverlapEnd(
        UPrimitiveComponent* OverlappedComp,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex);
};
