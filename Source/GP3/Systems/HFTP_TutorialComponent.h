// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HFTP_TutorialComponent.generated.h"


enum class ETutorialType;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GP3_API UHFTP_TutorialComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tutorial")
	ETutorialType TutorialType{};
};
