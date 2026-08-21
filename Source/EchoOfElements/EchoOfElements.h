#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FEchoOfElementsModule : public FDefaultGameModuleImpl
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};

DECLARE_LOG_CATEGORY_EXTERN(LogEchoOfElements, Log, All);
