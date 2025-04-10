#include "spypch.h"
#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"


namespace Spyen {
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

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
	}

    

   /* void Log::LogToFile(std::shared_ptr<spdlog::logger>&)
    {
        std::filesystem::create_directory("logs");

        auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(GetTimestampedFilename(), true);
        fileSink->set_pattern("[%T] [%l] %n: %v");
        s_CoreLogger->sinks().push_back(fileSink);
        s_ClientLogger->sinks().push_back(fileSink);
    }*/
}