// MovingPlatform.h
// 왕복 이동하는 이동 플랫폼 Actor 클래스
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class PUZZLESTAGEPROJECT_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:
	AMovingPlatform();

    // APlatformSpawnerManager에 접근하기 위함
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Settings")
    float MoveSpeed;        // 이동 속도
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Settings")
    float MaxRange;         // 시작 위치 기준 최대 이동 거리 (StartLocation 기준 거리)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Settings")
    FVector MoveDirection;  // 이동 방향 벡터

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Platform|Component")
    UStaticMeshComponent* StaticMeshComp;   // 실제 발판의 시각적 형태를 담당할 StaticMesh 컴포넌트

private:
    FVector StartLocation;  // 이동 시작 위치 저장용 (게임 시작 시 위치 기록)
    bool bMovingForward;    // true면 정방향(+), false면 역방향(-)으로 이동 중

};
