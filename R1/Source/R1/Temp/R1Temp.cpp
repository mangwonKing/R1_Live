// Fill out your copyright notice in the Description page of Project Settings.


#include "R1Temp.h"
#include "R1/R1LogChannel.h"

// Sets default values
AR1Temp::AR1Temp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AR1Temp::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Warning, TEXT("HELLO world!"));
	UE_LOG(LogTemp, Log, TEXT("HELLO world!"));
	UE_LOG(LogTemp, Error, TEXT("HELLO world!"));
	UE_LOG(LogR1, Error, TEXT("HELLO world!!!"));
	//UE_LOG(LogTemp, Fatal, TEXT("HELLO world!"));
}

// Called every frame
void AR1Temp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

