// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/R1Character.h"
#include "GameFramework/SpringArmComponent.h" //전방선언한 내용들 include
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h" //인풋 관련 전방선언 인클루드
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Kismet/KismetMathLibrary.h" // 수학 관련 라이브러리
// Sets default values
AR1Character::AR1Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//메쉬 컴포넌트 부착예시
	//GetMesh()->SetSkeletalMesh();

	//스프링 암, 카메라 불러오기
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	
	//스프링 암, 카메라 붙히기
	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);

	//각도와 위치 조정
	SpringArm->SetRelativeRotation(FRotator(-30, 0, 0));
	SpringArm->TargetArmLength = 700;
	
	// 에셋 긁어오기
	
	GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -88), FRotator(0, -90, 0));

	ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshResource(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonGreystone/Characters/Heroes/Greystone/Meshes/Greystone.Greystone'"));
	
		
	if (MeshResource.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshResource.Object);
	}

	//input 에셋과 멤버변수 연결
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

	//EnhancedInput 블루프린트 부분 옮기기
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
		// 인풋 바인딩 해주기
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AR1Character::IA_Move);
		EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Triggered, this, &AR1Character::IA_Turn);

	}
}

//인풋받아서 컨트롤러에 값을 넘겨주는 함수들
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

