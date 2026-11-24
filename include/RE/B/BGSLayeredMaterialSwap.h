#pragma once

#include "RE/B/BGSKeyword.h"
#include "RE/B/BGSReflectedForm.h"
#include "RE/B/BSFixedString.h"
#include "RE/B/BSTArray.h"

namespace RE
{
	class BGSLayeredMaterialSwap :
		public BGSReflectedForm,                         // 00
		public BSTEventSink<BGSKeyword::OnDestroyEvent>  // 38
	{
	public:
		SF_RTTI_VTABLE(BGSLayeredMaterialSwap);
		SF_FORMTYPE(LMSW);

		enum class SOURCE
		{
			kNone = 0,
			kModelOnly = 1,
			kRefDefined = 2,
			kBiome = 3,
			kObjectTemplate = 4,
			kSkin = 5,
			kPackin = 6
		};

		struct Entry
		{
		public:
			// members
			BSFixedString key;                   // 000 - material being replaced
			void*         keyMaterialPathForm;   // 008
			BSFixedString overrideMaterialPath;  // 010
			std::byte     unk018[0x1A8];         // 018
		};
		static_assert(sizeof(Entry) == 0x1C0);

		~BGSLayeredMaterialSwap() override;  // 00

		// members
		BSTArray<BGSKeyword*> keywords;        // 40
		BSTArray<Entry>       entries;         // 50
		BSTArray<void*>       swapCollection;  // 60
	};
	static_assert(offsetof(BGSLayeredMaterialSwap, entries) == 0x50);
	static_assert(sizeof(BGSLayeredMaterialSwap) == 0x70);
}
