/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/nemu-cpp/mustache-template-engine/blob/main/LICENSE.txt
*/

#ifndef _NEMU_CPP_MUSTACHETEMPLATEENGINE_MUSTACHETEMPLATEENGINE_HPP_
#define _NEMU_CPP_MUSTACHETEMPLATEENGINE_MUSTACHETEMPLATEENGINE_HPP_

#include <boost/filesystem/path.hpp>
#include <Nemu/WebFramework.hpp>
#include <boost/optional.hpp>
#include <string>

namespace Nemu
{

class MustacheTemplateEngine : public TemplateEngine
{
public:
    class Options
    {
    public:
        // TODO: this can contain env variables that will be subsituted
        // TODO: error if subsitution fails
        Options(const std::string& templatesRootDirectory);
        Options(const std::string& templatesRootDirectory, const std::string& layoutsRootDirectory);

        const boost::filesystem::path& templatesRootDirectory() const;
        const boost::optional<boost::filesystem::path>& layoutsRootDirectory() const;

    private:
        boost::filesystem::path m_templatesRootDirectory;
        boost::optional<boost::filesystem::path> m_layoutsRootDirectory;
    };

    MustacheTemplateEngine(Options options);

    std::string render(const std::string& view, ViewContext& context) override;
    std::string render(const std::string& view, ViewContext& context, const std::string& layout) override;

private:
    Options m_options;
};

}

#endif
