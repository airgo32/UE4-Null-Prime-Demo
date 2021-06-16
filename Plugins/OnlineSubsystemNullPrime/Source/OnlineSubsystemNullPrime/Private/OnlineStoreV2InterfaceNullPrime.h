// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/OnlineStoreInterfaceV2.h"
#include "OnlineSubsystemNullPrimePackage.h"

class FOnlineSubsystemNullPrime;
class FUniqueNetIdNullPrime;

/**
 * Implementation for online store via NullPrime interface
 */
class FOnlineStoreV2NullPrime : public IOnlineStoreV2, public TSharedFromThis<FOnlineStoreV2NullPrime, ESPMode::ThreadSafe>
{
public:
	FOnlineStoreV2NullPrime(FOnlineSubsystemNullPrime& InNullPrimeSubsystem);
	virtual ~FOnlineStoreV2NullPrime() = default;

public:// IOnlineStoreV2
	virtual void QueryCategories(const FUniqueNetId& UserId, const FOnQueryOnlineStoreCategoriesComplete& Delegate) override;
	virtual void GetCategories(TArray<FOnlineStoreCategory>& OutCategories) const override;
	virtual void QueryOffersByFilter(const FUniqueNetId& UserId, const FOnlineStoreFilter& Filter, const FOnQueryOnlineStoreOffersComplete& Delegate) override;
	virtual void QueryOffersById(const FUniqueNetId& UserId, const TArray<FUniqueOfferId>& OfferIds, const FOnQueryOnlineStoreOffersComplete& Delegate) override;
	virtual void GetOffers(TArray<FOnlineStoreOfferRef>& OutOffers) const override;
	virtual TSharedPtr<FOnlineStoreOffer> GetOffer(const FUniqueOfferId& OfferId) const override;

PACKAGE_SCOPE:
	void QueryOffers(const FUniqueNetIdNullPrime& UserId, const TArray<FUniqueOfferId>& OfferIds, const FOnQueryOnlineStoreOffersComplete& Delegate);

PACKAGE_SCOPE:
	FOnlineSubsystemNullPrime& NullPrimeSubsystem;
	TMap<FUniqueOfferId, FOnlineStoreOfferRef> AvailableOffers;

private:
	void CreateFakeOffer(const FString& Id, const FString& Title, const FString& Description, int32 Price);
};

using FOnlineStoreNullPrimePtr = TSharedPtr<FOnlineStoreV2NullPrime, ESPMode::ThreadSafe>;
using FOnlineStoreNullPrimeRef = TSharedRef<FOnlineStoreV2NullPrime, ESPMode::ThreadSafe>;
