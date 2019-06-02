// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class DamianCenturionTP2Target : TargetRules
{
	public DamianCenturionTP2Target(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "DamianCenturionTP2" } );
	}
}
