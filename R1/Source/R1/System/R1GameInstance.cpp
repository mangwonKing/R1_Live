// Fill out your copyright notice in the Description page of Project Settings.


#include "System/R1GameInstance.h"

UR1GameInstance::UR1GameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) // �⺻�����ڰ� �ƴ� ��� �θ� ������ ȣ��
{

}

void UR1GameInstance::Init()
{
	Super::Init(); // �����Լ� ������ �Լ� ȣ�� cpp �⺻
	//to do
}
void UR1GameInstance::Shutdown()
{
	Super::Shutdown();
	//to do
}