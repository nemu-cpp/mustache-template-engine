/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/nemu-cpp/mustache-templating-engine/blob/main/LICENSE.txt
*/

#include "MustacheTemplateEngineTests.hpp"
#include "Nemu/MustacheTemplateEngine/linkoptions.hpp"
#include <Ishiko/Tests.hpp>

using namespace Ishiko;

int main(int argc, char* argv[])
{
    TestHarness theTestHarness("NemuMustacheTemplatingEngine");

    TestSequence& theTests = theTestHarness.tests();
    theTests.append<MustacheTemplatingEngineTests>();

    return theTestHarness.run();
}
