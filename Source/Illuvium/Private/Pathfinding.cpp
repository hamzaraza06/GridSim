// Fill out your copyright notice in the Description page of Project Settings.


#include "Pathfinding.h"
#include "Algo/Reverse.h"

TArray<FVector2D> UPathfinding::FindPath(FVector2D Start, FVector2D Target, int GridSize)
{
    TArray<FVector2D> OpenList = { Start };
    TMap<FVector2D, FVector2D> CameFrom;
    TMap<FVector2D, int32> GScore;
    GScore.Add(Start, 0);

    TMap<FVector2D, int32> FScore;
    FScore.Add(Start, Heuristic(Start, Target));
    while (OpenList.Num() > 0)
    {
        FVector2D Current = GetLowestFScoreNode(OpenList, FScore);

        if (Current.Equals(Target, 0.99f) )
        {
            return ReconstructPath(CameFrom, Current);
        }

        OpenList.Remove(Current);
        TArray<FVector2D> Neighbors = GetNeighbors(Current, GridSize);
        for (FVector2D Neighbor : Neighbors)
        {
            int32 TentativeGScore = GScore[Current] + 1;

            if (!GScore.Contains(Neighbor) || TentativeGScore < GScore[Neighbor])
            {
                CameFrom.Add(Neighbor, Current);
                GScore.Add(Neighbor, TentativeGScore);
                FScore.Add(Neighbor, GScore[Neighbor] + Heuristic(Neighbor, Target));

                if (!OpenList.Contains(Neighbor))
                {
                    OpenList.Add(Neighbor);
                }
            }
        }
    }

    return TArray<FVector2D>();
}

int UPathfinding::Heuristic(FVector2D A, FVector2D B)
{
    return FMath::Abs(A.X - B.X) + FMath::Abs(A.Y - B.Y);
}

FVector2D UPathfinding::GetLowestFScoreNode(TArray<FVector2D>& OpenList, TMap<FVector2D, int>& FScore)
{
    FVector2D Lowest = OpenList[0];
    int32 LowestScore = FScore[Lowest];

    for (FVector2D Point : OpenList)
    {
        int32 Score = FScore[Point];
        if (Score < LowestScore)
        {
            Lowest = Point;
            LowestScore = Score;
        }
    }

    return Lowest;
}

TArray<FVector2D> UPathfinding::GetNeighbors(FVector2D Node, int GridSize)
{
    TArray<FVector2D> Neighbors;

    Neighbors.Add(FVector2D(Node.X + 1, Node.Y));
    Neighbors.Add(FVector2D(Node.X - 1, Node.Y));
    Neighbors.Add(FVector2D(Node.X, Node.Y + 1));
    Neighbors.Add(FVector2D(Node.X, Node.Y - 1));

    Neighbors.RemoveAll([GridSize](FVector2D Neighbor)
    {
        return Neighbor.X < 0 || Neighbor.Y < 0 || Neighbor.X >= GridSize || Neighbor.Y >= GridSize;
    });

    return Neighbors;
}

TArray<FVector2D> UPathfinding::ReconstructPath(TMap<FVector2D, FVector2D>& CameFrom, FVector2D Current)
{
    TArray<FVector2D> Path;
    Path.Add(Current);

    while (CameFrom.Contains(Current))
    {
        Current = CameFrom[Current];
        Path.Add(Current);
    }

    Algo::Reverse(Path);
    return Path;
}
