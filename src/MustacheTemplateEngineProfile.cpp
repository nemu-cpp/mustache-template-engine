/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/nemu-cpp/mustache-template-engine/blob/main/LICENSE.txt
*/

#include "MustacheTemplateEngineProfile.hpp"
#include <Ishiko/Process.hpp>
#include <Ishiko/FileSystem.hpp>
#include <mstch/mstch.hpp>
#include <map>

using namespace Nemu;

namespace
{

void Add(const ViewContext::Value& value, mstch::node& mustacheNode)
{
    // To avoid the use of a recursive function we use an explicit stack to process the input. We think the additional
    // complexity is justified by the fact that this function may end up processing untrusted input data.
    // 
    // Each pair on the stack contains:
    //   - a value that has not been added to the mstch data structure,
    //   - a reserved unitialized node into which that value should be copied.
    // At each step of the loop:
    //   1. we take the element at the front of the queue and copy it into the reserved unitialized node,
    //   2. create a new reserved unitialized node for each children value of the element,
    //   3. add new items at the back of the stack for each of the children and their uninitialized reserved nodes.

    // TODO: we should also set a limit to the size of the stack. Although if we can't hold the stack in memory then
    // the input data structure itseld is probably so big it wouldn't fit in memory.

    std::vector<std::pair<const ViewContext::Value*, mstch::node*>> stack = { { &value, &mustacheNode } };
    while (!stack.empty())
    {
        const ViewContext::Value* currentValue = stack.front().first;
        mstch::node* currentUnitializedNode = stack.front().second;
        stack.erase(stack.begin());

        switch (currentValue->type())
        {
        case ViewContext::Value::Type::string:
            // A string has no children so there is nothing to push on the stack.
            *currentUnitializedNode = currentValue->asString();
            break;

        case ViewContext::Value::Type::valueArray:
            {
                // For an array we create a new array node and add N unitialized child nodes where N is the size of the
                // array. We add a new item on the stack for each child value and its reserved node.
                const std::vector<ViewContext::Value>& srcArray = currentValue->asValueArray();
                *currentUnitializedNode = mstch::array();
                mstch::array& dstArray = boost::get<mstch::array>(*currentUnitializedNode);
                // It is imperative to reserve the right capacity for the array as we are adding a pointer to the last
                // element at each iteration. The pointers would become invalid if the array was reallocated. 
                dstArray.reserve(srcArray.size());
                for (std::vector<ViewContext::Value>::const_iterator it = srcArray.begin(); it != srcArray.end(); ++it)
                {
                    dstArray.push_back(mstch::node());
                    stack.emplace_back(&(*it), &dstArray.back());
                }
            }
            break;

        case ViewContext::Value::Type::valueMap:
            {
                // For a map we create a new map node and add unitialized nodes to each for each item in the map. We
                // add a new item on the stack for each child value and its reserved node.
                *currentUnitializedNode = mstch::map();
                mstch::map& dstMap = boost::get<mstch::map>(*currentUnitializedNode);
                const std::map<std::string, ViewContext::Value>& srcMap = currentValue->asValueMap();
                for (std::map<std::string, ViewContext::Value>::const_iterator it = srcMap.begin(); it != srcMap.end();
                    ++it)
                {
                    stack.emplace_back(&it->second, &dstMap[it->first]);
                }
            }
            break;

        default:
            // TODO error
            break;
        }
    }
}

}

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
        Add(item.second, mustacheContext[item.first]);
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
