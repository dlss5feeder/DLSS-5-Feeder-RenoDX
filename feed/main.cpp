// rev-c3d90e-20260902 main.cpp
// rev-a1c90e-20260830 main.cpp
#include "NvngxFeed.h"
#include <iostream>

int main(int argc, char** argv) {
    dlss5::Feeder feeder;
    dlss5::FeedConfig cfg;
    cfg.load("cards/Supported.json");

    std::cout << "DLSS 5 Feeder v1.0.7\n";

    if (!feeder.probeGpu(cfg)) {
        std::cerr << "refused: not on RTX 30/40/50 Tensor path\n";
        return 1;
    }

    const char* gameDir = (argc > 1) ? argv[1] : ".";
    if (!feeder.feedNvngx(gameDir, cfg)) {
        std::cerr << "feed failed: nvngx_dlss.dll not written\n";
        return 2;
    }

    feeder.writePreset(gameDir);
    return 0;
}
