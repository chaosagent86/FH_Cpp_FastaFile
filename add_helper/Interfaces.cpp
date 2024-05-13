#include <string>
#include <iostream>
#include <fstream>
#include <vector>

// ----------------------------------------------------
// Example of information hiding though interfaces and 
// usage of function polymorphismus.
// ----------------------------------------------------

// Interface contract - hides away any logging details
class Logger
{
    public:
        virtual void log(const std::string &i_message) const = 0;
};

// a concrete implementation
class ConsoleLogger : public Logger
{
    public:
        virtual void log(const std::string &i_message) const 
        {
            std::cout << i_message << std::endl;
         }
};

// another but different implementation of the same function/interface
// creating a polimorphic function/interface.
class FileLogger : public Logger
{
    public:
        FileLogger(const std::string &i_fileName)
        {
            // open file and remember file handle in m_file
        }
    public:
        virtual void log(const std::string &i_message) const 
        {
            // write to log file in m_file
        }

    private:
        std::ofstream m_file;
};

// a more curious altenative implementation.
class MultiLogger : public Logger
{
    public:
        MultiLogger() {}

        void addLogger(Logger *pLogger) { m_loggers.push_back(pLogger); }

    public:
        virtual void log(const std::string &i_message) const 
        {
            // forward to all my loggers
            for (auto *pLogger : m_loggers)
                pLogger->log(i_message);
        }

    private:
        std::vector<Logger *>m_loggers;
};

// unaware of any logging implementations.
void algorithm(Logger *pLogger)
{
    // lots of code that just logs without knowledge of logging gets performed.
    pLogger->log("Hello");
}

int main()
{
    // shows how unaware the 'algorithm' is of the concrete implementation of the interface.
    // we can pass in any of the three loggers.
    FileLogger fLogger("log.txt");
    ConsoleLogger cLogger;
    MultiLogger mLogger;
    mLogger.addLogger(&fLogger);
    mLogger.addLogger(&cLogger);

    algorithm(&mLogger);     // will log to console and file

    return 0;
}