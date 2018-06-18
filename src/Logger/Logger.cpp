#include "Logger.h"

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

void Logger::init(std::string string) {
    logging::register_simple_formatter_factory<logging::trivial::severity_level, char> ("Severity");
    logging::add_file_log
    (
        keywords::file_name = "sample_%N.log",                                        /*< file name pattern >*/
        keywords::rotation_size = 10 * 1024 * 1024,                                   /*< rotate files every 10 MiB... >*/
        keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0), /*< ...or at midnight >*/
        keywords::format = "[%TimeStamp%] [%Severity%]: %Message%",                    /*< log record format >*/
        keywords::auto_flush = true        
    );


    changeSeverity(string);
    logging::add_common_attributes();
}

void Logger::changeSeverity(std::string sev_lvl) {
    auto a = logging::trivial::debug;
    
    if (sev_lvl == "debug") a = logging::trivial::debug;
    else if (sev_lvl == "info") a = logging::trivial::info;
    else if (sev_lvl == "warning") a = logging::trivial::warning;
    else if (sev_lvl == "error") a = logging::trivial::error;
    else if (sev_lvl == "fatal") a = logging::trivial::fatal;
    
    logging::core::get()->set_filter
    (
        logging::trivial::severity >= a 
    );
}
