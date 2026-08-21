#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeakPointComponent.generated.h"

USTRUCT(BlueprintType)
struct FWeakPointDefinition
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weak Point")
    FName SocketName;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weak Point", meta = (ClampMin = "1.0"))
    float DamageMultiplier = 2.2f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weak Point", meta = (ClampMin = "1.0"))
    float StaggerMultiplier = 1.75f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weak Point")
    bool bStartsExposed = false;
};

USTRUCT(BlueprintType)
struct FWeakPointRuntimeState
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "Weak Point")
    bool bIsExposed = false;

    UPROPERTY(BlueprintReadOnly, Category = "Weak Point")
    bool bIsBroken = false;

    UPROPERTY(BlueprintReadOnly, Category = "Weak Point")
    float RemainingExposureTime = 0.0f;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWeakPointStateChangedSignature, FName, SocketName);

UCLASS(ClassGroup = (Combat), Blueprintable, meta = (BlueprintSpawnableComponent))
class ECHOOFELEMENTS_API UWeakPointComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UWeakPointComponent();

    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    UFUNCTION(BlueprintCallable, Category = "Weak Point")
    void SetWeakPointExposed(FName SocketName, bool bExposed, float Duration = 0.0f);

    UFUNCTION(BlueprintCallable, Category = "Weak Point")
    bool BreakWeakPoint(FName SocketName);

    UFUNCTION(BlueprintPure, Category = "Weak Point")
    float GetDamageMultiplier(FName SocketName) const;

    UFUNCTION(BlueprintPure, Category = "Weak Point")
    float GetStaggerMultiplier(FName SocketName) const;

    UFUNCTION(BlueprintPure, Category = "Weak Point")
    bool IsExposed(FName SocketName) const;

    UFUNCTION(BlueprintPure, Category = "Weak Point")
    bool IsBroken(FName SocketName) const;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weak Point")
    TArray<FWeakPointDefinition> Definitions;

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Weak Point")
    TMap<FName, FWeakPointRuntimeState> RuntimeStates;

    UPROPERTY(BlueprintAssignable, Category = "Weak Point|Events")
    FWeakPointStateChangedSignature OnWeakPointExposed;

    UPROPERTY(BlueprintAssignable, Category = "Weak Point|Events")
    FWeakPointStateChangedSignature OnWeakPointBroken;

protected:
    const FWeakPointDefinition* FindDefinition(FName SocketName) const;
    void EnsureRuntimeStates();
};
