#ifndef I3PYTHIAWRAPPERMODULE_HH
#define I3PYTHIAWRAPPERMODULE_HH

#include "icetray/I3ConditionalModule.h"
#include "icetray/I3Module.h"
#include "Pythia8/Pythia.h"

class I3PythiaWrapperModule : public I3ConditionalModule
{
public:
    I3PythiaWrapperModule(const I3Context &context) : I3ConditionalModule(context)
    {
        AddParameter("PythiaCommands",
                     "Commands to pass to Pythia.",
                     pythiaCommands_);
        AddParameter("PythiaCommandPath",
                     "Path to the .cmnd file with pythia commands.",
                     pythiaCommandPath_);
        AddParameter("Statistics Function", "Function to run statistics based off Pythia events.");
        AddOutBox("OutBox");
    }

    virtual ~I3PythiaWrapperModule();

    virtual void Configure();

    void DAQ(I3FramePtr frame);

    bool ShouldDoProcess(I3FramePtr frame);

    void SetStatsFunction(void (*stats)(Pythia8::Event &))
    {
        stats_ = stats;
    }

private:
    I3PythiaWrapperModule();
    I3PythiaWrapperModule(const I3PythiaWrapperModule &);
    I3PythiaWrapperModule &operator=(const I3PythiaWrapperModule &);

    std::vector<std::string> pythiaCommands_;
    std::string pythiaCommandPath_;
    void (*stats_)(Pythia8::Event &) = nullptr;
};

#endif // I3PYTHIAWRAPPERMODULE_HH