// RotatingPlatform.h
// 사라지는 발판 Actor 클래스
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DisappearingPlatform.generated.h"

class UBoxComponent;

UCLASS()
class PUZZLESTAGEPROJECT_API ADisappearingPlatform : public AActor
{
	GENERATED_BODY()
	
public:
	ADisappearingPlatform();

    // APlatformSpawnerManager에 접근하기 위함
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Disappear Settings")
    float DisappearDelay;                   // 사라지기까지의 시간

protected:
	virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Platform|Component")
    UStaticMeshComponent* StaticMeshComp;   // 실제 발판의 시각적 형태를 담당할 StaticMesh 컴포넌트
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Platform|Component")
    UBoxComponent* CollisionComp;            // 플레이어가 발판에 올라왔는지 감지하기 위한 오버랩 박스 (네모난 발판 형태에 맞춤)

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Disappear Settings")
    float ReappearDelay;                    // 사라진 후 다시 나타날 시간

    UFUNCTION()
    void DisappearPlatform();   // 사라지는 함수
    UFUNCTION()
    void ReappearPlatform();    // 다시 나타나는 함수

    // 오버랩 감지 함수
    UFUNCTION()
    void OnPlatformBeginOverlap(
        UPrimitiveComponent* OverlappedComp,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult);

private:
    FTimerHandle DisappearTimerHandle;  // 타이머 핸들 - 사라지기용
    FTimerHandle ReappearTimerHandle;   // 타이머 핸들 - 다시 나타나기용

};
