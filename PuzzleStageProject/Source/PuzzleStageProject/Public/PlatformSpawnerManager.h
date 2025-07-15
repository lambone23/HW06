// PlatformSpawnerManager.h
// 발판 동적스폰 관리 Actor 클래스
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatformSpawnerManager.generated.h"

class APlatformSpawnPoint;

UCLASS()
class PUZZLESTAGEPROJECT_API APlatformSpawnerManager : public AActor
{
	GENERATED_BODY()
	
public:
	APlatformSpawnerManager();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Settings")
	int32 NumPlatformsPerSpawnPoint;					// 한 스폰 포인트당 생성할 발판 수 (블루프린트에서 설정 가능)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Settings")
	TArray<TSubclassOf<AActor>> PlatformTypesToSpawn;	// 여러 종류의 발판 클래스 보관

private:
	UPROPERTY()
	TArray<APlatformSpawnPoint*> SpawnPoints;			// 스폰 지점으로 사용할 플랫폼 스폰 포인트

	// 모든 SpawnPoint를 찾아 저장하고, 거기서 발판 스폰
	void SpawnPlatforms();
	// 특정 SpawnPoint에서 발판을 스폰하는 함수
	void SpawnPlatformsAtPoint(APlatformSpawnPoint* SpawnPoint, int32 NumToSpawn);
	// 스폰된 발판에 속성을 세팅하는 함수
	void SetupPlatformProperties(AActor* SpawnedActor);
};
