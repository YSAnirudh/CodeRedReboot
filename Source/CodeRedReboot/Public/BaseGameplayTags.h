#pragma once

#include "NativeGameplayTags.h"

namespace BaseGameplayTags
{
	CODEREDREBOOT_API		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Gameplay_AbilityInputBlocked);
	CODEREDREBOOT_API		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Move);

	CODEREDREBOOT_API		FGameplayTag FindTagByString(const FString& GameplayTagString, bool bMatchPartialTag = false);
}