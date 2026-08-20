---
title: "Echo of Elements — Steam Launch Plan"
version: "0.1"
status: "خطة نشر أولية؛ تتطلب تحديثاً عند فتح Steamworks"
target: "Windows/Steam first; Steam Deck testing after PC stability"
---

# خطة النشر على Steam

## 0. استراتيجية الإصدار

- **المنصة الأولى:** Windows على Steam.
- **النسخة الأولى:** Single-player كاملة، 12 مرحلة، 12 زعيم.
- **التعددية:** لا نربط إطلاق النسخة الأولى بإنهاء Co-op؛ نطلقه لاحقاً كتحديث عندما ينجح اختبار الشبكة.
- **اللغات:** English وArabic للواجهة والنصوص والترجمة؛ الصوت الإنكليزي أو غير الصوتي أولاً، ثم نضيف صوتاً عربياً إذا أثبت الاختبار فائدته.
- **الهوية:** لعبة Action بعنصر امتصاص وتفاعلات؛ لا نسوقها كـ«لعبة عناصر أخرى» فقط.
- **السعر المقترح:** `USD 14.99–19.99` كتقدير أولي؛ القرار النهائي بعد مقارنة ألعاب مستقلة مشابهة واختبار الـDemo، وليس وعداً ثابتاً.

## 1. Steamworks onboarding الرسمي

Valve تطلب توقيع الأوراق الرقمية، دفع رسم Steam Direct لكل App، استكمال بيانات البنك والضرائب والتحقق من الهوية قبل تجهيز الإصدار.[1][2]

الحقائق التشغيلية الحالية التي يجب وضعها في الميزانية:

- رسم Steam Direct هو **100 دولار أمريكي أو ما يعادله لكل App جديد**.[1]
- الرسم غير قابل للاسترداد، لكنه يصبح قابلاً للاسترداد في دفعة لاحقة بعد وصول المنتج إلى **1000 دولار Adjusted Gross Revenue** حسب شروط Steam.[1]
- توجد فترة انتظار **30 يوماً بين دفع رسم التطبيق وإمكانية إصدار اللعبة** لأول العناوين بحسب صفحة onboarding.[2]
- يجب أن تكون صفحة `Coming Soon` عامة لمدة **أسبوعين على الأقل** قبل الإصدار حتى يستطيع الناس إضافة اللعبة إلى Wishlist.[2][3]
- Valve تراجع صفحة المتجر والـBuild قبل السماح بالإطلاق؛ موافقة الصفحة لا تعني أن اللعبة ستطلق وحدها، بل يضغط المطور `Release App` عند الموعد.[3]

> هذه أرقام وسياسات من صفحات Steamworks الرسمية التي تم فحصها أثناء إنشاء الخطة. نعيد التحقق منها داخل Steamworks قبل دفع الرسم، لأن Valve قد تغير الشروط.

## 2. حساب التكاليف

### تكاليف إلزامية/محتملة

| البند | الحالة |
|---|---|
| Steam Direct Fee | 100 USD لكل App، قابل للاسترداد وفق الشروط أعلاه |
| Unreal Engine | راجع شروط Epic الحالية عند بدء الإيرادات |
| Steamworks | أدوات النشر نفسها ضمن onboarding؛ لا نسجل أرقاماً غير مؤكدة |
| أصول فنية/صوتية | ميزانية منفصلة، مع إثبات الترخيص لكل Asset |
| ترجمة وتدقيق | ميزانية منفصلة للعربية والإنكليزية |
| خوادم Co-op لاحقاً | لا تُشترى قبل اختيار Listen/Dedicated ومقياس اللاعبين |
| تسويق | Trailer، capsule art، demo، creators، إعلانات اختبارية |

## 3. قبل فتح صفحة المتجر

نجهز أولاً:

- اسم نهائي وLogo.
- Capsule art: Header، Small capsule، Main capsule، Library assets.
- Trailer قصير 60–90 ثانية يبدأ بالـHook خلال أول 5 ثوانٍ.
- 8–12 Screenshot حقيقية من Build قابلة للعب، لا Concept Art فقط.
- وصف قصير يذكر: امتصاص الطاقة، 12 زعيماً، التفاعلات، والمدة التقريبية.
- GIFs قصيرة لثلاثة Reactions: Fire+Wind، Water+Lightning، Light+Gravity.
- Content survey، تصنيف المحتوى، معلومات الخصوصية، وبيانات التواصل.
- صفحة دعم وإيميل واضح.
- قائمة لغات دقيقة؛ لا نعلن Voice-over إذا لم يكن موجوداً.

### النص التسويقي الأساسي

> **Absorb the force of your enemies. Master twelve elements. Break twelve rulers.**
>
> قاتل، تعلّم، وامتصص الطاقة. كل زعيم يترك وراءه قوة جديدة، وكل دمج بين عنصرين يغير طريقة القتال والبيئة.

هذا النص مسودة تسويقية أصلية وليس وصفاً نهائياً حتى يثبت اسم اللعبة والـArt Direction.

## 4. خطة تطوير ما قبل Steam

### المرحلة A — Prototype

- حركة البطل.
- قتال أساسي.
- Fire + Absorb.
- نِبراس كـAI Weak-Point Hunter.
- فينو كتجربة Venom/Trap.
- Boss Fire صغير.

**بوابة النجاح:** لاعب جديد يفهم الحلقة خلال 10 دقائق.

### المرحلة B — Vertical Slice

- قلعة الجمر كاملة.
- ملك النار بثلاث مراحل.
- Save/Load.
- Debug HUD.
- 3 أتباع وMini-boss.
- أول Reaction قابل للعرض.
- Trailer داخلي لا للنشر.

### المرحلة C — Production

- إنتاج المراحل 2–4.
- اختبار القتال والتفاعلات.
- بناء Store assets من نسخة حقيقية.
- فتح قناة Discord/صفحة أخبار إن كانت مفيدة.

### المرحلة D — Content complete

- المراحل 5–12.
- كل الـBosses.
- Credits، Accessibility، Localization، Save migration.
- Performance pass.
- Crash reporting.
- Demo عامة أو Playtest مغلق.

## 5. الجدول النسبي للنشر

### T−6 أشهر أو أبكر — التحضير

- افتح كيان النشر/بيانات الدفع التي تطابق الهوية القانونية.
- ادفع Steam Direct Fee بعد التأكد من الاسم والـApp الصحيح.
- جهز صفحة `Coming Soon` ضمن نافذة الانتظار، ولا تدفع قبل أن تكون قادراً على متابعة الحساب.

### T−4 أشهر — صفحة المتجر

- انشر `Coming Soon` عامة.
- ضع Trailer أولي وScreenshots حقيقية.
- اجمع Wishlists عضوية عبر Demo، فيديوهات، ومجتمعات مطورين؛ لا نشتري Wishlists وهمية.

### T−3 أشهر — Demo/Playtest

- Demo من المرحلة الأولى أو مقدمة مقصوصة لا تكشف النهاية.
- Feedback form يسأل عن وضوح Weak Points، Reactions، ووقت الملل.
- أصلح أولاً مشاكل الفهم والـCrashes، لا اللمعان البصري.

### T−8 أسابيع — Content lock

- اقفل القصة والمراحل.
- راجع كل Asset license.
- اختبر Steam Input، Controller، cloud save إن استُخدم، achievements، overlay، resolutions، 16:9 و16:10.
- ابدأ ترجمة النصوص النهائية.

### T−30 يوماً

- Store page كاملة ومراجعة النصوص.
- Pricing وPackages وBranches.
- Build Release Candidate.
- ارفع Windows depots.
- راجع الـContent Survey وAge Ratings.
- اطلب review عبر Steamworks عندما تصبح قوائم المتجر والـBuild جاهزة.

### T−14 يوماً على الأقل

- تأكد أن صفحة Coming Soon العامة حققت مدة الأسبوعين المطلوبة.[2][3]
- انشر موعد الإصدار بعد امتلاك Build مرشح حقيقي.
- أرسل مفاتيح Review بطريقة منظمة، بلا وعود أو تضخيم.

### T−7 أيام

- لا تغيّر نظام القتال أو Save format.
- اختبر clean install على جهاز غير جهاز المطور.
- تأكد من AppID/DepotID/Branch.
- حضّر rollback build.
- راقب crash logs وSteam Discussions.

### T−0

- ارفع آخر Build.
- تحقق من package/branch من جهاز نظيف.
- استخدم `Release App` يدوياً بعد تحقق نهائي؛ Steam توضح أن العنوان الموافق عليه لا يطلق نفسه تلقائياً.[3]
- انشر إعلان الإطلاق، Patch notes، وروابط الدعم.

### T+1 يوم، T+7 أيام، T+30 يوماً

- راقب Crashes، Reviews، Refund reasons، ووقت الخروج من اللعبة.
- لا ترد على Reviews بعصبية؛ صنفها إلى Bug، UX، توازن، أو ذوق.
- الإصلاحات العاجلة أولاً.
- بعد أسبوعين، انشر أول Patch صغير يثبت أن المشروع حي دون كسر الـSave.

## 6. Steam Deck وLinux

لا نعد بـ`Verified` قبل الاختبار والمراجعة. نبدأ بـ:

- Windows build يعمل عبر Proton في بيئة اختبار.
- Controller كامل عبر Enhanced Input/Steam Input.
- نصوص UI قابلة للقراءة على شاشة صغيرة.
- لا نعتمد على Launcher خارجي أو DRM يسبب فشل التشغيل.
- نختبر suspend/resume، shader stutter، 30/40/60 FPS، وإعادة فتح اللعبة.
- نوثق القيود، ثم نقرر إن كان طلب Steam Deck compatibility مناسباً بعد ثبات PC.[4]

## 7. Achievements والميزات التي نضيفها

### عند الإطلاق

- 12 Boss achievements.
- 12 Element unlock achievements.
- 6 Reaction mastery achievements.
- Achievement لإنهاء اللعبة.
- Steam Cloud فقط بعد اختبار conflict وSave migration.
- Controller/Steam Input من أول Build عامة.

### لا نضيف في البداية

- Microtransactions.
- Battle pass.
- PvP.
- Online co-op غير مستقر.
- DRM مخصص يضر Proton.

## 8. خطة التسويق

### Content pillars

1. **Weak Point moments:** نِبراس يحدد نقطة ويصيبها.
2. **Element reactions:** قبل/بعد Fire+Wind وغيرها.
3. **Boss reveals:** كل زعيم في لقطة قصيرة لها ميكانيك واضح.
4. **Character stories:** فينو، رُكان، ريما، وميرا، وليس البطل وحده.
5. **Behind the scenes:** تحويل Data Asset إلى قدرة تعمل داخل Unreal.

### القنوات

- Steam News وEvents.
- YouTube Shorts/TikTok/Reels للـReactions والـBoss telegraphs.
- Reddit/Discord ومجتمعات Unreal بعرض Build حقيقي لا Spam.
- صناع محتوى مستقلون بعد وجود Demo مستقرة.
- محتوى عربي وإنكليزي منفصل حسب الجمهور؛ لا ترجمة آلية للنصوص القصصية النهائية.

### مؤشرات داخلية

- نمو Wishlists أسبوعياً.
- نسبة مشاهدة Trailer إلى زيارة Store page.
- نسبة Demo players الذين يصلون إلى أول Absorb.
- نسبة من يفهمون Weak Point دون شرح خارجي.
- Crashes لكل جلسة.
- Refund reasons بعد الإصدار.

هذه مؤشرات قرار داخلية وليست شروطاً رسمية من Steam.

## 9. مراجعة المتجر والحقوق

قبل الإرسال:

- كل صورة/صوت/Font/Plugin له مصدر وترخيص محفوظ.
- لا نستخدم كتب هنداوي أو أي مادة مرجعية كـAsset أو نص منسوخ داخل اللعبة.
- الأسماء والشخصيات والـLore أصلية.
- Privacy policy تذكر Telemetry وCrash reporting إن وُجدا.
- Age/content questionnaire صادق ومراجع.
- الوصف والصور يطابقان النسخة التي سيلعبها المشتري.

## 10. Definition of Done للإطلاق

لا نضغط Release App قبل أن:

- ينهي لاعب جديد المرحلة الأولى دون مساعدة المطور.
- ينهي فريق QA الحملة من البداية إلى النهاية على Release Candidate.
- لا يوجد Crash blocker أو Save corruption معروف.
- تعمل Keyboard وController.
- الترجمتان العربية والإنكليزية مدققتان.
- الصفحة والمتجر والصور والفيديو يطابقون الـBuild.
- Steam review/permissions/branches جاهزة.
- يوجد Rollback build وPatch plan.

## مصادر Steamworks

[1] Steam Direct Fee — https://partner.steamgames.com/doc/gettingstarted/appfee  
[2] Steamworks Onboarding — https://partner.steamgames.com/doc/gettingstarted/onboarding  
[3] Steam Release Process — https://partner.steamgames.com/doc/store/releasing  
[4] Getting your game ready for Steam Deck — https://partner.steamgames.com/doc/steamhardware/steamdeck

## Sources

[1] https://partner.steamgames.com/doc/gettingstarted/appfee — Steam Direct Fee
[2] https://partner.steamgames.com/doc/gettingstarted/onboarding — Steamworks Onboarding
[3] https://partner.steamgames.com/doc/store/releasing — Steam Release Process
[4] https://partner.steamgames.com/doc/steamhardware/steamdeck — Getting your game ready for Steam Deck
