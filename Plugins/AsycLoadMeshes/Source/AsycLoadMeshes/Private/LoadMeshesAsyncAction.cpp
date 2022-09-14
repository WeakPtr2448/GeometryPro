// Fill out your copyright notice in the Description page of Project Settings.


#include "LoadMeshesAsyncAction.h"


ULoadMeshesAsyncAction* ULoadMeshesAsyncAction::WaitForLoadMeshes(UObject* WorldContext, FString InPath,
                                                                  FMeshInfo MeshInfo)
{
	ULoadMeshesAsyncAction* Node = NewObject<ULoadMeshesAsyncAction>();
	(new FAutoDeleteAsyncTask<FLoadMeshesTask>(Node, InPath, MeshInfo))->StartBackgroundTask();
	return Node;
}

void FLoadMeshesTask::DoWork()
{
	//StaticMesh'/Game/Geometries/meshId4057_name.meshId4057_name'

	// AsyncTask(ENamedThreads::GameThread, [this]()
	// {
	// 	MeshMat = LoadObject<UMaterialInterface>(NULL, *MaterialPath.ToString());
	// });
	AsyncTask(ENamedThreads::GameThread, [this]()
	{
		for (int i = 0; i < Indexes.Num(); ++i)
		{
			FString FileName = FString("StaticMesh'")
				+ FString("/Game/2D/Geometries")
				+ FString("/meshId")
				+ FString::FromInt(Indexes[i])
				+ FString("_name.")
				+ FString("meshId")
				+ FString::FromInt(Indexes[i])
				+ FString("_name'");
			Paths.Add(FileName);
			UE_LOG(LogTemp, Warning, TEXT("@%u ,PathName=%s"), __LINE__,*Paths[i]);
		}
		return;
		FPlatformProcess::Sleep(0.01f);
		for (int i = 0; i < Paths.Num(); ++i)
		{
			const TCHAR* charFile = *Paths[i];
			// char* file = TCHAR_TO_UTF8(charFile);

			UE_LOG(LogTemp, Warning, TEXT("@%u ,PathName=%s"), __LINE__,charFile);
			if (i > 1)
			{
				LoadedMesh = LoadObject<UStaticMesh>(NULL, charFile);

				Node->OnSuccess.Broadcast(LoadedMesh, Depths[i], MeshMat);
			}
			if (i == Paths.Num())
			{
				Paths.Empty();
			}
		}
		Node->OnFailed.Broadcast(nullptr, {}, MeshMat);
	});
}
