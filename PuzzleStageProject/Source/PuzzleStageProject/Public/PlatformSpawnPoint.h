// PlatformSpawnPoint.h
// 발판 동적스폰 영역 Actor 클래스
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatformSpawnPoint.generated.h"

class UBoxComponent;

UCLASS()
class PUZZLESTAGEPROJECT_API APlatformSpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:
	APlatformSpawnPoint();
	UBoxComponent* GetSpawnBox() const { return SpawnAreaBox; }	// 스폰 영역 박스 컴포넌트를 반환하는 getter 함수

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SpawnArea|Component")
	USceneComponent* RootSceneComponent;	// 위치 표시용 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SpawnArea|Component")
	UBoxComponent* SpawnAreaBox;			// 이 박스 범위 안에서 발판이 랜덤으로 생성됨 (스폰 영역 시각화 및 설정용)
};
