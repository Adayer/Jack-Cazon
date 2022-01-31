// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MyDEditor : ModuleRules
{
	public MyDEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "MyD" });

		PrivateDependencyModuleNames.AddRange(new string[] {"UnrealEd", "UMG", "Blutility", "EditorScriptingUtilities"  });
	}
}
