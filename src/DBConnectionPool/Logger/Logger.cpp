#include "Logger.h"

Logger::Logger() {
    logging::register_simple_formatter_factory<logging::trivial::severity_level, char> ("Severity");
    logging::add_file_log
    (
        keywords::file_name = "sample_%N.log",                                        /*< file name pattern >*/
        keywords::rotation_size = 10 * 1024 * 1024,                                   /*< rotate files every 10 MiB... >*/
        keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0), /*< ...or at midnight >*/
        keywords::format = "[%TimeStamp%][%Severity%]: %Message%",                    /*< log record format >*/
        keywords::auto_flush = true        
    );
    logging::core::get()->set_filter
    (
        logging::trivial::severity >= logging::trivial::debug
    );
    logging::add_common_attributes();
}

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}