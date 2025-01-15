// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grid.h"
#include "Ball.generated.h"

UCLASS()
class ILLUVIUM_API ABall : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ABall();

protected:

	virtual void BeginPlay() override;

public:

    UPROPERTY(BlueprintReadOnly, Category = "BallProperty")
    int HitPoints;

    UPROPERTY(EditAnywhere, Category = "BallProperty")
    float MoveRate = 1.0f;

    UPROPERTY(EditAnywhere, Category = "BallProperty")
    float AttackRate = 1.0f;

    UPROPERTY(EditAnywhere, Category = "BallProperty")
    int AttackRange = 3.0f;

    UPROPERTY(EditAnywhere, Category = "BallProperty")
    float LerpDuration = 0.5f;


    void Initialize(FVector2D StartPosition, ABall* Targetball, AGrid* GridActor);

private:
    UPROPERTY()
    FVector2D CurrentPosition;

    UPROPERTY()
    ABall* Target;

    UPROPERTY()
    AGrid* Grid;

    UPROPERTY()
    FTimerHandle MoveTimerHandle;

    UPROPERTY()
    FTimerHandle AttackTimerHandle;

    UPROPERTY()
    UMaterialInstanceDynamic* MaterialInstance;

    UPROPERTY()
    FVector2D NextPosition;

    UPROPERTY()
    float CurrentLerpTime;

    UPROPERTY()
    bool bIsMoving;

    void MoveTowardsTarget();

    void Attack();

    void TakeDamage();

    void UpdateAttackVisuals();

    void UpdateLerp(float DeltaTime);

    virtual void Tick(float DeltaTime) override;
};
