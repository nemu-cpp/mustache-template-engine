/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/nemu-cpp/mustache-templating-engine/blob/main/LICENSE.txt
*/

#include "MustacheTemplatingEngineTests.hpp"
#include <Ishiko/Tests.hpp>

using namespace Ishiko::Tests;

int main(int argc, char* argv[])
{
    TestHarness theTestHarness("NemuMustacheTemplatingEngine");

    TestSequence& theTests = theTestHarness.tests();
    theTests.append<MustacheTemplatingEngineTests>();

    return theTestHarness.run();
}
