// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/common/string_view.h>
#include <iostream>
#include <cassert>
#include <type_traits>
#include <exception>

namespace aeon::Common
{

enum class ExpectAction
{
    None,
    Assert,
    Log,
    Exception,
    Terminate
};

template <ExpectAction ActionT = ExpectAction::Terminate, typename ConditionT>
constexpr void Expect([[maybe_unused]] ConditionT c,
                      [[maybe_unused]] const char *errorMessage) noexcept(ActionT != ExpectAction::Exception)
{
    bool conditionResult;
    if constexpr (std::is_same_v<std::decay_t<ConditionT>, bool>)
        conditionResult = c;
    else
        conditionResult = c();

    if constexpr (ActionT == ExpectAction::Assert)
    {
        assert(conditionResult);
    }
    else if constexpr (ActionT == ExpectAction::Log)
    {
        if (!conditionResult)
            std::cerr << errorMessage << '\n';
    }
    else if constexpr (ActionT == ExpectAction::Exception)
    {
        if (!conditionResult)
            throw std::runtime_error{errorMessage};
    }
    else if constexpr (ActionT == ExpectAction::Terminate)
    {
        if (!conditionResult)
            std::terminate();
    }
}

template <ExpectAction ActionT = ExpectAction::Terminate, typename ConditionT>
constexpr void Expect([[maybe_unused]] ConditionT c,
                      [[maybe_unused]] const StringView errorMessage) noexcept(ActionT != ExpectAction::Exception)
{
    expect<ActionT>(std::forward<ConditionT>(c), std::data(errorMessage));
}

template <ExpectAction ActionT = ExpectAction::Terminate, typename ConditionT>
constexpr void Expect([[maybe_unused]] ConditionT c) noexcept(ActionT != ExpectAction::Exception)
{
    expect<ActionT>(std::forward<ConditionT>(c), "Expectation failed.");
}

} // namespace aeon::Common
