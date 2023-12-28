// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/R1Character.h"
#include "GameFramework/SpringArmComponent.h" //���漱���� ����� include
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h" //��ǲ ���� ���漱�� ��Ŭ���
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Kismet/KismetMathLibrary.h" // ���� ���� ���̺귯��
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

	//input ���°� ������� ����
	ConstructorHelpers::FObjectFinder<UInputMappingContext> MappingContext(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Input/IMC_Default.IMC_Default'"));
	if (MappingContext.Succeeded())
	{
		InputMappingContext = MappingContext.Object;
	}
	ConstructorHelpers::FObjectFinder<UInputAction> MoveAsset(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_Move.IA_Move'"));
	if (MoveAsset.Succeeded())
	{
		MoveAction = MoveAsset.Object;
	}
	ConstructorHelpers::FObjectFinder<UInputAction> TurnAsset(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_Turn.IA_Turn'"));
	if (TurnAsset.Succeeded())
	{
		TurnAction = TurnAsset.Object;
	}
}

// Called when the game starts or when spawned
void AR1Character::BeginPlay()
{
	Super::BeginPlay();

	//EnhancedInput �������Ʈ �κ� �ű��
	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController)
	{
		auto* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem)
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}

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

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// ��ǲ ���ε� ���ֱ�
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AR1Character::IA_Move);
		EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Triggered, this, &AR1Character::IA_Turn);

	}
}

//��ǲ�޾Ƽ� ��Ʈ�ѷ��� ���� �Ѱ��ִ� �Լ���
void AR1Character::IA_Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (MovementVector.X != 0)
	{
		FRotator Rotator = GetControlRotation();
		FVector Direction = UKismetMathLibrary::GetForwardVector(FRotator(0, Rotator.Yaw, 0));
		AddMovementInput(Direction, MovementVector.X);
	}
	if (MovementVector.Y != 0)
	{
		FRotator Rotator = GetControlRotation();
		FVector Direction = UKismetMathLibrary::GetRightVector(FRotator(0, Rotator.Yaw, 0));
		AddMovementInput(Direction, MovementVector.Y);
	}
}

void AR1Character::IA_Turn(const FInputActionValue& Value)
{
	float Val = Value.Get<float>();
	AddControllerYawInput(Val);
}

