#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayTagContainer.h"
#include "CharacterBase.generated.h"

class UCharacterDataAsset;
class ACharacterBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterResourceChangedSignature, ACharacterBase*, Character);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterDeathSignature, ACharacterBase*, Character);

UCLASS(Abstract, Blueprintable)
class ECHOOFELEMENTS_API ACharacterBase : public ACharacter
{
    GENERATED_BODY()

public:
    ACharacterBase();

    virtual void BeginPlay() override;
    virtual float TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

    UFUNCTION(BlueprintCallable, Category = "Character|Resources")
    void SetCharacterData(UCharacterDataAsset* InCharacterData);

    UFUNCTION(BlueprintPure, Category = "Character|Resources")
    UCharacterDataAsset* GetCharacterData() const { return CharacterData; }

    UFUNCTION(BlueprintPure, Category = "Character|Resources")
    float GetHealthPercent() const;

    UFUNCTION(BlueprintPure, Category = "Character|Resources")
    bool IsAlive() const { return Health > 0.0f; }

    UFUNCTION(BlueprintCallable, Category = "Character|Resources")
    void RestoreHealth(float Amount);

    UFUNCTION(BlueprintCallable, Category = "Character|Resources")
    bool ConsumeResonance(float Amount);

    UFUNCTION(BlueprintCallable, Category = "Character|Combat")
    void DealCharacterDamage(AActor* Target, float DamageAmount, TSubclassOf<UDamageType> DamageType = nullptr);

    UPROPERTY(BlueprintAssignable, Category = "Character|Events")
    FCharacterResourceChangedSignature OnResourceChanged;

    UPROPERTY(BlueprintAssignable, Category = "Character|Events")
    FCharacterDeathSignature OnCharacterDeath;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character|Data")
    TObjectPtr<UCharacterDataAsset> CharacterData;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character|Resources")
    float Health = 1000.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character|Resources")
    float Resonance = 0.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character|Resources")
    float Stamina = 100.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character|Resources")
    FGameplayTagContainer ActiveElementTags;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character|State")
    bool bIsDead = false;

    virtual void HandleDeath(AController* EventInstigator, AActor* DamageCauser);
    void BroadcastResourceChanged();
};
