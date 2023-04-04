#pragma once
#include "spotify.h"

#include "imgui/imgui.h"
#include "imtui/imtui.h"
#include "imtui/imtui-impl-ncurses.h"

class TUI {
public:
        TUI(Spotify* spt) : spotify(spt){};
        void Render();
private:
        Spotify* spotify;
        void Seperator(char, int);
        void Style();
};
