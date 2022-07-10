// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;


public class VfxSamplesEditorTarget : TargetRules
{
	public VfxSamplesEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange( new string[] { "VfxSamples" } );
	}
}
