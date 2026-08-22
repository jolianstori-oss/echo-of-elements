# ADAPTIVE_MUSIC.md — نظام موسيقى تكيفي لـ Echo of Elements — صدى الأثير

هذا المستند يحدد التصميم القابل للتنفيذ لنظام موسيقى تكيفي يعمل داخل Unreal Engine 5.8، ويخدم الحلقة الأساسية: الاستكشاف → أتباع بعنصر جزئي → قتال/لغز → زعيم بثلاث مراحل → امتصاص → اختبار قصير → Hub. يعتمد على طبقات موسيقية ديناميكية، انتقالات مضبوطة زمنياً، وStingers متزامنة مع أحداث اللعب الجوهرية: Stagger وAbsorb، مع حالات إضافية للهدوء، خسارة اللاعب، والعودة إلى الـHub.

## 1) أهداف النظام ومبادئ المزج

الغرض هو إبراز هوية كل مملكة/عنصر مع الحفاظ على اتساق زمني ومقامي بين الحالات الخمس القتالية. تبنى المقطوعات على حلقات بطول 8 مقاطع/Measures في توقيع 4/4 افتراضياً، مع سرعة BPM تتدرج صعوداً بحسب الحالة. تدار الكثافة بمزج خماسي الطبقات في كل حالة، وتُقاس القرارات الانتقالية على حدود المقاطع لتحافظ على القطع النظيف والإحساس النبضي.

- التزامن الموسيقي: كل انتقال حالة يقاس إلى bar أو نصف bar باستخدام Quartz Clocks؛ يمنع القطع في منتصف إيقاع الطبل الرئيسي.
- تجانس المقام: تُحفظ الطبقات الأساسية في مقام القصر/المملكة، وتنتقل الحالات عبر تبدلات مدروسة في الديناميكية والطبقة الآلية لا عبر تغييرات فجائية في المقام.
- ربط اللعب: يربط النظام طبقات التوتر بمقياس Stagger للأعداء والزعماء، ويُطلق Stingers قصيرة وعالية الوضوح عند انهيار القناع العنصري، فتح نافذة الامتصاص، ونجاح/فشل Absorb، دون كسر تدفق الموسيقى.

## 2) بنية التنفيذ في Unreal Engine 5.8

يبنى النظام بالكامل بأدوات Unreal الأصلية.

- توقيت ومزامنة:
  - Quartz Subsystem: ساعة رئيسية Music_Master بوضوح 480 PPQ، وإشارات Quantization على 1 Bar، 1/2 Bar، 1 Beat.
  - Transport لكل حالة على Clock موحّد لتأمين اصطفاف الطبقات بين الحالات.

- توليد ومزج:
  - MetaSounds لكل حالة/مملكة بصيغة MS_MUS_[Realm]_[State].ms: تستقبل Parameters للطبقات الخمس (0..1)، وIntensity، وStagger، وAbsorb_State.
  - Submix Routing: MUS_BUS_Master → MUS_BUS_Element (حسب المملكة) → MUS_BUS_State → Output. قناة Stinger_Bus موازية مع Duck تلقائي للـState Bus عند إطلاق Stinger.

- بيانات التحكم:
  - Primary Data Asset: DA_MusicRouting يحتوي تعيين المملكة/الحالة إلى أصول MetaSound، وBPM، والمقام، وإعدادات Reverb.
  - Gameplay Tags Events: يستخدم النظام إشارات من Gameplay Ability System وElementReactionSubsystem عبر Tags موحدة، مثل:
    - Music.State.Exploration / Skirmish / Boss.P1 / Boss.P2 / Boss.P3
    - Music.Event.Stagger.25 / .50 / .75 / .100
    - Music.Event.Absorb.WindowOpen / Start / Success / Fail
    - Music.Event.Reaction.[اسم التفاعل المعتمد]
  - Hysteresis: حد أدنى 4 ثوانٍ بقاء قبل السماح بالعودة من Skirmish إلى Exploration لتفادي الخفقان.

- مزج تكيفي:
  - Audio Modulation: معلمات ديناميكية للتحكم في Gain، Filter Cutoff، وDistortion لطبقات الآلات ضمن نطاق آمن لا يغير الهوية المقامية.

## 3) حالات القتال الخمس — الطبقات والأدوار

تعتمد كل حالة على خمس طبقات ثابتة البنية، تختلف آلياً بحسب المملكة. القيم الافتراضية للسرعة والمزج يمكن تعديلها لكل مملكة عبر DA_MusicRouting، لكن بنية الطبقات تبقى موحّدة.

### 3.1 الاستكشاف (Exploration) — 84–96 BPM

- الهدف: دعم الفضول وسماع البيئة دون صخب، مع لمحات لونية من عنصر المرحلة.
- الطبقات:
  1) Bed/Texture: سجاد صوتي محيطي منخفض، يلمّح إلى عنصر المملكة (هواء مهتز، نيران خافتة...).
  2) Light Pulse: نبض إيقاعي هش على Percussion خفيف/Organic.
  3) Harmonic Drone: وتر مقامي طويل يثبت هوية المقام.
  4) Motif Hints: شذرات لحنية متقطعة تلمّح إلى موضوع الزعيم.
  5) Elemental Foley Musique: مؤثرات بيئية موسيقية قصيرة تتبع حركة آرين الخفيفة والقفزات.
- قواعد الطبقات: تبدو الطبقة 2 و4 فقط عند نشاط اللاعب (جري/تسلق)، وتهدأ إلى 0.3–0.4 Gain عند التوقف >3 ثوانٍ.

### 3.2 الاشتباك (Skirmish) — 104–118 BPM

- الهدف: رفع التوتر ضد أتباع يملكون نسخة ناقصة من قدرات الزعيم.
- الطبقات:
  1) Groove Base: طبلة رئيسية وخط إيقاعي واضح.
  2) Harmonic Ostinato: تتابع أوستيناتو يخلق دفعاً مستمراً.
  3) Counter Percussion: نقرات مضادة/سنكوب لعكس حركات الأتباع.
  4) Lead Shards: لُقيم لحنية سريعة تستجيب لردّات الفعل المعتمدة.
  5) Elemental FX Perc: نقرات/Whooshes ملونة بالعُنصر لتمييز تفاعلات Inferno وSteam Burst وغيرها.
- قواعد الطبقات: ترتفع الطبقة 3 عند وصول Stagger الفردي لأي تابع إلى ≥50% لمدة 2 Bars، ثم تعود. يمنع إطلاق Absorb Stinger على الأتباع الأحياء وفق القاعدة الأخلاقية؛ تُستخدم فقط عند تحرير Energy Mote بعد انهيار القناع.

### 3.3 Boss Stage 1 — 120–128 BPM

- الهدف: تعريف موضوع الزعيم بنسخة أقل كثافة، وفتح مساحة تعلم.
- الطبقات:
  1) Low Strings/Drums: قاعدة ثقيلة بمود حذر.
  2) Harmonic Swells: انتفاخات هارمونية متزامنة مع Telegraphs.
  3) Boss Motif A: لحن رئيسي بصيغة سؤال.
  4) Elemental Signature: آلة مميزة للعنصر (مثلاً نفخ معدني للنار، Flute هوائي للهواء).
  5) Tension Noise: طبقة حبيبية أو معدنية خافتة لإحساس الخطر.
- قواعد الطبقات: عند Music.Event.Stagger.25 تفتح الطبقة 2 إلى 0.7 Gain، وعند .50 تدخل الطبقة 3 بوضوح، وعند .75 تُرفع الطبقة 5 قليلاً لإشعار قرب الانهيار.

### 3.4 Boss Stage 2 — 132–142 BPM

- الهدف: تصعيد الإيقاع وتبديل الإجابة اللحنية.
- الطبقات:
  1) Hybrid Drums: إضافة طبول ثانوية/Triplets بين النبضات.
  2) Harmonic Drive: تبديل هارموني أسرع يضاعف الإحساس بالدفع.
  3) Boss Motif B: إجابة لحنية أكثر حدة/زوايا.
  4) Elemental Counterlines: خطوط لحنية قصيرة تعكس قدرات الزعيم الجديدة.
  5) Impact FX: ضربات Transition على حدود المقاطع.
- قواعد الطبقات: تتبدل Motif A→B على Bar Boundary عند نزول صحة الزعيم إلى 66%. عند Music.Event.Stagger.100 يُسكت الطبقة 1 لمدة نصف Bar قبل إطلاق Stinger الانهيار، لتسليط الضوء على النافذة.

### 3.5 Boss Stage 3 / Ultimate — 146–160 BPM

- الهدف: أقصى كثافة، مساحة لظهور Ultimate لدى اللاعب وتبدلات الزعيم النهائية.
- الطبقات:
  1) Full Kit + Low End: مجموعة طبول كاملة وSub متحكم به.
  2) Harmonic Arps: Arpeggios سريعة تخلق دوّامة توتر.
  3) Boss Motif C (Final): صيغة الحسم، أعرض في المجال.
  4) Elemental Blaze/Storm: طبقة عنصر مفرطة النطاق (كورس نار/رياح/برق... حسب المملكة).
  5) Spark Layer: حبيبات/Clicks عالية تُفتح فقط أثناء Ultimate لدى اللاعب.
- قواعد الطبقات: أثناء تفعيل Ultimate لدى اللاعب ترتفع الطبقة 5 إلى 1.0 وتُخفت الطبقة 2 بنسبة 3 dB لتفريغ حيز الترددات العالية. عند Absorb.Success تُطفأ الطبقات 1–4 خلال 250 ms Crossfade بعد Stinger الفوز، وتبقى الطبقة 5 تلمع 1.5 ثانية قبل خروج المرحلة.

## 4) Stingers، التوقيت، والتزامن مع Stagger وAbsorb

الـStingers أصوات قصيرة (300–1200 ms) ذات أولوية عليا، تُحقن عبر Stinger_Bus وتُقاس إلى أقرب Beat أو Half-Bar بحسب الحدث.

| الحدث | شرط الإطلاق | طول نموذجي | قياس/Quantization | قاعدة المزج |
|---|---|---:|---|---|
| دخول اشتباك | أوّل عدو يثبّت Combat Tag | 500 ms | 1/2 Bar | Duck لحافّة 3 dB على State Bus |
| دخول Boss P1 | تفعيل بوابة الزعيم | 800 ms | 1 Bar | Crossfade من Skirmish في 2 Bars |
| Stagger 25/50/75 | عبور العتبات | 300 ms | 1 Beat | Pulse Accent فقط |
| Stagger Break 100 | فتح نافذة 5 ثوانٍ | 900 ms | 1/2 Bar + Silence 1/8 قبله | إسكات طبلة رئيسية 1/2 Beat |
| Absorb.WindowOpen | مباشرة بعد Stagger Break | 450 ms | 1/4 Bar | High Bell Cue، لا Duck |
| Absorb.Start | بدء الامتصاص | 600 ms | 1 Beat | Gate خفيف للطبقات العلوية 1/4 Bar |
| Absorb.Success | امتصاص ناجح (غير الأتباع الأحياء) | 1000 ms | 1/2 Bar | Kill طبقات الحالة في 250 ms، فتح Bloom Reverb 1 s |
| Absorb.Fail | انقضاء النافذة/قَطع | 500 ms | 1/2 Bar | إعادة الطبقات إلى ما قبل الـWindow خلال 1 Bar |
| Perfect Absorb | داخل نافذة P-Frame المحددة للمرحلة | 700 ms | 1 Beat | Pitch Uplift +3 Semitones قصير |

ملاحظات تطبيقية:
- النافذة الأخلاقية: لا يُطلق Absorb.Success Stinger على أتباع أحياء. يقتصر على الزعماء أو الأتباع بعد انهيار القناع العنصري وإطلاق Energy Mote فقط.
- الفشل لا يعيد القتال من الصفر؛ موسيقياً يعاد 8% فقط من طبقة التوتر عبر خفض Intensity Parameter بمقدار 0.08، لمحاكاة قاعدة الـStagger.

## 5) حالات إضافية: الهدوء، خسارة اللاعب، والعودة إلى الـHub

هذه الحالات غير قتالية لكنها أساسية لحياكة الإيقاع العاطفي للحملة.

### 5.1 الهدوء (Calm Aftermath)

- سياق: بعد معركة قصيرة أو حل لغز بسيط.
- سلوك: خفض BPM الوهمي عبر سحب الطبلة إلى 0 وتوسيع الـReverb في Submix بنسبة 20% لمدة 4 Bars، ثم العودة إلى Exploration Layers خلال 2 Bars. لا تغيّر المقام.

### 5.2 خسارة اللاعب (Player Defeat)

- Stinger: خماسي نغمي هابط مع Sub Drop قصير (450–700 ms)، يقاس إلى 1 Beat فور نفاد صحة آرين.
- SFX-Music مزج: Duck عام 6 dB للـState Bus، إبقاء Stinger واضحاً، ثم صمت 1.5 ثانية قبل إعادة تحميل Checkpoint. لا يُقطع Transport الرئيس؛ يستأنف من بداية Segment التالية عند العودة.

### 5.3 العودة إلى الـHub

- انتقال: عند دخول الـHub، Crossfade من الحالة الحالية إلى MS_MUS_Hub_Main في 2 Bars على 92 BPM.
- طبقات الـHub:
  1) Warm Bed: قماشة دافئة تشير إلى الأمان المؤقت.
  2) Light Rhythm: نبض هادئ يرافق واجهة لينا/التحميل.
  3) Memory Motifs: إشارات لحنية ترتبط بسُلاف وذاكرة العالم.
  4) Crafting Hints: نقرات خشبية خفيفة عند إدارة الـLoadout.
  5) Visitor Tail: طبقة زائرة قصيرة عند ظهور نور أو مارد أو غيرهم بحسب تقدم المراحل.

## 6) خرائط لونية آلية حسب المملكة/العنصر

المقطع التالي يربط هوية كل عنصر بحزمة آلات رئيسية ومفردات لونية. تُطبق على طبقات الحالات الخمس تلقائياً عبر DA_MusicRouting.

| # | المملكة/العنصر | آلات مميزة | ملمس إيقاعي | ألوان هارمونية |
|---:|---|---|---|---|
| 1 | قلعة الجمر — النار | طبول جلدية/Metal Hits/Brass خشن | دفع مستقيم وFlams | درجات حارة، صيغ مينورية قوية |
| 2 | سراديب المد — الماء | Marimba/Glass/Strings ليّنة | تموّج Swing خفيف | تبدلات مدارية مع Sus4 |
| 3 | سهول الانشقاق — التراب | Taikos منخفضة/Baritone Guitar | ثِقَل على الضربة الأولى | Fifths مفتوحة وجذور ثابتة |
| 4 | مقابر الجبل — الصخر | Granular Bowed Metals | Patterns بطيئة متكسّرة | Pedal Drone وصعودات قصيرة |
| 5 | مدينة الريح — الهواء | Flutes/Whistles/Aeolian Textures | نقرات خفيفة سريعة | تلوينات Lydian خافتة |
| 6 | مرصد العاصفة — البرق | Synth Plucks/Arps/Noisy Leads | سنكوب خاطف | تبدلات حادة ونبرات حادة |
| 7 | قصر الشتاء — الجليد | Celesta/High Strings/Chimes | نقرات بلورية | تآلفات شفافة وSpace واسع |
| 8 | الغابة — الطبيعة | Hand Perc/Seeds/Woodwinds | Grooves عضوية | ألوان دورية مودالية |
| 9 | بحر الرمال — الرمل | Frame Drums/Shakers | Patterns متوالية/Triplets | توترات معلّقة وكادنس متأخر |
| 10 | مصنع الحديد — المعدن | Industrial Perc/Anvils | نبض ميكانيكي | Power Chords مشذّبة |
| 11 | معبد الطيف — الضوء | Harp/Choir/Glass Harmonica | حبيبات مضيئة | تبدلات رقيقة على درجات مضيئة |
| 12 | قلب السقوط — الجاذبية | Low Synths/Sub Pulses | نبض ثقيل متقطّع | مدوّرات بطيئة وهبوط Chromatic |

## 7) Stingers تفاعلات العناصر المعتمدة

يرد النظام على التفاعلات الأربعة عشر المعتمدة فقط عبر طبقة Elemental FX Perc والـStingers الملونة التالية. كل Stinger 250–500 ms ويقاس إلى 1 Beat. لا يُضاف أي تفاعل آخر.

| التفاعل | ملمس/آلة مميِّزة | قاعدة إطلاق |
|---|---|---|
| Inferno | Brass Rip + Flame Whoosh | عند تراكم/اشتعال موسّع |
| Steam Burst | Valve Burst + High Glass Ping | عند تلاقي ماء/نار |
| Magma | Sub Gurgle + Low Tom | عند ذوبان ترابي/ناري |
| Thermal Shock | Ice Shatter + Metal Ping | تبدّل حراري حاد |
| Conductive | Electric Zap + Short Pluck | وصل قوسي/برقي |
| Permafrost | Frost Creak + Bell Low | تجمّد تراكمي |
| Quicksand | Sand Bristle + Low Rattle | هبوط أرضي |
| Duststorm | Air Rush + Shaker Swell | دوّامة غبار |
| Resonant Shatter | Crystal Break + Sine Hit | كسر متوافق |
| Scorched Bloom | Charred Bloom + Wood Knock | ذبول محروق |
| Overload | Spark Burst + Noise Pop | تحميل زائد معدني |
| Lens Collapse | Glass Implode + Choir Ah | انهيار بصري/ضوئي |
| Sandstorm | Long Air Roar + Frame Drum | عاصفة رملية شاملة |
| Compression | Gravity Thump + Low Suck | ضغط جاذبي مع أي عنصر |

ملاحظة: تفاعل Compression لا يزيد الضرر إلا إذا كان للعنصر تفاعل مسجّل؛ موسيقياً يُطلق Thump قصير دون مضاعفة إضافية.

## 8) قواعد الانتقال بين الحالات

- الدخول إلى Skirmish:
  - شرط: تثبيت Combat Tag على ≥1 عدو قريب.
  - توقيت: الانتقال على أول 1 Bar Boundary.
  - مزج: رفع Groove Base إلى 0.8 خلال 2 Beats.

- Skirmish إلى Exploration:
  - شرط: 4 ثوانٍ بلا عدو مرئي/مستشعر + لا Projectile وارد.
  - توقيت: 1 Bar Boundary مع Fade 1.5 s.
  - تهدئة: تعطيل Elemental FX Perc أولاً، ثم Counter Percussion.

- الدخول إلى Boss P1:
  - شرط: تفعيل بوابة الزعيم.
  - تسليم لحن: استبدال Motif Hints بـBoss Motif A فور الانتقال.

- Stage 1→2:
  - شرط: صحة الزعيم ≤66%.
  - توقيت: 1 Bar Boundary، إطلاق Impact FX Stinger، تبديل Motif A→B.
  - Stagger Sync: في حال عبور Stagger 75% قبل العتبة الصحية، يُجهّز تبديل الطبقة 3 لكنه ينتظر العتبة الصحية.

- Stage 2→3:
  - شرط: صحة الزعيم ≤33% أو فتح قدرة الزعيم النهائية.
  - توقيت: 1/2 Bar Boundary لتبدو أسرع.
  - Ultimate لدى اللاعب: فتح Spark Layer فور التفعيل، وإبقاؤها Locked إلى نهاية Ultimate + 1 Beat Release.

- Stagger Break/Window:
  - قبل Stinger: إسكات Groove 1/8 Bar لإبراز الانكسار.
  - أثناء النافذة (5 ثوانٍ): تثبيت Intensity عند القيمة السابقة، منع انتقالات حالة جديدة إلا Absorb.Success/Fail.

- Absorb.Success:
  - تسليم: Stinger نجاح، ثم Drop مُتحكّم للطبقات إلى 0 خلال 250 ms، فتح Bloom Reverb 1 s، ثم تسليم إلى اختبار قصير أو Hub بحسب تصميم المرحلة.

- Absorb.Fail:
  - استرجاع: إعادة الطبقات إلى الحالة قبل النافذة في 1 Bar، بلا Stinger انتصار.

## 9) مصفوفة الممالك/الحالات — أصول قابلة للتنفيذ

يعرض الجدول أسماء الأصول القياسية داخل Unreal. يمكن تعديل السرعات والمقامات عبر DA_MusicRouting دون كسر التعيين.

| # | المملكة/العنصر | Exploration | Skirmish | Boss P1 | Boss P2 | Boss P3 | Calm | Loss | Hub Return |
|---:|---|---|---|---|---|---|---|---|---|
| 1 | قلعة الجمر — النار | MS_MUS_Fire_Expl | MS_MUS_Fire_Skrm | MS_MUS_Fire_B1 | MS_MUS_Fire_B2 | MS_MUS_Fire_B3 | MS_MUS_Fire_Calm | MS_MUS_Loss_Generic | MS_MUS_Hub_Return |
| 2 | سراديب المد — الماء | MS_MUS_Water_Expl | MS_MUS_Water_Skrm | MS_MUS_Water_B1 | MS_MUS_Water_B2 | MS_MUS_Water_B3 | MS_MUS_Water_Calm | MS_MUS_Loss_Generic | MS_MUS_Hub_Return |
| 3 | سهول الانشقاق — التراب | MS_MUS_Earth_Expl | MS_MUS_Earth_Skrm | MS_MUS_Earth_B1 | MS_MUS_Earth_B2 | MS_MUS_Earth_B3 | MS_MUS_Earth_Calm | MS_MUS_Loss_Generic | MS_MUS_Hub_Return |
| 4 | مقابر الجبل — الصخر | MS_MUS_Rock_Expl | MS_MUS_Rock_Skrm | MS_MUS_Rock_B1 | MS_MUS_Rock_B2 | MS_MUS_Rock_B3 | MS_MUS_Rock_Calm | MS_MUS_Loss_Generic | MS_MUS_Hub_Return |
| 5 | مدينة الريح — الهواء | MS_MUS_Air_Expl | MS_MUS_Air_Skrm | MS_MUS_Air_B1 | MS_MUS_Air_B2 | MS_MUS_Air_B3 | MS_MUS_Air_Calm | MS_MUS_Loss_Generic | MS_MUS_Hub_Return |
| 6 | مرصد العاصفة — البرق | MS_MUS_Elec_Expl | MS_MUS_Elec_Skrm | MS_MUS_Elec_B1 | MS_MUS_Elec_B2 | MS_MUS_Elec_B3 | MS_MUS_Elec_Calm | MS_MUS_Loss_Generic | MS_MUS_Hub_Return |
| 7 | قصر الشتاء — الجليد | MS_MUS_Ice_Expl | MS_MUS_Ice_Skrm | MS_MUS_Ice_B1 | MS_MUS_Ice_B2 | MS_MUS_Ice_B3 | MS_MUS_Ice_Calm | MS_MUS_Loss_Generic | MS_MUS_Hub_Return |
| 8 | الغابة — الطبيعة | MS_MUS_Nature_Expl | MS_MUS_Nature_Skrm | MS_MUS_Nature_B1 | MS_MUS_Nature_B2 | MS_MUS_Nature_B3 | MS_MUS_Nature_Calm | MS_MUS_Loss_Generic | MS_MUS_Hub_Return |
| 9 | بحر الرمال — الرمل | MS_MUS_Sand_Expl | MS_MUS_Sand_Skrm | MS_MUS_Sand_B1 | MS_MUS_Sand_B2 | MS_MUS_Sand_B3 | MS_MUS_Sand_Calm | MS_MUS_Loss_Generic | MS_MUS_Hub_Return |
| 10 | مصنع الحديد — المعدن | MS_MUS_Metal_Expl | MS_MUS_Metal_Skrm | MS_MUS_Metal_B1 | MS_MUS_Metal_B2 | MS_MUS_Metal_B3 | MS_MUS_Metal_Calm | MS_MUS_Loss_Generic | MS_MUS_Hub_Return |
| 11 | معبد الطيف — الضوء | MS_MUS_Light_Expl | MS_MUS_Light_Skrm | MS_MUS_Light_B1 | MS_MUS_Light_B2 | MS_MUS_Light_B3 | MS_MUS_Light_Calm | MS_MUS_Loss_Generic | MS_MUS_Hub_Return |
| 12 | قلب السقوط — الجاذبية | MS_MUS_Grav_Expl | MS_MUS_Grav_Skrm | MS_MUS_Grav_B1 | MS_MUS_Grav_B2 | MS_MUS_Grav_B3 | MS_MUS_Grav_Calm | MS_MUS_Loss_Generic | MS_MUS_Hub_Return |

مرفقات التنفيذ:
- Stinger Assets: SC_STG_[Event].cue (مثال: SC_STG_StaggerBreak، SC_STG_AbsorbSuccess).
- Submixes: SUB_MUS_Master، SUB_MUS_Elements_[Realm]، SUB_MUS_State، SUB_MUS_Stinger.
- Data Asset: DA_MusicRouting.uasset يحمّل لكل مملكة: BPM الاستكشاف/الاشتباك/الزعيم، المقام الأساسي، إعدادات Reverb/Delay، وخريطة الطبقات إلى الآلات المحددة أعلاه.

## 10) اختبارات قبول

- انتقالات نظيفة: جميع الانتقالات بين Exploration ↔ Skirmish ↔ Boss P1/P2/P3 تحدث عند حدود Bars بدون تقطيع سمعي.
- تزامن Stagger: عند Music.Event.Stagger.100 تُسكت الطبلة الرئيسية لمدّة 1/8 Bar قبل Stinger، وتعود بسلاسة بعد Absorb.Fail أو تنطفئ كلياً بعد Absorb.Success.
- نافذة الامتصاص: يمتنع النظام عن إطلاق أي Absorb.Success Stinger على الأتباع الأحياء؛ لا يُسمح سوى بعد انهيار القناع العنصري أو مع الزعماء ضمن النافذة.
- كثافة الطبقات: لا تتجاوز خمس طبقات فعّالة في أي حالة؛ Spark Layer لا تُفتح إلا أثناء Ultimate.
- زمن الاستعادة: بعد خسارة اللاعب، يعود النظام إلى بداية Segment موسيقية كاملة عند الاستئناف، متزامناً مع 1 Bar Countdown غير مسموع.

بهذا التصميم، تصبح الموسيقى جزءاً فاعلاً من قراءة اللاعب لمقاصد العالم وقواعده، فتشدّ على توترات Stagger وطقوس Absorb دون الإخلال بأسس اللعب أو أخلاقياته، وتؤطر هويّة كل مملكة بعلامات سمعية متّسقة يمكن تنفيذها مباشرة داخل Unreal Engine 5.8.
