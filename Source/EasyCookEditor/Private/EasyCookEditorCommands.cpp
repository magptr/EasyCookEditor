// Copyright Epic Games, Inc. All Rights Reserved.

#include "EasyCookEditorCommands.h"

#define LOCTEXT_NAMESPACE "FEasyCookEditorModule"

void FEasyCookEditorCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "EasyCook", "Bring up EasyCook window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
