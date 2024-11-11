#pragma once

#include "CoreMinimal.h"
#include "HFTP_BookMenuBase.h"
#include "HFTP_SketchesMenuLeftPage.generated.h"

struct FHFTP_ObjectiveData;
class UHFTP_ObjectiveDataAsset;
class UHFTP_ObjectiveSystem;
class UButton;
class UImage;

UCLASS(Abstract)
class GP3_API UHFTP_SketchesMenuLeftPage : public UHFTP_BookMenuBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sketches", meta = (BindWidget))
	TObjectPtr<UImage> BackgroundImage{};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sketches", meta = (BindWidget))
	TObjectPtr<UImage> SketchImage{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sketches", meta = (BindWidget))
	TObjectPtr<UButton> PreviousPageButton{};

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