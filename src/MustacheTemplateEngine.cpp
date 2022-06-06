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
    const Ishiko::Configuration::Value* layoutsRootDirectory = configuration.valueOrNull("layouts-root-directory");
    MustacheTemplateEngineProfile::Options options(configuration.value("templates-root-directory").asString(),
        (layoutsRootDirectory ? &layoutsRootDirectory->asString() : nullptr));
    return std::make_shared<MustacheTemplateEngineProfile>(options);
}
