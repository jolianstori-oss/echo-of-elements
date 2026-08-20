# C++ Drop-in Pack — Echo of Elements

## الملفات

```text
EchoOfElements.uproject.template
Source/EchoOfElements/
├── EchoOfElements.Build.cs
├── EchoOfElements.cpp
├── Characters/ResonanceCharacterData.h
├── Combat/WeakPointComponent.h/.cpp
├── Combat/VenomStatusComponent.h/.cpp
├── AI/WeakPointHunterComponent.h/.cpp
├── AI/WeakPointHunterAIController.h/.cpp
├── AbilitySystem/NibrasPinpointAbility.h/.cpp
├── AbilitySystem/VenomDartAbility.h/.cpp
└── Elements/ElementReactionLibrary.h/.cpp

Source/EchoOfElementsTests/
├── EchoOfElementsTests.Build.cs
├── EchoOfElementsTests.cpp
└── ResonanceReactionSpec.cpp

Config/DefaultGameplayTags.ini
Tools/resonance_core_test.cpp
```

## ما الذي ينفذه الكود فعلاً؟

- تعريف Data Asset للشخصيات والأدوار والعناصر.
- Weak Points قابلة للفتح والكسر والـReplication.
- اختيار نِبراس لأفضل نقطة ضعف مرئية مع حساب المسافة والضرر والـStagger.
- إعادة تموضع نِبراس حول نقطة الضعف، ثم إرسال Opportunity إلى Gameplay Ability.
- Venom stacks capped مع Pulse event server-authoritative.
- Fire/Wind وغيرها من Element Reactions مع damage/stagger multipliers.
- Damage formula متوافقة مع Balance Sheet.
- Automation tests أولية لـReaction وDamage.

## ما الذي لا يمكن للكود أن يصنعه وحده؟

- Animations/Montages وBlueprint Graph الذي يربط الحركة بالقدرة.
- Gameplay Effect assets النهائية وAttributes الخاصة بمشروعك.
- موديلات، Skeletons، VFX، SFX، `.uasset`، `.umap`، وNavMesh.
- متجر Steam أو Steam AppID.

هذه أصول وتأليف داخل Unreal، وليست أسطر C++ فقط.

## خطوات وضعه في Unreal Engine 5.8

1. انسخ `EchoOfElements.uproject.template` إلى مشروع جديد باسم `EchoOfElements.uproject`، أو أنشئ مشروع C++ باسم `EchoOfElements` واستعمله كمرجع.
2. انسخ مجلد `Source/EchoOfElements` إلى `Project/Source/EchoOfElements`.
3. انسخ `Source/EchoOfElementsTests` إلى `Project/Source/EchoOfElementsTests` أو ضم الاختبارات إلى Module اختبار موجود.
4. انسخ `Config/DefaultGameplayTags.ini` إلى `Project/Config`.
5. فعّل Plugins: GameplayAbilities، GameplayTags، GameplayTasks، EnhancedInput، AIModule، NavigationSystem، Niagara، UMG.
6. Generate project files ثم Build `Development Editor`.
7. أنشئ Blueprint مشتقاً من Character لنِبراس، وأضف:
   - `UWeakPointHunterComponent`
   - `UAbilitySystemComponent`
   - Mesh فيه sockets مثل `Head`, `Core`, `LeftJoint`, `RightJoint`.
8. عيّن `AWeakPointHunterAIController` في Pawn/AI settings.
9. في Boss Blueprint أضف `UWeakPointComponent` وعرّف Definitions للـSockets.
10. في `EchoOfElements.uproject` أضف Module باسم `EchoOfElementsTests` من النوع `Developer` إذا أردت تشغيل Automation tests كوحدة مستقلة.
11. أنشئ/ولّد ملفات المشروع ثم Build `Development Editor`.
12. اربط `OnWeakPointAttackOpportunity` بقدرة `GA_Nibras_PinpointShot` بعد أن تتحقق القدرة من cooldown/range/authority.
13. اربط `OnVenomPulse` بـGameplay Effect يطبق `Damage.Venom` على السيرفر فقط.
14. شغّل Automation tests قبل أول Playtest.

## ملاحظة عن الـWeak Point

`UWeakPointComponent` لا يطبق الضرر. هذا مقصود حتى لا يصبح عندنا نظامان للصحة:

```text
Hit Trace
  → WeakPointComponent يقرر multiplier
  → GAS Damage Effect يحسب Health/Stagger
  → Niagara/SFX يعرضان النتيجة
```

إذا أصيب Socket غير مكشوف يعود multiplier إلى `1.0`، وإذا كان مكشوفاً يعود إلى قيمة الـDefinition، مثل `2.2` لنِبراس.

## ملاحظة عن نِبراس

لا تجعل AI يطلق الهجمة من `Think()` مباشرة. الـController يقرر أن هناك فرصة فقط؛ الـGameplay Ability هي التي تتحقق من:

- Authority.
- المسافة.
- الهدف ما زال صالحاً.
- Cooldown.
- Resonance/Stamina.
- عدم وجود Stun أو Death.

بهذا لا يستطيع Client أو Timer قديم منح ضربة مجانية.

## اختبار سريع خارج Unreal

على Linux أو أي جهاز فيه `g++`:

```bash
g++ -std=c++17 -O2 Tools/resonance_core_test.cpp -o /tmp/resonance_core_test
/tmp/resonance_core_test
```

الناتج المتوقع:

```text
resonance_core_test: PASS
```

هذا يختبر المعادلات والتفاعلات فقط. الاختبار الحقيقي لـWeakPointComponent وGAS يحتاج Unreal Editor/Build Tool ومشروعاً فعلياً.
