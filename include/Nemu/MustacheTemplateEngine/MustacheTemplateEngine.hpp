/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/nemu-cpp/mustache-template-engine/blob/main/LICENSE.txt
*/

#ifndef _NEMU_CPP_MUSTACHETEMPLATEENGINE_MUSTACHETEMPLATEENGINE_HPP_
#define _NEMU_CPP_MUSTACHETEMPLATEENGINE_MUSTACHETEMPLATEENGINE_HPP_

#include <Ishiko/Configuration.hpp>
#include <Nemu/WebFramework.hpp>
#include <memory>

namespace Nemu
{

class MustacheTemplateEngine : public TemplateEngine
{
public:
    std::shared_ptr<TemplateEngineProfile> createProfile(const Ishiko::Configuration& configuration) const override;
};

}

#endif
