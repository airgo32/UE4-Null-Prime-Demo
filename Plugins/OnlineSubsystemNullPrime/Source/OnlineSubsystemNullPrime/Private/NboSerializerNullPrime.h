// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSubsystemNullPrimeTypes.h"
#include "NboSerializer.h"

/**
 * Serializes data in network byte order form into a buffer
 */
class FNboSerializeToBufferNullPrime : public FNboSerializeToBuffer
{
public:
	/** Default constructor zeros num bytes*/
	FNboSerializeToBufferNullPrime() :
		FNboSerializeToBuffer(512)
	{
	}

	/** Constructor specifying the size to use */
	FNboSerializeToBufferNullPrime(uint32 Size) :
		FNboSerializeToBuffer(Size)
	{
	}

	/**
	 * Adds NullPrime session info to the buffer
	 */
 	friend inline FNboSerializeToBufferNullPrime& operator<<(FNboSerializeToBufferNullPrime& Ar, const FOnlineSessionInfoNullPrime& SessionInfo)
 	{
		check(SessionInfo.HostAddr.IsValid());
		// Skip SessionType (assigned at creation)
		Ar << SessionInfo.SessionId;
		Ar << *SessionInfo.HostAddr;
		return Ar;
 	}

	/**
	 * Adds NullPrime Unique Id to the buffer
	 */
	friend inline FNboSerializeToBufferNullPrime& operator<<(FNboSerializeToBufferNullPrime& Ar, const FUniqueNetIdNullPrime& UniqueId)
	{
		Ar << UniqueId.UniqueNetIdStr;
		return Ar;
	}
};

/**
 * Class used to write data into packets for sending via system link
 */
class FNboSerializeFromBufferNullPrime : public FNboSerializeFromBuffer
{
public:
	/**
	 * Initializes the buffer, size, and zeros the read offset
	 */
	FNboSerializeFromBufferNullPrime(uint8* Packet,int32 Length) :
		FNboSerializeFromBuffer(Packet,Length)
	{
	}

	/**
	 * Reads NullPrime session info from the buffer
	 */
 	friend inline FNboSerializeFromBufferNullPrime& operator>>(FNboSerializeFromBufferNullPrime& Ar, FOnlineSessionInfoNullPrime& SessionInfo)
 	{
		check(SessionInfo.HostAddr.IsValid());
		// Skip SessionType (assigned at creation)
		Ar >> SessionInfo.SessionId; 
		Ar >> *SessionInfo.HostAddr;
		return Ar;
 	}

	/**
	 * Reads NullPrime Unique Id from the buffer
	 */
	friend inline FNboSerializeFromBufferNullPrime& operator>>(FNboSerializeFromBufferNullPrime& Ar, FUniqueNetIdNullPrime& UniqueId)
	{
		Ar >> UniqueId.UniqueNetIdStr;
		return Ar;
	}
};
