#include "pythia-wrapper/I3PythiaWrapperModule.hh"
#include "Pythia8/Pythia.h"
typedef I3PythiaWrapperModule pythia_wrapper;
namespace
{
    I3_MODULE(pythia_wrapper);
}

I3PythiaWrapperModule::~I3PythiaWrapperModule()
{
}

void I3PythiaWrapperModule::Configure()
{
    GetParameter("PythiaCommands", pythiaCommands_);
    GetParameter("PythiaCommandPath", pythiaCommandPath_);
}

void I3PythiaWrapperModule::DAQ(I3FramePtr frame)
{
    using namespace Pythia8;
    Pythia pythia;

    for (auto &cmnd : pythiaCommands_)
    {
        pythia.readString(cmnd);
    }

    if (!pythiaCommandPath_.empty())
    {
        pythia.readFile(pythiaCommandPath_);
    }

    Event &event = pythia.event;

    if (!pythia.init())
        log_error("Pythia failed to initialize!");
    return;

    if (pythia.next())
    {
        if (stats_ != nullptr)
        {
            stats_(event);
        }
    }

    auto level = GetIcetrayLogger()->LogLevelForUnit("pythia-wrapper");
    if (level <= I3LOG_DEBUG)
    {
        pythia.stat();
    }

    // I3MCTree construction goes here :)
}

bool I3PythiaWrapperModule::ShouldDoProcess(I3FramePtr frame)
{
    return true;
}
