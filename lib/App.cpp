#include "../headers/App.h"
#include "../headers/glfw3.h"
#include "../headers/imgui.h"
#include <fstream>
#include <iostream>
#include "../headers/SerialPort.hpp"
#include <cstring>

#define DATA_LENGTH 4096
#define INPUT_BUF_LENGTH 256

bool endsWith(const std::string& str, const char* txt)
{
    std::string txt_str(txt);
    if (str.length() >= txt_str.length())
        return (0
                == str.compare(str.length() - txt_str.length(),
                               txt_str.length(), txt_str));
    return false;
}
const char *portName = "\\\\.\\COM5";

namespace MyApp {
    char output_text[DATA_LENGTH] = "";
    char arduino_data[INPUT_BUF_LENGTH];
    char file_name[INPUT_BUF_LENGTH] = "";
    bool save = false;
    bool stop = false;
    void save_txt();
    SerialPort *arduino = new SerialPort(portName);
    void RenderUI()
    {
        if(!stop){
            if (arduino->isConnected()){
                int hasRead = arduino->readSerialPort(arduino_data, INPUT_BUF_LENGTH);
                strcat_s(output_text, arduino_data);
            }else{
                exit(0);
            }
        }

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
        if (ImGui::Button("Continue", ImVec2(ImGuiWindowWidth * 0.29f*0.4f, 0))){
            stop = false;
        }
        ImGui::SameLine();
        if (ImGui::Button("Stop", ImVec2(ImGuiWindowWidth * 0.29f*0.4f, 0))){
            stop = true;
        }
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
