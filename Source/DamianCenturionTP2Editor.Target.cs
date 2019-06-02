// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class DamianCenturionTP2EditorTarget : TargetRules
{
	public DamianCenturionTP2EditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "DamianCenturionTP2" } );
	}
}
