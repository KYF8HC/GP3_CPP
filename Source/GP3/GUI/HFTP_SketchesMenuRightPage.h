#pragma once

#include "CoreMinimal.h"
#include "HFTP_BookMenuBase.h"
#include "HFTP_SketchesMenuRightPage.generated.h"

struct FHFTP_ObjectiveData;
class UHFTP_ObjectiveDataAsset;
class UHFTP_ObjectiveSystem;
class UImage;
class UButton;
class UTextBlock;

UCLASS(Abstract)
class GP3_API UHFTP_SketchesMenuRightPage : public UHFTP_BookMenuBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sketches", meta = (BindWidget))
	TObjectPtr<UImage> BackgroundImage{};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sketches", meta = (BindWidget))
	TObjectPtr<UTextBlock> SketchTitle{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sketches", meta = (BindWidget))
	TObjectPtr<UTextBlock> SketchDesc{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sketches", meta = (BindWidget))
	TObjectPtr<UButton> NextPageButton{};
protected:
	virtual void Init(ABookMenuActor* InBookMenuActor, int32 InPageSectionIndex, int32 InPageIndex) override;
private:
	
	UFUNCTION()
	void OnObjectiveCompleted(const FHFTP_ObjectiveData& ObjectiveData);

	UFUNCTION()
	void OnRestartGame();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ObjectiveSystem", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UHFTP_ObjectiveSystem> ObjectiveSystemRef{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ObjectiveSystem", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UHFTP_ObjectiveDataAsset> ObjectiveRef{};
};
