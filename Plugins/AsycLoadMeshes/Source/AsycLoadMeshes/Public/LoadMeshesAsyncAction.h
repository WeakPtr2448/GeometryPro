// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonType.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "LoadMeshesAsyncAction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnLoadingSignature,
                                               UStaticMesh*, RiverMesh,
                                               float, Depths,
                                               UMaterialInterface*, MeshMat);

/**
 * 
 */
UCLASS()
class ULoadMeshesAsyncAction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnLoadingSignature OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnLoadingSignature OnFailed;

	UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContext"), Category="Load")
	static ULoadMeshesAsyncAction* WaitForLoadMeshes(UObject* WorldContext,
	                                                 FString InPath,
	                                                 FMeshInfo MeshInfo);
};

class FLoadMeshesTask : public FNonAbandonableTask
{
	//1
	friend class FAutoDeleteAsyncTask<FLoadMeshesTask>;

	ULoadMeshesAsyncAction* Node;
	TArray<int32> Indexes;
	FString MeshPath;
	TArray<FString> Paths;
	FStringAssetReference MaterialPath;

	UMaterialInterface* MeshMat;

	TArray<float> Depths;
	UStaticMesh* LoadedMesh;


	FLoadMeshesTask(ULoadMeshesAsyncAction* InNode, FString InPath, FMeshInfo MeshInfo):
		Node(InNode), Indexes(MeshInfo.Indexes), MeshPath(InPath),
		MaterialPath(MeshInfo.MaterialPath), Depths(MeshInfo.Depths)
	{
	}

	//2
	void DoWork();

	//3
	FORCEINLINE TStatId GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(FLoadMeshesTask, STATGROUP_ThreadPoolAsyncTasks);
	}

	~FLoadMeshesTask()
	{
	}
};
