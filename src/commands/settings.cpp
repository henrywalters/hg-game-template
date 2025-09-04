//
// Created by henry on 9/1/25.
//
#include "settings.h"

SetVSyncCommand::SetVSyncCommand():
    hg::Console::Command({hg::Console::ArgType::Int}, [&](hg::Console* console, auto args) {
        try {
            GameState::Get()->persistentSettings.vsync = std::get<int>(args[0].value);
            return 0;
        } catch(std::exception const& e) {
            console->putLine(e.what());
            return 1;
        } catch(...) {
            console->putLine("Unknown error occured");
            return 1;
        }
    }){}

HelpCommand::HelpCommand():
    hg::Console::Command({}, [&](hg::Console* console, auto args) {

        for (auto&& [key, command] : console->m_commands) {
            console->putLine("\t" + key + " " + command.help());
        }

        return 0;
    })
{}
