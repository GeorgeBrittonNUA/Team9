// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Engine.h"
#include "RedBloodCell.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "WhiteBloodCell.generated.h"

UENUM() // Enum for the placement of the shield relative to the cell
enum class ShieldOrientationEnum : uint8 {
	ShieldOrientation_Up UMETA(DisplayName = "Up"),
	ShieldOrientation_Down UMETA(DisplayName = "Down"),
	ShieldOrientation_Left UMETA(DisplayName = "Left"),
	ShieldOrientation_Right UMETA(DisplayName = "Right"),
};

UCLASS()
class BLOODGAME_API AWhiteBloodCell : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AWhiteBloodCell();

	// Applies all the modified changed
	UPROPERTY(EditAnywhere, Category = "White Blood Cell", BlueprintReadWrite)
		bool ApplyChanges = false;

	// Whether or not the cell difts
	UPROPERTY(EditAnywhere, Category = "White Blood Cell", BlueprintReadWrite)
		bool VerticalSway = false;
	UPROPERTY(EditAnywhere, Category = "White Blood Cell", BlueprintReadWrite)
		bool HorizontalSway = false;

	// How far the cell drifts
	UPROPERTY(EditAnywhere, Category = "White Blood Cell", BlueprintReadWrite)
		int32 VerticalSwaySeverity = 20;
	UPROPERTY(EditAnywhere, Category = "White Blood Cell", BlueprintReadWrite)
		int32 HorizontalSwaySeverity = 20;

	// Destination the cell's swaying will end at
	UPROPERTY()
		int32 VerticalSwayDestination = VerticalSwaySeverity;
	UPROPERTY()
		int32 HorizontalSwayDestination = HorizontalSwaySeverity;

	// How far the cell has swayed so far
	UPROPERTY()
		int32 VerticalSwayCount = 0;
	UPROPERTY()
		int32 HorizontalSwayCount = 0;

	// Chosen location of the shield relative to the cell
	UPROPERTY(EditAnywhere, Category = "White Blood Cell", BlueprintReadWrite)
		ShieldOrientationEnum ShieldOrientation = ShieldOrientationEnum::ShieldOrientation_Left;

	// Direction the cell's moving in
	UPROPERTY(EditAnywhere, Category = "White Blood Cell", BlueprintReadWrite)
		MovementDirectionEnum CellMovementDirection = MovementDirectionEnum::NoMovement;

	// Whether or not the cell is moving
	UPROPERTY()
		bool IsMoving = true;

	// Speed at which the cell moves
	UPROPERTY(EditAnywhere, Category = "White Blood Cell", BlueprintReadWrite)
		float Speed = 5.0f;

	// Whether or not the cell has collided with something
	UPROPERTY()
		bool Collided = false;

	// Sprite body for the cell
	UPROPERTY(EditAnywhere, Category = "White Blood Cell", BlueprintReadWrite)
		UPaperFlipbook * SpriteFlipbook;

	// Sprite that is spawned to represent the cell
	UPROPERTY()
		UPaperFlipbookComponent * CellSprite;

	// Static mesh for the shield
	UPROPERTY(EditAnywhere, Category = "White Blood Cell", BlueprintReadWrite)
		UPaperSprite * Shield;

	// Strength with which the cell hits the player
	UPROPERTY(EditAnywhere, Category = "White Blood Cell", BlueprintReadWrite)
		float BounceStrength = 30000;

	// Sound that plays when the player bounces off the shield
	UPROPERTY(EditAnywhere, Category = "White Blood Cell", BlueprintReadWrite)
		USoundCue * ShieldBounceSound;

	// Sound component to play the bounce sound
	UPROPERTY()
		UAudioComponent * ShieldBounceAudioComponent;

	// Shield sprite component
	UPROPERTY()
		UPaperSpriteComponent * ShieldSprite;

	// Used to save the cell's movement pre-bounce
	UPROPERTY()
		MovementDirectionEnum TempCellDirection;

	// Makes sure the movement is always reset
	UPROPERTY()
		bool MovementReset = true;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// Called every time anything is changed
	virtual void OnConstruction(const FTransform& Transform) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called when the cell hits anything
	UFUNCTION()
		void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

	// Called during runtime to restart the cell's movement post-bounce
	UFUNCTION()
		void RestartMovement();
};
