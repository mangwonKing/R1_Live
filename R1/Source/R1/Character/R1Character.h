// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h" // input �� ���� ��Ŭ���
#include "R1Character.generated.h"

UCLASS()
class R1_API AR1Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AR1Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:
	//�ݹ��Լ�
	UFUNCTION()
	void IA_Move(const FInputActionValue& Value);
	UFUNCTION()
	void IA_Turn(const FInputActionValue& Value);

public:
	/*UPROPERTY(EditAnywhere, Category = R1)
	int32 Hp = 100;

	UPROPERTY(EditAnywhere, Category = R1)
	float Speed = 1.5;

	UPROPERTY(EditAnywhere, Category = R1)
    FString Name = TEXT("KIM");*/
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<class USpringArmComponent> SpringArm; //���漱�� class ǥ��

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UCameraComponent> Camera;
private:
	//IMC ����
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<class UInputMappingContext> InputMappingContext;
	//��ǲ �׼� ����
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<class UInputAction> TurnAction;
};
