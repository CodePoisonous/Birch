#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Birch
{
	class BIRCH_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// Core log macros
#define BC_CORE_TRACE(...)	::Birch::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define BC_CORE_INFO(...)	::Birch::Log::GetCoreLogger()->info(__VA_ARGS__)
#define BC_CORE_WARN(...)	::Birch::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define BC_CORE_ERROR(...)	::Birch::Log::GetCoreLogger()->error(__VA_ARGS__)
#define BC_CORE_FATAL(...)	::Birch::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define BC_TRACE(...)	::Birch::Log::GetClientLogger()->trace(__VA_ARGS__)
#define BC_INFO(...)	::Birch::Log::GetClientLogger()->info(__VA_ARGS__)
#define BC_WARN(...)	::Birch::Log::GetClientLogger()->warn(__VA_ARGS__)
#define BC_ERROR(...)	::Birch::Log::GetClientLogger()->error(__VA_ARGS__)
#define BC_FATAL(...)	::Birch::Log::GetClientLogger()->fatal(__VA_ARGS__)
