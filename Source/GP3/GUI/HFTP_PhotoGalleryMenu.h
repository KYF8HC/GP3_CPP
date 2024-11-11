#pragma once

#include "CoreMinimal.h"
#include "HFTP_BookMenuBase.h"
#include "HFTP_PhotoGalleryMenu.generated.h"

class UHFTP_IndividualPhoto;
class UWrapBox;
class UScrollBox;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnIndividualPhotoClicked, UTextureRenderTarget2D*, PhotoTexture);

UCLASS(Abstract)
class GP3_API UHFTP_PhotoGalleryMenu : public UHFTP_BookMenuBase
{
	GENERATED_BODY()


public:
	
	UPROPERTY(VisibleAnywhere, Category= "PhotoGallery", meta=(BindWidget))
	TObjectPtr<UScrollBox> PhotoScrollBox{};

	UPROPERTY(VisibleAnywhere, Category= "PhotoGallery", meta=(BindWidget))
	TObjectPtr<UWrapBox> PhotoWrapBox{};

	UFUNCTION()
	void OnPhotoClicked(UTextureRenderTarget2D* PhotoTexture);
	UFUNCTION()
	void RefreshPhotoGallery(bool bShouldRefresh);

	FOnIndividualPhotoClicked OnIndividualPhotoClicked;

protected:
	virtual void Init(ABookMenuActor* InBookMenuActor, int32 InPageSectionIndex, int32 InPageIndex) override;

private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PhotoGallery", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UHFTP_IndividualPhoto> IndividualPhotoClass{};
};
