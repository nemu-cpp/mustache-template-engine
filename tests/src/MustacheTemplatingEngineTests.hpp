/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/nemu-cpp/mustache-templating-engine/blob/main/LICENSE.txt
*/


#ifndef _NEMU_CPP_MUSTACHETEMPLATINGENGINE_TESTS_MUSTACHETEMPLATINGENGINETESTS_HPP_
#define _NEMU_CPP_MUSTACHETEMPLATINGENGINE_TESTS_MUSTACHETEMPLATINGENGINETESTS_HPP_

#include <Ishiko/Tests.hpp>

class MustacheTemplatingEngineTests : public Ishiko::Tests::TestSequence
{
public:
    MustacheTemplatingEngineTests(const Ishiko::Tests::TestNumber& number, const Ishiko::Tests::TestContext& context);

private:
    static void ConstructorTest1(Ishiko::Tests::Test& test);
};

#endif
