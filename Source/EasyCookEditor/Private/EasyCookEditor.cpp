// Copyright Epic Games, Inc. All Rights Reserved.

#include "EasyCookEditor.h"
#include "EasyCookEditorStyle.h"
#include "EasyCookEditorCommands.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"
#include "SEasyCookTab.h"

static const FName EasyCookEditorTabName("EasyCookEditor");

#define LOCTEXT_NAMESPACE "FEasyCookEditorModule"

void FEasyCookEditorModule::StartupModule()
{
	FEasyCookEditorStyle::Initialize();
	FEasyCookEditorStyle::ReloadTextures();
	FEasyCookEditorCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FEasyCookEditorCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FEasyCookEditorModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FEasyCookEditorModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(EasyCookEditorTabName, FOnSpawnTab::CreateRaw(this, &FEasyCookEditorModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FEasyCookEditorTabTitle", "EasyCook"))
		.SetMenuType(ETabSpawnerMenuType::Hidden)
		.SetIcon(FSlateIcon(FEasyCookEditorStyle::GetStyleSetName(), "EasyCookEditor.TabIcon"));
}

void FEasyCookEditorModule::ShutdownModule()
{
	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FEasyCookEditorStyle::Shutdown();

	FEasyCookEditorCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(EasyCookEditorTabName);
}

TSharedRef<SDockTab> FEasyCookEditorModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SBox)
			.MinDesiredWidth(900)
			.MinDesiredHeight(700)
			[
				SNew(SEasyCookTab)
			]
		];
}

void FEasyCookEditorModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(EasyCookEditorTabName);
}

void FEasyCookEditorModule::RegisterMenus()
{
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FEasyCookEditorCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FEasyCookEditorCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FEasyCookEditorModule, EasyCookEditor)