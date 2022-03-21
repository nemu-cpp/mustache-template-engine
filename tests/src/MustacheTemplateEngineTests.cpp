/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/nemu-cpp/mustache-template-engine/blob/main/LICENSE.txt
*/

#include "MustacheTemplateEngineTests.hpp"
#include "Nemu/MustacheTemplateEngine/MustacheTemplateEngine.hpp"

using namespace Ishiko;
using namespace Nemu;

MustacheTemplateEngineTests::MustacheTemplateEngineTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "MustacheTemplateEngine tests", context)
{
    append<HeapAllocationErrorsTest>("Creation test 1", ConstructorTest1);
}

void MustacheTemplateEngineTests::ConstructorTest1(Test& test)
{
    MustacheTemplateEngine templatingEngine;

    ISHIKO_TEST_PASS();
}
