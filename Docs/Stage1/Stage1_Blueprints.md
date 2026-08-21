# Echo of Elements — Stage 1 Blueprint Structure
## Fire Castle / قلعة الجمر

**الغرض:** تحويل الـ Blockout إلى قائمة تنفيذ واضحة لفريق Unreal، مع فصل مسؤوليات اللاعب، الأعداء، التفاعلات، التقدم، والمواجهة.

> **قاعدة تنفيذ:** كل Blueprint يملك مسؤولية واحدة قابلة للاختبار. منطق القتال العام يظل في مكونات أو واجهات مشتركة قدر الإمكان، بينما تبقى قيم Stage 1 قابلة للضبط من خلال Instance Editable variables.

## 1. خريطة العلاقات

```text
BP_GameMode_Stage1
  ├── BP_Stage1Manager
  │     ├── BP_Checkpoint
  │     ├── BP_Door_Stage1
  │     ├── BP_ExitGate
  │     └── BP_LorePickup / BP_CinderKey / BP_EmberSigil
  ├── BP_PlayerCharacter
  │     ├── AC_AbsorbComponent
  │     ├── AC_HealthComponent
  │     └── AC_InteractionComponent
  ├── BP_Emberling
  ├── BP_EmberWarden
  ├── BP_Ignar
  ├── BP_AbsorbShrine
  └── BP_Brazier
```

## 2. Blueprints الأساسية

| Blueprint | النوع | المسؤولية | أولوية |
|---|---|---|---:|
| `BP_PlayerCharacter` | Character | الحركة، الصحة، التفاعل، استقبال العنصر | P0 |
| `BP_Ignar` | Character / Boss | منطق Boss، المراحل، النوافذ، والانتقال للخروج | P0 |
| `BP_Emberling` | Character | عدو التدريب والاختبار، إطلاق مقذوفات الجمر | P0 |
| `BP_EmberWarden` | Character / Elite | اختبار Elite قبل Boss | P0 |
| `BP_AbsorbShrine` | Actor | شرح وتفعيل دورة الامتصاص التدريبية | P0 |
| `BP_EmberProjectile` | Actor | مقذوف قابل للامتصاص أو الاصطدام | P0 |
| `BP_AbsorbComponent` | Actor Component | منطق العادي وPerfect Absorb | P0 |
| `BP_HealthComponent` | Actor Component | الصحة والضرر والموت | P0 |
| `BP_InteractionComponent` | Actor Component | التفاعل القريب مع Shrine، الأبواب، والمكافآت | P1 |
| `BP_Stage1Manager` | Actor | إدارة التقدم، الأبواب، الحفظ، ونتيجة المرحلة | P0 |
| `BP_Door_Stage1` | Actor | بوابات التعلم والاختبار وBoss | P0 |
| `BP_Checkpoint` | Actor | حفظ نقطة الإعادة واسترجاع الحالة | P0 |
| `BP_Brazier` | Actor | مصادر المرحلة الثانية من Boss | P0 |
| `BP_ExitGate` | Actor | فتح الخروج بعد هزيمة إغنار | P0 |
| `BP_CinderKey` | Actor / Pickup | مكافأة Elite وفتح Antechamber | P1 |
| `BP_EmberSigil` | Actor / Pickup | مكافأة Boss وبدء الخروج | P0 |
| `BP_LorePickup` | Actor | النص الاختياري في Side Room | P2 |
| `BP_Stage1HUD` | Widget | هدف المرحلة، مورد الامتصاص، وإشارات Perfect | P1 |
| `BP_Stage1AudioDirector` | Actor | انتقالات الصوت والإشارات السياقية | P2 |

## 3. `BP_PlayerCharacter`

### المتغيرات

| المتغير | النوع | القيمة الأولية المقترحة | الاستخدام |
|---|---|---:|---|
| `MoveSpeed` | Float | 600 | سرعة الحركة في الـ Blockout |
| `JumpHeight` | Float | قابل للضبط | اجتياز Broken Bridge والمنصات |
| `Health` | Float | 100 | يدار فعلياً عبر `BP_HealthComponent` |
| `EmberCharge` | Float | 0 | مورد العنصر الناري، من 0 إلى 100 |
| `MaxEmberCharge` | Float | 100 | سقف المورد |
| `bCanAbsorb` | Boolean | true | قفل القدرة في حالات الموت أو المشاهد |
| `CurrentCheckpointId` | Name | `CP-01` | نقطة العودة الحالية |
| `bHasCinderKey` | Boolean | false | فتح مرحلة ما قبل Boss |
| `bHasEmberSigil` | Boolean | false | تفعيل الخروج |
| `TargetInteractable` | Actor Reference | None | العنصر القابل للتفاعل أمام اللاعب |

### الوظائف والأحداث

`Move(InputVector)` و`Look(InputVector)` للحركة الأساسية، `Interact()` للتفاعل، `RequestAbsorb()` لبدء الامتصاص، `OnPerfectAbsorb(SuccessData)` لاستقبال النجاح، `OnDamaged(DamageData)` لتطبيق رد الفعل، `Die()` للموت، `RespawnAtCheckpoint()` للإعادة، و`SetStageObjective(ObjectiveId)` لتحديث HUD.

**اختبار الوحدة:** يستطيع اللاعب التحرك والتفاعل والعودة إلى `CP-04` بعد الموت دون فقدان `bHasCinderKey`.

## 4. `BP_AbsorbComponent`

### المتغيرات

| المتغير | النوع | الوصف |
|---|---|---|
| `AbsorbRadius` | Float | نصف قطر الالتقاط |
| `PerfectWindow` | Float | مدة نافذة Perfect Absorb بالثواني |
| `PerfectStartOffset` | Float | التوقيت بالنسبة لوصول المقذوف |
| `ChargeGainNormal` | Float | مقدار الشحنة في الامتصاص العادي |
| `ChargeGainPerfect` | Float | مقدار الشحنة في الامتصاص الكامل |
| `bIsAbsorbing` | Boolean | حالة القدرة الحالية |
| `LastAbsorbGrade` | Enum | None / Normal / Perfect / Failed |
| `AbsorbCooldown` | Float | منع الضغط المتكرر غير المقروء |

### الوظائف والأحداث

`BeginAbsorb()`, `FindAbsorbTargets()`, `EvaluateAbsorbTiming(Target)`, `ApplyAbsorb(Target, Grade)`, `AddCharge(Amount)`, `ConsumeCharge(Amount)`, `CancelAbsorb()`, و`BroadcastAbsorbResult(Grade)`.

**قاعدة Perfect:** لا يُعلن النجاح إلا إذا وقع الاصطدام داخل `PerfectWindow`، ويُرسل Event واحد فقط حتى لا تتكرر المكافأة عند تداخل التصادمات.

## 5. `BP_AbsorbShrine`

### المتغيرات

| المتغير | النوع | الوصف |
|---|---|---|
| `ShrineId` | Name | معرف الحرم في Stage1 |
| `TutorialStep` | Enum | Basic / Moving / Perfect / Complete |
| `RequiredGrade` | Enum | Normal أو Perfect |
| `SpawnInterval` | Float | فاصل ظهور Emberling أو المقذوف |
| `MaxAttempts` | Integer | عدد المحاولات قبل إعادة التهيئة |
| `LinkedDoor` | Actor Reference | `BP_Door_Stage1` المرتبط |
| `bCompleted` | Boolean | يمنع تكرار التدريب بعد الإنجاز |

### الوظائف والأحداث

`StartTutorial()`, `SpawnTrainingTarget()`, `OnAbsorbResult(Grade)`, `AdvanceTutorialStep()`, `CompleteShrine()`, `ResetAttempt()`, و`UnlockLinkedDoor()`.

يجب أن يبقى الحرم قابلاً لإعادة الشرح عبر التفاعل، لكن بعد الإكمال لا يعيد قفل البوابة ولا يمسح تقدم اللاعب.

## 6. `BP_Emberling`

### المتغيرات

| المتغير | النوع | تدريب | اختبار |
|---|---|---:|---:|
| `MaxHealth` | Float | 30 | 45 |
| `MoveSpeed` | Float | 180 | 240 |
| `AttackCooldown` | Float | 2.5 | 1.8 |
| `ProjectileCount` | Integer | 1 | 2 |
| `ProjectileSpeed` | Float | 700 | 850 |
| `AggroRadius` | Float | 900 | 1200 |
| `bCanBeAbsorbed` | Boolean | true | true |

### الوظائف والأحداث

`AcquireTarget()`, `ChooseAttack()`, `LaunchEmberProjectile()`, `OnAbsorbed(Grade)`, `OnStaggered(Duration)`, `OnDeath()`, و`ResetToSpawn()`.

يجب أن يصدر العدو إشارة قبل القذف، وأن تكون نقطة إطلاق المقذوف مرئية في الـ Blockout. لا يُسمح له بتغيير الهدف أثناء نافذة الامتصاص حتى لا تبدو النتيجة عشوائية.

## 7. `BP_EmberWarden`

المتغيرات الرئيسية هي `MaxHealth=500`، `SlamCooldown`، `WaveTravelSpeed`، `ArenaLockDuration`، `PhaseThreshold=0.5`، و`StaggerDuration`. الوظائف هي `EnterArena()`, `PerformSlam()`, `SpawnAbsorbableWave()`, `EnterPhaseTwo()`, `OpenDamageWindow()`, `OnDeath()`, و`ReleaseArenaLock()`.

يشترط التنفيذ أن تكون موجة الجمر قابلة للامتصاص، وأن يؤدي Perfect Absorb إلى Stagger أو نافذة ضرر، بينما يؤدي الامتصاص العادي إلى شحنة أو تخفيف ضرر فقط.

## 8. `BP_Ignar`

### المتغيرات

| المتغير | النوع | القيمة/الوصف |
|---|---|---|
| `MaxHealth` | Float | 3000 مبدئياً، للضبط فقط |
| `CurrentPhase` | Enum | Gatekeeper / CastleHeart / Defeated |
| `PhaseTwoThreshold` | Float | 0.45 من الصحة |
| `ProjectileCount` | Integer | 3 في المرحلة الأولى |
| `BrazierCount` | Integer | 3 في المرحلة الثانية |
| `AttackTelegraphTime` | Float | قابل للضبط، يجب أن يكون مقروءاً |
| `PerfectBreakRequired` | Integer | 1 في P1، 2 في دورة P2 |
| `BossArena` | Box / Volume Reference | حدود الحلبة |
| `ExitGate` | Actor Reference | `BP_ExitGate` |

### الوظائف والأحداث

`BeginBossFight()`, `SelectAttackPattern()`, `PerformFrontStrike()`, `LaunchTripleEmber()`, `PerformDelayedBurst()`, `CheckPhaseTransition()`, `IgniteNextBrazier()`, `OnPerfectAbsorb(Grade)`, `OpenStaggerWindow()`, `OnHealthChanged()`, `DefeatBoss()`, و`GrantEmberSigil()`.

**آلة الحالات:** لا ينتقل إغنار إلى `CastleHeart` إلا مرة واحدة عند عبور العتبة. لا تُنشأ Braziers جديدة في كل Tick؛ تُنشأ أو تُفعّل مرة واحدة عند بدء المرحلة الثانية. عند `Defeated` تتوقف الهجمات، تُفتح الحلبة، وتُرسل إشارة إلى `BP_Stage1Manager`.

## 9. `BP_EmberProjectile`

المتغيرات: `Damage`, `Speed`, `Lifetime`, `AbsorbType=Fire`, `bIsPerfectEligible`, `TelegraphColor`, و`OnHitBehavior`. الوظائف: `InitializeProjectile(Data)`, `OnOverlapPlayer()`, `OnAbsorbRequested()`, `ResolveAbsorb(Grade)`, `DestroyProjectile()`. يجب أن يكون مسار المقذوف مستقلاً عن رسومياته حتى يظل الاختبار قابلاً للضبط في Blockout.

## 10. `BP_Stage1Manager`

### الحالة التي يديرها

`StageSegment`، `CompletedTutorialSteps`، `TestRoomsCleared`، `bEliteDefeated`، `bBossDefeated`، `CurrentCheckpointId`، `StageStartTime`، `PerfectAbsorbCount`، و`SecretsFound`.

### الوظائف

`StartStage()`, `SetSegment(SegmentId)`, `RegisterPerfectAbsorb()`, `RegisterRoomClear(RoomId)`, `RegisterEliteDefeat()`, `RegisterBossDefeat()`, `SaveCheckpoint(State)`, `LoadCheckpoint()`, `OpenDoor(DoorId)`, `ShowStageSummary()`, و`CompleteStage()`.

المدير لا يملك منطق الضرر أو الحركة؛ ينسق الأحداث فقط. جميع الأحداث المهمة يجب أن تكون قابلة للتسجيل في Log باسم المقطع والوقت.

## 11. `BP_Door_Stage1` و`BP_Checkpoint`

يحتوي الباب على `DoorId`, `RequiredCondition`, `OpenTimeline`, `LockedMessage`, `LinkedManager`, و`bOneWay`. الوظائف هي `CanOpen()`, `OpenDoor()`, `LockDoor()`, و`ShowRequirement()`.

يحتوي checkpoint على `CheckpointId`, `RespawnTransform`, `RestoreHealthPercent`, `RestoreCharge`, و`SavePolicy`. الوظائف هي `ActivateCheckpoint()`, `CaptureState()`, و`ApplyStateToPlayer()`.

## 12. `BP_Brazier` و`BP_ExitGate`

يحتوي Brazier على `BrazierId`, `bIgnited`, `IgniteDuration`, `ProjectileSpawnPoint`, و`BossReference`. الوظائف هي `Ignite()`, `ExtinguishTemporary()`, `SpawnAbsorbableProjectile()`, و`ResetBrazier()`.

يحتوي ExitGate على `RequiredItem=EmberSigil`, `bIsOpen`, `OpenDelay`, و`NextStageId`. الوظائف هي `EvaluateUnlock()`, `OpenGate()`, `ShowExitObjective()`, و`CompleteStageTransition()`.

## 13. واجهات وأحداث مشتركة

| الواجهة/الحدث | المستهلكون | الغرض |
|---|---|---|
| `BPI_Interactable` | Shrine، الأبواب، pickups، الخروج | توحيد `CanInteract`, `Interact`, `GetPrompt` |
| `BPI_Absorbable` | المقذوفات، Emberling، Brazier | توحيد `GetAbsorbData`, `OnAbsorb` |
| `BPI_Damageable` | اللاعب، Elite، Ignar | توحيد تطبيق الضرر والموت |
| `EAbsorbGrade` | جميع الأنظمة | None / Normal / Perfect / Failed |
| `OnStageSegmentChanged` | HUD، الصوت، المدير | تحديث الهدف والإيقاع |
| `OnBossDefeated` | المدير، الخروج، HUD | فتح نهاية المرحلة |

## 14. ترتيب التنفيذ

يبدأ الفريق بـ `BP_HealthComponent` و`BP_AbsorbComponent`، ثم `BP_PlayerCharacter` و`BP_EmberProjectile`. بعد ذلك تُنفذ Shrine وEmberling والبوابات ونقاط الحفظ، ثم Elite، وأخيراً Ignar وBrazier وExitGate. لا يبدأ تنفيذ المؤثرات أو واجهة التجميل قبل نجاح مسار Perfect Absorb في غرفة التعلم وفي Boss.

## References

[1]: https://github.com/jolianstori-oss/echo-of-elements/blob/main/docs/01-unreal-architecture-v0.1.md "Unreal Architecture v0.1"
[2]: https://github.com/jolianstori-oss/echo-of-elements/blob/main/docs/00-game-design-bible-v0.1.md "Game Design Bible v0.1"

المحتوى خاص بالمرحلة الأولى ومبني على نطاق التنفيذ المطلوب؛ القيم الرقمية الأولية مخصصة للـ Blockout وتحتاج معايرة عبر الاختبارات.

**المؤلف:** Manus AI  
**الإصدار:** Stage 1 Blueprints v0.1

[1] [2]
