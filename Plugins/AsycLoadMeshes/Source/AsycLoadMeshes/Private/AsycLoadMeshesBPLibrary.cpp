// Copyright Epic Games, Inc. All Rights Reserved.

#include "AsycLoadMeshesBPLibrary.h"
#include "Engine/StreamableManager.h"

#define GEOMETRIES_PATH_1 "/Game/2D/Geometries"

TArray<FStringAssetReference> UAsycLoadMeshesBPLibrary::GeometryPaths = {};
FStreamableManager* UAsycLoadMeshesBPLibrary::GeometryManager = nullptr;
TArray<UObject*> UAsycLoadMeshesBPLibrary::LoadedMeshes = {};
TSharedPtr<FStreamableHandle> UAsycLoadMeshesBPLibrary::GeometryHandle = NULL;

UAsycLoadMeshesBPLibrary::UAsycLoadMeshesBPLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UAsycLoadMeshesBPLibrary::StartLoad(UObject* AsyncLoadMeshesActor, const FString& InPathName,
                                         const TArray<FString>& InIndexes,
                                         const FName& InFuncName)
{
	//StaticMesh'/Game/Geometries/meshId4057_name.meshId4057_name'
	TArray<FString> Paths;
	for (FString Index : InIndexes)
	{
		Paths.Add(FString("StaticMesh'")
			+ InPathName
			+ FString("/meshId")
			+ Index
			+ FString("_name.")
			+ FString("meshId")
			+ Index
			+ FString("_name'"));
	}
	for (FString Path : Paths)
	{
		UE_LOG(LogTemp, Log, TEXT("%s"), *Path);
	}


	SetAssetsPaths(Paths);
	GeometryManager = new FStreamableManager();
	if (InFuncName.IsEqual("None"))return;
	GeometryHandle = GeometryManager->RequestAsyncLoad(GeometryPaths,
	                                                   FStreamableDelegate::CreateUFunction(
		                                                   AsyncLoadMeshesActor, InFuncName));
}

void UAsycLoadMeshesBPLibrary::SetAssetsPaths(const TArray<FString>& Paths)
{
	for (FString Path : Paths)
	{
		GeometryPaths.Add(Path);
	}
}

TArray<UObject*> UAsycLoadMeshesBPLibrary::GetLoadedMeshes()
{
	// TArray<UObject*> LoadedMeshes;
	// GeometryHandle->GetLoadedAssets(LoadedMeshes);
	// GeometryHandle->ReleaseHandle();
	// GeometryPaths.Empty();
	return LoadedMeshes;
}

// void UAsycLoadMeshesBPLibrary::Loading()
// {
// 	for (FStringAssetReference GeometryPath : GeometryPaths)
// 	{
// 		LoadedMeshes.Add(LoadObject<UStaticMesh>(NULL, *GeometryPath.ToString()));
// 	}
// }