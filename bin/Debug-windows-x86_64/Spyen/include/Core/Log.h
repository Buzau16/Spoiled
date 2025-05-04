#pragma once

#pragma warning(push)
#pragma warning(disable: 4251)

#include "Core/Core.h"

namespace spdlog {
	class logger;
}

namespace Spyen {
	class SPYEN_API Log
	{
	public:
		static void Init();

		static void CoreInfo(const std::string& msg);
		static void CoreWarn(const std::string& msg);
		static void CoreError(const std::string& msg);
		static void CoreCritical(const std::string& msg);

		static void ClientInfo(const std::string& msg);
		static void ClientWarn(const std::string& msg);
		static void ClientError(const std::string& msg);
		static void ClientCritical(const std::string& msg);

	};

}

#pragma warning(pop)