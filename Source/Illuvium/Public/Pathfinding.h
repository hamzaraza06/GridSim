// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Pathfinding.generated.h"

/**
 * 
 */
UCLASS()
class ILLUVIUM_API UPathfinding : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Pathfinding")
	static TArray<FVector2D> FindPath(FVector2D Start, FVector2D Target, int GridSize);


private:

	static int Heuristic(FVector2D A, FVector2D B);
	static FVector2D GetLowestFScoreNode(TArray<FVector2D>& OpenList, TMap<FVector2D, int>& FScore);
	static TArray<FVector2D> GetNeighbors(FVector2D Node, int GridSize);
	static TArray<FVector2D> ReconstructPath(TMap<FVector2D, FVector2D>& CameFrom, FVector2D Current);

};
