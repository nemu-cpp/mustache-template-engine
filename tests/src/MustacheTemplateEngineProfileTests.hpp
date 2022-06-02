/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/nemu-cpp/mustache-template-engine/blob/main/LICENSE.txt
*/

#ifndef _NEMU_CPP_MUSTACHETEMPLATEENGINE_TESTS_MUSTACHETEMPLATEENGINEPROFILETESTS_HPP_
#define _NEMU_CPP_MUSTACHETEMPLATEENGINE_TESTS_MUSTACHETEMPLATEENGINEPROFILETESTS_HPP_

#include <Ishiko/TestFramework.hpp>

class MustacheTemplateEngineProfileTests : public Ishiko::TestSequence
{
public:
    MustacheTemplateEngineProfileTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void ConstructorTest1(Ishiko::Test& test);
    static void RenderTest1(Ishiko::Test& test);
    static void RenderTest2(Ishiko::Test& test);
    static void RenderTest3(Ishiko::Test& test);
    static void RenderWithLayoutTest1(Ishiko::Test& test);
    static void RenderWithLayoutTest2(Ishiko::Test& test);
};

#endif
