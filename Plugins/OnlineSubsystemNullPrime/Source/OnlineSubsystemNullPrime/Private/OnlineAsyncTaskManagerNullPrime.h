// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OnlineAsyncTaskManager.h"

/**
 *	Null version of the async task manager to register the various Null callbacks with the engine
 */
class FOnlineAsyncTaskManagerNullPrime : public FOnlineAsyncTaskManager
{
protected:

	/** Cached reference to the main online subsystem */
	class FOnlineSubsystemNullPrime* NullPrimeSubsystem;

public:

	FOnlineAsyncTaskManagerNullPrime(class FOnlineSubsystemNullPrime* InOnlineSubsystem)
		: NullPrimeSubsystem(InOnlineSubsystem)
	{
	}

	~FOnlineAsyncTaskManagerNullPrime() 
	{
	}

	// FOnlineAsyncTaskManager
	virtual void OnlineTick() override;
};
