#pragma once

#include "NativeGameplayTags.h"

namespace BaseGameplayTags
{
	CODEREDREBOOT_API		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Gameplay_AbilityInputBlocked);
	CODEREDREBOOT_API		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Gameplay_InHub);
	CODEREDREBOOT_API		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Gameplay_GOW);
	CODEREDREBOOT_API		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Gameplay_SpiderMan);
	CODEREDREBOOT_API		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Gameplay_Control);
	CODEREDREBOOT_API		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Move);
	CODEREDREBOOT_API		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Jump);
	CODEREDREBOOT_API		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Interact);
	CODEREDREBOOT_API		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Menu);

	CODEREDREBOOT_API		FGameplayTag FindTagByString(const FString& GameplayTagString, bool bMatchPartialTag = false);
}