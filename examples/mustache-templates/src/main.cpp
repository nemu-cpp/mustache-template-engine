/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/nemu-cpp/nemu/blob/main/LICENSE.txt
*/

#include <Nemu/MustacheTemplateEngine.hpp>
#include <Nemu/WebFramework.hpp>
#include <iostream>

int main(int argc, char* argv[])
{
    // Create a log that sends its output to the console.
    Ishiko::StreamLoggingSink sink(std::cout);
    Ishiko::Logger logger(sink);

    // TODO: use the async server
    std::shared_ptr<Nemu::SingleConnectionWebServer> server =
        std::make_shared<Nemu::SingleConnectionWebServer>(Ishiko::TCPServerSocket::AllInterfaces,
            Ishiko::Port::http, logger);

    Nemu::WebApplication app(server, logger);

    // Set the mustache engine with the following options as the default template engine profile
    const std::string templatesRootDir = "${NEMU_CPP}/mustache-template-engine/examples/mustache-templates/data/views";
    app.views().setDefaultProfile(std::make_shared<Nemu::MustacheTemplateEngineProfile>(templatesRootDir));

    // Add a single route that only handled the "/" path
    app.routes().add(
        Nemu::Route("/*",
            std::make_shared<Nemu::FunctionWebRequestHandler>(
                [](const Nemu::WebRequest& request, Nemu::WebResponseBuilder& response, void* handlerData,
                    Ishiko::Logger& logger)
                {
                    Nemu::ViewContext context;
                    context["mustache"] = "Mustache";
                    std::string templatePath = request.url().path();
                    if (templatePath == "/")
                    {
                        templatePath = "index.html";
                    }
                    response.view(templatePath, context);
                })));

    app.run();

    return 0;
}
