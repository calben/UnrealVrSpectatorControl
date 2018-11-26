# Purpose

Asymmetrical virtual reality applications and games often include a participant with a virtual reality headset on and another participant using either mouse and keyboard or a gamepad.
In Unreal Engine it's possible to make this, but it involves a little more work than you'd initially anticipate.
This project includes a sample of a virtual reality application in which one user can look at an environment in virtual reality and another can use a virtual cursor to interact with the game through a UMG widget on a spectator screen.

# Tutorial

## Player Pawn Setup

1. Add a `UWidgetComponent` to your player pawn.
   This will be used to render the widget for the spectator screen.
   In the sample project, this component was added as a child to the camera for debugging purposes, but you will probably want to attach it directly to the root and position the widget so that it is facing outward and thus invisible.
   While the `UWidgetComponent` doesn't necessarily need to be on the player pawn, I found it a reasonable, organized place to put it.
   If you feel your player pawn is already crowded with too much functionality, then put the `UWidgetComponent` on a unique actor in the world that can be easily found and referenced.

1. Add a `UWidgetInteractionComponent` as a child of the previously add `UWidgetComponent`.
   This component *must* be a child as its position will be set relative to its parent component.
   The widget interaction will be used to provide interactivity for the fake cursor.
   This isn't the most efficient approach as a line trace is being employed; however, if your application is being run on a computer than can handle a virtual reality render and an extra spectator render, I think an extra line trace can be forgiven.

1. Set up a function on tick that will set the cursor and widget interaction positions from the absolute location for cursor widget from mouse position and the offset position for the middle pivot.
   An example of such a function is below in the scrollable viewport as well as an explanation of why we're doing all this.

<iframe src="https://blueprintue.com/render/y5q-09au" scrolling="no" width=100% height=400px></iframe>

## Widget Setup

1. Create a widget blueprint or a `UUserWidget`.

1. Add a `UImage` behaving as a virtual cursor as the very last widget in the widget blueprint so that it shows on top of all other items. 
   Under the Behavior panel, set the visibility to "hit test invisible."
   We need to do this because the widget interaction component will be tracing onto the widget directly on the center of this widget.
   If the widget were visible to hit tests, then the widget interaction would only ever hit this widget and thus not be able to interact with the underlying UI elements.
   ![logo](_media/hit_test_invisible.png)

## Render Target Setup

1. A render target that renders out the real scene and displays it on the UI through a user interface material.

## Switching Spectator Modes

1. A behaviour such that when the `P` key is pressed when running in virtual reality the spectator mode is switched to (and from) texture and the texture is set to the render target of the widget component.

# Code Reference

There are only 3 functions in the blueprint library for this codebase, so rather than provide a full docsite for these functions, they are presented below with their comments.

```cpp
/**
* Calculates the expected cursor position from a viewport of some size to a widget of some size.
*
* @param PlayerController The player controller reference from which to get the mouse position.
* @param WidgetSize The size of the widget for which the cursor position should be calculated.
* @return Returns the "absolute" location for the widget as a FVector2D offset from the widget origin of 0,0 (top left corner).
*/
UFUNCTION(BlueprintPure)
	static const FVector2D GetAbsoluteLocationForCursorWidgetFromMousePosition(class APlayerController* PlayerController, const FVector2D WidgetSize);
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
```

# Credits

<div>Icons made by <a href="https://www.flaticon.com/authors/smashicons" title="Smashicons">Smashicons</a> from <a href="https://www.flaticon.com/" 			    title="Flaticon">www.flaticon.com</a> is licensed by <a href="http://creativecommons.org/licenses/by/3.0/" 			    title="Creative Commons BY 3.0" target="_blank">CC 3.0 BY</a></div>
