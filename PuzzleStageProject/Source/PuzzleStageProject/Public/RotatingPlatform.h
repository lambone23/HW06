// RotatingPlatform.h
// 회전하는 발판 Actor 클래스
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotatingPlatform.generated.h"

UCLASS()
class PUZZLESTAGEPROJECT_API ARotatingPlatform : public AActor
{
	GENERATED_BODY()
	
public:
	ARotatingPlatform();

	// APlatformSpawnerManager에 접근하기 위함
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation Settings")
	FRotator RotationSpeed;		// 회전 속도 (초당 회전 각도), 에디터에서 조절 가능

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Platform|Component")
	UStaticMeshComponent* StaticMeshComp;	// 실제 발판의 시각적 형태를 담당할 StaticMesh 컴포넌트

};
