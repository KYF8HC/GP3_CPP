#pragma once

#include "CoreMinimal.h"
#include "HFTP_BookMenuBase.h"
#include "HFTP_PhotoGalleryMenuRight.generated.h"

class UBorder;
class UHFTP_PhotoGalleryMenu;
class UButton;
class UImage;

UCLASS(Abstract)
class GP3_API UHFTP_PhotoGalleryMenuRight : public UHFTP_BookMenuBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UTextureRenderTarget2D> BigPhotoTexture;

	UFUNCTION(BlueprintImplementableEvent)
	void InitBigPhoto();
protected:
	UFUNCTION()
	void SetBigPhotoTexture(UTextureRenderTarget2D* PhotoTexture);
	virtual void Init(ABookMenuActor* InBookMenuActor, int32 InPageSectionIndex, int32 InPageIndex) override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Buttons", meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UBorder> Border;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Buttons", meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UImage> BigPhoto{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Buttons", meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UButton> NextPageButton{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PhotoGallery", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UHFTP_PhotoGalleryMenu> PhotoGalleryMenuRef{};
};
