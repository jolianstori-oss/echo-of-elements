using UnrealBuildTool;

public class EchoOfElements : ModuleRules
{
    public EchoOfElements(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "EnhancedInput",
            "GameplayAbilities",
            "GameplayTags",
            "GameplayTasks",
            "Niagara",
            "Chaos",
            "ChaosSolverEngine",
            "PhysicsCore",
            "NetCore"
        });

        PrivateDependencyModuleNames.AddRange(new string[] { });

        PublicIncludePaths.AddRange(new string[]
        {
            "EchoOfElements/Public"
        });

        PrivateIncludePaths.AddRange(new string[]
        {
            "EchoOfElements/Private"
        });
    }
}
