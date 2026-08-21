#include "EchoOfElements.h"

DEFINE_LOG_CATEGORY(LogEchoOfElements);

void FEchoOfElementsModule::StartupModule()
{
    UE_LOG(LogEchoOfElements, Log, TEXT("Echo of Elements module started."));
}

void FEchoOfElementsModule::ShutdownModule()
{
    UE_LOG(LogEchoOfElements, Log, TEXT("Echo of Elements module shut down."));
}

IMPLEMENT_PRIMARY_GAME_MODULE(FEchoOfElementsModule, EchoOfElements, "EchoOfElements");
