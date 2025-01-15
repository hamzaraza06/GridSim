// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid.h"
#include "Ball.h"

AGrid::AGrid()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AGrid::BeginPlay()
{
    Super::BeginPlay();

    for (int x = 0; x < GridSize; ++x)
    {
        for (int y = 0; y < GridSize; ++y)
        {
            FVector Location(x * CellSize, y * CellSize, 0.0f);
            GetWorld()->SpawnActor<AActor>(Cell, Location, FRotator::ZeroRotator);
        }
    }

    FRandomStream RandomStream(12345);

    FVector2D RedPosition(RandomStream.FRandRange(0, GridSize), RandomStream.FRandRange(0, GridSize));
    FVector2D BluePosition(RandomStream.FRandRange(0, GridSize), RandomStream.FRandRange(0, GridSize));

    ABall* RedBall = GetWorld()->SpawnActor<ABall>(RedBallPrefab, FVector(RedPosition, 0.0f), FRotator::ZeroRotator);
    ABall* BlueBall = GetWorld()->SpawnActor<ABall>(BlueBallPrefab, FVector(BluePosition, 0.0f), FRotator::ZeroRotator);

    RedBall->Initialize(RedPosition, BlueBall, this);
    BlueBall->Initialize(BluePosition, RedBall, this);
	
}

FVector AGrid::GetCellLocation(int X, int Y) const
{
    return FVector(X * CellSize, Y * CellSize, 0.0f);
}


