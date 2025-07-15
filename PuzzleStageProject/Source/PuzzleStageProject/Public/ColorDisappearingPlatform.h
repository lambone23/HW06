// ColorDisappearingPlatform.h
// 색이 주기적으로 바뀌고, 일정 시간마다 사라졌다 다시 나타나는 발판 Actor 클래스
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ColorDisappearingPlatform.generated.h"

UCLASS()
class PUZZLESTAGEPROJECT_API AColorDisappearingPlatform : public AActor
{
	GENERATED_BODY()
	
public:
	AColorDisappearingPlatform();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Platform|Component")
	UStaticMeshComponent* StaticMeshComp;   // 실제 발판의 시각적 형태를 담당할 StaticMesh 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Disappear Settings")
	float VisibleDuration;		// 발판이 보이는 시간 (초 단위)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Disappear Settings")
	float InvisibleDuration;	// 발판이 사라지는 시간 (초 단위)

	UFUNCTION()
	void ToggleVisibility();	// 현재 상태를 반전시켜 보이거나 숨김
	UFUNCTION()
	void ChangeColor();			// 발판의 머티리얼 색상을 무작위로 변경

private:
	UMaterialInstanceDynamic* DynamicMaterial;	// 동적으로 머티리얼을 제어하기 위한 인스턴스
	bool bIsVisible;							// 현재 발판이 보이는 상태인지 여부
	FTimerHandle VisibilityTimerHandle;			// 발판 숨김/표시 타이머 핸들

};
