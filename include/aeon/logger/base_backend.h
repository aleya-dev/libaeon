/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2015 Robin Degen
 * All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains the property of
 * Robin Degen and its suppliers, if any. The intellectual and technical
 * concepts contained herein are proprietary to Robin Degen and its suppliers
 * and may be covered by U.S. and Foreign Patents, patents in process, and are
 * protected by trade secret or copyright law. Dissemination of this
 * information or reproduction of this material is strictly forbidden unless
 * prior written permission is obtained from Robin Degen.
 */

#pragma once

namespace aeon
{
namespace logger
{

class base_backend
{
    friend class logger_stream;

public:
    base_backend()
        : level_(log_level::message)
    {
    }

    base_backend(log_level level)
        : level_(level)
    {
    }

    base_backend(const base_backend &) = delete;

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
