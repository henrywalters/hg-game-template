//
// Created by henry on 8/6/24.
//

#ifndef HABAN_PERSISTENTSETTINGS_H
#define HABAN_PERSISTENTSETTINGS_H

#include <hagame/utils/watcher.h>
#include <hagame/utils/enum.h>

const std::string SETTINGS_FILE = "settings.hg";

class PersistentSettings {
public:

    PersistentSettings();

    hg::utils::Watcher<bool> devMode;
    hg::utils::Watcher<bool> vsync;
    hg::utils::Watcher<hg::utils::enum_t> debugLevel;


private:

    void save();
    void load();

};

#endif //HABAN_PERSISTENTSETTINGS_H
