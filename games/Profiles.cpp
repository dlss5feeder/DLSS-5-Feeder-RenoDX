// rev-c3d90e-20260902 Profiles.cpp
// rev-a1c90e-20260830 Profiles.cpp
#include "../feed/NvngxFeed.h"
#include <map>
#include <string>

namespace dlss5 {

struct GameProfile {
    std::string exe;
    std::string nvngxRel;
    bool needsRenoDxFirst;
};

static const std::map<std::string, GameProfile> kProfiles = {
    {"gta5",     {"GTA5.exe",          ".",           false}},
    {"cp2077",   {"Cyberpunk2077.exe", "bin/x64",     true}},
    {"skyrim",   {"SkyrimSE.exe",      ".",           true}},
    {"witcher3", {"witcher3.exe",      "bin/x64",     false}},
    {"wow",      {"Wow.exe",           ".",           false}},
    {"nte",      {"NTE.exe",           ".",           false}},
};

const GameProfile* findProfile(const std::string& id) {
    auto it = kProfiles.find(id);
    return it == kProfiles.end() ? nullptr : &it->second;
}

} // namespace dlss5
