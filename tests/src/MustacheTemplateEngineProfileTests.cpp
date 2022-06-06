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
#include <Nemu/WebFramework/MapViewContext.hpp>
#include <map>
#include <string>
#include <vector>

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
    append<HeapAllocationErrorsTest>("render test 4", RenderTest4);
    append<HeapAllocationErrorsTest>("render test 5", RenderTest5);
    append<HeapAllocationErrorsTest>("render test 6", RenderTest6);
    append<HeapAllocationErrorsTest>("render test 7", RenderTest7);
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

    MapViewContext context;
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

    MapViewContext context;
    context.map()["name"] = "John";
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

    MapViewContext context;
    context.map()["name"] = "<John>";
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

void MustacheTemplateEngineProfileTests::RenderTest4(Test& test)
{
    boost::filesystem::path templateRootDir = test.context().getTestDataPath("templates");
    MustacheTemplateEngineProfile templateEngineProfile(
        MustacheTemplateEngineProfile::Options(templateRootDir.string()));

    // Create a context where a "person" object is composed of 2 member objects: "name" and "country".
    MapViewContext context;
    context.map()["person"] =
        std::map<std::string, ViewContext::Value>({ { "name", "Paul" }, { "country", "Belgium" } });
    std::string renderedView =
        templateEngineProfile.render("MustacheTemplateEngineProfileTests_RenderTest4.html", context, nullptr);

    boost::filesystem::path outputPath =
        test.context().getTestOutputPath("MustacheTemplateEngineProfileTests_RenderTest4.html");
    Error error; // TODO: use exception
    BinaryFile outputFile = BinaryFile::Create(outputPath, error);
    outputFile.write(renderedView.c_str(), renderedView.size());
    outputFile.close();

    ISHIKO_TEST_FAIL_IF_FILES_NEQ("MustacheTemplateEngineProfileTests_RenderTest4.html",
        "MustacheTemplateEngineProfileTests_RenderTest4.html");
    ISHIKO_TEST_PASS();
}

void MustacheTemplateEngineProfileTests::RenderTest5(Test& test)
{
    boost::filesystem::path templateRootDir = test.context().getTestDataPath("templates");
    MustacheTemplateEngineProfile templateEngineProfile(
        MustacheTemplateEngineProfile::Options(templateRootDir.string()));

    // Create a context where a "person" object is composed of 2 member objects: "name" and "country".
    // In addition to that "name" itself is composed of 2 member objects: "first-name" and "last-name".
    MapViewContext context;
    ViewContext::Value name =
        std::map<std::string, ViewContext::Value>({ {"first-name", "John"}, {"last-name", "Doe"} });
    context.map()["person"] =
        std::map<std::string, ViewContext::Value>({ { "name", name }, { "country", "Belgium" } });
    std::string renderedView =
        templateEngineProfile.render("MustacheTemplateEngineProfileTests_RenderTest5.html", context, nullptr);

    boost::filesystem::path outputPath =
        test.context().getTestOutputPath("MustacheTemplateEngineProfileTests_RenderTest5.html");
    Error error; // TODO: use exception
    BinaryFile outputFile = BinaryFile::Create(outputPath, error);
    outputFile.write(renderedView.c_str(), renderedView.size());
    outputFile.close();

    ISHIKO_TEST_FAIL_IF_FILES_NEQ("MustacheTemplateEngineProfileTests_RenderTest5.html",
        "MustacheTemplateEngineProfileTests_RenderTest5.html");
    ISHIKO_TEST_PASS();
}

void MustacheTemplateEngineProfileTests::RenderTest6(Test& test)
{
    boost::filesystem::path templateRootDir = test.context().getTestDataPath("templates");
    MustacheTemplateEngineProfile templateEngineProfile(
        MustacheTemplateEngineProfile::Options(templateRootDir.string()));

    // Create a context where the "names" object is an array of strings.
    MapViewContext context;
    context.map()["names"] = std::vector<ViewContext::Value>({ "John", "Paul" });
    std::string renderedView =
        templateEngineProfile.render("MustacheTemplateEngineProfileTests_RenderTest6.html", context, nullptr);

    boost::filesystem::path outputPath =
        test.context().getTestOutputPath("MustacheTemplateEngineProfileTests_RenderTest6.html");
    Error error; // TODO: use exception
    BinaryFile outputFile = BinaryFile::Create(outputPath, error);
    outputFile.write(renderedView.c_str(), renderedView.size());
    outputFile.close();

    ISHIKO_TEST_FAIL_IF_FILES_NEQ("MustacheTemplateEngineProfileTests_RenderTest6.html",
        "MustacheTemplateEngineProfileTests_RenderTest6.html");
    ISHIKO_TEST_PASS();
}

void MustacheTemplateEngineProfileTests::RenderTest7(Test& test)
{
    boost::filesystem::path templateRootDir = test.context().getTestDataPath("templates");
    MustacheTemplateEngineProfile templateEngineProfile(
        MustacheTemplateEngineProfile::Options(templateRootDir.string()));

    // Create a context where the "employees" object is an array of "person" objects that are composed of 2 member
    //  objects: "name" and "country".
    MapViewContext context;
    std::vector<ViewContext::Value> employees;
    employees.push_back(std::map<std::string, ViewContext::Value>({ { "name", "Paul" }, { "country", "Belgium" } }));
    employees.push_back(std::map<std::string, ViewContext::Value>({ { "name", "Jane" }, { "country", "France" } }));
    context.map()["employees"] = employees;
    std::string renderedView =
        templateEngineProfile.render("MustacheTemplateEngineProfileTests_RenderTest7.html", context, nullptr);

    boost::filesystem::path outputPath =
        test.context().getTestOutputPath("MustacheTemplateEngineProfileTests_RenderTest7.html");
    Error error; // TODO: use exception
    BinaryFile outputFile = BinaryFile::Create(outputPath, error);
    outputFile.write(renderedView.c_str(), renderedView.size());
    outputFile.close();

    ISHIKO_TEST_FAIL_IF_FILES_NEQ("MustacheTemplateEngineProfileTests_RenderTest7.html",
        "MustacheTemplateEngineProfileTests_RenderTest7.html");
    ISHIKO_TEST_PASS();
}

void MustacheTemplateEngineProfileTests::RenderWithLayoutTest1(Test& test)
{
    boost::filesystem::path templateRootDir = test.context().getTestDataPath("templates");
    boost::filesystem::path layoutRootDir = test.context().getTestDataPath("layouts");
    MustacheTemplateEngineProfile templateEngineProfile(
        MustacheTemplateEngineProfile::Options(templateRootDir.string(), &layoutRootDir.string()));

    MapViewContext context;
    context.map()["name"] = "John";
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

    MapViewContext context;
    context.map()["name"] = "<John>";
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
