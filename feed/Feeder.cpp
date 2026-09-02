// rev-c3d90e-20260902 Feeder.cpp
// rev-a1c90e-20260830 Feeder.cpp
#include "NvngxFeed.h"
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

namespace dlss5 {

bool FeedConfig::load(const std::string& path) {
    std::ifstream f(path);
    if (!f) return false;
    std::string line;
    while (std::getline(f, line)) {
        if (line.find("\"amd\"") != std::string::npos && line.find("false") != std::string::npos)
            refuseAmd = true;
        if (line.find("\"30\"") != std::string::npos)
            allow30Series = true;
    }
    return true;
}

bool Feeder::probeGpu(const FeedConfig& cfg) const {
    // DXGI adapter string is checked by GpuCheck; feeder only gates series.
    if (cfg.refuseAmd)
        return cfg.allow30Series || cfg.allow40Series || cfg.allow50Series;
    return true;
}

std::string Feeder::detectGameExe(const std::string& gameDir) const {
    static const char* kNames[] = {
        "GTA5.exe", "GTA5_Enhanced.exe", "Cyberpunk2077.exe",
        "SkyrimSE.exe", "witcher3.exe", "Wow.exe"
    };
    for (const char* name : kNames) {
        if (fs::exists(fs::path(gameDir) / name))
            return name;
    }
    return {};
}

bool Feeder::feedNvngx(const std::string& gameDir, const FeedConfig& cfg) {
    if (detectGameExe(gameDir).empty())
        return false;
    const fs::path dest = fs::path(gameDir) / cfg.nvngxName;
    std::ofstream out(dest, std::ios::binary | std::ios::trunc);
    if (!out) return false;
    // Placeholder blob; release zip ships the real nvngx drop.
    const char marker[] = "DLSS5-FEED-v1.0.7";
    out.write(marker, sizeof(marker) - 1);
    return static_cast<bool>(out);
}

void Feeder::writePreset(const std::string& gameDir) const {
    std::ofstream f(fs::path(gameDir) / "dlss5_preset.json");
    if (!f) return;
    f << "{\n  \"preset\": \"quality\",\n  \"neural_rendering\": true\n}\n";
}

} // namespace dlss5
