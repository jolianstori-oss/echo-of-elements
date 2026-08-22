# دليل خامات العرض النهائي — قلعة الجمر

**الإصدار:** 1.0  
**النطاق:** خرائط PBR وخامات العرض النهائي للـVertical Slice في **Echo of Elements / Fire Castle**.

تضيف هذه الإصدارة **11 مجموعة خامات متكررة بدقة 1024 × 1024**، مع خرائط Base Color وNormal وORM وHeight لكل خامة، وخرائط Emissive للحالات التي يجب أن تقرأ بصرياً بوصفها طاقة أو ناراً أو حالة تفاعلية. صُممت المجموعة لتؤكد لغة قلعة بركانية من الحجر الأسود المتشقق والطوب المحترق والحديد المؤكسد، مع فصل واضح بين الخطر الناري، نقاط الأمان، الـElite، والمكافآت، وهو ما تتطلبه وثائق المرحلة لقابلية قراءة الخطر والتفاعل في الحركة والقتال.[1] [2]

> **مهم:** ملفات PNG هي المصدر المعتمد للعرض في Unreal. لا تعتمد على مادة FBX المستوردة تلقائياً بوصفها مادة نهائية؛ استورد خرائط PNG واضبط إعداداتها ثم اربطها عبر Material Instances كما هو موضح أدناه.

## محتوى كل مجموعة PBR

| اللاحقة | المحتوى | إعداد Unreal المطلوب |
|---|---|---|
| `_BC.png` | Base Color | `sRGB = On`، Compression افتراضي. |
| `_N.png` | Tangent-space Normal | `sRGB = Off`، `Compression Settings = Normalmap`، `Sampler Type = Normal`. |
| `_ORM.png` | **R = Ambient Occlusion، G = Roughness، B = Metallic** | `sRGB = Off`، `Compression Settings = Masks`، `Sampler Type = Linear Color`. |
| `_H.png` | Height رمادية | `sRGB = Off`، `Compression Settings = Grayscale`؛ اختيارية للـParallax فقط. |
| `_E.png` | Emissive Color | `sRGB = On`، تستخدم فقط في الخامات النارية/السحرية. |

تسمح واجهة FBX في Unreal باستيراد المواد والخامات المرتبطة، لكن الخرائط التي تحتاج ضبطاً خاصاً، مثل Masks وNormal، يجب فحصها داخل المحرر بعد الاستيراد وربطها بقنواتها الصحيحة.[3]

## مجموعات الخامات ومواضع استخدامها

| Material Instance المقترح | مجموعة الخرائط | الاستخدام الأساسي | شدة الانبعاث الابتدائية |
|---|---|---|---:|
| `MI_FC_Obsidian` | `T_FC_Obsidian_*` | أرضيات، حجر داكن، حواف القلعة | 0.25 للشقوق فقط |
| `MI_FC_ScorchedBrick` | `T_FC_ScorchedBrick_*` | الجدران، الأقواس، السلالم | 0 |
| `MI_FC_BurntIron` | `T_FC_BurntIron_*` | سلاسل، بوابات، مواقد، دروع | 0 |
| `MI_FC_Ash` | `T_FC_Ash_*` | أرض طريق الرماد والحطام | 0 |
| `MI_FC_Magma` | `T_FC_Magma_*` | شقوق الحمم والمنصات الساخنة | 8.0 |
| `MI_FC_Ember` | `T_FC_Ember_*` | قذائف، نواة الحرم، شرر النار | 6.0 |
| `MI_FC_CinderGold` | `T_FC_CinderGold_*` | أقفال، حلقات الحرم، المفاتيح والـSigil | 2.0 |
| `MI_FC_SafeCyan` | `T_FC_SafeCyan_*` | نقاط الحفظ والمناطق الآمنة | 3.5 |
| `MI_FC_EliteViolet` | `T_FC_EliteViolet_*` | تمييز Ember Warden وحالات الـElite | 3.5 |
| `MI_FC_BoneAsh` | `T_FC_BoneAsh_*` | شاهد الحرم واللوحات القديمة | 0 |
| `MI_FC_CharredCloth` | `T_FC_CharredCloth_*` | رايات، رداء Ignar، ملابس Caster | 0 |

## إنشاء المواد الرئيسية

أنشئ المادتين التاليتين داخل:

```text
/Content/EchoOfElements/Stage1/Materials/
```

### `M_FC_Master_Surface`

استخدم مادة Surface عادية، وفعّل `Use Material Attributes` فقط إذا كان ذلك معيار مشروعكم. أنشئ معاملات Texture التالية بأسمائها **حرفياً** كي يعمل النص المرفق دون تعديل:

| المعامل | النوع | الربط |
|---|---|---|
| `T_BaseColor` | Texture Sample Parameter 2D | `RGB → Base Color` |
| `T_Normal` | Texture Sample Parameter 2D، Sampler Normal | `RGB → Normal` |
| `T_ORM` | Texture Sample Parameter 2D، Sampler Linear Color | `R → Ambient Occlusion`، `G → Roughness`، `B → Metallic` |
| `T_Height` | Texture Sample Parameter 2D | اختياري: إلى Parallax Occlusion Mapping؛ لا تربطه في النسخة الأولى إن لم يكن ضرورياً. |
| `TextureTiling` | Scalar Parameter = `2.0` | يضرب بـ`TextureCoordinate` قبل مداخل UV لجميع خرائط Texture Sample. |
| `RoughnessBias` | Scalar Parameter = `0.0` | أضفه إلى Roughness ثم Clamp من 0 إلى 1 عند الحاجة. |

### `M_FC_Master_Emissive`

انسخ `M_FC_Master_Surface` أو استخدمه بوصفه Parent، ثم أضف المعاملين:

| المعامل | النوع | الربط |
|---|---|---|
| `T_Emissive` | Texture Sample Parameter 2D | `RGB × EmissiveIntensity → Emissive Color` |
| `EmissiveIntensity` | Scalar Parameter | القيمة الافتراضية `5.0`؛ تُعدل في الـMaterial Instance أو Blueprint. |

لا تجعل التوهج وحده مصدر تعريف الخطر: أبقِ حدود `HeatBarrier` و`FlameJet` مقروءة من شكلها وإضاءة المشهد، واسمح للـBlueprint بتحريك `EmissiveIntensity` وفق الحالة (`Warning`، `Active`، `Recovery`). هذا ينسجم مع مطلب المرحلة بأن تكون حالات الخطر والتفاعل مرئية وقابلة للتنبؤ.[1]

## مسار الاستيراد والربط

انسخ مجلد `Textures/` محلياً دون تغيير الأسماء، ثم استورده إلى المسارات التالية:

```text
/Content/EchoOfElements/Stage1/Materials/Textures/BaseColor
/Content/EchoOfElements/Stage1/Materials/Textures/Normal
/Content/EchoOfElements/Stage1/Materials/Textures/ORM
/Content/EchoOfElements/Stage1/Materials/Textures/Height
/Content/EchoOfElements/Stage1/Materials/Textures/Emissive
/Content/EchoOfElements/Stage1/Materials/Instances
```

بعد إنشاء المادتين الرئيسيتين، افتح **Output Log** داخل Unreal ونفّذ نص Python التالي بعد تعديل `PACKAGE_ROOT` لمسار فك الضغط:

```text
Source/UnrealPython/import_fire_castle_materials.py
```

سينشئ النص `MI_FC_*` ويستورد الخرائط ويضبط sRGB وCompression لكل دور من الأدوار. يُستحسن تشغيله أولاً على نسخة عمل من المشروع؛ فهو ينشئ الأصول لكنه لا يعدّل Blueprint أو Level أو خرائط لعب.

## ربط الخامات بالنماذج

| النموذج أو المجموعة | Material Slot / المادة المقترحة | حالة Blueprint عند الحاجة |
|---|---|---|
| `SM_FC_FloorTile_400`، `SM_FC_Archway_400`، `SM_FC_Pillar_360` | `MI_FC_Obsidian` و`MI_FC_ScorchedBrick` | ثابتة. |
| `SM_FC_Wall_400x400`، `SM_FC_Stair_6Step` | `MI_FC_ScorchedBrick` | ثابتة. |
| `SM_FC_FireGate`، `SM_FC_HangingChain`، `SM_FC_RewardChest` | `MI_FC_BurntIron` | بوابة: ارفع انبعاث ختم النار فقط عند الفتح. |
| `SM_FC_MagmaFissure_400`، `SM_FC_HotPlatform_400` | `MI_FC_Magma` | `Active` يرفع `EmissiveIntensity`؛ الضرر في Volume منفصل. |
| `SM_FC_FlameJet`، `SM_FC_EmberProjectile`، نواة `SM_FC_AbsorbShrine` | `MI_FC_Ember` | اربط Pulse أو Telegraph مع Blueprint/Niagara. |
| `SM_FC_Brazier` | `MI_FC_BurntIron` + `MI_FC_Ember` | `BP_Brazier`: تشغيل/إطفاء وPulse. |
| `SM_FC_CheckpointObelisk`، `SM_FC_ElementalExitGate` | `MI_FC_SafeCyan` | نشط عند Checkpoint أو بعد هزيمة Ignar. |
| `SM_FC_CinderKey`، `SM_FC_EmberSigil`، حلقات الحرم | `MI_FC_CinderGold` | Pickup: دوران خفيف وPulse فقط. |
| `SK_EmberWarden` | `MI_FC_EliteViolet` + `MI_FC_BurntIron` | Phase Two أو Stagger. |
| `SK_Ignar` | `MI_FC_CharredCloth` + `MI_FC_Obsidian` + `MI_FC_Ember` | غيّر شدة النواة/السلاح بين مراحل القتال. |
| `SK_CinderCaster` | `MI_FC_CharredCloth` + `MI_FC_Ember` | حالة الإلقاء فقط. |

## تعريف الجاهزية للعرض النهائي

تعتبر هذه الخامات جاهزة لعرض الـVertical Slice عند تحقق النقاط التالية: تباين الحجر والحديد لا يخفي حدود الجسر أو المدخل، الحمم والجمر لا يحجبان المقذوفات أو الـTelegraph، نقاط الحفظ الزرقاء مميزة عن الخطر البرتقالي، وقيم Bloom تعرض التوهج دون حرق كامل تفاصيل النموذج. تعمل نماذج هذه الحزمة بحجم 1024 لتسريع التكرار؛ يمكن رفع أكثر الخامات ظهوراً إلى 2048 فقط بعد قياس الذاكرة على منصة الهدف.

لم تشمل الحزمة Lightmap UV أو Nanite/LOD أو نسيجاً فريداً لكل نموذج، لأن نماذجها تستهدف تكرار المرحلة واختبارها قبل الاعتماد الفني الكامل. افحص كل Static Mesh داخل المحرر بعد الاستيراد لتأكيد الاصطدامات والمواد والـUVs، وهي خطوة موصى بها ضمن مسار FBX الرسمي.[3]

## المراجع

[1]: https://github.com/jolianstori-oss/echo-of-elements/blob/main/Docs/Stage1/Stage1_Blockout.md "Stage 1 Blockout"
[2]: https://github.com/jolianstori-oss/echo-of-elements/blob/main/Docs/Stage1/Stage1_AssetList.md "Stage 1 Asset List"
[3]: https://dev.epicgames.com/documentation/unreal-engine/fbx-static-mesh-pipeline-in-unreal-engine?lang=en-US "FBX Static Mesh Pipeline in Unreal Engine"
