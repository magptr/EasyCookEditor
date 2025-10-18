// https://github.com/magxut/EasyCookEditor?tab=GPL-3.0-1-ov-file

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "EasyCookEditorStyle.h"

class FEasyCookEditorCommands : public TCommands<FEasyCookEditorCommands>
{
public:

	FEasyCookEditorCommands()
		: TCommands<FEasyCookEditorCommands>(TEXT("EasyCookEditor"), NSLOCTEXT("Contexts", "EasyCookEditor", "EasyCookEditor Plugin"), NAME_None, FEasyCookEditorStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};