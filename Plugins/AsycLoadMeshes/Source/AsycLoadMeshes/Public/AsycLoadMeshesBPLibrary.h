// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "AsycLoadMeshesBPLibrary.generated.h"

struct FStreamableManager;
struct FStreamableHandle;
/* 
*	Function library class.
*	Each function in it is expected to be static and represents blueprint node that can be called in any blueprint.
*
*	When declaring function you can define metadata for the node. Key function specifiers will be BlueprintPure and BlueprintCallable.
*	BlueprintPure - means the function does not affect the owning object in any way and thus creates a node without Exec pins.
*	BlueprintCallable - makes a function which can be executed in Blueprints - Thus it has Exec pins.
*	DisplayName - full name of the node, shown when you mouse over the node and in the blueprint drop down menu.
*				Its lets you name the node using characters not allowed in C++ function names.
*	CompactNodeTitle - the word(s) that appear on the node.
*	Keywords -	the list of keywords that helps you to find node when you search for it using Blueprint drop-down menu. 
*				Good example is "Print String" node which you can find also by using keyword "log".
*	Category -	the category your node will be under in the Blueprint drop-down menu.
*
*	For more info on custom blueprint nodes visit documentation:
*	https://wiki.unrealengine.com/Custom_Blueprint_Node_Creation
*/
UCLASS()
class UAsycLoadMeshesBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	//调用此函数，进行加载模型
	UFUNCTION(BlueprintCallable, Category = "AsycLoadMeshes")
	static void StartLoad(UObject* AsyncLoadMeshesActor,const FString& InPathName,const TArray<FString>& InIndexes,const FName& InFuncName);
	
	static void SetAssetsPaths(const TArray<FString>& Paths);

	// static void Loading();
	
	//获得当前加载到的模型
	UFUNCTION(BlueprintCallable, Category = "AsycLoadMeshes")
	static TArray<UObject*> GetLoadedMeshes();

	static TArray<UObject*> LoadedMeshes;
	
	static TSharedPtr<FStreamableHandle> GeometryHandle;
	
	static FStreamableManager* GeometryManager;

	static TArray<FStringAssetReference> GeometryPaths;


};
