#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "HFTP_GameInstance.generated.h"

UCLASS(Abstract)
class GP3_API UHFTP_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetFlashingLights(bool bEnable) noexcept{ bIsFlashingLightsEnabled = bEnable;};

	UFUNCTION(BlueprintCallable)
	void SetChromaticAberration(bool bEnable) noexcept { bIsChromaticAberration = bEnable; };

	bool IsFlashingLightsEnabled() const noexcept { return bIsFlashingLightsEnabled; }
	bool IsChromaticAberrationEnabled() const noexcept { return bIsChromaticAberration; }
	bool HavePlayedTutorial() const noexcept { return bHavePlayedTutorial; }
	void SetHavePlayedTutorial() noexcept { bHavePlayedTutorial = true; }
private:
	UPROPERTY(BlueprintReadOnly, Category="Accesibility", meta=(AllowPrivateAccess="true"))
	bool bIsFlashingLightsEnabled{true};

	UPROPERTY(BlueprintReadOnly, Category="Accesibility", meta=(AllowPrivateAccess="true"))
	bool bIsChromaticAberration{true};
	
	bool bHavePlayedTutorial{false};
};
