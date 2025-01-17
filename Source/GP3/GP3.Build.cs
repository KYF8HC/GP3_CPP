// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GP3 : ModuleRules
{
	public GP3(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
			{ 
				"Core",
				"CoreUObject",
				"Engine",
				"InputCore",
				"UMG",
				"EnhancedInput",
				"BookMenu",
				"GameplayTags",
				"NiagaraCore",
				"Niagara",
			});
	}
}