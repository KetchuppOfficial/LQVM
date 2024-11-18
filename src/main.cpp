#include <exception>
#include <filesystem>

#include <CLI/CLI.hpp>
#include <fmt/base.h>
#include <fmt/std.h>

int main(int argc, char **argv) try
{
    CLI::App app{"LQVM: Low Quality Virtual Machine"};

    std::filesystem::path bc_path;
    app.add_option("bc-file", bc_path, "Path to the file with bytecode")
        ->required()
        ->check(CLI::ExistingFile);

    CLI11_PARSE(app, argc, argv);

    fmt::println("Executing {}", bc_path);

    return 0;
}
catch (const std::exception &e)
{
    fmt::println(stderr, "Caught as instance of {}.\nwhat(): {}", typeid(e).name(), e.what());
    return 1;
}
catch (...)
{
    fmt::println(stderr, "Caught an unknown exception");
    return 1;
}
