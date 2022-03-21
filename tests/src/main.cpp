/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/nemu-cpp/mustache-template-engine/blob/main/LICENSE.txt
*/

#include "MustacheTemplateEngineTests.hpp"
#include "Nemu/MustacheTemplateEngine/linkoptions.hpp"
#include <Ishiko/Tests.hpp>

using namespace Ishiko;

int main(int argc, char* argv[])
{
    TestHarness theTestHarness("NemuMustacheTemplateEngine");

    TestSequence& theTests = theTestHarness.tests();
    theTests.append<MustacheTemplateEngineTests>();

    return theTestHarness.run();
}
