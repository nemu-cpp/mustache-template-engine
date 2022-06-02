/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/nemu-cpp/mustache-template-engine/blob/main/LICENSE.txt
*/

#include "MustacheTemplateEngineProfileTests.hpp"
#include "Nemu/MustacheTemplateEngine/MustacheTemplateEngineProfile.hpp"
#include <Ishiko/FileSystem.hpp>

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
    std::string renderedView = templateEngineProfile.render("MustacheTemplateEngineTests_RenderTest1.html", context);

    boost::filesystem::path outputPath =
        test.context().getTestOutputPath("MustacheTemplateEngineTests_RenderTest1.html");
    Error error; // TODO: use exception
    BinaryFile outputFile = BinaryFile::Create(outputPath, error);
    outputFile.write(renderedView.c_str(), renderedView.size());
    outputFile.close();

    ISHIKO_TEST_FAIL_IF_FILES_NEQ("MustacheTemplateEngineTests_RenderTest1.html",
        "MustacheTemplateEngineTests_RenderTest1.html");
    ISHIKO_TEST_PASS();
}

void MustacheTemplateEngineProfileTests::RenderTest2(Test& test)
{
    boost::filesystem::path templateRootDir = test.context().getTestDataPath("templates");
    MustacheTemplateEngineProfile templateEngineProfile(
        MustacheTemplateEngineProfile::Options(templateRootDir.string()));

    ViewContext context;
    context["name"] = "John";
    std::string renderedView = templateEngineProfile.render("MustacheTemplateEngineTests_RenderTest2.html", context);

    boost::filesystem::path outputPath =
        test.context().getTestOutputPath("MustacheTemplateEngineTests_RenderTest2.html");
    Error error; // TODO: use exception
    BinaryFile outputFile = BinaryFile::Create(outputPath, error);
    outputFile.write(renderedView.c_str(), renderedView.size());
    outputFile.close();

    ISHIKO_TEST_FAIL_IF_FILES_NEQ("MustacheTemplateEngineTests_RenderTest2.html",
        "MustacheTemplateEngineTests_RenderTest2.html");
    ISHIKO_TEST_PASS();
}

void MustacheTemplateEngineProfileTests::RenderTest3(Test& test)
{
    boost::filesystem::path templateRootDir = test.context().getTestDataPath("templates");
    MustacheTemplateEngineProfile templateEngineProfile(
        MustacheTemplateEngineProfile::Options(templateRootDir.string()));

    ViewContext context;
    context["name"] = "<John>";
    std::string renderedView = templateEngineProfile.render("MustacheTemplateEngineTests_RenderTest2.html", context);

    boost::filesystem::path outputPath =
        test.context().getTestOutputPath("MustacheTemplateEngineTests_RenderTest3.html");
    Error error; // TODO: use exception
    BinaryFile outputFile = BinaryFile::Create(outputPath, error);
    outputFile.write(renderedView.c_str(), renderedView.size());
    outputFile.close();

    ISHIKO_TEST_FAIL_IF_FILES_NEQ("MustacheTemplateEngineTests_RenderTest3.html",
        "MustacheTemplateEngineTests_RenderTest3.html");
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
    std::string renderedView =
        templateEngineProfile.render("MustacheTemplateEngineTests_RenderWithLayoutTest1.html", context,
            "MustacheTemplateEngineTests_RenderWithLayoutTest1.html");

    boost::filesystem::path outputPath =
        test.context().getTestOutputPath("MustacheTemplateEngineTests_RenderWithLayoutTest1.html");
    Error error; // TODO: use exception
    BinaryFile outputFile = BinaryFile::Create(outputPath, error);
    outputFile.write(renderedView.c_str(), renderedView.size());
    outputFile.close();

    ISHIKO_TEST_FAIL_IF_FILES_NEQ("MustacheTemplateEngineTests_RenderWithLayoutTest1.html",
        "MustacheTemplateEngineTests_RenderWithLayoutTest1.html");
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
    std::string renderedView =
        templateEngineProfile.render("MustacheTemplateEngineTests_RenderWithLayoutTest1.html", context,
            "MustacheTemplateEngineTests_RenderWithLayoutTest1.html");

    boost::filesystem::path outputPath =
        test.context().getTestOutputPath("MustacheTemplateEngineTests_RenderWithLayoutTest2.html");
    Error error; // TODO: use exception
    BinaryFile outputFile = BinaryFile::Create(outputPath, error);
    outputFile.write(renderedView.c_str(), renderedView.size());
    outputFile.close();

    ISHIKO_TEST_FAIL_IF_FILES_NEQ("MustacheTemplateEngineTests_RenderWithLayoutTest2.html",
        "MustacheTemplateEngineTests_RenderWithLayoutTest2.html");
    ISHIKO_TEST_PASS();
}
