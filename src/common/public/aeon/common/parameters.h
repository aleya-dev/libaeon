// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/common/string.h>
#include <vector>
#include <cstring>

namespace aeon::Common
{

// Simple wrapper to convert a vector of strings to a char*[].
class Parameters
{
public:
    explicit Parameters(std::vector<String> &params)
        : m_argc(0)
        , m_argv(new char *[params.size()])
    {
        for (auto &param : params)
        {
            m_argv[m_argc] = new char[param.Size() + 1];
            memcpy(m_argv[m_argc], param.Data(), param.Size() + 1);
            ++m_argc;
        }
    }

    ~Parameters()
    {
        if (!m_argv)
            return;

        for (int i = 0; i < m_argc; ++i)
        {
            delete[] m_argv[i];
        }

        delete[] m_argv;
    }

    Parameters(const Parameters &) = delete;
    auto operator=(const Parameters &) -> Parameters & = delete;

    Parameters(Parameters &&other) noexcept
        : m_argc{other.m_argc}
        , m_argv{other.m_argv}
    {
        other.m_argc = 0;
        other.m_argv = nullptr;
    }

    Parameters &operator=(Parameters &&other) noexcept
    {
        m_argc = other.m_argc;
        m_argv = other.m_argv;
        other.m_argc = 0;
        other.m_argv = nullptr;
        return *this;
    }

    [[nodiscard]] auto Argc() const
    {
        return m_argc;
    }

    [[nodiscard]] auto Argv() const
    {
        return m_argv;
    }

private:
    int m_argc;
    char **m_argv;
};

} // namespace aeon::Common
