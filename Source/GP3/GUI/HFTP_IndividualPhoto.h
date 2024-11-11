#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HFTP_IndividualPhoto.generated.h"

class UImage;
class UButton;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnButtonClicked, UTextureRenderTarget2D*, ButtonIndex);
UCLASS(Abstract)
class GP3_API UHFTP_IndividualPhoto : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Photo", meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UImage> PhotoDisplay{};
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Photo", meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UButton> PhotoButton{};


	UFUNCTION()
	void HandleButtonClick();
protected:
	virtual void NativeConstruct() override;
public:
	////////////////////
	// CONSTR & DESTR //
	////////////////////
	virtual ~UHFTP_IndividualPhoto() override;


	////////////////////
	// REFS & POINTERS//
	////////////////////
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UTextureRenderTarget2D> PhotoTexture;
	

	///////////////////
	// FUNC & EVENTS //
	///////////////////
	FOnButtonClicked OnButtonClicked;

	UFUNCTION(BlueprintImplementableEvent)
	void InitPhoto();

};
