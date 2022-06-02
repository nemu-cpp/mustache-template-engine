/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/nemu-cpp/mustache-template-engine/blob/main/LICENSE.txt
*/

#include "MustacheTemplateEngineTests.hpp"
#include "Nemu/MustacheTemplateEngine/MustacheTemplateEngine.hpp"
#include "Nemu/MustacheTemplateEngine/MustacheTemplateEngineProfile.hpp"
#include <Ishiko/Configuration.hpp>
#include <memory>

using namespace Ishiko;
using namespace Nemu;

MustacheTemplateEngineTests::MustacheTemplateEngineTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "MustacheTemplateEngine tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("createProfile test 1", CreateProfileTest1);
    append<HeapAllocationErrorsTest>("createProfile test 2", CreateProfileTest2);
}

void MustacheTemplateEngineTests::ConstructorTest1(Test& test)
{
    MustacheTemplateEngine templateEngine;

    ISHIKO_TEST_PASS();
}

void MustacheTemplateEngineTests::CreateProfileTest1(Test& test)
{
    MustacheTemplateEngine templateEngine;

    Ishiko::Configuration configuration;
    configuration.set("templates-root-directory", "templatesRootDir");
    std::shared_ptr<TemplateEngineProfile> templateEngineProfile = templateEngine.createProfile(configuration);

    const MustacheTemplateEngineProfile& mustacheTemplateEngineProfile =
        static_cast<MustacheTemplateEngineProfile&>(*templateEngineProfile);

    ISHIKO_TEST_FAIL_IF_NEQ(mustacheTemplateEngineProfile.options().templatesRootDirectory(), "templatesRootDir");
    ISHIKO_TEST_FAIL_IF(mustacheTemplateEngineProfile.options().layoutsRootDirectory().has_value());
    ISHIKO_TEST_PASS();
}

void MustacheTemplateEngineTests::CreateProfileTest2(Test& test)
{
    MustacheTemplateEngine templateEngine;

    Ishiko::Configuration configuration;
    configuration.set("templates-root-directory", "templatesRootDir");
    configuration.set("layouts-root-directory", "layoutsRootDir");
    std::shared_ptr<TemplateEngineProfile> templateEngineProfile = templateEngine.createProfile(configuration);

    const MustacheTemplateEngineProfile& mustacheTemplateEngineProfile =
        static_cast<MustacheTemplateEngineProfile&>(*templateEngineProfile);

    ISHIKO_TEST_FAIL_IF_NEQ(mustacheTemplateEngineProfile.options().templatesRootDirectory(), "templatesRootDir");
    ISHIKO_TEST_FAIL_IF_NEQ(*mustacheTemplateEngineProfile.options().layoutsRootDirectory(), "layoutsRootDir");
    ISHIKO_TEST_PASS();
}
