// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Mystings : ModuleRules
{
	public Mystings(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "AIModule", "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
