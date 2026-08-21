using UnrealBuildTool;
using System.Collections.Generic;

public class EchoOfElementsEditorTarget : TargetRules
{
    public EchoOfElementsEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.V5;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_8;
        ExtraModuleNames.Add("EchoOfElements");
    }
}
