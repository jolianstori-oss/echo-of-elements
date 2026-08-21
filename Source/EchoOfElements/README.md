# EchoOfElements Module

هذه هي وحدة Runtime الأساسية للمشروع. يعرّف `EchoOfElements.Build.cs` تبعيات Core وEngine وEnhanced Input وGameplay Ability System وGameplay Tags وNiagara وChaos. يعرّف `EchoOfElements.cpp` نقطة تسجيل الوحدة، ويحتوي `EchoOfElements.h` على واجهة الوحدة وفئة السجل.

يُستخدم `EchoOfElements.Target.cs` لبناء اللعبة، بينما يُستخدم `EchoOfElementsEditor.Target.cs` لبناء هدف المحرر. يمكن وضع الواجهات العامة في `Public/` والتنفيذات الخاصة في `Private/` مع إضافة ملفات المصدر الجديدة إلى الوحدة نفسها.
