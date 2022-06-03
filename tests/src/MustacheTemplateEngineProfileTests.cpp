/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/nemu-cpp/mustache-template-engine/blob/main/LICENSE.txt
*/

#include "MustacheTemplateEngineProfileTests.hpp"
#include "Nemu/MustacheTemplateEngine/MustacheTemplateEngineProfile.hpp"
#include <boost/filesystem.hpp>
#include <Ishiko/Errors.hpp>
#include <Ishiko/FileSystem.hpp>
#include <string>

using namespace Ishiko;
using namespace Nemu;

MustacheTemplateEngineProfileTests::MustacheTemplateEngineProfileTests(const TestNumber& number,
    const TestContext& context)
    : TestSequence(number, "MustacheTemplateEngineProfile tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("render test 1", RenderTest1);
    append<HeapAllocationErrorsTest>("render test 2", RenderTest2);
    append<HeapAllocationErrorsTest>("render test 3", RenderTest3);
    append<HeapAllocationErrorsTest>("render with layout test 1", RenderWithLayoutTest1);
    append<HeapAllocationErrorsTest>("render with layout test 2", RenderWithLayoutTest2);
}

void MustacheTemplateEngineProfileTests::ConstructorTest1(Test& test)
{
    MustacheTemplateEngineProfile templateEngineProfile(MustacheTemplateEngineProfile::Options("."));

    ISHIKO_TEST_PASS();
}

void MustacheTemplateEngineProfileTests::RenderTest1(Test& test)
{
    boost::filesystem::path templateRootDir = test.context().getTestDataPath("templates");
    MustacheTemplateEngineProfile templateEngineProfile(
        MustacheTemplateEngineProfile::Options(templateRootDir.string()));

    ViewContext context;
    std::string renderedView =
        templateEngineProfile.render("MustacheTemplateEngineProfileTests_RenderTest1.html", context, nullptr);

    boost::filesystem::path outputPath =
        test.context().getTestOutputPath("MustacheTemplateEngineProfileTests_RenderTest1.html");
    Error error; // TODO: use exception
    BinaryFile outputFile = BinaryFile::Create(outputPath, error);
    outputFile.write(renderedView.c_str(), renderedView.size());
    outputFile.close();

    ISHIKO_TEST_FAIL_IF_FILES_NEQ("MustacheTemplateEngineProfileTests_RenderTest1.html",
        "MustacheTemplateEngineProfileTests_RenderTest1.html");
    ISHIKO_TEST_PASS();
}

void MustacheTemplateEngineProfileTests::RenderTest2(Test& test)
{
    boost::filesystem::path templateRootDir = test.context().getTestDataPath("templates");
    MustacheTemplateEngineProfile templateEngineProfile(
        MustacheTemplateEngineProfile::Options(templateRootDir.string()));

    ViewContext context;
    context["name"] = "John";
    std::string renderedView =
        templateEngineProfile.render("MustacheTemplateEngineProfileTests_RenderTest2.html", context, nullptr);

    boost::filesystem::path outputPath =
        test.context().getTestOutputPath("MustacheTemplateEngineProfileTests_RenderTest2.html");
    Error error; // TODO: use exception
    BinaryFile outputFile = BinaryFile::Create(outputPath, error);
    outputFile.write(renderedView.c_str(), renderedView.size());
    outputFile.close();

    ISHIKO_TEST_FAIL_IF_FILES_NEQ("MustacheTemplateEngineProfileTests_RenderTest2.html",
        "MustacheTemplateEngineProfileTests_RenderTest2.html");
    ISHIKO_TEST_PASS();
}

void MustacheTemplateEngineProfileTests::RenderTest3(Test& test)
{
    boost::filesystem::path templateRootDir = test.context().getTestDataPath("templates");
    MustacheTemplateEngineProfile templateEngineProfile(
        MustacheTemplateEngineProfile::Options(templateRootDir.string()));

    ViewContext context;
    context["name"] = "<John>";
    std::string renderedView =
        templateEngineProfile.render("MustacheTemplateEngineProfileTests_RenderTest2.html", context, nullptr);

    boost::filesystem::path outputPath =
        test.context().getTestOutputPath("MustacheTemplateEngineProfileTests_RenderTest3.html");
    Error error; // TODO: use exception
    BinaryFile outputFile = BinaryFile::Create(outputPath, error);
    outputFile.write(renderedView.c_str(), renderedView.size());
    outputFile.close();

    ISHIKO_TEST_FAIL_IF_FILES_NEQ("MustacheTemplateEngineProfileTests_RenderTest3.html",
        "MustacheTemplateEngineProfileTests_RenderTest3.html");
    ISHIKO_TEST_PASS();
}

void MustacheTemplateEngineProfileTests::RenderWithLayoutTest1(Test& test)
{
    boost::filesystem::path templateRootDir = test.context().getTestDataPath("templates");
    boost::filesystem::path layoutRootDir = test.context().getTestDataPath("layouts");
    MustacheTemplateEngineProfile templateEngineProfile(
        MustacheTemplateEngineProfile::Options(templateRootDir.string(), &layoutRootDir.string()));

    ViewContext context;
    context["name"] = "John";
    const std::string layout = "MustacheTemplateEngineProfileTests_RenderWithLayoutTest1.html";
    std::string renderedView =
        templateEngineProfile.render("MustacheTemplateEngineProfileTests_RenderWithLayoutTest1.html", context,
            &layout);

    boost::filesystem::path outputPath =
        test.context().getTestOutputPath("MustacheTemplateEngineProfileTests_RenderWithLayoutTest1.html");
    Error error; // TODO: use exception
    BinaryFile outputFile = BinaryFile::Create(outputPath, error);
    outputFile.write(renderedView.c_str(), renderedView.size());
    outputFile.close();

    ISHIKO_TEST_FAIL_IF_FILES_NEQ("MustacheTemplateEngineProfileTests_RenderWithLayoutTest1.html",
        "MustacheTemplateEngineProfileTests_RenderWithLayoutTest1.html");
    ISHIKO_TEST_PASS();
}

void MustacheTemplateEngineProfileTests::RenderWithLayoutTest2(Test& test)
{
    boost::filesystem::path templateRootDir = test.context().getTestDataPath("templates");
    boost::filesystem::path layoutRootDir = test.context().getTestDataPath("layouts");
    MustacheTemplateEngineProfile templateEngineProfile(
        MustacheTemplateEngineProfile::Options(templateRootDir.string(), &layoutRootDir.string()));

    ViewContext context;
    context["name"] = "<John>";
    const std::string layout = "MustacheTemplateEngineProfileTests_RenderWithLayoutTest1.html";
    std::string renderedView =
        templateEngineProfile.render("MustacheTemplateEngineProfileTests_RenderWithLayoutTest1.html", context,
            &layout);

    boost::filesystem::path outputPath =
        test.context().getTestOutputPath("MustacheTemplateEngineProfileTests_RenderWithLayoutTest2.html");
    Error error; // TODO: use exception
    BinaryFile outputFile = BinaryFile::Create(outputPath, error);
    outputFile.write(renderedView.c_str(), renderedView.size());
    outputFile.close();

    ISHIKO_TEST_FAIL_IF_FILES_NEQ("MustacheTemplateEngineProfileTests_RenderWithLayoutTest2.html",
        "MustacheTemplateEngineProfileTests_RenderWithLayoutTest2.html");
    ISHIKO_TEST_PASS();
}
