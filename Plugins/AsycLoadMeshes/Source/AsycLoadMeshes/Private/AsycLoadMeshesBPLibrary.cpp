// Copyright Epic Games, Inc. All Rights Reserved.

#include "AsycLoadMeshesBPLibrary.h"

#include "Engine/ObjectLibrary.h"
#include "Engine/StreamableManager.h"

/*#define GEOMETRIES_PATH_1 "/Game/2D/Geometries"

TArray<FStringAssetReference> UAsycLoadMeshesBPLibrary::GeometryPaths = {};
FStreamableManager* UAsycLoadMeshesBPLibrary::GeometryManager = nullptr;
TArray<UObject*> UAsycLoadMeshesBPLibrary::LoadedMeshes = {};
TSharedPtr<FStreamableHandle> UAsycLoadMeshesBPLibrary::GeometryHandle = NULL;*/

UAsycLoadMeshesBPLibrary::UAsycLoadMeshesBPLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

//
// void UAsycLoadMeshesBPLibrary::StartLoad(UObject* AsyncLoadMeshesActor, const FString& InPathName,
//                                          const TArray<FString>& InIndexes,
//                                          const FName& InFuncName)
// {
// 	//StaticMesh'/Game/Geometries/meshId4057_name.meshId4057_name'
// 	TArray<FString> Paths;
// 	for (FString Index : InIndexes)
// 	{
// 		Paths.Add(FString("StaticMesh'")
// 			+ InPathName
// 			+ FString("/meshId")
// 			+ Index
// 			+ FString("_name.")
// 			+ FString("meshId")
// 			+ Index
// 			+ FString("_name'"));
// 	}
// 	for (FString Path : Paths)
// 	{
// 		UE_LOG(LogTemp, Log, TEXT("%s"), *Path);
// 	}
//
//
// 	SetAssetsPaths(Paths);
// 	GeometryManager = new FStreamableManager();
// 	if (InFuncName.IsEqual("None"))return;
// 	GeometryHandle = GeometryManager->RequestAsyncLoad(GeometryPaths,
// 	                                                   FStreamableDelegate::CreateUFunction(
// 		                                                   AsyncLoadMeshesActor, InFuncName));
// }
//
TArray<FStringAssetReference> UAsycLoadMeshesBPLibrary::GetAssetsPaths(const FString& Path)
{
	UObjectLibrary* ObjectLibrary = UObjectLibrary::CreateLibrary(UObject::StaticClass(), false, false);

	TArray<FStringAssetReference> Paths;
	ObjectLibrary->AddToRoot();
	ObjectLibrary->LoadAssetDataFromPath(*Path);

	TArray<FAssetData> AssetDatas;
	ObjectLibrary->GetAssetDataList(AssetDatas);

	// UE_LOG(LogTemp, Warning, TEXT("加载的资源个数为: %d"), GeometryPaths.Num());

	for (FAssetData AssetData : AssetDatas)
	{
		Paths.Add(AssetData.ToSoftObjectPath());
	}
	return Paths;
}

//
// TArray<UObject*> UAsycLoadMeshesBPLibrary::GetLoadedMeshes()
// {
// 	// TArray<UObject*> LoadedMeshes;
// 	// GeometryHandle->GetLoadedAssets(LoadedMeshes);
// 	// GeometryHandle->ReleaseHandle();
// 	// GeometryPaths.Empty();
// 	return LoadedMeshes;
// }

// void UAsycLoadMeshesBPLibrary::Loading()
// {
// 	for (FStringAssetReference GeometryPath : GeometryPaths)
// 	{
// 		LoadedMeshes.Add(LoadObject<UStaticMesh>(NULL, *GeometryPath.ToString()));
// 	}
// }
