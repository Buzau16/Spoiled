#include "spypch.h"
#include "Core/Log.h"


namespace Spyen {
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void DeleteExecessLogFiles() {
		uint32_t fileCount = 0;
		using Dir_Iterator = std::filesystem::directory_iterator;
		std::vector<std::filesystem::directory_entry> files;
		for (auto& file : Dir_Iterator("logs")) {
			//SPY_CORE_INFO("File in logs : {0}", file.path().string());
			files.push_back(file);
			++fileCount;
		}

		if (fileCount > 10) {
			std::sort(files.begin(), files.end(),
				[](const std::filesystem::directory_entry& a, const std::filesystem::directory_entry& b) {
				return std::filesystem::last_write_time(a) < std::filesystem::last_write_time(b);
				});
			for (size_t i = 0; i < files.size() - 10; i++) {
				//SPY_CORE_INFO("Deleting log file: {0}", files[i].path().string());
				std::filesystem::remove(files[i].path());
			}
		}
	}

	std::string GetTimestampedFilename()
	{
		auto now = std::chrono::system_clock::now();
		auto t = std::chrono::system_clock::to_time_t(now);
		std::tm tm;
#ifdef _WIN32
		localtime_s(&tm, &t);
#else
		localtime_r(&t, &tm);
#endif
		std::ostringstream oss;
		oss << "logs/Spyen-"
			<< std::put_time(&tm, "%Y-%m-%d_%H-%M-%S")
			<< ".log";
		return oss.str();
	}

	void Log::Init()
	{
		std::vector<spdlog::sink_ptr> logSinks;
		// Colored console sink
		logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
		// File sink
		std::string filename = GetTimestampedFilename();
		
		logSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>(filename, true));

		// Set the pattern for both sinks (as shown in your Log.cpp)
		logSinks[0]->set_pattern("%^[%T] %n: %v%$");
		logSinks[1]->set_pattern("[%T] [%l] %n: %v");

		// Create loggers with multiple sinks
		s_CoreLogger = std::make_shared<spdlog::logger>("SPYEN", begin(logSinks), end(logSinks));
		spdlog::register_logger(s_CoreLogger);
		s_CoreLogger->set_level(spdlog::level::trace);
		s_CoreLogger->flush_on(spdlog::level::trace);

		s_ClientLogger = std::make_shared<spdlog::logger>("APP", begin(logSinks), end(logSinks));
		spdlog::register_logger(s_ClientLogger);
		s_ClientLogger->set_level(spdlog::level::trace);
		s_ClientLogger->flush_on(spdlog::level::trace);
	
		DeleteExecessLogFiles();
	}
}