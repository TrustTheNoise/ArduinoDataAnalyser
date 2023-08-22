#define STB_IMAGE_IMPLEMENTATION
#include "../headers/App.h"
#include "../headers/glfw3.h"
#include "../headers/imgui.h"
#include <fstream>
#include <iostream>
#include <string>

bool endsWith(const std::string& str, const char* txt)
{
    std::string txt_str(txt);
    if (str.length() >= txt_str.length())
        return (0
                == str.compare(str.length() - txt_str.length(),
                               txt_str.length(), txt_str));
    return false;
}

namespace MyApp {
    char output_text[4096] = "";
    char file_name[256] = "";
    bool save = false;
    void save_txt();

    void RenderUI()
    {
        ImGui::Begin("Settigns", nullptr,
                     ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
        float ImGuiWindowWidth = ImGui::GetWindowContentRegionWidth();

        ImGui::BeginChild("TextBlock", ImVec2(ImGuiWindowWidth * 0.7f, -1),
                          true, ImGuiWindowFlags_HorizontalScrollbar);

        ImGui::TextWrapped("%s", output_text);

        ImGui::EndChild();

        ImGui::SameLine();
        ImGui::BeginChild("ButtonBlock", ImVec2(ImGuiWindowWidth * 0.29f, -1),
                          true);
        if (ImGui::Button("Save", ImVec2(ImGuiWindowWidth * 0.29f, 0)))
            save = true;

        if (save) save_txt();
        ImGui::EndChild();
        ImGui::End();
    }

    void save_txt()
    {
        ImGui::InputText("##", file_name, sizeof(file_name));
        std::string file_name_str(file_name);
        if (ImGui::Button("ToFile")) {
            if (!endsWith(file_name_str, ".txt")) file_name_str += ".txt";
            std::ofstream output_file(file_name_str);
            if (output_file.is_open()) {
                output_file << output_text;
                memset(output_text, '\0', sizeof(output_text));
                save = false;
                output_file.close();
            }
        }
    }
} // namespace MyApp
