/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/nemu-cpp/mustache-templating-engine/blob/main/LICENSE.txt
*/


#ifndef _NEMU_CPP_MUSTACHETEMPLATINGENGINE_TESTS_MUSTACHETEMPLATINGENGINETESTS_HPP_
#define _NEMU_CPP_MUSTACHETEMPLATINGENGINE_TESTS_MUSTACHETEMPLATINGENGINETESTS_HPP_

#include <Ishiko/Tests.hpp>

class MustacheTemplatingEngineTests : public Ishiko::TestSequence
{
public:
    MustacheTemplatingEngineTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void ConstructorTest1(Ishiko::Test& test);
};

#endif
