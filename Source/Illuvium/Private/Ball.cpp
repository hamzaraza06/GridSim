// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Pathfinding.h"


ABall::ABall()
{
	PrimaryActorTick.bCanEverTick = true;
	bIsMoving = false;
}

void ABall::BeginPlay()
{
	Super::BeginPlay();

	MaterialInstance = UMaterialInstanceDynamic::Create(this->GetComponentByClass<UStaticMeshComponent>()->GetMaterial(0), this);
	this->GetComponentByClass<UStaticMeshComponent>()->SetMaterial(0, MaterialInstance);
	
}

void ABall::Initialize(FVector2D StartPosition, ABall* Targetball, AGrid* GridActor)
{
	HitPoints = FMath::RandRange(2, 5);
	CurrentPosition = StartPosition;
	Grid = GridActor;
	SetActorLocation(Grid->GetCellLocation(CurrentPosition.X, CurrentPosition.Y));
	Target = Targetball;
	GetWorld()->GetTimerManager().SetTimer(MoveTimerHandle, this, &ABall::MoveTowardsTarget, MoveRate, true);

}

void ABall::MoveTowardsTarget()
{
	if (!Target || bIsMoving) return;

	TArray<FVector2D> Path = UPathfinding::FindPath(CurrentPosition, FVector2D(Target->GetActorLocation().X / Grid->CellSize, Target->GetActorLocation().Y / Grid->CellSize), Grid->GridSize);

	if (Path.Num() > 1)
	{
		NextPosition = Path[1];
		bIsMoving = true;
		CurrentLerpTime = 0.0f;
	}

	if (FVector2D::Distance(CurrentPosition, FVector2D(Target->GetActorLocation().X / Grid->CellSize, Target->GetActorLocation().Y / Grid->CellSize)) <= AttackRange)
	{
		GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, this, &ABall::Attack, AttackRate, true);
		GetWorld()->GetTimerManager().ClearTimer(MoveTimerHandle);
	}
}

void ABall::Attack()
{
	if (Target)
	{
		Target->TakeDamage();
		UpdateAttackVisuals();
	}
}

void ABall::TakeDamage()
{
	--HitPoints;

	if (HitPoints <= 0)
	{
		Destroy();
	}
}

void ABall::UpdateAttackVisuals()
{
	MaterialInstance->SetScalarParameterValue("inten", MaterialInstance->K2_GetScalarParameterValue("inten") * 10);
}

void ABall::UpdateLerp(float DeltaTime)
{
	CurrentLerpTime += DeltaTime;
	float Alpha = FMath::Clamp(CurrentLerpTime / LerpDuration, 0.0f, 1.0f);

	FVector StartLocation = Grid->GetCellLocation(CurrentPosition.X, CurrentPosition.Y);
	FVector EndLocation = Grid->GetCellLocation(NextPosition.X, NextPosition.Y);

	SetActorLocation(FMath::Lerp(StartLocation, EndLocation, Alpha));

	if (Alpha >= 1.0f)
	{
		CurrentPosition = NextPosition;
		bIsMoving = false;
	}
}

void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsMoving)
	{
		UpdateLerp(DeltaTime);
	}
}

