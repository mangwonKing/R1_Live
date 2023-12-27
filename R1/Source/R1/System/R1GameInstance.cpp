// Fill out your copyright notice in the Description page of Project Settings.


#include "System/R1GameInstance.h"

UR1GameInstance::UR1GameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) // 기본생성자가 아닌 경우 부모 생성자 호출
{

}

void UR1GameInstance::Init()
{
	Super::Init(); // 가상함수 원형의 함수 호출 cpp 기본
	//to do
}
void UR1GameInstance::Shutdown()
{
	Super::Shutdown();
	//to do
}