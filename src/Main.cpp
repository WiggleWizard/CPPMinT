#include "SimpleBench.h"

#include <spdlog/spdlog.h>
#include <EASTL/string.h>

#include <SkeletonMinRes/Loader.h>

#include "Logging.h"
LOG_DECL(logger, Main);


int main(int argc, char *argv[])
{
    SimpleBench bench(true);

    SkeletonMinRes::Resource dataRes = LOAD_RESOURCE(Data_json);

    const eastl::string str(dataRes.Data());
    logger->info("Data.json resource contents: \n{}", str);

    bench.Stop();
    logger->info("Took {}us to execute", bench.GetDurationInUs());
}
