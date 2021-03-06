/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/nemu-cpp/mustache-template-engine/blob/main/LICENSE.txt
*/


#ifndef _NEMU_CPP_MUSTACHETEMPLATEENGINE_TESTS_MUSTACHETEMPLATEENGINETESTS_HPP_
#define _NEMU_CPP_MUSTACHETEMPLATEENGINE_TESTS_MUSTACHETEMPLATEENGINETESTS_HPP_

#include <Ishiko/TestFramework.hpp>

class MustacheTemplateEngineTests : public Ishiko::TestSequence
{
public:
    MustacheTemplateEngineTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void ConstructorTest1(Ishiko::Test& test);
    static void CreateProfileTest1(Ishiko::Test& test);
    static void CreateProfileTest2(Ishiko::Test& test);
};

#endif
