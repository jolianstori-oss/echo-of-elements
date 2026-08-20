---
title: "Echo of Elements — تنفيذ واختبارات"
version: "0.1"
status: "Backlog أولي قابل للتنفيذ"
---

# خطة التنفيذ والاختبارات

## 0. الهدف

نحوّل التصميم إلى لعبة قابلة للعب عبر **Vertical Slice للمرحلة الأولى**، ثم نكرر القالب للمراحل 2–12. لا نعتبر كتابة مستند أو Stub إنجازاً؛ الإنجاز يعني تشغيل اللعبة واختبار السلوك داخل Unreal.

## 1. بوابات القرار

### Gate A — قبل إنشاء المحتوى

لا نحتاج كل الأصول الفنية بعد. يجب تثبيت:

- منظور Third-person.
- اسم المشروع المؤقت.
- Input scheme.
- أرقام Baseline من Game Design Bible.
- Target hardware والمنصة الأولى.
- License policy للأصوات والموديلات.

### Gate B — Vertical Slice

لا ننتج المرحلة الثانية قبل أن ينجح Stage 1 في:

- حركة ممتعة.
- قتال واضح.
- Fire + Absorb + Stagger.
- زعيم من 3 مراحل.
- Save/Load.
- Automation tests.
- Listen Server smoke test.

### Gate C — Production

بعد موافقة اللعب على Stage 1، نكرر القالب مع Water ثم ننتج بقية المراحل على دفعات: 3–4، 5–8، 9–12.

## 2. Milestone 0 — تأسيس المشروع

### M0-T01 — إنشاء Unreal project

**المطلوب:** مشروع C++ Third-person باسم مؤقت `EchoOfElements` في مستودع Git.

**قبول:**

- `.uproject` يفتح في UE 5.8.
- Target Editor/Client/Server يترجم في Development.
- مجلدات `Config/Source/Content` موجودة.
- أول commit لا يحتوي أسراراً أو أصولاً غير مرخصة.

### M0-T02 — تفعيل Plugins والـTags

**المطلوب:** GAS، GameplayTags، GameplayTasks، EnhancedInput، Niagara، AI، Navigation.

**قبول:**

- Editor يفتح بلا Plugin errors.
- Tags الاثنا عشر تظهر في Project Settings/Data Asset.
- Automation smoke test يعمل.

### M0-T03 — CI baseline

**المطلوب:** build/check على Windows target أو بيئة build مناسبة للمشروع؛ لا نفترض أن Linux Hermes يقدر يبني Unreal Editor.

**قبول:**

- أمر build موثق.
- log محفوظ.
- فشل build يعطي exit code غير صفري.

## 3. Milestone 1 — البطل والحركة

### M1-T01 — Character movement

**المطلوب:** Move, Look, Jump, Dodge، كاميرا Third-person.

**اختبار أحمر أولاً:** اختبار Functional يطلب من البطل الانتقال 500 وحدة خلال زمن محدد دون أن يصبح محشوراً.

**قبول:**

- الحركة لا تتوقف بعد إعادة فتح المستوى.
- Dodge يملك Invulnerability window موثقة.
- لا يوجد Input logic داخل Widget.
- يعمل Keyboard/Controller حسب المنصة الأولى.

### M1-T02 — AttributeSet

**المطلوب:** Health, MaxHealth, Stamina, Resonance, Stagger, AttackPower, Defense.

**اختبارات:**

- Health لا تتجاوز MaxHealth إلا عبر Effect معلن.
- Resonance لا تصبح سالبة.
- Stamina regeneration لا تعمل أثناء حالة StaminaLocked.
- كل Attribute المطلوب للـUI Replicated.

### M1-T03 — Basic melee

**المطلوب:** Light/Heavy attack مع TracePolicy وHitPolicy.

**قبول:**

- العدو يتلقى ضربة واحدة لكل نافذة Hit.
- الضرر يمر عبر GAS، لا `ApplyDamage` عشوائي من Montage.
- Debug HUD يعرض Raw/Final/Stagger.
- إعادة تشغيل الهجمة لا تترك Delegate أو Timer.

## 4. Milestone 2 — Fire vertical slice

### M2-T01 — Fire Data Assets

أنشئ:

- `DA_Element_Fire`
- `DA_Ability_Fire_EmberBolt`
- `DA_Ability_Fire_CinderStep`
- `DA_Ability_Fire_AshRing`
- `DA_Ability_Fire_InfernoCore`
- Effects: Burning، FireDamage، FireBuildup

**قبول:** تغيير BaseDamage في Data Asset ينعكس في اللعبة بلا تعديل C++.

### M2-T02 — Fire Mote وAbsorb

**اختبار RED:** حاول امتصاص Mote مرتين في Automation/PIE؛ يجب أن يفشل الطلب الثاني.

**قبول:**

- العدو يترك Mote من السيرفر.
- Perfect Absorb يفرق بصرياً وميكانيكياً.
- الـMote لا يعطي Core Shard.
- الـMote يُزال من العالم مرة واحدة.

### M2-T03 — أتباع المرحلة الأولى

الأعداء:

- Emberling: projectile ضعيف.
- Ash Guard: melee وحرق قصير.
- Cinder Caster: منطقة نار مع Telegraph.

**قبول:** كل عدو يعرض جزءاً من حركة Ignar، لكن لا ينسخ Boss logic بالكامل.

### M2-T04 — البيئة

**المطلوب:** حاجز قابل للحرق، منصة آمنة من الحمم، Shrine، checkpoint.

**قبول:**

- Fire يغيّر حالة البيئة مرة واحدة بطريقة server-authoritative.
- إعادة Load لا تعيد الحاجز إلى حالة غير منطقية.
- تعطيل VFX لا يعطل المنطق.

## 5. Milestone 3 — Boss Ignar

### M3-T01 — Boss state

الحالات:

```text
Intro → Phase01 → Phase02 → Phase03 → Staggered → AbsorbWindow → Defeated
```

**اختبار RED:** خفّض Boss Health إلى threshold؛ يجب أن ينتقل Phase مرة واحدة فقط.

### M3-T02 — هجمات Ignar

- Ember Cleave: ضربة أمامية.
- Delayed Eruption: دوائر أرضية.
- Ash Spear: مقذوف.
- Cinder Rain: Phase 2.
- Broken Crown: Phase 3.

**قبول:**

- كل هجمة لها Telegraph ومدى زمني مسجل.
- لا يحدث Damage أثناء الـwind-up.
- Safe Zone واضحة في Ultimate.
- Stagger يفتح AbsorbWindow خمس ثوانٍ.

### M3-T03 — امتصاص قلب الزعيم

**قبول:**

- Core Shard يمنح Fire مرة واحدة.
- عند الفوز، يُحفظ التقدم.
- عند إعادة Load، Fire موجودة ولا يعاد Boss.
- العميل لا يستطيع استدعاء Core Shard عبر RPC.

## 6. Milestone 4 — تفاعل Fire + Wind

حتى قبل بناء Wind كاملاً، نستخدم Test Element/Stub data فقط لاختبار النظام؛ لا نعتبر الـStub محتوى إنتاجياً.

**اختبارات:**

- Fire + Wind وWind + Fire نفس Reaction ID.
- Reaction لا يتكرر من نفس Hit.
- Inferno يطبق Damage/Duration/Stagger حسب Data Asset.
- Target المقاومة لا تصبح أقل من 0 أو أعلى من 1 بلا Clamp.
- إزالة VFX لا تمنع Reaction event.

## 7. Milestone 5 — Listen Server

### Smoke test

1. شغّل Listen Server.
2. وصل Client ثانٍ.
3. اللاعب 1 يضرب Emberling.
4. السيرفر واللاعبان يرون Health متقارباً بعد Replication.
5. اللاعب 2 يحاول إرسال طلب امتصاص من مسافة بعيدة.
6. السيرفر يرفضه.
7. اللاعبان يهزمان Boss في نسخة الاختبار.

**قبول:**

- لا Client يقرر Boss phase أو Core Shard.
- لا تكرار للموتة أو الـMote بسبب Replication.
- Reconnect policy موثقة؛ لا ندّعي دعمها قبل اختبارها.

## 8. Milestone 6 — Stage 2 Water

بعد نجاح Fire slice، نكرر القالب:

- Water Data Assets.
- Tide Adept/Bubble Eel/Pressure Knight.
- تغير مستوى الماء.
- Nymara بثلاث مراحل.
- Steam Burst وWater+Lightning data reaction.

**قاعدة:** لا ننسخ Fire Blueprint ثم نغيّر اللون فقط؛ نعيد استخدام C++ pipeline مع Data Assets وmechanics مختلفة.

## 9. Production batches للمراحل 3–12

### Batch A — Stages 3–4

Earth وStone؛ التركيز على الحفر، تغيير أرضية الحلبة، وكسر Armor.

### Batch B — Stages 5–8

Wind، Lightning، Ice، Nature؛ التركيز على الحركة الجوية، الشبكات، الـBuildup، ومناطق الشفاء.

### Batch C — Stages 9–12

Sand، Metal، Light، Gravity؛ التركيز على الـMirage، المغناطيسية، خطوط النظر، وتبديل الاتجاه.

لكل مرحلة Ticket مستقل:

```text
StageXX-Design
StageXX-Environment
StageXX-Enemies
StageXX-Boss
StageXX-Reactions
StageXX-Save
StageXX-QA
```

## 10. Test-first contract

لكل Feature جديدة:

```text
RED  → اكتب Automation/Functional test يفشل بسبب غياب السلوك
GREEN → أقل كود/Blueprint يجعل الاختبار ينجح
REFACTOR → نظف دون تغيير السلوك
VERIFY → PIE + Listen Server + log/telemetry
```

لا نكتب 48 Ability كاملة ثم نكتشف أن Damage pipeline خاطئ. نبني tracer bullet واحداً من Input إلى Damage إلى UI إلى Save.

## 11. Debug HUD في النسخة التطويرية

يعرض عند الضغط على مفتاح debug:

- Source Actor / Target Actor.
- Ability name.
- Source element / target statuses.
- Raw Damage / Resistance / Final Damage.
- Stagger before/after.
- Reaction ID.
- Authority role: Server/Client.
- Boss Phase وAbsorbWindow timer.

في Shipping: مغلق بالكامل أو خلف compile flag.

## 12. Playtest protocol

بعد كل Feature كبيرة:

1. لاعب من الفريق يعرف اللعبة.
2. لاعب جديد لا يعرفها.
3. تسجيل 20–30 دقيقة.
4. تسجيل لحظة الفشل، لا مجرد الانطباع النهائي.
5. قياس:
   - وقت الوصول لأول Ability.
   - عدد الضربات غير المفهومة.
   - زمن الزعيم.
   - عدد مرات استخدام Reaction.
   - موضع أول شعور بالتكرار.
6. تعديل رقم واحد أو قاعدة واحدة في كل دورة، ثم إعادة الاختبار.

## 13. Definition of Done عام

Feature لا تُغلق إلا إذا:

- لها Design Note.
- يوجد test فشل قبل التنفيذ ثم نجح بعده.
- تعمل في PIE.
- لا توجد أخطاء/تحذيرات جديدة في log مرتبطة بها.
- الأرقام في Data Asset.
- لا يوجد اعتماد على Asset غير مرخص.
- سلوك Authority/Client مكتوب.
- يمكن لشخص آخر إعادة تشغيل الاختبار.
- يوجد رابط/اسم commit أو مسار ملف عند التنفيذ الفعلي.

## 14. أول قائمة ملفات فعلية بعد توفير Unreal project

```text
Source/EchoOfElements/EchoOfElements.Build.cs
Source/EchoOfElements/AbilitySystem/ResonanceAttributeSet.h/.cpp
Source/EchoOfElements/AbilitySystem/ResonanceDamageExecution.h/.cpp
Source/EchoOfElements/Elements/ElementReactionSubsystem.h/.cpp
Source/EchoOfElements/Combat/AbsorbComponent.h/.cpp
Source/EchoOfElements/Stages/StageDirector.h/.cpp
Source/EchoOfElementsTests/ElementReactionSpec.cpp
Source/EchoOfElementsTests/DamageCalculationSpec.cpp
Content/Data/Elements/DA_Element_Fire.uasset
Content/Data/Bosses/DA_Boss_Ignar.uasset
Content/Levels/L_Stage01_Cinder.umap
```

هذه القائمة هي نقطة بدء البرمجة الحقيقية، وليست دليلاً على أن الملفات موجودة حالياً.

## 15. الكود الذي أصبح جاهزاً للنسخ

- `Combat/WeakPointComponent.h/.cpp`
- `AI/WeakPointHunterComponent.h/.cpp`
- `AI/WeakPointHunterAIController.h/.cpp`
- `AbilitySystem/NibrasPinpointAbility.h/.cpp`
- `Combat/VenomStatusComponent.h/.cpp`
- `AbilitySystem/VenomDartAbility.h/.cpp`
- `Elements/ElementReactionLibrary.h/.cpp`
- `Characters/ResonanceCharacterData.h`
- `Config/DefaultGameplayTags.ini`
- `Tools/resonance_core_test.cpp`

هذه الأجزاء مجرّبة باختبار C++ مستقل للمعادلات والتفاعلات، لكن Build Unreal نفسه ينتظر وجود `.uproject` وUnreal Engine 5.8 على جهاز التنفيذ.