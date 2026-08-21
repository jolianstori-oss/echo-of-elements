# Scripts

يحتوي هذا المجلد على أدوات مساعدة لا تُنشئ ملفات Unreal المولدة ولا تنفذ عملية بناء. يمرر `GenerateProjectFiles.sh` ملف المشروع إلى سكربت UnrealBuildTool الخاص بتثبيت Unreal Engine 5.8.

قبل الاستخدام، اضبط المتغير `UE_ROOT` على مسار تثبيت المحرك، ثم نفّذ:

```bash
export UE_ROOT=/path/to/UnrealEngine
./Scripts/GenerateProjectFiles.sh
```

السكربت مخصص لتوليد ملفات بيئة التطوير فقط، ولا يُعد دليلاً على نجاح بناء المشروع.
