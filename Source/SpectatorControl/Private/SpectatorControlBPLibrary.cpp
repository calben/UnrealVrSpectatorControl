// Fill out your copyright notice in the Description page of Project Settings.

#include "SpectatorControlBPLibrary.h"
#include "Runtime/HeadMountedDisplay/Public/HeadMountedDisplayFunctionLibrary.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"

const FVector2D USpectatorControlBPLibrary::GetAbsoluteLocationForCursorWidgetFromMousePosition(APlayerController* PlayerController)
{
	float mouse_x;
	float mouse_y;
	int max_x;
	int max_y;
	PlayerController->GetMousePosition(mouse_x, mouse_y);
	PlayerController->GetViewportSize(max_x, max_y);
	float pixel_density = UHeadMountedDisplayFunctionLibrary::GetPixelDensity();
	max_x /= pixel_density;
	max_y /= pixel_density;
	float mouse_x_percentage = mouse_x / (float)max_x;
	float mouse_y_percentage = mouse_y / (float)max_y;
	UE_LOG(LogTemp, Log, TEXT("Mouse position {x:%f,y:%f}"), mouse_x, mouse_y);
	return FVector2D(mouse_x_percentage  * 1920.f, mouse_y_percentage * 1080.f);
}

const FVector2D USpectatorControlBPLibrary::OffsetCursorWidgetFromMouseLocationForMiddlePivot(const FVector2D AbsoluteCursorLocation, const FVector2D TargetResolution)
{
	FVector2D Result = TargetResolution / 2.f - AbsoluteCursorLocation;
	return Result;
}
