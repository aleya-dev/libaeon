// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/logger/base_backend.h>

namespace aeon::logger
{

base_backend::base_backend()
    : level_(log_level::message)
{
}

base_backend::base_backend(const log_level level)
    : level_(level)
{
}

void base_backend::set_log_level(const log_level level)
{
    level_ = level;
}

auto base_backend::get_log_level() const -> log_level
{
    return level_;
}

void base_backend::handle_log(const common::string &message, const common::string &module, const log_level level)
{
    if (level >= level_)
        log(message, module, level);
}

} // namespace aeon::logger
