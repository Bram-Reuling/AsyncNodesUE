// Fill out your copyright notice in the Description page of Project Settings.


#include "UDemoAsyncNode.h"

//============================================================

UDemoAsyncNode* UDemoAsyncNode::DemoBlueprintNode(const UObject* WorldObject)
{
	UDemoAsyncNode* Node = NewObject<UDemoAsyncNode>(); // Create a new object of the class.
	if (Node) // Check if the object creation is successful.
	{
		// Initialize any variables of the created object.
		Node->WorldObject = WorldObject;
		Node->m_fDelayTime = 2.f;
	}
	return Node;
}

//============================================================

void UDemoAsyncNode::Activate()
{
	InternalDirectCall();

	if (!WorldObject)
		return;

	TimerDel.BindUObject(this, &UDemoAsyncNode::InternalLaterCall, m_fDelayTime);
	WorldObject->GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDel, m_fDelayTime, false);
}

//============================================================

void UDemoAsyncNode::InternalDirectCall()
{
	Direct.Broadcast(0.f);
}

//============================================================

void UDemoAsyncNode::InternalLaterCall(float timeElapsed)
{
	Later.Broadcast(timeElapsed);

	// Clean up the timer logic.
	WorldObject->GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	TimerHandle.Invalidate();
	TimerDel.Unbind();
}

//============================================================