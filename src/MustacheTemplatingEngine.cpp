/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/nemu-cpp/mustache-templating-engine/blob/main/LICENSE.txt
*/

#include "MustacheTemplatingEngine.hpp"
#include <mstch/mstch.hpp>

namespace Nemu
{

MustacheTemplatingEngine::MustacheTemplatingEngine()
{
}

std::string MustacheTemplatingEngine::render() const
{
    std::string view{ "{{#names}}Hi {{name}}!\n{{/names}}" };
    mstch::map context{
      {"names", mstch::array{
        mstch::map{{"name", std::string{"Chris"}}},
        mstch::map{{"name", std::string{"Mark"}}},
        mstch::map{{"name", std::string{"Scott"}}},
      }}
    };

    return mstch::render(view, context);
}

}
