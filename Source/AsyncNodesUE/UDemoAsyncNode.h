// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "UDemoAsyncNode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDemoOutputPin, float, DemoOutput);

UCLASS()
class ASYNCNODESUE_API UDemoAsyncNode : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

private:
	const UObject* WorldObject;

	FTimerDelegate TimerDel;
	FTimerHandle TimerHandle;

private:
	UFUNCTION()
	void InternalDirectCall();

	UFUNCTION()
	void InternalLaterCall(float timeElapsed);

public:
	float m_fDelayTime = 0.f;

	UPROPERTY(BlueprintAssignable)
	FDemoOutputPin Direct;

	UPROPERTY(BlueprintAssignable)
	FDemoOutputPin Later;

public:
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldObject"), Category = "Demo")
	static UDemoAsyncNode* DemoBlueprintNode(const UObject* WorldObject);

	virtual void Activate() override;
};
