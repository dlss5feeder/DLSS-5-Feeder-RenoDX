// rev-c3d90e-20260902 NvngxFeed.h
#pragma once
#include <string>
#include <vector>

namespace dlss5 {

struct FeedConfig {
    bool allow30Series = true;
    bool allow40Series = true;
    bool allow50Series = true;
    bool refuseAmd = true;
    std::string nvngxName = "nvngx_dlss.dll";
    std::string preset = "quality";

    bool load(const std::string& path);
};

class Feeder {
public:
    bool probeGpu(const FeedConfig& cfg) const;
    bool feedNvngx(const std::string& gameDir, const FeedConfig& cfg);
    void writePreset(const std::string& gameDir) const;

private:
    std::string detectGameExe(const std::string& gameDir) const;
};

} // namespace dlss5
