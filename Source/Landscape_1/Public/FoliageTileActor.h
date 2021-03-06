#pragma once

#include "TileActor.h"
#include "FoliageTileBlockingVolume.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "FoliageTileActor.generated.h"

USTRUCT()
struct FFoliageSpawnNoise
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ClampMin = "1", UIMin = "1"))
		int32 NoiseSize;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
		float Min;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
		float Max;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ClampMin = "0", UIMin = "0"))
		int32 Seed;

	FFoliageSpawnNoise()
	{
		NoiseSize = 1000;
		Min = 0.0f;
		Max = 1.0f;
		Seed = 0;
	}
};

USTRUCT()
struct FFoliageScaleNoise
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ClampMin = "1", UIMin = "1"))
		int32 NoiseSize;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ClampMin = "0.0", UIMin = "0.0"))
		float Min;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ClampMin = "0.0", UIMin = "0.0"))
		float Max;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ClampMin = "0", UIMin = "0"))
		int32 Seed;

	FFoliageScaleNoise()
	{
		NoiseSize = 1000;
		Min = 1.0f;
		Max = 1.0f;
		Seed = 0;
	}
};

UCLASS()
class UFoliageTile : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(transient)
		TArray<UHierarchicalInstancedStaticMeshComponent*> MeshComponents;
};

UCLASS()
class LANDSCAPE_1_API AFoliageTileActor : public ATileActor
{
	GENERATED_BODY()

public:
	AFoliageTileActor();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mesh")
		UStaticMesh* Mesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ClampMin = "0.0", UIMin = "0.0"), Category = "Mesh")
		FFoliageScaleNoise Scale;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mesh")
		bool AlignWithSlope;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mesh")
		bool Collision;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mesh")
		uint32 CastShadow : 1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mesh")
		bool AffectDistanceFieldLighting;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ClampMin = "0.0", UIMin = "0.0"), Category = "Spawning")
		float DistanceBetween;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ClampMin = "0.0", UIMin = "0.0"), Category = "Spawning")
		float OffsetFactor;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ClampMin = "0.0", UIMin = "0.0"), Category = "Spawning")
		float SpawnChance;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Spawning")
		FName Layer;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Spawning")
		TArray<FFoliageSpawnNoise> SpawnNoise;

	/** A value of 0.0 causes this to be calculated to 50 % of the radius. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ClampMin = "0.0", UIMin = "0.0"), Category = "Spawning")
		float MinCullDistance;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Advanced")
		int32 Seed;

protected:
	virtual void UpdateTile(int32 x, int32 y, FVector location) override;
	virtual void Load() override;
	virtual void Unload() override;
	virtual bool ShouldExport() override;

private:
	UPROPERTY(transient)
		TArray<UFoliageTile*> FoliageTiles;

	UPROPERTY(transient)
		TArray<AActor*> BlockingVolumes;

	uint32 Hash(uint32 a);
	FTransform GetTransform(FVector location, uint32 seed, TArray<AActor*> actorsToIgnore);
};
