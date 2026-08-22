# صدى الأثير — بنية المشروع وقواعد التسمية

## 1. بنية المستودع المقترحة

```text
SadaAlAthir/
├── SadaAlAthir.uproject
├── Config/
│   ├── DefaultEngine.ini
│   ├── DefaultGame.ini
│   ├── DefaultInput.ini
│   └── DefaultEditorPerProjectUserSettings.ini
├── Content/
│   └── SadaAlAthir/
│       ├── Core/
│       ├── Characters/
│       ├── Environments/
│       ├── Gameplay/
│       ├── Narrative/
│       ├── Audio/
│       ├── UI/
│       ├── VFX/
│       ├── Materials/
│       ├── Sequences/
│       ├── Maps/
│       └── Dev/
├── Source/
│   └── SadaAlAthir/
├── Plugins/
├── Scripts/
├── Docs/
└── Tests/
```

## 2. قاعدة الملكية

كل مجلد محتوى يملك جهة واحدة مسؤولة عن سلامة أصوله. لا تُحفظ أصول الاختبار في المجلد النهائي، بل في `Content/SadaAlAthir/Dev/`. لا تُستخدم أسماء عامة مثل `NewBlueprint` أو `TestSound` في الفرع الرئيسي.

## 3. بادئات الأصول

| النوع | البادئة | مثال |
|---|---|---|
| Blueprint Class | BP_ | BP_PlayerCharacter |
| Actor Component | AC_ | AC_EtherPerception |
| Widget | WBP_ | WBP_InteractionPrompt |
| Material | M_ | M_EtherSurface |
| Material Instance | MI_ | MI_EtherSurface_Cold |
| Static Mesh | SM_ | SM_RelayTower_A |
| Skeletal Mesh | SK_ | SK_Player |
| Texture | T_ | T_RelayTower_BaseColor |
| Niagara System | NS_ | NS_EtherTrace |
| Sound Wave | SW_ | SW_EtherSignal_01 |
| Sound Cue | SC_ | SC_EtherSignal_01 |
| Data Asset | DA_ | DA_Signal_Relay01 |
| Data Table | DT_ | DT_NarrativeNodes |
| Level | L_ | L_Prologue_Relay |
| Level Sequence | LS_ | LS_Relay_Reveal |
| Enum | E_ | E_EtherSignalType |
| Struct | F_ | F_InteractionResult |

## 4. نمط المعرفات

يستخدم كل عنصر منطقي معرفاً ثابتاً بصيغة `SA_<Domain>_<Name>_<Number>`، مثل `SA_ETHER_RELAY_001`. يجب ألا يعتمد الحفظ أو التوطين على اسم عرض قابل للتغيير.

## 5. فروع Git المقترحة

| الفرع | الاستخدام |
|---|---|
| main | نسخ مستقرة قابلة للتسليم |
| develop | تكامل العمل الجاري |
| feature/<name> | ميزة منفردة |
| content/<name> | حزمة أصول أو منطقة |
| fix/<name> | إصلاح محدد |
| docs/<name> | تعديل وثائقي مستقل |

## 6. ملفات لا تدخل المستودع

يجب استبعاد مجلدات الكاش والمخرجات المحلية وملفات المستخدم المؤقتة مثل `DerivedDataCache/` و`Intermediate/` و`Saved/` و`Binaries/` وملفات النظام المحلية. يبقى القرار النهائي لملف `.gitignore` مرتبطاً بنظام إدارة الملفات الثنائية المعتمد للفريق.

## 7. قواعد المراجعة

لا يُدمج أصل أو نظام جديد دون وصف، مالك، حالة، وملاحظة اختبار. أي تغيير في مخطط الحفظ أو معرفات السرد يحتاج مراجعة مشتركة من البرمجة والتصميم والسرد.
