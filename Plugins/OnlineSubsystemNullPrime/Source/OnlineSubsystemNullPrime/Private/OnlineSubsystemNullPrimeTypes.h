// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "OnlineSubsystemTypes.h"
#include "CoreMinimal.h"
#include "IPAddress.h"

class FOnlineSubsystemNullPrime;

// from OnlineSubsystemTypes.h
TEMP_UNIQUENETIDSTRING_SUBCLASS(FUniqueNetIdNullPrime, NULLPRIME_SUBSYSTEM);

/** 
 * Implementation of session information
 */
class FOnlineSessionInfoNullPrime : public FOnlineSessionInfo
{
protected:
	
	/** Hidden on purpose */
	FOnlineSessionInfoNullPrime(const FOnlineSessionInfoNullPrime& Src)
	{
	}

	/** Hidden on purpose */
	FOnlineSessionInfoNullPrime& operator=(const FOnlineSessionInfoNullPrime& Src)
	{
		return *this;
	}

PACKAGE_SCOPE:

	/** Constructor */
	FOnlineSessionInfoNullPrime();

	/** 
	 * Initialize a Null session info with the address of this machine
	 * and an id for the session
	 */
	void Init(const FOnlineSubsystemNullPrime& Subsystem);

	/** The ip & port that the host is listening on (valid for LAN/GameServer) */
	TSharedPtr<class FInternetAddr> HostAddr;
	/** Unique Id for this session */
	FUniqueNetIdNullPrime SessionId;

public:

	virtual ~FOnlineSessionInfoNullPrime() {}

 	bool operator==(const FOnlineSessionInfoNullPrime& Other) const
 	{
 		return false;
 	}

	virtual const uint8* GetBytes() const override
	{
		return NULL;
	}

	virtual int32 GetSize() const override
	{
		return sizeof(uint64) + sizeof(TSharedPtr<class FInternetAddr>);
	}

	virtual bool IsValid() const override
	{
		// LAN case
		return HostAddr.IsValid() && HostAddr->IsValid();
	}

	virtual FString ToString() const override
	{
		return SessionId.ToString();
	}

	virtual FString ToDebugString() const override
	{
		return FString::Printf(TEXT("HostIP: %s SessionId: %s"), 
			HostAddr.IsValid() ? *HostAddr->ToString(true) : TEXT("INVALID"), 
			*SessionId.ToDebugString());
	}

	virtual const FUniqueNetId& GetSessionId() const override
	{
		return SessionId;
	}
};
