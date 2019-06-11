#pragma once

#include <string>

namespace xml {
	namespace detail {

		struct TagToken
		{
			enum class Type
			{
				OPENING,
				CLOSING,
				SELF_CLOSING,
			};

			std::string identifier;
			Type type;
			std::string attributes;
		};

	}
}
