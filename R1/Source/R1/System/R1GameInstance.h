// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "R1GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class R1_API UR1GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	// 생성자 , f12를 타고 가보면 f오브젝트를 받는걸 알 수 있음 이 부분은 나중에 더 공부하기
	UR1GameInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
protected:
	virtual void Init() override; // 느낌상 게임 시작시 호출
	virtual void Shutdown() override; //느낌상 게임 종료시 호출
};
