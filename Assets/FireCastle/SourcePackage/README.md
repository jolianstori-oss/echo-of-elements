# Echo of Elements — Fire Castle Prototype 3D Pack

**الإصدار:** 1.0  
**الهدف:** Unreal Engine 5.8  
**نوع التسليم:** حزمة نماذج ثلاثية الأبعاد أولية قابلة للاستيراد لمرحلة **قلعة الجمر / Fire Castle**.

هذه الحزمة تحول قائمة أصول المرحلة وخرائط الـBlockout إلى **32 نموذجاً ثلاثي الأبعاد**: 26 نموذجاً ثابتاً للبيئة والتفاعل والمخاطر، و6 نماذج هيكلية أولية للشخصيات والأعداء. وهي مصممة لإثبات القراءة البصرية، الأحجام، مواضع الارتكاز، الاصطدام، وربط الـBlueprints في الـVertical Slice، حيث تبدأ المرحلة بمسار رماد وجسر مكسور ثم تنتقل عبر حرم الامتصاص والاختبار والـElite وصولاً إلى مواجهة إغنار وبوابة الخروج.[1] [2]

> **حد الجاهزية.** هذه نماذج **Prototype / Vertical Slice منخفضة التعقيد**، وليست بدائل عن نماذج إنتاج نهائية. تستخدم أشكالاً واضحة ومواداً لونية أساسية تساعد على اختبار الوظيفة والقراءة؛ ولا تشمل خامات PBR نهائية، UV2 للـLightmap، LODs يدوية، أو حركات لعب نهائية. نَماذج الشخصيات تتضمن Skeleton ووزناً أولياً فقط، ويجب ربطها بـAnimation Blueprint وحركات الإنتاج قبل إصدار اللعبة.

## بنية الحزمة

| المسار | المحتوى | الاستخدام المقصود |
|---|---|---|
| `StaticMeshes/` | 26 ملف `FBX` ثابتاً | الاستيراد الرئيسي إلى Unreal للبيئة والعناصر التفاعلية. |
| `SkeletalMeshes/` | 6 ملفات `FBX` هيكلية | اللاعب والأعداء؛ لكل ملف Skeleton مبدئي. |
| `GLB/` | نسخة `GLB` من كل أصل | معاينة سريعة أو تبادل مع أدوات DCC؛ ليست مسار الاستيراد الموصى به لهذا المشروع. |
| `Source/Blend/` | ملف Blender مستقل لكل أصل | تعديل المصدر، الخامات، نقطة الارتكاز، الاصطدام أو الـRig. |
| `Previews/` | معاينات PNG لعينات محورية | مراجعة الشكل قبل الاستيراد. |
| `Documentation/` | Manifest، تقرير فحص، وسجل بناء ومراجعة بصرية | التتبع والتحقق الفني. |
| `source/` | سكربتات البناء والفحص | إعادة بناء الحزمة أو تعديلها بشكل قابل للتكرار. |

تستخدم النماذج الثابتة تسمية `SM_`، والنماذج الهيكلية تسمية `SK_`، بما يتفق مع سجل المرحلة. وتحتوي ملفات FBX الثابتة على مجسمات اصطدام بسيطة تحمل بادئة `UCX_` ومتطابقة الاسم مع المجسم المرئي؛ يتعرف Unreal على هذه التسمية بوصفها اصطداماً مخصصاً عند الاستيراد.[3] [4]

## سجل النماذج

### البيئة والوحدات المعمارية

| الأصل | الصيغة الأساسية | الحجم التصميمي (سم) | موضع الدمج |
|---|---|---:|---|
| `SM_FC_FloorTile_400` | FBX ثابت | 400 × 400 × 40 | أرضيات الطريق والساحات. |
| `SM_FC_Wall_400x400` | FBX ثابت | 400 × 50 × 400 | جدران الغرف والممرات. |
| `SM_FC_Ceiling_400` | FBX ثابت | 400 × 400 × 36 | سقوف Furnace Hall والممرات المغلقة. |
| `SM_FC_Archway_400` | FBX ثابت | 400 × 85 × 425 | مداخل القلعة وإطارات المسارات؛ يحافظ الاصطدام على فتحة العبور. |
| `SM_FC_Stair_6Step` | FBX ثابت | 300 × 240 × 165 | انتقالات رأسية قصيرة. |
| `SM_FC_Battlement_400` | FBX ثابت | 400 × 120 × 125 | الحواف الخارجية والغطاء المنخفض. |
| `SM_FC_Pillar_360` | FBX ثابت | 135 × 135 × 365 | Courtyard، Arena، والممرات. |
| `SM_FC_BrokenBridge_800` | FBX ثابت | 800 × 240 × 150 | مقدمة المرحلة؛ اصطدامات منفصلة تحافظ على فجوة العبور. |
| `SM_FC_HotPlatform_400` | FBX ثابت | 400 × 400 × 46 | منصة حرارية دورية؛ الضرر منفصل في Blueprint. |
| `SM_FC_MagmaFissure_400` | FBX ثابت | 400 × 400 × 70 | شق حمم بصري؛ أضف Hazard Volume مستقلاً. |
| `SM_FC_RubbleCluster` | FBX ثابت | 200 × 180 × 80 | حطام وتوجيه بصري للمسار. |
| `SM_FC_HangingChain` | FBX ثابت | 65 × 65 × 270 | Furnace Hall ودعم الهوية الصناعية. |
| `SM_FC_EmberBanner` | FBX ثابت | 135 × 45 × 390 | علامة طريق ومعلم ناري. |

### التفاعل والتقدم والمكافآت

| الأصل | الصيغة الأساسية | Blueprint المقترح | الوظيفة |
|---|---|---|---|
| `SM_FC_AbsorbShrine` | FBX ثابت | `BP_AbsorbShrine` | حرم الدرس ونواة الامتصاص. |
| `SM_FC_CheckpointObelisk` | FBX ثابت | `BP_Checkpoint` | نقطة حفظ/إعادة بلون آمن مميز. |
| `SM_FC_FireGate` | FBX ثابت | `BP_Door_Stage1` | بوابة Gate 01 أو قفل مواجهة؛ حرّكها في Blueprint. |
| `SM_FC_Brazier` | FBX ثابت | `BP_Brazier` | واحد من الثلاثة في مرحلة إغنار الثانية. |
| `SM_FC_ElementalExitGate` | FBX ثابت | `BP_ExitGate` | بوابة الخروج بعد الحصول على الـSigil. |
| `SM_FC_CinderKey` | FBX ثابت | `BP_CinderKey` | مكافأة Elite/فتح غرفة Boss. |
| `SM_FC_EmberSigil` | FBX ثابت | `BP_EmberSigil` | مكافأة هزيمة إغنار. |
| `SM_FC_LorePedestal` | FBX ثابت | `BP_LorePickup` | تفاعل اختياري في Side Room. |
| `SM_FC_RewardChest` | FBX ثابت | `BP_RewardContainer` | مكافأة اختيارية؛ حرّك الغطاء في Blueprint. |

### المخاطر وإشارات اللعب

| الأصل | الصيغة الأساسية | Blueprint / نظام مقترح | الوظيفة |
|---|---|---|---|
| `SM_FC_FlameJet` | FBX ثابت | `BP_FlameJet` + Niagara | فوهة لهب ذات توقيت؛ لا تستخدم النموذج نفسه كضرر. |
| `SM_FC_HeatBarrier` | FBX ثابت | `BP_HeatBarrier` | حاجز حراري مرئي لمسار التعلّم والتقدم. |
| `SM_FC_EmberProjectile` | FBX ثابت | `BP_EmberProjectile` | مقذوف قابل للامتصاص؛ اتجاهه الأمامي `+X`. |
| `SM_FC_AbsorbTelegraph` | FBX ثابت | Niagara أو Component في `BP_AbsorbComponent` | حلقة Perfect Absorb المسطّحة. |

### الشخصيات والأعداء

| الأصل | الصيغة الأساسية | Skeleton مبدئي | الارتباط المقترح |
|---|---|---|---|
| `SK_Aren_Prototype` | FBX هيكلي | `root → pelvis → spine → head` | `BP_PlayerCharacter`؛ بديل بلوكاوت للاعب الحالي. |
| `SK_Emberling` | FBX هيكلي | `root → body → head` | `BP_Emberling`؛ عدو تدريب/خفيف. |
| `SK_CinderCaster` | FBX هيكلي | `root → pelvis → spine → head` | عدو بعيد المدى. |
| `SK_AshGuard` | FBX هيكلي | `root → pelvis → spine → head` | عدو ثقيل بدرع ودرع حماية. |
| `SK_EmberWarden` | FBX هيكلي | `root → pelvis → spine → head` | `BP_EmberWarden`؛ الـElite قبل Boss. |
| `SK_Ignar` | FBX هيكلي | `root → pelvis → spine → neck → head` | `BP_Ignar`؛ نموذج زعيم ذي سيف وتاج ونواة نارية. |

## خطوات الدمج في Unreal Engine

### 1. تنظيم المسارات

أنشئ المسارات التالية داخل Content Browser، وهي متسقة مع سجل أصول Stage 1:[2]

```text
/Content/EchoOfElements/Stage1/Environment/Modular
/Content/EchoOfElements/Stage1/Environment/SetDressing
/Content/EchoOfElements/Stage1/Interactive
/Content/EchoOfElements/Stage1/Hazards
/Content/EchoOfElements/Stage1/Characters
/Content/EchoOfElements/Stage1/Enemies
/Content/EchoOfElements/Stage1/FX
```

### 2. استيراد المجسمات الثابتة

انسخ ملفات `StaticMeshes/*.fbx` إلى مجلد محلي، ثم من Content Browser افتح المسار المقصود واختر **Import**. اترك `Skeletal Mesh` معطّلاً، فعّل `Import Materials` فقط إن رغبت باستيراد مواد الألوان الأولية، وفعّل `Import Collision` كي يستخدم Unreal مجسمات `UCX_` المضمنة. عند فحص `SM_FC_Archway_400` و`SM_FC_BrokenBridge_800` تأكد في Static Mesh Editor من أن فتحة الباب وفجوة الجسر غير محجوبتين بالتصادم.[3]

نقاط الارتكاز لجميع النماذج الثابتة في أصل العالم عند قاعدة النموذج أو مركز القاعدة؛ لذلك يمكن تثبيتها على شبكة المستوى بسهولة. توصي وثائق Unreal بأن تكون نقطة الارتكاز عند الأصل عند تصدير Static Mesh، وأن تُفحص الاصطدامات في محرر Static Mesh بعد الاستيراد.[3]

### 3. استيراد الشخصيات

استورد كل ملف ضمن `SkeletalMeshes/*.fbx` منفرداً إلى `Characters` أو `Enemies`. فعّل `Skeletal Mesh`، واترك حقل `Skeleton` فارغاً عند أول استيراد حتى ينشئ Unreal Skeleton الأصل؛ أو اختر Skeleton قائماً فقط بعد فحص توافق عظامه. بعد الاستيراد أنشئ Physics Asset تلقائياً، ثم افتح Skeletal Mesh لمراجعة الـbind pose والعظام.[5] [6]

> لا تتوقع حركات جاهزة من هذه الملفات: تحتوي الحزمة على Rig ووزن مبدئيين للاختبار والربط، لا على دورة حركة أو هجمات أو ملفات Animation Blueprint. اربط عناصر السلاح، مؤثرات القذف، ومخارج الـVFX عبر Sockets جديدة داخل Skeleton أو عبر Components في الـBlueprint.

### 4. ربط الـBlueprints

عيّن Static Mesh المناسب في Component المرئي داخل كل Blueprint الوارد أعلاه. اترك منطق الضرر، التفاعل، الحفظ، الإشعال، والمكافآت في الـBlueprints/المكونات كما تقترح وثائق المرحلة؛ النموذج يعرض الحالة ولا ينفذ منطقها. افصل دائماً مجسم الخطر عن Box/Sphere Collision أو Gameplay Ability Volume، خصوصاً في `FlameJet` و`HeatBarrier` و`MagmaFissure`.[1] [2]

### 5. مواد المرحلة الأولية

تتضمن الملفات مواداً أساسية بأسماء `M_FC_*` وألواناً وظيفية: برتقالي/أحمر للخطر والامتصاص، أزرق لـCheckpoint والمناطق الآمنة، وبنفسجي للـElite. أنشئ لاحقاً Material Instances في Unreal واربط Emissive بالمتحولات `bIgnited`، `bCompleted`، `bIsOpen`، أو حالة الـTelegraph بدلاً من تعديل المجسم.

## فحص التسليم

أجري فحص بنية للملفات قبل التسليم. تحقق الفحص من وجود ملفات FBX وGLB وBlend، أحجامها غير الصفرية، ترويسة GLB 2.0، وتوقيع FBX الثنائي لكل أصل.

| المقياس | النتيجة |
|---|---:|
| الأصول المتوقعة / المفحوصة | 32 / 32 |
| Static Meshes | 26 |
| Skeletal Meshes | 6 |
| الأصول التي اجتازت الفحص البنيوي | 32 / 32 |
| نتائج فاشلة | 0 |

راجع `Documentation/qa_report.json` للتفاصيل و`Documentation/visual_review.md` للمراجعة البصرية. لم يُجر اختبار استيراد محرر Unreal Engine فعلي داخل هذه الجلسة؛ لذلك يجب تنفيذ فحص استيراد سريع في مشروعك قبل حفظ أي Blueprint أو Map.

## ملاحظات العمل التالية

لتطوير الحزمة من نموذج Vertical Slice إلى جودة إنتاج، ابدأ بإعادة Topology للشخصيات، إضافة UVs وPBR textures وLODs، وتحضير حركات اللاعب/الخصوم. بعد ذلك أضف Niagara منفصلاً لمصادر الجمر واللهب وحلقات الامتصاص، ولا تجعل VFX أو الضرر أو المنطق محفوظاً داخل النموذج. هذا يحافظ على الفصل بين المحتوى والأنظمة الذي تحدده معمارية المشروع.[7]

## المراجع

[1]: https://github.com/jolianstori-oss/echo-of-elements/blob/main/Docs/Stage1/Stage1_Blockout.md "Stage 1 Blockout"
[2]: https://github.com/jolianstori-oss/echo-of-elements/blob/main/Docs/Stage1/Stage1_AssetList.md "Stage 1 Asset List"
[3]: https://dev.epicgames.com/documentation/unreal-engine/fbx-static-mesh-pipeline-in-unreal-engine?lang=en-US "FBX Static Mesh Pipeline in Unreal Engine"
[4]: https://dev.epicgames.com/documentation/unreal-engine/fbx-import-options-reference-in-unreal-engine?lang=en-US "FBX Import Options Reference in Unreal Engine"
[5]: https://dev.epicgames.com/documentation/unreal-engine/fbx-skeletal-mesh-pipeline-in-unreal-engine?lang=en-US "FBX Skeletal Mesh Pipeline in Unreal Engine"
[6]: https://dev.epicgames.com/documentation/unreal-engine/importing-skeletal-meshes-using-fbx-in-unreal-engine?lang=en-US "Importing Skeletal Meshes Using FBX in Unreal Engine"
[7]: https://github.com/jolianstori-oss/echo-of-elements/blob/main/docs/01-unreal-architecture-v0.1.md "Unreal Architecture v0.1"


---

## تحديث العرض النهائي للخامات — v1.0

أضيفت حزمة خامات PBR متكررة تضم **11 مجموعة** و**49 خريطة PNG بدقة 1024**، تشمل الحجر المتشقق والطوب المحروق والحديد المؤكسد والرماد والحمم والجمر ومواد الحالات الآمنة/النخبوية. رُبطت هذه الخرائط أيضاً بملفات Blender ونسخ GLB المُعاد تصديرها.

راجع [`Materials/Unreal_Material_Setup.md`](Materials/Unreal_Material_Setup.md) لإنشاء المواد الرئيسية وInstances وتشغيل نص الاستيراد. نتيجة الفحص النهائية محفوظة في [`Documentation/material_qa_report.json`](Documentation/material_qa_report.json): **49/49** خريطة و**32/32** نموذج FBX و**32/32** ملف GLB اجتازت الفحص البنيوي.

> تظل مواد Unreal (`.uasset`) غير مولّدة داخل هذه الحزمة لأن إنشائها يحتاج إلى تشغيل Unreal Editor في مشروعك. وفرنا بدلاً منها خرائط PBR، دليل عقد Master Material، ونص Unreal Python لإنشائها واستيرادها بصورة قابلة للتكرار.
