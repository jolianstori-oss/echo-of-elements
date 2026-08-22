# METASOUND_IMPL — مواصفات تنفيذ MetaSounds في UE5.8

## بنية الرسوم المطلوبة

| Graph | المدخلات | المخرجات | قاعدة التنفيذ |
|---|---|---|---|
| `MS_Ability_OneShot` | ElementTag, AbilityId, Intensity, Seed | SFX Bus | يختار طبقات Attack/Body/Tail ويمنع تكرار آخر Seed. |
| `MS_Reaction` | SourceTag, TargetTag, AreaSize, Phase | SFX + Impact Send | يقرأ التفاعلات المعتمدة فقط ويضبط الذيل حسب المساحة. |
| `MS_Absorb` | Perfect, ResonanceGain, BossFlag | SFX + Voice Duck | يرفع النواة في Perfect Absorb ويترك مساحة لصوت اللاعب. |
| `MS_Environment_Loop` | BiomeId, Distance, DangerState | Ambience Bus | يبدل طبقات المكان عند الاقتراب من خطر أو لغز. |
| `MS_UI` | UiEvent, Priority | UI Bus | قصير، أحادي، ولا ينافس تلغراف القتال. |
| `MS_Music_Stinger` | StateFrom, StateTo, BarPosition | Music Bus | يطلق Stinger على bar أو نصف bar فقط ما لم يكن خطر فوري. |

## العشوائية ومنع التكرار

تستعمل كل مجموعة Variations ثلاثة أصوات على الأقل، مع Pitch عشوائي ±3% وGain عشوائي ±1.5 dB فقط. يحتفظ Graph بآخر Seedين ويمنع تكرارهما. لا تطبق العشوائية على إشارات الخطر القاتلة أو Perfect Absorb؛ يجب أن تبقى هذه قابلة للتعرّف فوراً.

## الـBus والـSidechain

ترتيب الـBus هو `Music` و`SFX` و`Ambience` و`Voice` و`UI`. عند تلغراف زعيم حاسم، يخفض Sidechain موسيقى المعركة 3 dB لمدة 350ms ويرفع وضوح SFX المتوسط. عند حوار قصير، ينخفض Ambience 2 dB ولا يخفض SFX الذي يحمل تحذيراً. يمنع الـSidechain ضخّ الصوت في المشاهد القصيرة؛ يستخدم fade ثابتاً لا يتجاوز 120ms.

## الأداء والاختبار

يحدد Concurrency لكل مجموعة: هجمات عامة 8، تفاعلات منطقة 4، UI 3، أصوات Perfect Absorb 1. توثق كل لقطة باسم `Element_Ability_Phase_Variation`، وتختبر على Listen Server وعميل للتأكد أن التوقيت السمعي لا يمنح العميل سلطة على Health أو Core Shard. يسجل Telemetry وقت الإطلاق، Tag، وعدد الأصوات المسروقة، ولا يسجل بيانات اللاعب الشخصية.
