/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/nemu-cpp/mustache-template-engine/blob/main/LICENSE.txt
*/

#include "MustacheTemplateEngineProfile.hpp"
#include <Ishiko/Process.hpp>
#include <Ishiko/FileSystem.hpp>
#include <mstch/mstch.hpp>

using namespace Nemu;

MustacheTemplateEngineProfile::Options::Options(const std::string& templatesRootDirectory)
{
    m_templatesRootDirectory =
        Ishiko::CurrentEnvironment::ExpandVariablesInString(templatesRootDirectory,
            Ishiko::CurrentEnvironment::SubstitutionFormat::DollarAndCurlyBrackets);
}

MustacheTemplateEngineProfile::Options::Options(const std::string& templatesRootDirectory,
    const std::string* layoutsRootDirectory)
{
    m_templatesRootDirectory =
        Ishiko::CurrentEnvironment::ExpandVariablesInString(templatesRootDirectory,
            Ishiko::CurrentEnvironment::SubstitutionFormat::DollarAndCurlyBrackets);
    if (layoutsRootDirectory)
    {
        m_layoutsRootDirectory =
            Ishiko::CurrentEnvironment::ExpandVariablesInString(*layoutsRootDirectory,
                Ishiko::CurrentEnvironment::SubstitutionFormat::DollarAndCurlyBrackets);
    }
}

const boost::filesystem::path& MustacheTemplateEngineProfile::Options::templatesRootDirectory() const
{
    return m_templatesRootDirectory;
}

const boost::optional<boost::filesystem::path>& MustacheTemplateEngineProfile::Options::layoutsRootDirectory() const
{
    return m_layoutsRootDirectory;
}

MustacheTemplateEngineProfile::MustacheTemplateEngineProfile(Options options)
    : m_options(std::move(options))
{
}

std::string MustacheTemplateEngineProfile::render(const std::string& view, ViewContext& context,
    const std::string* layout)
{
    // TODO: load view from disk
    Ishiko::Error error;
    // TODO: handle error
    boost::filesystem::path templatePath = m_options.templatesRootDirectory() / view;
    std::string viewTemplate = Ishiko::FileSystem::ReadFile(templatePath, error);

    // TODO: this is annoying I should modify mustache implementation to make this integration easier
    mstch::map mustacheContext;
    for (const std::pair<std::string, ViewContext::Value>& item : context.toMap())
    {
        switch (item.second.type())
        {
        case ViewContext::Value::Type::string:
            mustacheContext.emplace(item.first, item.second.asString());
            break;

        case ViewContext::Value::Type::valueArray:
            {
                mstch::array items;
                for (const ViewContext::Value& v : item.second.asValueArray())
                {
                    switch (v.type())
                    {
                    case ViewContext::Value::Type::string:
                        items.push_back(mstch::map{ { "item", v.asString() } });
                        break;

                    case ViewContext::Value::Type::valueArray:
                        // TODO
                        break;

                    case ViewContext::Value::Type::valueMap:
                        {
                            // TODO: we only support 1 level of nesting. I need to make a "recursive" function out of
                            // this and merge with the valueMap case below
                            mstch::map items1;
                            for (const std::pair<std::string, ViewContext::Value>& item : v.asValueMap())
                            {
                                // TODO: we only cope with string values for now
                                items1.emplace(item.first, item.second.asString());
                            }
                            items.push_back(items1);
                        }
                        break;

                    default:
                        // TODO: error
                        break;
                    }
                }
                mustacheContext.emplace(item.first, std::move(items));
            }
            break;

        case ViewContext::Value::Type::valueMap:
            {
                mstch::map items;
                for (const std::pair<std::string, ViewContext::Value>& item : item.second.asValueMap())
                {
                    // TODO: we only cope with string values for now
                    items.emplace(item.first, item.second.asString());
                }
                mustacheContext.emplace(item.first, std::move(items));
            }
        break;

        default:
            // TODO error
            break;
        }
    }

    if (!layout)
    {
        return mstch::render(viewTemplate, mustacheContext);
    }
    else
    {
        // TODO: handle error and case where layotuRootDir is null
        boost::filesystem::path layoutPath = *m_options.layoutsRootDirectory() / *layout;
        std::string viewLayout = Ishiko::FileSystem::ReadFile(layoutPath, error);

        return mstch::render(viewLayout, mustacheContext, { {"content", viewTemplate} });
    }
}

const MustacheTemplateEngineProfile::Options& MustacheTemplateEngineProfile::options() const noexcept
{
    return m_options;
}
