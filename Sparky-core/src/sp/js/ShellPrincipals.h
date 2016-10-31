#pragma once
#include <jsapi.h>

namespace sp { namespace spjs {

	class ShellPrincipals final : public JSPrincipals {
		uint32_t bits;

		static uint32_t getBits(JSPrincipals* p) {
			if (!p)
				return 0xffff;
			return static_cast<ShellPrincipals*>(p)->bits;
		}

	public:
		explicit ShellPrincipals(uint32_t bits, int32_t refcount = 0) : bits(bits) {
			this->refcount = refcount;
		}

		bool write(JSContext* cx, JSStructuredCloneWriter* writer) override {

			return JS_WriteUint32Pair(writer, bits, 0);
		}

		static void destroy(JSPrincipals* principals) {
			MOZ_ASSERT(principals != &fullyTrusted);
			MOZ_ASSERT(principals->refcount == 0);
			js_delete(static_cast<const ShellPrincipals*>(principals));
		}

		static bool subsumes(JSPrincipals* first, JSPrincipals* second) {
			uint32_t firstBits = getBits(first);
			uint32_t secondBits = getBits(second);
			return (firstBits | secondBits) == firstBits;
		}

		static JSSecurityCallbacks securityCallbacks;

		static ShellPrincipals fullyTrusted;
	};

	JSSecurityCallbacks ShellPrincipals::securityCallbacks = {
		nullptr,
		subsumes
	};

	ShellPrincipals ShellPrincipals::fullyTrusted(-1, 1);

} }