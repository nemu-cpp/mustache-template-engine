/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/nemu-cpp/mustache-template-engine/blob/main/LICENSE.txt
*/

#include "MustacheTemplateEngine.hpp"
#include <Ishiko/FileSystem.hpp>
#include <Ishiko/Process.hpp>
#include <mstch/mstch.hpp>

using namespace Nemu;

MustacheTemplateEngine::Options::Options(const std::string& templatesRootDirectory)
{
    m_templatesRootDirectory = 
        Ishiko::CurrentEnvironment::ExpandVariablesInString(templatesRootDirectory,
            Ishiko::CurrentEnvironment::SubstitutionFormat::DollarAndCurlyBrackets);
}

MustacheTemplateEngine::Options::Options(const std::string& templatesRootDirectory,
    const std::string& layoutsRootDirectory)
{
    m_templatesRootDirectory =
        Ishiko::CurrentEnvironment::ExpandVariablesInString(templatesRootDirectory,
            Ishiko::CurrentEnvironment::SubstitutionFormat::DollarAndCurlyBrackets);
    m_layoutsRootDirectory =
        Ishiko::CurrentEnvironment::ExpandVariablesInString(layoutsRootDirectory,
            Ishiko::CurrentEnvironment::SubstitutionFormat::DollarAndCurlyBrackets);
}

const boost::filesystem::path& MustacheTemplateEngine::Options::templatesRootDirectory() const
{
    return m_templatesRootDirectory;
}

const boost::optional<boost::filesystem::path>& MustacheTemplateEngine::Options::layoutsRootDirectory() const
{
    return m_layoutsRootDirectory;
}

MustacheTemplateEngine::MustacheTemplateEngine(Options options)
    : m_options(std::move(options))
{
}

std::string MustacheTemplateEngine::render(const std::string& view, ViewContext& context)
{
    // TODO: load view from disk
    Ishiko::Error error;
    // TODO: handle error
    boost::filesystem::path templatePath = m_options.templatesRootDirectory() / view;
    std::string viewTemplate = Ishiko::FileSystem::ReadFile(templatePath, error);

    // TODO: this is annoying I should modify mustache implementation to make this integration easier
    mstch::map mustacheContext;
    for (const std::pair<std::string, std::string>& item : context)
    {
        mustacheContext.emplace(item);
    }

    return mstch::render(viewTemplate, mustacheContext);
}

std::string MustacheTemplateEngine::render(const std::string& view, ViewContext& context, const std::string& layout)
{
    // TODO: load view from disk
    Ishiko::Error error;
    // TODO: handle error
    boost::filesystem::path templatePath = m_options.templatesRootDirectory() / view;
    std::string viewTemplate = Ishiko::FileSystem::ReadFile(templatePath, error);

    // TODO: handle error and case where layotuRootDir is null
    boost::filesystem::path layoutPath = *m_options.layoutsRootDirectory() / layout;
    std::string viewLayout = Ishiko::FileSystem::ReadFile(layoutPath, error);

    // TODO: this is annoying I should modify mustache implementation to make this integration easier
    mstch::map mustacheContext;
    for (const std::pair<std::string, std::string>& item : context)
    {
        mustacheContext.emplace(item);
    }

    return mstch::render(viewLayout, mustacheContext, { {"content", viewTemplate} });
}
