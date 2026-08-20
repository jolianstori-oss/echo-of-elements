---
title: "Echo of Elements — Unreal Architecture"
version: "0.1"
engine: "Unreal Engine 5.8"
status: "جاهز كخطة تنفيذ؛ غير مبني بعد لعدم وجود مشروع .uproject"
---

# Unreal Engine 5.8 — مخطط البرمجة

## 0. حالة البيئة الحالية

- مجلد المشروع موجود في `/opt/data/vault/10-projects/03-unreal-game/`.
- يوجد الآن `Source/` و`Config/` فيهما حزمة C++ وGameplay Tags قابلة للنسخ.
- لا يوجد حالياً `.uproject` أو `Content/` أو `UnrealEditor`/`UnrealBuildTool` مثبتان في بيئة Hermes الحالية.
- لذلك هذه الحزمة **مخطط وكود هيكلي قابل للدمج**، وليس ادعاءً بأن اللعبة بُنيت أو اختُبرت داخل Unreal.
- صفحات Epic الرسمية المطلوبة أعادت HTTP 200 عند التحقق: Gameplay Ability System، Networking and Multiplayer، Enhanced Input، وUE 5.8 Release Notes.

## 1. قرار اللغة والتقنية

### القرار

- **C++ هو العمود الفقري:** القتال، الـAttributes، الضرر، التفاعلات، الـSave/Load، الـReplication، الـStage state، والتحقق من المدخلات.
- **Blueprint هو طبقة التأليف والتوليف:** ترتيب الهجمات، VFX/SFX، Timeline، الكاميرا، تفاصيل الحلبة، قيم Data Assets، وسلوك الزعيم القابل للتعديل.
- **Gameplay Ability System (GAS):** كل قدرة قتالية كـ`UGameplayAbility`، وكل تغيير صحة/طاقة/حالة كـ`GameplayEffect`، وكل عنصر/حالة كـ`GameplayTag`.
- **Enhanced Input:** طبقة الإدخال الوحيدة؛ لا نضع منطق القتال داخل `InputAction` نفسه.
- **Niagara:** VFX منفصل عن منطق الضرر؛ الـVFX لا يقرر Hit أو Damage.
- **StateTree أو Behavior Tree:** AI عالي المستوى؛ القدرة نفسها تنفذ عبر GAS حتى يبقى سلوك العدو واللاعب متسقاً.

### لماذا لا نبدأ بـBlueprint فقط؟

Blueprint ممتاز للتجريب، لكنه سيصنع فوضى عندما نضيف 12 عنصراً، 12 زعيماً، اختباراً آلياً، وReplication. المنطق الحساس يجب أن يكون قابلاً للاختبار في C++، والتوازن يجب أن يبقى Data-driven.

## 2. Plugins المقترحة

نفعّل الضروري فقط:

- `GameplayAbilities`
- `GameplayTags`
- `GameplayTasks`
- `EnhancedInput`
- `AIModule`
- `NavigationSystem`
- `Niagara`
- `UMG`
- `StateTree` إذا استُخدم للزعماء
- `OnlineSubsystemUtils` عند بدء اختبار Listen Server
- Plugin منصة واحد فقط لاحقاً: EOS أو Steam، خلف واجهة `IResonanceSessionService`

لا نضيف خدمات Online أو Backend إلى الـVertical Slice قبل نجاح النسخة الفردية واختبار Listen Server.

## 3. بنية المشروع

```text
EchoOfElements/
├── EchoOfElements.uproject
├── Config/
│   ├── DefaultEngine.ini
│   ├── DefaultGame.ini
│   ├── DefaultInput.ini
│   └── DefaultGameplayTags.ini
├── Source/
│   ├── EchoOfElements/
│   │   ├── EchoOfElements.Build.cs
│   │   ├── EchoOfElements.cpp
│   │   ├── Characters/
│   │   │   ├── ResonanceCharacterBase.h/.cpp
│   │   │   ├── ResonanceHeroCharacter.h/.cpp
│   │   │   └── ResonanceBossCharacter.h/.cpp
│   │   ├── AbilitySystem/
│   │   │   ├── ResonanceAbilitySystemComponent.h/.cpp
│   │   │   ├── ResonanceAttributeSet.h/.cpp
│   │   │   ├── ResonanceGameplayAbility.h/.cpp
│   │   │   ├── ResonanceDamageExecution.h/.cpp
│   │   │   └── ResonanceGameplayEffectTypes.h/.cpp
│   │   ├── Elements/
│   │   │   ├── ResonanceElementTypes.h
│   │   │   ├── ElementReactionSubsystem.h/.cpp
│   │   │   ├── ElementalHitLibrary.h/.cpp
│   │   │   └── ElementalDataAssets.h/.cpp
│   │   ├── Combat/
│   │   │   ├── CombatTraceComponent.h/.cpp
│   │   │   ├── StaggerComponent.h/.cpp
│   │   │   ├── AbsorbComponent.h/.cpp
│   │   │   └── DamageTelemetrySubsystem.h/.cpp
│   │   ├── AI/
│   │   │   ├── ResonanceAIController.h/.cpp
│   │   │   ├── ResonanceAIPerception.h/.cpp
│   │   │   └── BossPhaseComponent.h/.cpp
│   │   ├── Stages/
│   │   │   ├── StageDefinition.h/.cpp
│   │   │   ├── StageDirector.h/.cpp
│   │   │   ├── BossArenaManager.h/.cpp
│   │   │   └── ResonanceSaveGame.h/.cpp
│   │   ├── Input/
│   │   ├── UI/
│   │   └── Online/
│   └── EchoOfElementsTests/
│       ├── ElementReactionSpec.cpp
│       ├── DamageCalculationSpec.cpp
│       ├── AbsorbValidationSpec.cpp
│       └── StageProgressionSpec.cpp
├── Content/
│   ├── Abilities/
│   ├── Effects/
│   ├── GameplayTags/
│   ├── Data/
│   │   ├── Elements/
│   │   ├── Reactions/
│   │   ├── Stages/
│   │   └── Bosses/
│   ├── Characters/
│   ├── Enemies/
│   ├── Levels/
│   │   ├── L_Hub.umap
│   │   ├── L_Stage01_Cinder.umap
│   │   └── ...
│   ├── VFX/
│   ├── SFX/
│   └── UI/
└── Tests/
    └── Fixtures/
```

## 4. Build.cs dependencies

الصيغة التالية نقطة بداية للمشروع، وتُراجع بعد إنشاء الـ`.uproject`:

```csharp
using UnrealBuildTool;

public class EchoOfElements : ModuleRules
{
    public EchoOfElements(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core", "CoreUObject", "Engine", "InputCore",
            "EnhancedInput", "GameplayAbilities", "GameplayTags",
            "GameplayTasks", "AIModule", "NavigationSystem",
            "Niagara", "UMG"
        });

        PrivateDependencyModuleNames.AddRange(new string[]
        {
            "Slate", "SlateCore", "NetCore", "PhysicsCore"
        });
    }
}
```

## 5. Gameplay Tags

نستخدم Tags بدل Enum ثابت للأشياء التي ستكبر:

```text
Element.Fire
Element.Water
Element.Earth
Element.Stone
Element.Wind
Element.Lightning
Element.Ice
Element.Nature
Element.Sand
Element.Metal
Element.Light
Element.Gravity

Damage.Kinetic
Damage.Elemental
Damage.Reaction
State.Burning
State.Wet
State.Buildup.Frozen
State.Staggered
State.AbsorbWindow
State.Invulnerable
Boss.Phase.01
Boss.Phase.02
Boss.Phase.03
Input.Ability.Basic
Input.Ability.Mobility
Input.Ability.Control
Input.Ability.Ultimate
```

قاعدة: الكود يتعامل مع `FGameplayTag` وData Assets؛ لا نكتب أسماء العناصر داخل 48 Ability مختلفة إلا عند الحاجة البصرية.

## 6. Data-driven design

### 6.1 تعريف العنصر

```cpp
USTRUCT(BlueprintType)
struct FResonanceAbilityNumbers
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float BaseDamage = 0.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float ResonanceCost = 0.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float Cooldown = 0.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float StaggerDamage = 0.f;
};

UCLASS(BlueprintType)
class ECHOOFELEMENTS_API UElementDefinition : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    FGameplayTag ElementTag;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    FText DisplayName;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<UTexture2D> Icon;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    FLinearColor PrimaryColor = FLinearColor::White;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    FResonanceAbilityNumbers BasicNumbers;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    FGameplayTagContainer AppliedStatusTags;
};
```

### 6.2 تعريف التفاعل

```cpp
USTRUCT(BlueprintType)
struct FElementReactionDefinition
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    FGameplayTag ElementA;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    FGameplayTag ElementB;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    FGameplayTag ReactionTag;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float DamageMultiplier = 1.15f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float StaggerMultiplier = 1.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float BuildupRequired = 100.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float Duration = 0.f;
};
```

يُخزن هذا في `UReactionTableDataAsset`. مفتاح البحث يجب أن يكون **غير حساس للترتيب**: `Sort(TagA, TagB)` ثم lookup، حتى لا نكتب Fire+Wind وWind+Fire كنسختين.

### 6.3 تعريف المرحلة والزعيم

`UStageDefinition` يضم:

- رقم المرحلة.
- Level/World Asset.
- عنصر المرحلة.
- Data Assets للأعداء.
- Mini-boss.
- Boss Class وBoss Definition.
- نقاط الـSpawn والـSafe Zones.
- الـEnvironmental Interactions.
- الـSave checkpoint.

`UBossDefinition` يضم:

- الاسم والـDisplay Data.
- `BossHP` و`StaggerThreshold`.
- Resistances حسب Gameplay Tag.
- ثلاثة Phase Data Assets.
- قائمة القدرات والـTelegraph durations.
- Animation/VFX/SFX references.
- شروط فتح `AbsorbWindow`.

## 7. GAS: مسار القدرة والضرر

### 7.1 Attribute Set

الحد الأدنى:

```cpp
UCLASS()
class ECHOOFELEMENTS_API UResonanceAttributeSet : public UAttributeSet
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Health)
    FGameplayAttributeData Health;
    ATTRIBUTE_ACCESSORS(UResonanceAttributeSet, Health)

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MaxHealth)
    FGameplayAttributeData MaxHealth;
    ATTRIBUTE_ACCESSORS(UResonanceAttributeSet, MaxHealth)

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Resonance)
    FGameplayAttributeData Resonance;
    ATTRIBUTE_ACCESSORS(UResonanceAttributeSet, Resonance)

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Stamina)
    FGameplayAttributeData Stamina;
    ATTRIBUTE_ACCESSORS(UResonanceAttributeSet, Stamina)

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Stagger)
    FGameplayAttributeData Stagger;
    ATTRIBUTE_ACCESSORS(UResonanceAttributeSet, Stagger)

    UPROPERTY(BlueprintReadOnly)
    FGameplayAttributeData AttackPower;
    ATTRIBUTE_ACCESSORS(UResonanceAttributeSet, AttackPower)

    UPROPERTY(BlueprintReadOnly)
    FGameplayAttributeData Defense;
    ATTRIBUTE_ACCESSORS(UResonanceAttributeSet, Defense)

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
```

الصحة لا تُعدّل من Blueprint على العميل. كل تغيير يمر عبر Gameplay Effect صادر من Authority أو قدرة predicted موثوقة ثم يحسمه السيرفر.

### 7.2 Ability base

`UResonanceGameplayAbility` يوفر:

- قراءة `AbilityDefinition`.
- فحص Tags والمورد والـCooldown.
- تطبيق `GameplayEffectSpec` مع SetByCaller للضرر والتكلفة.
- تمييز `CosmeticOnly` عن `GameplayState`.
- وظيفة `CommitAbility` موحدة.
- Hook لـ`OnAbilityEnded` كي لا تتسرب حالات Invulnerable أو Input lock.

### 7.3 Damage Execution

`UResonanceDamageExecution` يقرأ:

1. `SetByCaller.Damage.Raw`.
2. `SetByCaller.Damage.Stagger`.
3. `Data.Target.Armor`.
4. المقاومة المرتبطة بـElement Tag.
5. Reaction multiplier الناتج قبل التنفيذ.
6. حالة Crit الموثقة، لا عشوائية مخفية.

الناتج يطبّق Health Damage وStagger Damage كقيمتين منفصلتين. لا تجعل الـVFX أو `OnHit` يطبق الضرر مرة ثانية.

## 8. ElementReactionSubsystem

مسار التنفيذ:

```text
Ability produces HitContext
  → HitContext carries SourceElement + AppliedTags
  → Target StatusComponent stores recent elemental applications
  → ReactionSubsystem canonicalizes tag pair
  → reads ReactionDefinition
  → applies Reaction GameplayEffect
  → emits one telemetry event
  → Niagara/SFX listen to the event cosmetically
```

شروط مهمة:

- منع التفاعل المكرر من Hit واحد.
- مدة احتفاظ العنصر على الهدف محددة، مثلاً 4 ثوانٍ.
- إذا وصلت ثلاثة عناصر في نفس الإطار، يختار النظام عنصرين حسب أقدم تطبيق أو أولوية Data Asset، ولا ينفذ ثلاث تفاعلات غير قابلة للقراءة.
- الـReaction يملك ID واحداً وTimestamp حتى لا يتكرر عند RepNotify.

## 9. AbsorbComponent

الحالات:

```text
Idle
TargetingMote
Charging
PerfectWindow
BossAbsorbWindow
Interrupted
Cooldown
```

التحقق على السيرفر:

- المسافة أقل من `AbsorbRange`.
- الـTarget ليس `State.Invulnerable` إلا إذا كان Boss في `State.AbsorbWindow`.
- الـMote لم يُلتقط مسبقاً.
- البطل ليس Downed أو Stunned.
- الوقت بين المحاولات مقبول.

العميل يطلب، السيرفر يتحقق، ثم يرسل نتيجة الحالة؛ لا نمنح Core Shard من `Client RPC`.

## 10. CombatTraceComponent

- لا نستخدم Overlap دائم لكل سيف إذا كان Line/Sweep Trace يكفي.
- كل Ability يحدد `TraceProfile` و`HitPolicy` في Data Asset.
- `HitPolicy` يمنع ضرب الهدف نفسه أكثر من مرة في نافذة محددة.
- الـTrace يعطينا Hit Context، لكنه لا يقرر Damage؛ GAS هو نقطة القرار.
- نضيف Debug Draw اختياري مع `r.Resonance.DebugCombat 1`.

## 11. Boss AI

### 11.1 الهيكل

```text
BossAIController
  ├── Perception / Target selection
  ├── BossPhaseComponent
  ├── StateTree or BehaviorTree
  ├── Ability selection rules
  └── Arena/Boss telegraph component
```

الـAI يقرر **أي قدرة ومتى**؛ `UGameplayAbility` يقرر كيف تُنفّذ، وتطبيق الضرر يبقى في GAS.

### 11.2 Phase rules

- `Phase 1`: صحة 100–66%، تعليم الميكانيك.
- `Phase 2`: صحة 66–33%، تغيير الحلبة أو إضافة عدو جزئي.
- `Phase 3`: صحة 33–0%، دمج الميكانيك مع Safe Zones واضحة.
- التحول Phase مرة واحدة فقط لكل threshold، مع `Boss.Phase.X` Tag.
- لا نسمح للزعيم بتفعيل Ultimate أثناء انتقال Phase أو AbsorbWindow.

### 11.3 Telegraph

كل قدرة زعيم لها:

- صوت بدء.
- Animation wind-up.
- VFX لون/شكل.
- مدة قبل الضرر.
- Safe Zone أو Counter محدد.
- Event للـQA لقياس هل وصلت الإشارة قبل الضرر.

## 12. Input وUI

Enhanced Input Actions:

```text
IA_Move
IA_Look
IA_Jump
IA_Dodge
IA_LightAttack
IA_HeavyAttack
IA_Absorb
IA_AbilityBasic
IA_AbilityMobility
IA_AbilityControl
IA_AbilityUltimate
IA_TargetLock
IA_Interact
```

UI لا يقرأ المتغيرات الداخلية مباشرة؛ يراقب ViewModel/Widget Controller يستمع إلى Attribute changes وAbility events. هذا يمنع Widget من تعديل الصحة أو الـCooldown.

## 13. Save/Load

`UResonanceSaveGame` يحفظ:

- آخر Stage checkpoint.
- Bosses defeated.
- Elements unlocked.
- Abilities unlocked/equipped.
- Shrine upgrades.
- Optional collectibles.
- Version number وmigration data.

الـSave يتم:

- بعد هزيمة Boss.
- عند Shrine.
- عند الانتقال بين المراحل.
- لا نحفظ كل Frame.

عند التعددية:

- النسخة الفردية تحفظ محلياً.
- Session online لا تثق بالـSave المرسل من العميل؛ نحتاج خدمة/Authority لاحقاً.

## 14. Multiplayer readiness

### الآن

- كل Character وAbility وAttribute قابل للـReplication.
- نختبر Listen Server بعميلين في المرحلة 1.
- Server هو صاحب Health، Stagger، Core Shard، Boss phase، Reaction state.
- Client prediction مسموحة للحركة وتفعيل بعض القدرات، لكن النتيجة النهائية server-authoritative.

### لاحقاً

نعرّف interfaces لا ترتبط بمزود:

```cpp
class IResonanceSessionService
{
public:
    virtual void CreateSession() = 0;
    virtual void FindSessions() = 0;
    virtual void JoinSession(const FString& SessionId) = 0;
};
```

ثم نختار EOS أو Steam بعد اختبار المنصة المستهدفة. لا نضع نداءات `OnlineSubsystem` داخل Gameplay code.

قواعد RPC:

- `ServerTryActivateAbility`: يتحقق من Input/Target/Resource.
- `ServerTryAbsorb`: يتحقق من المسافة والنافذة.
- `NetMulticast` للـCosmetic فقط، لا لمنح الضرر أو المكافأة.
- `Client` RPC للـUI/feedback، لا للحقيقة القابلة للاستغلال.

## 15. Performance budgets

للـVertical Slice:

- 60 FPS target على جهاز المواصفات المستهدفة.
- أقل من 100 Actor قتالي فعال في الحلبة.
- Niagara يحوي scalability levels؛ لا نترك 12 Ultimate كلها تعمل بأقصى جودة.
- لا Tick لكل Ability إذا كان Timer/Event كافياً.
- لا Spawn متكرر لمقذوفات؛ نستخدم pooling فقط بعد قياس حقيقي.
- Telemetry مغلق في Shipping.

## 16. الاختبارات الآلية

### Unit/Automation

- Fire + Wind canonicalizes إلى Inferno مهما كان ترتيب التطبيق.
- Resistance 0.35 لا تنتج ضرراً سالباً أو صفراً غير مقصود.
- BossHP stage 1 = 6500 وstage 12 = 13650.
- Stagger يصل إلى AbsorbWindow مرة واحدة فقط.
- Core Shard لا يُمنح من Client.
- Mote لا يمكن امتصاصه مرتين.
- Reaction لا يتكرر عند وصول RepNotify نفسه.

### Functional PIE

- بدء Stage 1، قتل ثلاثة أتباع، استخدام Fire في الحاجز.
- دخول Boss Phase 2 عند threshold الصحيح.
- فشل Absorb يعيد 8% من Stagger فقط.
- Save ثم Load يعيد Core Shard وLoadout.
- Listen Server بعميلين: السيرفر يرى نفس Health/Phase، والعميل لا يفرض قيمة.

### Test naming

```text
ElementReaction.FireWind_IsCommutative
Damage.Resistance_AppliesAfterReaction
Absorb.BossOnlySucceedsDuringWindow
Progression.Stage12UsesExpectedBossHealth
Networking.ClientCannotGrantCoreShard
```

## 17. Git وCI

- `main`: آخر نسخة قابلة للتشغيل.
- `develop`: تجميع ميزات بعد مراجعة.
- `feat/stage-01-cinder`، `feat/gas-damage-pipeline`، `test/reaction-specs`.
- كل Feature يرفق: GDD note، diff، test result، فيديو/لقطة إن كانت بصرية.
- لا نرفع `.env` أو مفاتيح Unreal/Steam أو ملفات تجارية غير مرخصة.
- Git LFS للأصول الثنائية، مع `.gitattributes` مناسب لـ`.uasset`/`.umap` بعد إنشاء المستودع.

## 18. ترتيب البناء الصحيح

```text
1. إنشاء .uproject وSource module
2. Enhanced Input + حركة البطل
3. Health/Stamina/Resonance AttributeSet
4. Basic melee + Damage Execution
5. Fire Ability + Fire Mote + Absorb
6. Enemy partial fire abilities
7. Boss Ignar phases + Arena
8. Stage 1 environment interaction
9. Save/Load
10. Automation tests + Debug HUD
11. Listen Server test
12. فقط بعد نجاح ذلك: Water + Stage 2
```

لا نبدأ بكتابة 48 Ability أو بناء 12 مرحلة قبل أن تصبح الحلقة الأولى قابلة للعب والاختبار.

## 19. Definition of Done للكود

- الكود يترجم في Development Editor/Client/Server.
- يوجد اختبار أحمر قبل السلوك الجديد ثم أخضر بعده.
- لا توجد صحة/ضرر تعدلهما Blueprint على العميل.
- القيم القابلة للتوازن في Data Assets، لا Magic Numbers داخل Ability.
- PIE single-player وListen Server يعملان للميزة.
- لا تسرب Timer/Delegate/GameplayTag بعد انتهاء Ability.
- Debug telemetry يثبت ما حدث بدلاً من الاعتماد على قول الوكيل.

## 20. مصادر Epic التي تم التحقق من وصولها

- Gameplay Ability System: `https://dev.epicgames.com/documentation/en-us/unreal-engine/gameplay-ability-system-for-unreal-engine`
- Networking and Multiplayer: `https://dev.epicgames.com/documentation/en-us/unreal-engine/networking-and-multiplayer`
- Enhanced Input: `https://dev.epicgames.com/documentation/en-us/unreal-engine/enhanced-input`
- Unreal Engine 5.8 Release Notes: `https://dev.epicgames.com/documentation/en-us/unreal-engine/unreal-engine-5.8-release-notes`

هذه الروابط مرجع التنفيذ. إذا اختلفت واجهة API الدقيقة في build معيّن من 5.8، نثبتها من headers/Editor المثبتين قبل كتابة الكود النهائي.
