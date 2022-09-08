// Fill out your copyright notice in the Description page of Project Settings.


#include "LoadMeshesAsyncAction.h"

ULoadMeshesAsyncAction* ULoadMeshesAsyncAction::WaitForLoadMeshes(UObject* WorldContext, FString InPath,
                                                                  TArray<int32> Indexes,
                                                                  TArray<float> Indepthes)
{
	ULoadMeshesAsyncAction* Node = NewObject<ULoadMeshesAsyncAction>();
	(new FAutoDeleteAsyncTask<FLoadMeshesTask>(Node, InPath, Indexes, Indepthes))->StartBackgroundTask();
	return Node;
}

void FLoadMeshesTask::DoWork()
{
	while (IsValid(Node))
	{
		if (TargetCounter >= Indexes.Num())
		{
			TargetCounter = 0;
			break;
		}
		AsyncTask(ENamedThreads::GameThread, [=]()
		{
			TArray<FString> Paths;
			TArray<UStaticMesh*> LoadedMeshes;

			for (int32 Index : Indexes)
			{
				//StaticMesh'/Game/Geometries/meshId4057_name.meshId4057_name'
				Paths.Add(FString("StaticMesh'")
					+ FString(MeshPath)
					+ FString("/meshId")
					+ FString::FromInt(Index)
					+ FString("_name.")
					+ FString("meshId")
					+ FString::FromInt(Index)
					+ FString("_name'"));
			}
			for (FString Path : Paths)
			{
				LoadedMeshes.Add(LoadObject<UStaticMesh>(NULL, *Path));
				++TargetCounter;
			}

			Node->OnSuccess.Broadcast(LoadedMeshes, Depths);
		});
		FPlatformProcess::Sleep(0.01f);
		AsyncTask(ENamedThreads::GameThread, [=]()
		{
			UE_LOG(LogTemp, Warning, TEXT("@%u ,Counter=%d"), __LINE__, TargetCounter);
			Node->OnFailed.Broadcast({}, {});
		});
	}
}
