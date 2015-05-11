#ifndef aeon_logger_base_backend_h__
#define aeon_logger_base_backend_h__

namespace aeon
{
namespace logger
{

class base_backend
{
friend class logger_stream;
public:
    base_backend() :
        level_(log_level::message)
    {
    }

    base_backend(log_level level) :
        level_(level)
    {
    }

    base_backend(const base_backend&) = delete;

    virtual ~base_backend()
    {
    }

    void set_log_level(log_level level)
    {
        level_ = level;
    }

    log_level get_log_level() const
    {
        return level_;
    }

    virtual void log(std::string &&message, log_level level) = 0;

private:
    void handle_log_(std::string &&message, log_level level)
    {
        if (level >= level_)
            log(std::move(message), level);
    }

    log_level level_;
};

} // namespace logger
} // namespace aeon

#endif // aeon_logger_base_backend_h__
