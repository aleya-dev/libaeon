// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/logger/log_sink.h>
#include <aeon/logger/base_backend.h>
#include <aeon/logger/log_level.h>
#include <set>

namespace aeon::logger
{

class simple_sink_backend : public base_backend
{
public:
    simple_sink_backend();

    ~simple_sink_backend() override = default;

    explicit simple_sink_backend(const log_level level);

    void add_sink(log_sink *sink);

    void remove_all_sinks();

private:
    void log(const common::string &message, const common::string &module, const log_level level) override;

    std::set<log_sink *> sinks_;
};

} // namespace aeon::logger
