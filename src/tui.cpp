#include "tui.h"

void TUI::Style() {
    auto & style = ImGui::GetStyle();

    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.1,0.1,0.1, 1);
}

void TUI::Seperator(char chr, int width) {
    char buffer[255];
    if (width > 255) width = 255;
    if (width < 0) width = 0;
    for (int i = 0; i < width; i++) {
        buffer[i] = chr;
    }

    buffer[width] = 0;
    ImGui::Text("%s", buffer);
}

void TUI::Render() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    auto screen = ImTui_ImplNcurses_Init(true);
    ImTui_ImplText_Init();
    Style();

    while (true) {
        ImTui_ImplNcurses_NewFrame();
        ImTui_ImplText_NewFrame();

        ImGui::NewFrame();
        ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(screen->nx, screen->ny), ImGuiCond_Always);

        ImGui::Begin("CPPotify", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
        {
            ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.2,0.2,0.2,1));
            ImGui::BeginChild("LeftPanel", ImVec2(30,0), true);
            ImGui::Text("%s","");
            ImGui::Text("CPPotify");
            ImGui::Text("%s","");
            ImGui::Text("%s","");
            ImGui::Text("playlist");
            ImGui::Text("%s","");
            ImGui::Text("playlist");
            ImGui::Text("%s","");
            ImGui::Text("playlist");
            ImGui::Text("%s","");
            ImGui::Text("playlist");
            ImGui::Text("%s","");
            ImGui::Text("playlist");
            ImGui::Text("%s","");
            ImGui::Text("playlist");
            ImGui::Text("%s","");
            ImGui::Text("playlist");
            ImGui::EndChild();
            ImGui::PopStyleColor();
        }

        {
            ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.15,0.15,0.15,1));
            ImGui::SetNextWindowPos(ImVec2(31,0));
            ImGui::BeginChild("MainPanel", ImVec2(screen->nx,screen->ny), ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
            ImGui::Text("%s","");
            ImGui::Text("Playlist Name");
            ImGui::Text("by HutchyBen");
            ImGui::SameLine();
            ImGui::Text("| 50 likes");
            Seperator('-', screen->nx);
            ImGui::Text("Text");
            ImGui::EndChild();
        }
        ImGui::End();


        ImGui::Render();

        ImTui_ImplText_RenderDrawData(ImGui::GetDrawData(), screen);
        ImTui_ImplNcurses_DrawScreen();
    }

    ImTui_ImplText_Shutdown();
    ImTui_ImplNcurses_Shutdown();
}
