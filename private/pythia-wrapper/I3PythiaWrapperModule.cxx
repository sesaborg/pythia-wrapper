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

    // int nMu = 0;
    // int nC = 0;
    if (pythia.next())
    {
        for (int i = 0; i < pythia.event.size(); i++)
        {
            // if (pythia.event[i].isFinal()) {
            //     e.fill(pythia.event[i].e()*1e9);
            // }

            // if (pythia.event[i].isFinal() && pythia.event[i].idAbs() == 13)
            // {
            //     nMu++;
            // }

            // if (pythia.event[i].idAbs() == 4)
            // {
            //     nC++;
            // }
        }
    }
    // mu.fill(nMu);
    // c.fill(nC);

    pythia.stat();
}

bool I3PythiaWrapperModule::ShouldDoProcess(I3FramePtr frame)
{
    return true;
}
