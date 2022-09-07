#include "Application.h"

#define CREATE_APPLICATION_DEFINE(ApplicationClass) \
	ApplicationBase* CreateApplication() { return new ApplicationClass(); }

/**	Initializes application base.

	Basic "bootstraping" line to get booted as soon as the application can do so.
 */
#define START_APPLICATION(ApplicationClass) \
CREATE_APPLICATION_DEFINE(ApplicationClass) \
int main(int argc, const char* argv[]) \
{ \
	ApplicationBase::CreateInstance = &CreateApplication; \
	return ApplicationBase::GlobalMain(argc, argv); \
} \


START_APPLICATION(Application)