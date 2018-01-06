#pragma once

#include "controlspecification.h"
#include "enums.h"

namespace Dso {

struct ControlSamplerateLimits;

//////////////////////////////////////////////////////////////////////////////
/// \struct ControlSettingsSamplerateTarget                   hantek/control.h
/// \brief Stores the target samplerate settings of the device.
struct ControlSettingsSamplerateTarget {
    double samplerate; ///< The target samplerate set via setSamplerate
    double duration;   ///< The target record time set via setRecordTime
    enum SamplerrateSet { Duration, Samplerrate } samplerateSet;
};

//////////////////////////////////////////////////////////////////////////////
/// \struct ControlSettingsSamplerate                         hantek/control.h
/// \brief Stores the current samplerate settings of the device.
struct ControlSettingsSamplerate {
    ControlSettingsSamplerateTarget target; ///< The target samplerate values
    ControlSamplerateLimits *limits;        ///< The samplerate limits
    unsigned int downsampler = 1;           ///< The variable downsampling factor
    double current = 1e8;                   ///< The current samplerate
};

//////////////////////////////////////////////////////////////////////////////
/// \struct ControlSettingsTrigger                            hantek/control.h
/// \brief Stores the current trigger settings of the device.
struct ControlSettingsTrigger {
    std::vector<double> level;                        ///< The trigger level for each channel in V
    double position = 0.0;                            ///< The current pretrigger position
    unsigned int point = 0;                           ///< The trigger position in Hantek coding
    Dso::TriggerMode mode = Dso::TriggerMode::HARDWARE_SOFTWARE; ///< The trigger mode
    Dso::Slope slope = Dso::Slope::Positive;          ///< The trigger slope
    bool special = false;                             ///< true, if the trigger source is special
    unsigned int source = 0;                          ///< The trigger source
};

//////////////////////////////////////////////////////////////////////////////
/// \struct ControlSettingsVoltage                            hantek/control.h
/// \brief Stores the current amplification settings of the device.
struct ControlSettingsVoltage {
    double offset;     ///< The screen offset for each channel
    double offsetReal; ///< The real offset for each channel (Due to quantization)
    unsigned gain;     ///< The gain id
    bool used;         ///< true, if the channel is used
};

//////////////////////////////////////////////////////////////////////////////
/// \struct ControlSettings                                   hantek/control.h
/// \brief Stores the current settings of the device.
struct ControlSettings {
    ControlSettings(ControlSamplerateLimits *limits, size_t channelCount);
    ControlSettingsSamplerate samplerate;        ///< The samplerate settings
    std::vector<ControlSettingsVoltage> voltage; ///< The amplification settings
    ControlSettingsTrigger trigger;              ///< The trigger settings
    RecordLengthID recordLengthId = 1;           ///< The id in the record length array
    unsigned usedChannels = 0;                   ///< Number of activated channels
    unsigned swSampleMargin = 2000;              ///< Software trigger, sample margin
};
}
