// Copyright Epic Games, Inc. All Rights Reserved.

#include "OnlineSubsystemNullPrimeModule.h"
#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "OnlineSubsystemModule.h"
#include "OnlineSubsystemNames.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemNullPrimePackage.h"
#include "OnlineSubsystemNullPrime.h"

//#include "OnlineSubsystemNullPrimeTypes.h"
//#include "OnlineSubsystemUtilsModule.h"

#define LOCTEXT_NAMESPACE "FOnlineSubsystemNullPrimeModule"

IMPLEMENT_MODULE(FOnlineSubsystemNullPrimeModule, OnlineSubsystemNullPrime);

/**
 * Class responsible for creating instance(s) of the subsystem
 */
class FOnlineFactoryNullPrime : public IOnlineFactory
{
public:

	FOnlineFactoryNullPrime() {}
	virtual ~FOnlineFactoryNullPrime() {}

	virtual IOnlineSubsystemPtr CreateSubsystem(FName InstanceName)
	{
		FOnlineSubsystemNullPrimePtr OnlineSub = MakeShared<FOnlineSubsystemNullPrime, ESPMode::ThreadSafe>(InstanceName);
		if (OnlineSub->IsEnabled())
		{
			if (!OnlineSub->Init())
			{
				UE_LOG_ONLINE(Warning, TEXT("Null Prime API failed to initialize!"));
				OnlineSub->Shutdown();
				OnlineSub = NULL;
			}
		}
		else
		{
			UE_LOG_ONLINE(Warning, TEXT("Null Prime API disabled!"));
			OnlineSub->Shutdown();
			OnlineSub = NULL;
		}

		return OnlineSub;
	}
};
// 
// CREATE_HASH(NULLPRIME_SUBSYSTEM);

void FOnlineSubsystemNullPrimeModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	UE_LOG_ONLINE(Warning, TEXT("NullPrime OSS Loading now..."));


	NullPrimeFactory = new FOnlineFactoryNullPrime();

	// Create and register our singleton factory with the main online subsystem for easy access
	FOnlineSubsystemModule& OSS = FModuleManager::GetModuleChecked<FOnlineSubsystemModule>("OnlineSubsystem");
	OSS.RegisterPlatformService(NULLPRIME_SUBSYSTEM, NullPrimeFactory);
}

void FOnlineSubsystemNullPrimeModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	FOnlineSubsystemModule& OSS = FModuleManager::GetModuleChecked<FOnlineSubsystemModule>("OnlineSubsystem");
	OSS.UnregisterPlatformService(NULLPRIME_SUBSYSTEM);

	delete NullPrimeFactory;
	NullPrimeFactory = NULL;
}

#undef LOCTEXT_NAMESPACE
	
//IMPLEMENT_MODULE(FOnlineSubsystemNullPrimeModule, OnlineSubsystemNullPrime)