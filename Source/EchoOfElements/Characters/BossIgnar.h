#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "BossIgnar.generated.h"

UENUM(BlueprintType)
enum class EIgnarCombatPhase : uint8
{
    PhaseOne,
    PhaseTwo,
    PhaseThree,
    Defeated
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FIgnarPhaseChangedSignature, EIgnarCombatPhase, NewPhase);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FIgnarTelegraphSignature, FName, AttackId);

UCLASS(Blueprintable)
class ECHOOFELEMENTS_API ABossIgnar : public ACharacterBase
{
    GENERATED_BODY()

public:
    ABossIgnar();

    virtual void BeginPlay() override;
    virtual float TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

    UFUNCTION(BlueprintPure, Category = "Ignar|Combat")
    EIgnarCombatPhase GetCombatPhase() const { return CombatPhase; }

    UFUNCTION(BlueprintPure, Category = "Ignar|Combat")
    float GetPhaseHealthPercent() const;

    UFUNCTION(BlueprintCallable, Category = "Ignar|Combat")
    void StartTelegraph(FName AttackId, float Duration);

    UFUNCTION(BlueprintCallable, Category = "Ignar|Combat")
    void OpenAbsorbWindow(float Duration);

    UFUNCTION(BlueprintPure, Category = "Ignar|Combat")
    bool IsAbsorbWindowOpen() const { return bAbsorbWindowOpen; }

    UPROPERTY(BlueprintAssignable, Category = "Ignar|Events")
    FIgnarPhaseChangedSignature OnPhaseChanged;

    UPROPERTY(BlueprintAssignable, Category = "Ignar|Events")
    FIgnarTelegraphSignature OnTelegraphStarted;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ignar|Tuning")
    float PhaseTwoHealthThreshold = 0.66f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ignar|Tuning")
    float PhaseThreeHealthThreshold = 0.33f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ignar|Tuning")
    float PhaseTwoDamageMultiplier = 1.15f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ignar|Tuning")
    float PhaseThreeDamageMultiplier = 1.35f;

    UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Ignar|Combat")
    EIgnarCombatPhase CombatPhase = EIgnarCombatPhase::PhaseOne;

    UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Ignar|Combat")
    bool bAbsorbWindowOpen = false;

    FTimerHandle TelegraphTimerHandle;
    FTimerHandle AbsorbWindowTimerHandle;
    FName ActiveTelegraphAttack;

    void UpdateCombatPhase();
    void SetCombatPhase(EIgnarCombatPhase NewPhase);
    void FinishTelegraph();
    void CloseAbsorbWindow();
};
