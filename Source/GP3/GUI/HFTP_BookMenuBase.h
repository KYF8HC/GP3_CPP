#pragma once

#include "CoreMinimal.h"
#include "Widgets/BookPageWidget.h"
#include "HFTP_BookMenuBase.generated.h"


enum class EGameState : uint8;
class AHFTP_GameMode;

UCLASS(Abstract)
class GP3_API UHFTP_BookMenuBase : public UBookPageWidget
{
	GENERATED_BODY()
public:
	virtual void InitializeMenu();
	virtual void AddListeners();
	void SetSystemReferences(AHFTP_GameMode& GameMode) noexcept;

	EGameState PreviousState{};
protected:

	virtual void Init(ABookMenuActor* InBookMenuActor, int32 InPageSectionIndex, int32 InPageIndex) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "System References", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AHFTP_GameMode> GameModeRef{};

};
