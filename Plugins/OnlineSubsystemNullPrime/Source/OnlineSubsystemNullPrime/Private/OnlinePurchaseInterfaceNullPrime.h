// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Interfaces/OnlinePurchaseInterface.h"
#include "OnlineSubsystemNullPrimeTypes.h"

class FOnlineSubsystemNullPrime;

class FOnlinePurchaseNullPrime
	: public IOnlinePurchase
	, public TSharedFromThis<FOnlinePurchaseNullPrime, ESPMode::ThreadSafe>
{
public:
	FOnlinePurchaseNullPrime(FOnlineSubsystemNullPrime& InNullPrimeSubsystem);
	virtual ~FOnlinePurchaseNullPrime();

	void Tick();

public:
	//~ Begin IOnlinePurchase Interface
	virtual bool IsAllowedToPurchase(const FUniqueNetId& UserId) override;
	virtual void Checkout(const FUniqueNetId& UserId, const FPurchaseCheckoutRequest& CheckoutRequest, const FOnPurchaseCheckoutComplete& Delegate) override;
	virtual void FinalizePurchase(const FUniqueNetId& UserId, const FString& ReceiptId) override;
	virtual void RedeemCode(const FUniqueNetId& UserId, const FRedeemCodeRequest& RedeemCodeRequest, const FOnPurchaseRedeemCodeComplete& Delegate) override;
	virtual void QueryReceipts(const FUniqueNetId& UserId, bool bRestoreReceipts, const FOnQueryReceiptsComplete& Delegate) override;
	virtual void GetReceipts(const FUniqueNetId& UserId, TArray<FPurchaseReceipt>& OutReceipts) const override;
	virtual void FinalizeReceiptValidationInfo(const FUniqueNetId& UserId, FString& InReceiptValidationInfo, const FOnFinalizeReceiptValidationInfoComplete& Delegate) override;
	//~ End IOnlinePurchase Interface

PACKAGE_SCOPE:
	void CheckoutSuccessfully(const FUniqueNetIdNullPrime& UserId, TSharedPtr<FOnlineStoreOffer> Offer);

PACKAGE_SCOPE:
	/** Pointer back to our parent subsystem */
	FOnlineSubsystemNullPrime& NullPrimeSubsystem;

	/** Cached receipts information per user */
	TMap<FUniqueNetIdNullPrime, TArray<FPurchaseReceipt> > UserFakeReceipts;

	/** Do we have a purchase currently in progress? */
	TOptional<FOnPurchaseCheckoutComplete> PendingPurchaseDelegate;

	TOptional<double> PendingPurchaseFailTime;
};

using FOnlinePurchaseNullPrimePtr = TSharedPtr<FOnlinePurchaseNullPrime, ESPMode::ThreadSafe>;
using FOnlinePurchaseNullPrimeRef = TSharedRef<FOnlinePurchaseNullPrime, ESPMode::ThreadSafe>;
