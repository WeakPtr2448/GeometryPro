// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "LoadMeshesAsyncAction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLoadingSignature,
                                             UStaticMesh*, RiverMesh,
                                             float, Depths);

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
	                                                 TArray<int32> Indexes,
	                                                 TArray<float> Indepths);
	
};

class FLoadMeshesTask : public FNonAbandonableTask
{
	//1
	friend class FAutoDeleteAsyncTask<FLoadMeshesTask>;

	ULoadMeshesAsyncAction* Node;
	TArray<int32> Indexes;
	FString MeshPath;
	TArray<FString> Paths;
	
	float Depth;
	UStaticMesh* LoadedMesh;


	FLoadMeshesTask(ULoadMeshesAsyncAction* InNode, FString InPath, TArray<int32> InIndexes, float Indepth):
		Node(InNode), Indexes(InIndexes), MeshPath(InPath), Depth(Indepth)
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
