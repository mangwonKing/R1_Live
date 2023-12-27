// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/R1Character.h"
#include "GameFramework/SpringArmComponent.h" //���漱���� ����� include
#include "Camera/CameraComponent.h"

// Sets default values
AR1Character::AR1Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//�޽� ������Ʈ ��������
	//GetMesh()->SetSkeletalMesh();

	//������ ��, ī�޶� �ҷ�����
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	
	//������ ��, ī�޶� ������
	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);

	//������ ��ġ ����
	SpringArm->SetRelativeRotation(FRotator(-30, 0, 0));
	SpringArm->TargetArmLength = 700;
	
	// ���� �ܾ����
	
	GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -88), FRotator(0, -90, 0));

	ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshResource(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonGreystone/Characters/Heroes/Greystone/Meshes/Greystone.Greystone'"));
	
		
	if (MeshResource.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshResource.Object);
	}
}

// Called when the game starts or when spawned
void AR1Character::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AR1Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

// Called to bind functionality to input
void AR1Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

