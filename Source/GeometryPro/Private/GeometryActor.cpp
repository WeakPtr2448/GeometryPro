// Fill out your copyright notice in the Description page of Project Settings.


#include "GeometryActor.h"

#include "Engine/ObjectLibrary.h"

#define GEOMETRIES_PATH "/Game/2D/Geometries"
#define GEOMETRIES_PATH_1 "StaticMesh'/Game/2D/Geometries/"

// Sets default values
AGeometryActor::AGeometryActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGeometryActor::BeginPlay()
{
	Super::BeginPlay();

	// StartLoad();
}

void AGeometryActor::Start()
{
	// FTestableRunnable* th1 = new FTestableRunnable(this);
	// FTestableRunnable* th2 = new FTestableRunnable(this);
	// FTestableRunnable* th3 = new FTestableRunnable(this);
	// FTestableRunnable* th4 = new FTestableRunnable(this);
	// FRunnableThread* RunnableThread_1 = FRunnableThread::Create(th1,TEXT("线程1"));
	// FRunnableThread* RunnableThread_2 = FRunnableThread::Create(th2,TEXT("线程2"));
	// FRunnableThread* RunnableThread_3 = FRunnableThread::Create(th3,TEXT("线程3"));
	// FRunnableThread* RunnableThread_4 = FRunnableThread::Create(th4,TEXT("线程4"));
}

void AGeometryActor::StartLoad(const TArray<FString>& InIndexes)
{
	//StaticMesh'/Game/Geometries/meshId4057_name.meshId4057_name'
	TArray<FString> Paths;
	for (FString Index : InIndexes){
	
		Paths.Add(FString(GEOMETRIES_PATH_1)
			+ FString("meshId")
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
	/*GeometryManager = new FStreamableManager();
	GeometryHandle = GeometryManager->RequestAsyncLoad(GeometryPaths,
	                                                   FStreamableDelegate::CreateUObject(
		                                                   this, &AGeometryActor::LoadGeometriesComplete));*/
}

void AGeometryActor::SetAssetsPaths(const TArray<FString>& Paths)
{
	/*UObjectLibrary* ObjectLibrary = UObjectLibrary::CreateLibrary(UObject::StaticClass(), false, false);

	ObjectLibrary->AddToRoot();
	ObjectLibrary->LoadAssetDataFromPath(TEXT(GEOMETRIES_PATH));*/
	for (FString Path : Paths)
	{
		GeometryPaths.Add(Path);
	}

	/*TArray<FAssetData> AssetDatas;
	ObjectLibrary->GetAssetDataList(AssetDatas);*/

	UE_LOG(LogTemp, Warning, TEXT("加载的资源个数为: %d"), GeometryPaths.Num());

	/*for (FAssetData AssetData : AssetDatas)
	{
		GeometryPaths.Add(AssetData.ToSoftObjectPath());
	}*/
}

void AGeometryActor::LoadGeometriesComplete()
{
	TArray<UObject*> LoadedMeshes;
	// GeometryHandle->GetLoadedAssets(LoadedMeshes);
	// LoadedMeshes.Append(UAsycLoadMeshesBPLibrary::GetLoadedMeshes());

	FTransform Transform = FTransform();
	for (int i = 0; i < LoadedMeshes.Num(); ++i)
	{
		UE_LOG(LogTemp, Warning, TEXT("模型为: %s"), *LoadedMeshes[i]->GetFName().ToString());

		UStaticMeshComponent* StaticMeshComp = Cast<UStaticMeshComponent>(
			AddComponentByClass(UStaticMeshComponent::StaticClass(), true, Transform, false));
		StaticMeshComp->SetStaticMesh(Cast<UStaticMesh>(LoadedMeshes[i]));
		StaticMeshComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

		/*FString ModelNameStr = LoadedMeshes[i]->GetFName().ToString().Right(6);
		FString NumStr = ModelNameStr.Mid(0, 1);
		Index = FCString::Atoi(*NumStr);*/

		StaticMeshComp->SetRelativeLocation(FVector(i * 0.f, 0.f, 0.f));

		/*if (Index % 2 != 0)
		{
			StaticMeshComp->SetMaterial(0, MaterialInterface);
		}*/
	}
}


// Called every frame
void AGeometryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
