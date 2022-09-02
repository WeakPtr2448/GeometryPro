// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StreamableManager.h"
#include "GameFramework/Actor.h"
#include "GeometryActor.generated.h"

UCLASS()
class AGeometryActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGeometryActor();

	//调用此函数，进行加载模型
	UFUNCTION(BlueprintCallable)
	void StartLoad(const TArray<FString>& Paths);
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* GeometryComp;

	TArray<FStringAssetReference> GeometryPaths;

	UFUNCTION()
	void LoadGeometriesComplete();

	void SetAssetsPaths(const TArray<FString>& InIndexes);

protected:
	TSharedPtr<FStreamableHandle> GeometryHandle;

	FStreamableManager* GeometryManager;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
