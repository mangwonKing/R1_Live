// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/R1GameMode.h"
#include "Character/R1Character.h"

AR1GameMode::AR1GameMode(const FObjectInitializer& ObjectInitializer)
	:	Super(ObjectInitializer)
{
	// 디폴트 폰을 변경해주는 부분 , 객체를 즉석에서 생성해서 디폴트폰에 덮어씌워준다는 것
	DefaultPawnClass = AR1Character::StaticClass(); //cpp 에서는 못하는 문법

}
