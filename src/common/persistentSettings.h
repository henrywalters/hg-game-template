//
// Created by henry on 8/6/24.
//

#ifndef HABAN_PERSISTENTSETTINGS_H
#define HABAN_PERSISTENTSETTINGS_H

#include <hagame/utils/watcher.h>

const std::string SETTINGS_FILE = "settings.hg";

class PersistentSettings {
public:

    PersistentSettings();

    hg::utils::Watcher<bool> devMode;
    hg::utils::Watcher<bool> vsync;


private:

    void save();
    void load();

};

#endif //HABAN_PERSISTENTSETTINGS_H
