// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Engine.h"
#include "UncontrollableZone.generated.h"

UCLASS()
class BLOODGAME_API AUncontrollableZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUncontrollableZone();

	// Box the player will overlap and lose control
	UPROPERTY(EditAnywhere, Category = "Uncontrollable Zone", BlueprintReadWrite)
		UBoxComponent * Box;

	// Called when the actor overlaps with anything
	UFUNCTION()
		void NotifyActorBeginOverlap(AActor* OtherActor) override;

	// Called when the actor stops overlapping with anything
	UFUNCTION()
		void NotifyActorEndOverlap(AActor* OtherActor) override;
};
