#pragma once

#include "RE/B/BSTArray.h"
#include "RE/B/BaseFormComponent.h"

namespace RE
{
	class BGSLayeredMaterialSwap;
	class BGSModelMaterialSwap;

	class TESModel : public BaseFormComponent
	{
	public:
		SF_RTTI_VTABLE(TESModel);

		~TESModel() override;  // 00

		// override (BaseFormComponent)
		const BSFixedString& GetFormComponentType() const override;  // 01 - { return "TESModel_Component"; }
		void                 InitializeDataComponent() override;     // 02

		// add
		virtual void                  Unk_0B();                  // 0B
		virtual void                  Unk_0C();                  // 0C
		virtual BGSModelMaterialSwap* GetAsModelMaterialSwap();  // 0E

		class MaterialSwapVisitor
		{
		public:
			virtual ~MaterialSwapVisitor() = default;  // 00

			// Called with the engine's material swap lock held: copy what you need and return.
			virtual void Visit(const BSTArray<BGSLayeredMaterialSwap*>& a_swaps) = 0;  // 01
		};

		// Calls a_visitor with the layered material swaps registered for this model, if any.
		void VisitMaterialSwaps(MaterialSwapVisitor& a_visitor) const
		{
			using func_t = void (*)(const TESModel*, MaterialSwapVisitor*, bool);
			static REL::Relocation<func_t> func{ ID::TESModel::VisitMaterialSwaps };
			func(this, std::addressof(a_visitor), false);  // false: don't create an empty entry
		}

		// members
		BSFixedString model;  // 08
		std::uint64_t unk10;  // 10
		std::uint32_t unk18;  // 18
		std::uint16_t unk1C;  // 1C
		std::uint16_t pad1E;  // 1E
	};
	static_assert(sizeof(TESModel) == 0x20);
}
