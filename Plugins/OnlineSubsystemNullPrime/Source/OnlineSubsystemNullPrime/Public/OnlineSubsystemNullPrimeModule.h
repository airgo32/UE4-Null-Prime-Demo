// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FOnlineSubsystemNullPrimeModule : public IModuleInterface
{

private:

	/** Class responsible for creating instance(s) of the subsystem */
	class FOnlineFactoryNullPrime* NullPrimeFactory;

public:

	FOnlineSubsystemNullPrimeModule() :
		NullPrimeFactory(NULL)
	{}

	virtual ~FOnlineSubsystemNullPrimeModule() {}

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	virtual bool SupportsDynamicReloading() override
	{
		return false;
	}

	virtual bool SupportsAutomaticShutdown() override
	{
		return false;
	}
};
