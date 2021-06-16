// Copyright Epic Games, Inc. All Rights Reserved.

#include "OnlineAsyncTaskManagerNullPrime.h"

void FOnlineAsyncTaskManagerNullPrime::OnlineTick()
{
	check(NullPrimeSubsystem);
	check(FPlatformTLS::GetCurrentThreadId() == OnlineThreadId || !FPlatformProcess::SupportsMultithreading());
}

