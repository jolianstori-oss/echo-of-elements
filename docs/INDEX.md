# مشروع لعبة Unreal Engine

## مراجع هنداوي

- [[01-references/hindawi/arts-globalization_85183841.pdf|الفنون والآداب تحت ضغط العولمة]] — عالم اللعبة والثقافة.
- [[01-references/hindawi/soft-hands_30706163.pdf|الأيدي الناعمة]] — الحوار والمشهد المسرحي.
- [[01-references/hindawi/book-of-illusions_49140393.pdf|كتاب الأوهام]] — الخيال والهوية وبناء الألغاز.
- [[01-references/hindawi/cosima_97594728.pdf|كوزيما]] — مادة أدبية للشخصيات والعلاقات.

## وثائق اللعبة

- [[00-game-design-bible-v0.1|Game Design Bible v0.1 — صدى الأثير]] — الرؤية، 12 مرحلة، العناصر، الزعماء، القدرات، الأرقام، التفاعلات.
- [[01-unreal-architecture-v0.1|Unreal Architecture v0.1]] — C++/Blueprint/GAS، AI، Save/Load، Replication، واختبارات التعددية.
- [[02-implementation-backlog-v0.1|Implementation Backlog v0.1]] — الـVertical Slice، المهام، بوابات القرار، ومعايير القبول.
- [[03-balance-sheet-v0.1|Balance Sheet v0.1]] — ضرر كل حركة، صحة الأعداء، الزعماء، البيئة، والتفاعلات.
- [[04-character-roster-v0.1|Character Roster v0.1]] — نِبراس، فينو، وبقية الشخصيات وأدوارهم القتالية.
- [[05-steam-launch-plan-v0.1|Steam Launch Plan v0.1]] — onboarding، الصفحة، الـComing Soon، الـBuild، التسويق، والإطلاق.
- [[06-cpp-drop-in-pack|C++ Drop-in Pack]] — كود Weak Points، ذكاء نِبراس، السموم، التفاعلات، والاختبارات.

## مهارات

- Anthropic Skills للكتابة والوثائق: https://github.com/anthropics/skills
- Superpowers للتخطيط وTDD والتحقق: https://github.com/obra/superpowers
- Browser Use للبحث في وثائق Unreal: https://github.com/browser-use/browser-use
- Hermes: `systematic-debugging`, `test-driven-development`, `github-pr-workflow`, `docx`, `pdf`

## قاعدة العمل

كل ميزة لعبة تخرج معها Game Design Note، كود/Blueprint أو خطوات دقيقة، واختبار قبول. لا نخلط مراجع الأدب مع أصول محمية أو assets غير مرخصة.

## مرحلة قلعة الجمر والأصول المستوردة

- [مرحلة قلعة الجمر — خطة التنفيذ](stages/fire-castle/Stage1-FireCastle.md) — خطة الـVertical Slice، المراحل، والاختبارات ومعايير القبول.
- [دليل خامات العرض النهائي — قلعة الجمر](stages/fire-castle/Fire-Castle-Final-Materials-Guide.md) — إعداد خرائط PBR والمواد ومسارات الاستيراد.
- [فهرس حزمة قلعة الجمر](../Assets/FireCastle/README.md) — الأرشيفات الأصلية، النماذج، الخامات، المعاينات، وخطوات الاستيراد الآمن.
- [الوثائق التأسيسية لصدى الأثير](foundations/sada-al-athir/) — ملفات عربية مستوردة للمراجعة قبل اعتمادها في الوثائق الإصدارية.
- [مصادر مكتبة المشروع المستوردة](imported-library/) — النسخ الأصلية من وثائق README والمساهمة ومدونة السلوك الواردة ضمن التسليم.

## إرشادات العمل الآلي

- [تعليمات الوكيل](../AGENTS.md) — قواعد التخطيط والتنفيذ والتحقق وإدارة الأصول لهذا المستودع.
- [قوالب القضايا](../.github/ISSUE_TEMPLATE/) — قوالب المهام والأعطال وطلبات الميزات المستخدمة لتوثيق العمل القابل للمراجعة.

> الملفات المضافة إلى `Assets/` هي مصادر وأرشيفات قابلة للمراجعة؛ لا تعني جاهزيتها للاستيراد أو النشر ما لم توثق إعدادات الاستيراد والترخيص والتحقق داخل المحرك.
