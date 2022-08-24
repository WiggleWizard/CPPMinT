#include "SimpleBench.h"

#include <spdlog/spdlog.h>
#include <EASTL/string.h>

#include "Logging.h"
LOG_DECL(logger, Main);


int main(int argc, char *argv[])
{
    SimpleBench bench(true);

    const eastl::string str("Hello World");
    logger->info("{}", str);

    bench.Stop();
    logger->info("Took {}us to execute", bench.GetDurationInUs());
}
