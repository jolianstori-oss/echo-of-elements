---
title: "Echo of Elements — Balance Sheet"
version: "0.1"
status: "أرقام Baseline للـPrototype وليست توازناً نهائياً"
---

# Balance Sheet — الضرر، الصحة، الحركة، والبيئة

## 1. قواعد قراءة الأرقام

- كل الأرقام **قبل المقاومة والدروع** تسمى `Raw`.
- هجمات الزعماء تتدرج حسب المرحلة:

```text
BossMoveRaw(s) = MoveBase × (1 + 0.08 × (s - 1))
```

- ضرر الأتباع يتدرج حسب المرحلة:

```text
EnemyMoveRaw(s) = EnemyBase × (1 + 0.08 × (s - 1))
```

- `FinalDamage = Raw × ResistanceMultiplier × 100 / (100 + Armor)`.
- اللاعب يبدأ بـ1000 Health ويصل إلى 1825 في المرحلة 12.
- لا نعدّل الأرقام عشوائياً أثناء التنفيذ؛ كل تعديل يسجل في Changelog مع سبب ونتيجة Playtest.

## 2. حركات البطل الأساسية

| الحركة | Raw Damage | Stagger | التكلفة | ملاحظات |
|---|---:|---:|---:|---|
| Light Combo hit 1 | 35 | 8 | 0 | سريع، لا يوقف Heavy |
| Light Combo hit 2 | 40 | 10 | 0 | يربط بالضربة الثالثة |
| Light Combo hit 3 | 50 | 14 | 0 | يفتح Finish window |
| Light Combo finisher | 75 | 25 | 0 | Knockback خفيف |
| Heavy attack | 110 | 35 | 15 Stamina | بطيء، يكسر Guard ضعيف |
| Air attack | 45 | 12 | 5 Stamina | لا يثبت الزعيم |
| Charged heavy | 180 | 55 | 30 Stamina | خطر أثناء الشحن |
| Perfect Parry counter | 140 | 70 | 20 Stamina | فقط بعد صد صحيح |
| Perfect Absorb burst | 80 | 45 | 0 | يحصل مرة عند نافذة مثالية |
| Dodge / Jump / Interact | 0 | 0 | 0 | حركة لا ضرر |

## 3. قدرات العناصر الـ48

القيم الكاملة للقدرات موجودة في الـGame Design Bible. هذا جدول تشغيل مختصر يثبت نوع الضرر والـStagger:

| العنصر | Basic (Damage/Stagger/Cost) | Mobility (Damage/Stagger/Cost) | Control/Defense (Damage/Stagger/Cost) | Ultimate (Damage/Stagger/Cost) |
|---|---|---|---|---|
| Fire | 90 / 18 / 20 | 0 / 0 / 15؛ أثر 40/ث | 160 / 35 / 35؛ Burning | 520 / 100 / 80 |
| Water | 100 / 20 / 20 | 40 / 8 / 20 | 120 / 30 / 40؛ حاجز | 480 / 90 / 75 |
| Earth | 110 / 25 / 20 | 80 / 20 / 25 | 0 / 0 / 35؛ تخفيف | 500 / 110 / 80 |
| Stone | 130 / 30 / 25 | 100 / 25 / 30 | 0 / 0 / 40؛ حاجز 300 | 600 / 130 / 95 |
| Wind | 95 / 15 / 18 | 60 / 15 / 15 | 180 / 30 / 40؛ سحب | 450 / 85 / 70 |
| Lightning | 125 / 22 / 25 | 70 / 15 / 20 | 160 + chain / 35 / 45 | 550 / 120 / 85 |
| Ice | 105 / 22 / 20 | 30 / 8 / 15 | 100 / 28 / 35؛ Freeze buildup | 520 / 115 / 80 |
| Nature | 90 / 18 / 18 | 70 / 16 / 20 | 0 / 0 / 35؛ Heal 140 | 500 / 100 / 75 |
| Sand | 100 / 17 / 18 | 50 / 12 / 15 | 0 / 0 / 35؛ Mirage | 480 / 90 / 70 |
| Metal | 140 / 28 / 30 | 100 / 22 / 25 | 0 / 0 / 40؛ حاجز 400 | 620 / 140 / 90 |
| Light | 120 / 22 / 25 | 80 / 18 / 20 | 140 / 32 / 40 | 580 / 125 / 85 |
| Gravity | 110 / 25 / 25 | 100 / 25 / 25 | 180 / 35 / 45؛ إبطاء | 650 / 150 / 100 |

`Mobility` قد تكون ضررها صفر إذا كانت حركة بحتة. القيمة غير الصفرية هي فقط عند اصطدام الحركة بالهدف.

## 4. الأتباع والـElite

### 4.1 قوالب الصحة والضرر

| الفئة | HP Base | MoveBase | Stagger | Tier |
|---|---:|---:|---:|---:|
| Light minion | 250 | 45 | 100 | 1.0 |
| Ranged/Caster | 300 | 55 | 80 | 1.2 |
| Heavy | 425 | 70 | 160 | 1.7 |
| Shield/Armor | 500 | 65 | 220 | 2.0 |
| Elite | 1400 | 105 | 350 | — |
| Mini-boss | 3000 | 145 | 600 | — |

**مثال:** Heavy في المرحلة 8 يملك `425 × 1.77 × 1.7` HP قبل أي Modifier خاص. هذه الأرقام تمنع جعل كل عدو نسخة من الآخر، لكنها تحتاج Profiling وPlaytest.

### 4.2 أتباع المراحل

| المرحلة | Light | Ranged/Caster | Heavy/Shield | الحركة التي يتعلمها اللاعب |
|---:|---|---|---|---|
| 1 | Emberling: 45 projectile | Cinder Caster: 55 fire zone | Ash Guard: 70 cleave | Telegraph النار |
| 2 | Bubble Eel: 45 dash | Tide Adept: 55 jet | Pressure Knight: 70 push | اتجاه الموجة |
| 3 | Mudling: 45 burrow | Quake Caller: 55 pillar | Earth Brute: 70 slam | الأرض غير الآمنة |
| 4 | Pebble Scout: 45 shot | Boulder Thrower: 55 rock | Shield Golem: 70 guard | كسر Armor |
| 5 | Updraft Wisp: 45 gust | Feather Blade: 55 air slash | Gale Hunter: 70 dive | مراقبة السماء |
| 6 | Spark Rat: 45 arc | Arc Monk: 55 chain | Coil Sentinel: 70 grid | عدم الوقوف على الشبكة |
| 7 | Frostling: 45 shard | Ice Archer: 55 freeze | Crystal Bear: 70 charge | Buildup الجليد |
| 8 | Thornling: 45 thorn | Bloom Priest: 55 heal zone | Vine Stalker: 70 root | قطع الشفاء |
| 9 | Sand Skirmisher: 45 needle | Mirage Twin: 55 fake shot | Sand Burrower: 70 ambush | تمييز الحقيقي |
| 10 | Magnet Drone: 45 bolt | Rail Cannon: 55 rail | Iron Guard: 70 crush | التعامل مع المرساة |
| 11 | Prism Adept: 45 ray | Lens Wraith: 55 beam | Halo Knight: 70 blade | زاوية الضوء |
| 12 | Gravity Husk: 45 orb | Echo Caster: 55 pull | Vector Brute: 70 crush | اتجاه الجاذبية |

كل قيمة بعد النقطتين هي `MoveBase` قبل معامل المرحلة. الـCaster لا يملك Damage مستمراً بلا نهاية؛ كل منطقة تنتهي بعد 3 ثوانٍ كحد أقصى.

## 5. الزعماء — كل الهجمات الأساسية

`Telegraph` هو الزمن بين إشارة الهجمة وبدء الضرر. `Phase` يحدد أول ظهور لها.

### 5.1 إغنار — Fire — المرحلة 1

| الحركة | Base Damage | Stagger | Telegraph | Phase |
|---|---:|---:|---:|---:|
| Cinder Cleave | 95 | 30 | 0.55 ث | 1 |
| Flame Arc | 85 | 20 | 0.75 ث | 1 |
| Delayed Eruption | 150 | 45 | 1.1 ث | 1 |
| Cinder Rain | 210 | 60 | 1.5 ث | 2 |
| Broken Crown | 260 | 85 | 1.8 ث | 3 |

### 5.2 نيمارا — Water — المرحلة 2

| الحركة | Base Damage | Stagger | Telegraph | Phase |
|---|---:|---:|---:|---:|
| Wave Lash | 90 | 25 | 0.6 ث | 1 |
| Water Spear | 80 | 18 | 0.8 ث | 1 |
| Whirlpool | 145 | 40 | 1.0 ث | 1 |
| Rising Tide | 180 | 50 | 1.4 ث | 2 |
| Tidal Collapse | 245 | 80 | 1.8 ث | 3 |

### 5.3 داهر — Earth — المرحلة 3

| الحركة | Base Damage | Stagger | Telegraph | Phase |
|---|---:|---:|---:|---:|
| Quake Fist | 100 | 32 | 0.6 ث | 1 |
| Burrow Ambush | 90 | 25 | 0.9 ث | 1 |
| Pillar Burst | 150 | 45 | 1.1 ث | 1 |
| Faultline | 190 | 60 | 1.5 ث | 2 |
| Earthheart | 250 | 85 | 1.9 ث | 3 |

### 5.4 خاروس — Stone — المرحلة 4

| الحركة | Base Damage | Stagger | Telegraph | Phase |
|---|---:|---:|---:|---:|
| Stone Hammer | 110 | 35 | 0.7 ث | 1 |
| Boulder Roll | 95 | 25 | 0.9 ث | 1 |
| Armor Pulse | 135 | 20 | 1.0 ث | 1 |
| Mountain Fall | 200 | 65 | 1.5 ث | 2 |
| Cataclysm | 270 | 90 | 2.0 ث | 3 |

### 5.5 زيفرا — Wind — المرحلة 5

| الحركة | Base Damage | Stagger | Telegraph | Phase |
|---|---:|---:|---:|---:|
| Gale Claw | 85 | 25 | 0.5 ث | 1 |
| Wind Blades | 80 | 18 | 0.7 ث | 1 |
| Updraft Drop | 140 | 45 | 1.0 ث | 1 |
| Cyclone Ring | 185 | 55 | 1.4 ث | 2 |
| Sky Hunt | 250 | 80 | 1.8 ث | 3 |

### 5.6 فولتارا — Lightning — المرحلة 6

| الحركة | Base Damage | Stagger | Telegraph | Phase |
|---|---:|---:|---:|---:|
| Arc Lash | 90 | 25 | 0.55 ث | 1 |
| Chain Bolt | 85 | 20 | 0.8 ث | 1 |
| Ground Grid | 150 | 40 | 1.0 ث | 1 |
| Storm Cage | 195 | 60 | 1.4 ث | 2 |
| Tempest Crown | 255 | 85 | 1.9 ث | 3 |

### 5.7 إسكرِل — Ice — المرحلة 7

| الحركة | Base Damage | Stagger | Telegraph | Phase |
|---|---:|---:|---:|---:|
| Frost Scythe | 90 | 28 | 0.6 ث | 1 |
| Ice Lance | 80 | 18 | 0.8 ث | 1 |
| Frozen Floor | 125 | 35 | 1.0 ث | 1 |
| Crystal Prison | 180 | 60 | 1.5 ث | 2 |
| Absolute Winter | 245 | 85 | 1.9 ث | 3 |

### 5.8 فيرِليا — Nature — المرحلة 8

| الحركة | Base Damage | Stagger | Telegraph | Phase |
|---|---:|---:|---:|---:|
| Thorn Swipe | 95 | 28 | 0.6 ث | 1 |
| Seed Burst | 80 | 18 | 0.8 ث | 1 |
| Root Snare | 135 | 42 | 1.0 ث | 1 |
| Spore Rain | 160 | 50 | 1.4 ث | 2 |
| Worldroot | 235 | 80 | 1.9 ث | 3 |

### 5.9 سَحراق — Sand — المرحلة 9

| الحركة | Base Damage | Stagger | Telegraph | Phase |
|---|---:|---:|---:|---:|
| Sand Slash | 85 | 24 | 0.55 ث | 1 |
| Mirage Shot | 75 | 16 | 0.8 ث | 1 |
| Quicksand | 100 | 30 | 1.0 ث | 1 |
| Dune Wave | 170 | 55 | 1.4 ث | 2 |
| Desert Eye | 230 | 80 | 1.8 ث | 3 |

### 5.10 فيرّون — Metal — المرحلة 10

| الحركة | Base Damage | Stagger | Telegraph | Phase |
|---|---:|---:|---:|---:|
| Iron Fist | 105 | 32 | 0.65 ث | 1 |
| Rail Shot | 90 | 20 | 0.85 ث | 1 |
| Magnet Crush | 150 | 45 | 1.0 ث | 1 |
| Iron Rain | 205 | 65 | 1.5 ث | 2 |
| Core Overload | 275 | 90 | 2.0 ث | 3 |

### 5.11 لوميرا — Light — المرحلة 11

| الحركة | Base Damage | Stagger | Telegraph | Phase |
|---|---:|---:|---:|---:|
| Prism Blade | 95 | 28 | 0.55 ث | 1 |
| Ray Line | 85 | 18 | 0.8 ث | 1 |
| Mirror Burst | 145 | 42 | 1.0 ث | 1 |
| Halo Cage | 190 | 60 | 1.5 ث | 2 |
| Zenith Fall | 260 | 85 | 1.9 ث | 3 |

### 5.12 غرافيِم — Gravity — المرحلة 12

| الحركة | Base Damage | Stagger | Telegraph | Phase |
|---|---:|---:|---:|---:|
| Gravity Fist | 115 | 35 | 0.65 ث | 1 |
| Orb Pull | 90 | 22 | 0.85 ث | 1 |
| Vector Crush | 160 | 50 | 1.1 ث | 1 |
| Singularity Field | 220 | 70 | 1.6 ث | 2 |
| Falling World | 300 | 100 | 2.0 ث | 3 |

## 6. البيئة والـHazards

ضرر البيئة لا يأتي بلا تحذير؛ كل Hazard يملك VFX وصوتاً و`Telegraph`.

| المرحلة | Hazard | DamageBase | تكرار/مدة | حل اللاعب |
|---:|---|---:|---|---|
| 1 | Lava edge | 60 | كل 1 ث أثناء الوقوف | Fire/مسار آمن |
| 2 | Drowning pocket | 45 | كل 1 ث بعد 3 ث سماح | Water/خروج سريع |
| 3 | Quake crack | 100 | نبضة واحدة بعد 1.2 ث | قفز/شق أرض |
| 4 | Falling stone | 120 | ضربة منطقة بعد 1.5 ث | ظل يوضح Safe Zone |
| 5 | Void fall | 100% Health | سقوط؛ لا Damage عادي | Wind/منصة/Respawn |
| 6 | Electric floor | 70 | كل 0.75 ث؛ max 3 ticks | قطع الموصل |
| 7 | Freeze field | 35 + Buildup 25 | كل 1 ث | Fire/تغيير المسار |
| 8 | Thorn growth | 55 | 2 ticks بعد إنذار | Fire/قطع الجذر |
| 9 | Quicksand | 30 | كل 1 ث + إبطاء | Water/Wind/قفزة |
| 10 | Magnetic rail | 90 | ضربة خطية بعد 1.0 ث | Metal/تغيير المرساة |
| 11 | Prism beam | 130 | ضربة خطية بعد 1.3 ث | Light/زاوية مرآة |
| 12 | Gravity crush | 160 | نبضة بعد 1.5 ث | Gravity/تثبيت الاتجاه |

`Void fall` ليس ضرراً عادياً؛ يعيد اللاعب إلى آخر Safe Zone مع عقوبة زمنية، حتى لا يصبح السقوط ضربة غير عادلة.

## 7. التفاعلات: أرقام Baseline

| Reaction | DamageMultiplier | StaggerMultiplier | المدة | الأثر |
|---|---:|---:|---:|---|
| Inferno | 1.25 | 1.15 | 4 ث | منطقة نار + Burning |
| Steam Burst | 1.15 | 1.35 | 2 ث | Blind + نافذة هجوم |
| Magma | 1.20 | 1.20 | 4 ث | أرض حارة |
| Thermal Shock | 1.10 | 1.50 | فوري | كسر Armor |
| Conductive | 1.20 | 1.25 | 3 ث | قفزة إلى 3 أهداف |
| Permafrost | 1.10 | 1.30 | 1.5 ث | Freeze عند Buildup 100 |
| Quicksand | 1.05 | 1.10 | 3 ث | إبطاء/سحب |
| Duststorm | 1.05 | 1.15 | 3 ث | حجب جزئي |
| Resonant Shatter | 1.25 | 1.40 | فوري | كسر Armor |
| Scorched Bloom | 1.20 | 1.25 | 4 ث | يلغي Heal |
| Overload | 1.30 | 1.20 | 2 ث | تفريغ مؤجل |
| Lens Collapse | 1.35 | 1.30 | فوري | اختراق دفاع |
| Compression | 1.05 | 1.10 | 1 ث | جذب؛ لا تكديس غير محدود |

## 8. معايير التوازن

- Boss DPS النظري لا يتجاوز 22% من MaxHealth للاعب في هجمة Ultimate واحدة بعد المقاومة العادية.
- يجب أن تنجو المراوغة الناجحة من كل منطقة Telegraph إذا كان توقيتها صحيحاً.
- لا نرفع BossHP لتعويض عدم وضوح الهجمة.
- إذا كانت نسبة موت اللاعبين الجدد من Hazard وحده أعلى من 25% في أول اختبارين، نرفع وضوح الإنذار قبل تخفيض الضرر.
- إذا لم يستخدم اللاعب Reaction في 50% من اختبارات Stage 2، نعدّل الـUI/الأتباع قبل زيادة مكافأة الضرر.
- إذا استغرق Boss أكثر من 10 دقائق بسبب ضعف الضرر، نراجع الـResistance/Hit uptime قبل إضافة Skill جديدة.

## 9. اختبار الأرقام

### Automation

- `BossHealth.Stage01_Equals6500`
- `BossHealth.Stage12_Equals13650`
- `HeroHealth.Stage12_Equals1825`
- `Reaction.FireWind_Is1_25DamageAnd1_15Stagger`
- `Resistance.NeverProducesNegativeDamage`
- `Telegraph.DamageStartsAfterConfiguredDelay`
- `Hazard.VoidFall_RespawnsInsteadOfApplyingNegativeHealth`

### Playtest capture

لكل Boss نسجل:

- متوسط زمن القتال.
- DPS اللاعب الفعلي.
- Damage taken حسب الحركة.
- عدد محاولات Absorb.
- عدد مرات عدم رؤية Telegraph.
- عدد Reactions.
- نسبة استخدام كل Ability.

الأرقام النهائية تُحسم من البيانات، لا من الانطباع أو من قوة اسم الزعيم.
