# Echo of Elements — Stage 1 Asset List
## Fire Castle / قلعة الجمر

**الغرض:** تحديد الأصول اللازمة لبناء المرحلة الأولى، مع فصل الحد الأدنى القابل للعب عن الأصول التي يمكن استبدالها لاحقاً. يبدأ التنفيذ باستخدام **cubes / spheres** ومواد مسطحة، ولا يعتمد على الأصول النهائية لإثبات المسار أو القتال.

## 1. قواعد الـ Blockout

| الرمز | الاستخدام | تمثيل مؤقت |
|---|---|---|
| `GEO` | جدران، أرضيات، منصات، بوابات | Cubes بأحجام شبكية ثابتة |
| `ACT` | اللاعب والأعداء والمقذوفات | Spheres أو Capsules |
| `INT` | shrine، checkpoint، brazier، exit | Cubes مميزة بلون الوظيفة |
| `FX` | Telegraph، Perfect، فتح البوابة | مواد emissive بسيطة ودوائر مسطحة |
| `UI` | هدف المرحلة ومورد الامتصاص | Widgets نصية وأشرطة بدائية |
| `AUD` | الإشارات الصوتية | أصوات placeholder قصيرة |

**ترميز الألوان المؤقت:** البرتقالي للخطر والامتصاص، الأزرق للحفظ والعلاج، الأبيض للمسار والهدف، البنفسجي للـ Elite، والأحمر الداكن للـ Boss.

## 2. أصول P0 — ضرورية للـ Blockout القابل للعب

| المعرّف | الأصل | النوع | الكمية التقريبية | الاستخدام |
|---|---|---|---:|---|
| P0-GEO-01 | جدار قياسي | Cube mesh | 20 نسخة | حدود كل الغرف |
| P0-GEO-02 | أرضية معيارية | Cube mesh | 30 نسخة | المسار الرئيسي |
| P0-GEO-03 | منصة صغيرة ومتوسطة | Cube mesh | 12 نسخة | Broken Bridge والتعلم |
| P0-GEO-04 | حاجز حراري | Cube mesh | 8 نسخ | Gate 01 والاختبار |
| P0-GEO-05 | بوابة مقفلة/مفتوحة | Cube + frame | 6 نسخ | الأبواب الرئيسية |
| P0-ACT-01 | اللاعب | Capsule/Sphere | 1 | اختبار الحركة |
| P0-ACT-02 | Emberling | Sphere | 8 نسخ | التدريب والاختبار |
| P0-ACT-03 | Ember Warden | Sphere كبيرة | 1 | Elite |
| P0-ACT-04 | Ignar | Sphere كبيرة | 1 | Boss |
| P0-ACT-05 | Ember Projectile | Sphere صغيرة | Pool من 12 | المقذوف القابل للامتصاص |
| P0-INT-01 | Absorb Shrine | Cube مضيء | 1 | درس الامتصاص |
| P0-INT-02 | Checkpoint | Cube أزرق | 5 | الحفظ والإعادة |
| P0-INT-03 | Brazier | Cube/Column | 3 | دورة Boss الثانية |
| P0-INT-04 | Exit Gate | Cube كبير | 1 | الخروج |
| P0-INT-05 | Cinder Key | Sphere صغيرة | 1 | مكافأة Elite |
| P0-INT-06 | Ember Sigil | Sphere/Disc | 1 | مكافأة Boss |
| P0-FX-01 | Perfect Telegraph | Ring/Plane | 1 مادة | إشارة نافذة النجاح |
| P0-FX-02 | Absorb Success | Flash plane | 1 مادة | تأكيد Perfect |
| P0-FX-03 | Hazard Volume | Box volume | 10 | مناطق الحرارة والموت |
| P0-UI-01 | Stage HUD | Widget | 1 | الهدف والشحنة |
| P0-UI-02 | Interaction Prompt | Widget | 1 | تفاعل Shrine والبوابات |

## 3. أصول البيئة النهائية المقترحة

تُبنى البيئة النهائية حول قلعة بركانية متآكلة، لكن لا يُشترط إنتاجها قبل اعتماد الـ Blockout. الأولوية للقراءة الوظيفية: شكل الطريق، موضع العدو، وحدود الخطر أهم من كثافة التفاصيل.

| المجموعة | الأصول المقترحة | أولوية |
|---|---|---:|
| طريق الرماد | أرضية رماد، صخور سوداء، آثار أقدام، حواف متكسرة | P1 |
| بوابة القلعة | قوس حجري، مفصلات، نقوش عنصر النار، بوابة داخلية | P1 |
| Courtyard | أعمدة مكسورة، أرضية بلاطات، أحواض جمر، حطام | P1 |
| Furnace Hall | أنابيب، قنوات حمم، جسور معدنية، منصات متحركة | P1 |
| Elite Pit | حلقة حلبة، أعمدة تليغراف، جدار احتجاز | P1 |
| Boss Arena | منصة دائرية، قلب قلعة، ثلاث Braziers، حواف متوهجة | P0/P1 |
| Exit Corridor | ممر حجري، بوابة العناصر، رموز انتقال | P1 |
| Side Room | محراب صغير، حامل Lore، صندوق علاج | P2 |

## 4. أصول الشخصيات والأعداء

| الأصل | المطلوب للـ Blockout | المطلوب للنسخة النهائية | ملاحظات |
|---|---|---|---|
| Player | Capsule/Sphere وحركة أساسية | Mesh اللاعب، Skeleton، Animations | لا تؤجل اختبار الاصطدام |
| Emberling | Sphere مع اتجاه إطلاق | مخلوق صغير ناري، حالات حركة وهجوم | silhouette واضح |
| Ember Warden | Sphere كبيرة | Elite مدرع بالجمر، Stagger animation | يجب تمييزه عن Ignar |
| Ignar | Sphere كبيرة مع مؤشرات | Boss كامل، مرحلتان، animations | يجب أن تبقى Telegraphs واضحة |
| Projectile | Sphere emissive | مقذوف جمر مع Trail وImpact | أصل مركزي قابل لإعادة الاستخدام |

## 5. الأصول البصرية والمؤثرات

| المعرّف | الأصل | المرحلة | معيار الاستخدام |
|---|---|---:|---|
| FX-01 | توهج جمر أساسي | P0 | يوضح مصادر الامتصاص |
| FX-02 | دائرة Perfect Absorb | P0 | تظهر قبل نافذة النجاح |
| FX-03 | وميض نجاح أبيض | P0 | يثبت نتيجة Perfect |
| FX-04 | شرارة امتصاص عادي | P0 | يفرق Normal عن Perfect |
| FX-05 | موجة ضربة أرضية | P1 | هجمة Elite وIgnar |
| FX-06 | انفجار Brazier | P1 | انتقال المرحلة الثانية |
| FX-07 | دخان رماد متحرك | P1 | عمق بصري دون إخفاء المسار |
| FX-08 | سقوط Ember Sigil | P1 | مكافأة Boss |
| FX-09 | فتح بوابة العناصر | P1 | تأكيد نهاية المرحلة |

## 6. الصوت والموسيقى المؤقتة

في الـ Blockout تكفي ملفات قصيرة ذات وظيفة واحدة: نغمة تفاعل Shrine، صوت امتصاص عادي، صوت Perfect Absorb، تحذير Boss، ضربة أرضية، فتح باب، التقاط Sigil، وصوت الخروج. يجب أن يحمل كل حدث صوتاً مميزاً حتى لو استُبدل لاحقاً بالتسجيل النهائي.

| المعرّف | الحدث | أولوية |
|---|---|---:|
| AUD-01 | تفاعل Shrine | P0 |
| AUD-02 | بداية نافذة Perfect | P0 |
| AUD-03 | نجاح Perfect | P0 |
| AUD-04 | فشل الامتصاص | P1 |
| AUD-05 | Telegraph Ignar | P0 |
| AUD-06 | سقوط Elite | P0 |
| AUD-07 | سقوط Ignar | P0 |
| AUD-08 | التقاط Cinder Key | P1 |
| AUD-09 | التقاط Ember Sigil | P0 |
| AUD-10 | فتح Exit Gate | P0 |
| AUD-11 | طبقة موسيقية للـ Boss | P1 |

## 7. واجهة المستخدم

تحتاج المرحلة إلى HUD صغير لا ينافس القراءة البصرية. العناصر الأساسية هي شريط أو مؤشر `EmberCharge`، حالة الهدف الحالي، Prompt للتفاعل، وFeedback مستقل لـ Perfect Absorb. في شاشة نهاية المرحلة تظهر المدة، عدد Perfect Absorbs، الأسرار، وحالة Boss.

## 8. معايير تسمية ومجلدات

تستخدم الأصول البادئات التالية: `SM_` للمجسمات، `M_` للمواد، `MI_` للمواد المثيلة، `T_` للخامات، `NS_` للمؤثرات، `SFX_` للصوت، `WBP_` للواجهات، و`BP_` للـ Blueprints. يقترح حفظ أصول المرحلة في:

```text
/Content/EchoOfElements/Stage1/Environment
/Content/EchoOfElements/Stage1/Characters
/Content/EchoOfElements/Stage1/Blueprints
/Content/EchoOfElements/Stage1/FX
/Content/EchoOfElements/Stage1/Audio
/Content/EchoOfElements/Stage1/UI
```

## 9. بوابة استبدال الـ Placeholder

لا يُستبدل أي Cube أو Sphere لمجرد التجميل. يستبدل الأصل عندما يثبت اختبار القبول أن الحجم، الاصطدام، الـ silhouette، وقراءة الـ Telegraph صحيحة. عند الاستبدال يجب الحفاظ على نقاط الـ Spawn، أسماء الـ Sockets، Tags، وCollision channels حتى لا ينكسر منطق Blueprint.

## 10. تعريف الجاهزية

تكون قائمة الأصول جاهزة للانتقال إلى الإنتاج الفني عندما يعمل المسار الكامل بأصول P0 فقط، ويجتاز اللاعب معايير الزمن، وتكون مصادر الامتصاص والمخاطر مقروءة بالألوان والمؤثرات المؤقتة. الأصول P1 وP2 يمكن جدولتها بعد تثبيت المساحات وقواعد القتال.

## References

[1]: https://github.com/jolianstori-oss/echo-of-elements/blob/main/Docs/Stage1/Stage1_Blockout.md "Stage 1 Blockout"
[2]: https://github.com/jolianstori-oss/echo-of-elements/blob/main/docs/01-unreal-architecture-v0.1.md "Unreal Architecture v0.1"

القائمة تنفيذية ومخصصة للمرحلة الأولى؛ الكميات تقريبية وتُراجع بعد أول تمريرة Greybox.

**المؤلف:** Manus AI  
**الإصدار:** Stage 1 Asset List v0.1

[1] [2]
