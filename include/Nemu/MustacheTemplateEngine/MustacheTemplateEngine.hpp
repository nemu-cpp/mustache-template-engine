/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/nemu-cpp/mustache-template-engine/blob/main/LICENSE.txt
*/

#ifndef _NEMU_CPP_MUSTACHETEMPLATEENGINE_MUSTACHETEMPLATEENGINE_HPP_
#define _NEMU_CPP_MUSTACHETEMPLATEENGINE_MUSTACHETEMPLATEENGINE_HPP_

#include <boost/filesystem/path.hpp>
#include <Nemu/Core.hpp>

namespace Nemu
{

class MustacheTemplateEngine : public TemplatingEngine
{
public:
    MustacheTemplateEngine();

    std::string render() const override;

private:
    boost::filesystem::path m_templatesDirectory;
};

}

#endif
