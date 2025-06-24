// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class EclipseProtocol : ModuleRules
{
	public EclipseProtocol(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"EclipseProtocol",
			"EclipseProtocol/Variant_Platforming",
			"EclipseProtocol/Variant_Combat",
			"EclipseProtocol/Variant_Combat/AI",
			"EclipseProtocol/Variant_SideScrolling",
			"EclipseProtocol/Variant_SideScrolling/Gameplay",
			"EclipseProtocol/Variant_SideScrolling/AI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
