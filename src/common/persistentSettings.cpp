//
// Created by henry on 8/6/24.
//
#include "persistentSettings.h"
#include <hagame/utils/file.h>
#include <hagame/utils/config.h>

using namespace hg::utils;

PersistentSettings::PersistentSettings():
    devMode(false),
    vsync(false),
    debugLevel(1)
{
    if (f_exists(SETTINGS_FILE)) {
        load();
    } else {
        vsync = false;
        devMode = false;
        save();
    }

    auto saveFn = [&](){save();};

    vsync.onUpdate = saveFn;
    devMode.onUpdate = saveFn;
}

void PersistentSettings::save() {
    Config settings;
    settings.addSection("General");
    settings.addSection("Audio");

    settings.set("General", "devMode", devMode.value());
    settings.set("General", "vsync", vsync.value());
    settings.set("General", "debugLevel", debugLevel.value());

    f_write(SETTINGS_FILE, settings.toString());
}

void PersistentSettings::load() {
    auto settings = Config::Parse(f_readLines(SETTINGS_FILE));

    devMode = settings.get<bool>("General", "devMode");
    vsync = settings.get<bool>("General", "vsync");
    debugLevel = settings.get<hg::utils::enum_t>("General", "debugLevel");
}

