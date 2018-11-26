// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SpectatorControlBPLibrary.generated.h"

/**
 *
 */
UCLASS()
class SPECTATORCONTROL_API USpectatorControlBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/**
	* Calculates the expected cursor position from a viewport of some size to a widget of some size.
	*
	* @param PlayerController The player controller reference from which to get the mouse position.
	* @param WidgetSize The size of the widget for which the cursor position should be calculated.
	* @return Returns the "absolute" location for the widget as a FVector2D offset from the widget origin of 0,0 (top left corner).
	*/
	UFUNCTION(BlueprintPure)
		static const FVector2D GetAbsoluteLocationForCursorWidgetFromMousePosition(class APlayerController* PlayerController, const FVector2D WidgetSize = FVector2D(1920.f, 1080.f));

	/**
	* Retargets a cursor's absolute position to a 3D widget given that in order for widget interaction to work correctly, the widget component should have a pivot of (0.5, 0.5).
	*
	* @param AbsoluteCursorLocation The position of the cursor as an offset from the widget origin.
	* @param TargetResolution The target resolution of the widget.
	* @return The cursor location corrected for the pivot offset.
	*/
	UFUNCTION(BlueprintPure)
		static const FVector2D OffsetCursorWidgetFromMouseLocationForMiddlePivot(const FVector2D AbsoluteCursorLocation, const FVector2D TargetResolution = FVector2D(1920.f, 1080.f));

	/**
	* Gets the spectator display resolution for both in editor and in game
	*
	* @return The display resolution.
	*/
	UFUNCTION(BlueprintPure)
		static const FVector2D GetSpectatorDisplayResolution();

};
