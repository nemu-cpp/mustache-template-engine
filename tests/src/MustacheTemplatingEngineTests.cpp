/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/nemu-cpp/mustache-templating-engine/blob/main/LICENSE.txt
*/

#include "MustacheTemplatingEngineTests.hpp"
#include "Nemu/MustacheTemplatingEngine/MustacheTemplatingEngine.h"

using namespace Ishiko::Tests;
using namespace Nemu;

MustacheTemplatingEngineTests::MustacheTemplatingEngineTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "MustacheTemplatingEngine tests", context)
{
    append<HeapAllocationErrorsTest>("Creation test 1", ConstructorTest1);
}

void MustacheTemplatingEngineTests::ConstructorTest1(Test& test)
{
    MustacheTemplatingEngine templatingEngine;

    ISHIKO_PASS();
}
