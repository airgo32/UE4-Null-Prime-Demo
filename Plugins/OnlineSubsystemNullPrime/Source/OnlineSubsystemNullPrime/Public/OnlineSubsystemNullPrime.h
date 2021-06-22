// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSubsystemImpl.h"
#include "OnlineSubsystemNullPrimePackage.h"
#include "HAL/ThreadSafeCounter.h"

class FOnlineAchievementsNullPrime;
class FOnlineIdentityNullPrime;
class FOnlineLeaderboardsNullPrime;
class FOnlineSessionNullPrime;
class FOnlineVoiceImpl;

/** Forward declarations of all interface classes */
typedef TSharedPtr<class FOnlineSessionNullPrime, ESPMode::ThreadSafe> FOnlineSessionNullPrimePtr;
typedef TSharedPtr<class FOnlineProfileNullPrime, ESPMode::ThreadSafe> FOnlineProfileNullPrimePtr;
typedef TSharedPtr<class FOnlineFriendsNullPrime, ESPMode::ThreadSafe> FOnlineFriendsNullPrimePtr;
typedef TSharedPtr<class FOnlineUserCloudNullPrime, ESPMode::ThreadSafe> FOnlineUserCloudNullPrimePtr;
typedef TSharedPtr<class FOnlineLeaderboardsNullPrime, ESPMode::ThreadSafe> FOnlineLeaderboardsNullPrimePtr;
typedef TSharedPtr<class FOnlineVoiceImpl, ESPMode::ThreadSafe> FOnlineVoiceImplPtr;
typedef TSharedPtr<class FOnlineExternalUINullPrime, ESPMode::ThreadSafe> FOnlineExternalUINullPrimePtr;
typedef TSharedPtr<class FOnlineIdentityNullPrime, ESPMode::ThreadSafe> FOnlineIdentityNullPrimePtr;
typedef TSharedPtr<class FOnlineAchievementsNullPrime, ESPMode::ThreadSafe> FOnlineAchievementsNullPrimePtr;
typedef TSharedPtr<class FOnlineStoreV2NullPrime, ESPMode::ThreadSafe> FOnlineStoreV2NullPrimePtr;
typedef TSharedPtr<class FOnlinePurchaseNullPrime, ESPMode::ThreadSafe> FOnlinePurchaseNullPrimePtr;
typedef TSharedPtr<class FMessageSanitizerNullPrime, ESPMode::ThreadSafe> FMessageSanitizerNullPrimePtr;

/**
 *	OnlineSubsystemNullPrime - Implementation of the online subsystem for NullPrime services
 */
class ONLINESUBSYSTEMNULLPRIME_API FOnlineSubsystemNullPrime : 
	public FOnlineSubsystemImpl
{

public:

	virtual ~FOnlineSubsystemNullPrime() = default;

	// IOnlineSubsystem

	virtual IOnlineSessionPtr GetSessionInterface() const override;
	virtual IOnlineFriendsPtr GetFriendsInterface() const override;
	virtual IOnlinePartyPtr GetPartyInterface() const override;
	virtual IOnlineGroupsPtr GetGroupsInterface() const override;
	virtual IOnlineSharedCloudPtr GetSharedCloudInterface() const override;
	virtual IOnlineUserCloudPtr GetUserCloudInterface() const override;
	virtual IOnlineEntitlementsPtr GetEntitlementsInterface() const override;
	virtual IOnlineLeaderboardsPtr GetLeaderboardsInterface() const override;
	virtual IOnlineVoicePtr GetVoiceInterface() const override;
	virtual IOnlineExternalUIPtr GetExternalUIInterface() const override;	
	virtual IOnlineTimePtr GetTimeInterface() const override;
	virtual IOnlineIdentityPtr GetIdentityInterface() const override;
	virtual IOnlineTitleFilePtr GetTitleFileInterface() const override;
	virtual IOnlineStoreV2Ptr GetStoreV2Interface() const override;
	virtual IOnlinePurchasePtr GetPurchaseInterface() const override;
	virtual IOnlineEventsPtr GetEventsInterface() const override;
	virtual IOnlineAchievementsPtr GetAchievementsInterface() const override;
	virtual IOnlineSharingPtr GetSharingInterface() const override;
	virtual IOnlineUserPtr GetUserInterface() const override;
	virtual IOnlineMessagePtr GetMessageInterface() const override;
	virtual IOnlinePresencePtr GetPresenceInterface() const override;
	virtual IOnlineChatPtr GetChatInterface() const override;
	virtual IOnlineStatsPtr GetStatsInterface() const override;
	virtual IOnlineTurnBasedPtr GetTurnBasedInterface() const override;
	virtual IOnlineTournamentPtr GetTournamentInterface() const override;
	virtual IMessageSanitizerPtr GetMessageSanitizer(int32 LocalUserNum, FString& OutAuthTypeToExclude) const override;

	virtual bool Init() override;
	virtual bool Shutdown() override;
	virtual FString GetAppId() const override;
	virtual bool Exec(class UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;
	virtual FText GetOnlineServiceName() const override;

	// FTickerObjectBase
	
	virtual bool Tick(float DeltaTime) override;

	// FOnlineSubsystemNullPrime

PACKAGE_SCOPE:

	/** Only the factory makes instances */
	FOnlineSubsystemNullPrime() = delete;
	explicit FOnlineSubsystemNullPrime(FName InInstanceName) :
		FOnlineSubsystemImpl(NULLPRIME_SUBSYSTEM, InInstanceName),
		SessionInterface(nullptr),
		VoiceInterface(nullptr),
		bVoiceInterfaceInitialized(false),
		LeaderboardsInterface(nullptr),
		IdentityInterface(nullptr),
		AchievementsInterface(nullptr),
		StoreV2Interface(nullptr),
		MessageSanitizerInterface(nullptr),
		OnlineAsyncTaskThreadRunnable(nullptr),
		OnlineAsyncTaskThread(nullptr)
	{}

private:

	/** Interface to the session services */
	FOnlineSessionNullPrimePtr SessionInterface;

	/** Interface for voice communication */
	mutable IOnlineVoicePtr VoiceInterface;

	/** Interface for voice communication */
	mutable bool bVoiceInterfaceInitialized;

	/** Interface to the leaderboard services */
	FOnlineLeaderboardsNullPrimePtr LeaderboardsInterface;

	/** Interface to the identity registration/auth services */
	FOnlineIdentityNullPrimePtr IdentityInterface;

	/** Interface for achievements */
	FOnlineAchievementsNullPrimePtr AchievementsInterface;

	/** Interface for store */
	FOnlineStoreV2NullPrimePtr StoreV2Interface;

	/** Interface for purchases */
	FOnlinePurchaseNullPrimePtr PurchaseInterface;

	/** Interface for message sanitizing */
	FMessageSanitizerNullPrimePtr MessageSanitizerInterface;

	/** Online async task runnable */
	class FOnlineAsyncTaskManagerNullPrime* OnlineAsyncTaskThreadRunnable;

	/** Online async task thread */
	class FRunnableThread* OnlineAsyncTaskThread;

	// task counter, used to generate unique thread names for each task
	static FThreadSafeCounter TaskCounter;
};

typedef TSharedPtr<FOnlineSubsystemNullPrime, ESPMode::ThreadSafe> FOnlineSubsystemNullPrimePtr;

