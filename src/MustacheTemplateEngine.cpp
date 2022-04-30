/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/nemu-cpp/mustache-template-engine/blob/main/LICENSE.txt
*/

#include "MustacheTemplateEngine.hpp"
#include <Ishiko/FileSystem.hpp>
#include <mstch/mstch.hpp>

namespace Nemu
{

MustacheTemplateEngine::MustacheTemplateEngine()
{
}

std::string MustacheTemplateEngine::render(const std::string& view, ViewContext& context)
{
    // TODO: load view from disk
    Ishiko::Error error;
    // TODO: handle error
    std::string viewTemplate = Ishiko::FileSystem::ReadFile("C:\\Data\\Projects\\nemu\\cpp\\mustache-template-engine\\examples\\mustache-templates\\data\\views\\index.html", error);

    // TODO: this is annoying I should modify mustache implementation to make this integration easier
    mstch::map mustacheContext;
    for (const std::pair<std::string, std::string>& item : context)
    {
        mustacheContext.emplace(item);
    }

    return mstch::render(view, mustacheContext);
}

}
