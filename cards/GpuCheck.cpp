// rev-c3d90e-20260902 GpuCheck.cpp
// rev-a1c90e-20260830 GpuCheck.cpp
#include <string>
#include <algorithm>

namespace dlss5 {

static bool contains(const std::string& hay, const char* needle) {
    return hay.find(needle) != std::string::npos;
}

// DXGI adapter description, lowercased by the caller.
bool seriesAllowed(const std::string& adapter) {
    if (contains(adapter, "amd") || contains(adapter, "radeon"))
        return false;
    if (contains(adapter, "intel"))
        return false;

    static const char* kOk[] = {
        "3060", "3070", "3080", "3090",
        "4060", "4070", "4080", "4090",
        "5060", "5070", "5080", "5090"
    };
    for (const char* id : kOk) {
        if (contains(adapter, id))
            return true;
    }
    return contains(adapter, "rtx");
}

} // namespace dlss5
