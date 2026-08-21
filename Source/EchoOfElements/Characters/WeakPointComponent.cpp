#include "WeakPointComponent.h"
#include "Net/UnrealNetwork.h"

UWeakPointComponent::UWeakPointComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    SetIsReplicatedByDefault(true);
}

void UWeakPointComponent::BeginPlay()
{
    Super::BeginPlay();
    EnsureRuntimeStates();
}

void UWeakPointComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (!GetOwner() || !GetOwner()->HasAuthority())
    {
        return;
    }

    for (TPair<FName, FWeakPointRuntimeState>& Pair : RuntimeStates)
    {
        FWeakPointRuntimeState& State = Pair.Value;
        if (State.bIsExposed && State.RemainingExposureTime > 0.0f)
        {
            State.RemainingExposureTime = FMath::Max(0.0f, State.RemainingExposureTime - DeltaTime);
            if (State.RemainingExposureTime <= 0.0f)
            {
                State.bIsExposed = false;
                OnWeakPointExposed.Broadcast(Pair.Key);
            }
        }
    }
}

void UWeakPointComponent::EnsureRuntimeStates()
{
    for (const FWeakPointDefinition& Definition : Definitions)
    {
        if (Definition.SocketName.IsNone())
        {
            continue;
        }

        FWeakPointRuntimeState& State = RuntimeStates.FindOrAdd(Definition.SocketName);
        State.bIsExposed = Definition.bStartsExposed;
        State.bIsBroken = false;
        State.RemainingExposureTime = 0.0f;
    }
}

void UWeakPointComponent::SetWeakPointExposed(FName SocketName, bool bExposed, float Duration)
{
    if (!GetOwner() || !GetOwner()->HasAuthority() || !FindDefinition(SocketName))
    {
        return;
    }

    FWeakPointRuntimeState& State = RuntimeStates.FindOrAdd(SocketName);
    State.bIsExposed = bExposed && !State.bIsBroken;
    State.RemainingExposureTime = State.bIsExposed ? FMath::Max(0.0f, Duration) : 0.0f;
    OnWeakPointExposed.Broadcast(SocketName);
}

bool UWeakPointComponent::BreakWeakPoint(FName SocketName)
{
    if (!GetOwner() || !GetOwner()->HasAuthority() || !FindDefinition(SocketName))
    {
        return false;
    }

    FWeakPointRuntimeState& State = RuntimeStates.FindOrAdd(SocketName);
    if (!State.bIsExposed || State.bIsBroken)
    {
        return false;
    }

    State.bIsBroken = true;
    State.bIsExposed = false;
    State.RemainingExposureTime = 0.0f;
    OnWeakPointBroken.Broadcast(SocketName);
    return true;
}

float UWeakPointComponent::GetDamageMultiplier(FName SocketName) const
{
    const FWeakPointRuntimeState* State = RuntimeStates.Find(SocketName);
    const FWeakPointDefinition* Definition = FindDefinition(SocketName);
    return (State && Definition && State->bIsExposed && !State->bIsBroken) ? Definition->DamageMultiplier : 1.0f;
}

float UWeakPointComponent::GetStaggerMultiplier(FName SocketName) const
{
    const FWeakPointRuntimeState* State = RuntimeStates.Find(SocketName);
    const FWeakPointDefinition* Definition = FindDefinition(SocketName);
    return (State && Definition && State->bIsExposed && !State->bIsBroken) ? Definition->StaggerMultiplier : 1.0f;
}

bool UWeakPointComponent::IsExposed(FName SocketName) const
{
    const FWeakPointRuntimeState* State = RuntimeStates.Find(SocketName);
    return State && State->bIsExposed && !State->bIsBroken;
}

bool UWeakPointComponent::IsBroken(FName SocketName) const
{
    const FWeakPointRuntimeState* State = RuntimeStates.Find(SocketName);
    return State && State->bIsBroken;
}

const FWeakPointDefinition* UWeakPointComponent::FindDefinition(FName SocketName) const
{
    return Definitions.FindByPredicate([SocketName](const FWeakPointDefinition& Definition)
    {
        return Definition.SocketName == SocketName;
    });
}

void UWeakPointComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(UWeakPointComponent, RuntimeStates);
}
