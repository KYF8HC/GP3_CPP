#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HFTP_MenuBase.generated.h"

enum class EGameState : uint8;
class UHFTP_SoundManager;
class AHFTP_GameMode;

UCLASS(Abstract)
class UHFTP_MenuBase : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void InitializeMenu();
	virtual void AddListeners();
	void EnableWidget(bool bEnable);
	void SetSystemReferences(AHFTP_GameMode& GameMode) noexcept;

	EGameState PreviousState{};
protected:

	UPROPERTY(BlueprintReadOnly, Category = "References", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AHFTP_GameMode> GameModeRef{};
};
