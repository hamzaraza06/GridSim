// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grid.generated.h"

class ABall;

UCLASS()
class ILLUVIUM_API AGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AGrid();

protected:

	virtual void BeginPlay() override;

public:	

	UPROPERTY(EditAnywhere, Category = "Grid")
	int GridSize = 100;

	UPROPERTY(EditAnywhere, Category = "Grid")
	TSubclassOf<AActor> Cell;

	UPROPERTY(EditAnywhere, Category = "Grid")
	float CellSize = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Grid")
	TSubclassOf<ABall> RedBallPrefab;

	UPROPERTY(EditAnywhere, Category = "Grid")
	TSubclassOf<ABall> BlueBallPrefab;

	FVector GetCellLocation(int X, int Y) const;
};
