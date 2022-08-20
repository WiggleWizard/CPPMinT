#include "SimpleBench.h"

#include <spdlog/spdlog.h>
#include <EASTL/string.h>


int main(int argc, char *argv[])
{
    SimpleBench bench(true);

    const eastl::string str("Hello World");
    spdlog::info("{}", str.c_str());

    bench.Stop();
    spdlog::info("Took {}us to execute", bench.GetDurationInUs());
}