/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/nemu-cpp/mustache-template-engine/blob/main/LICENSE.txt
*/

#include "MustacheTemplateEngine.hpp"
#include "MustacheTemplateEngineProfile.hpp"

using namespace Nemu;

std::shared_ptr<TemplateEngineProfile> MustacheTemplateEngine::createProfile(
    const Ishiko::Configuration& configuration) const
{
    // TODO: validate configuration
    MustacheTemplateEngineProfile::Options options(configuration.value("templates-root-directory"),
        configuration.valueOrNull("layouts-root-directory"));
    return std::make_shared<MustacheTemplateEngineProfile>(options);
}
