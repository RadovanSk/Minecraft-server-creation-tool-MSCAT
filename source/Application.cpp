#include "Application.h"
#include "imgui.h"
#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <String.h>

using namespace std;

namespace MyApp
{
    static void HelpMarker(const char* desc)

    {
        ImGui::TextDisabled("(?)");
        if (ImGui::IsItemHovered())
        {
            ImGui::BeginTooltip();
            ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
            ImGui::TextUnformatted(desc);
            ImGui::PopTextWrapPos();
            ImGui::EndTooltip();
        }
    }

    void RenderUI()
    {
        static bool show_app_fullscreen = true;
        static bool use_work_area = true;
        static ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings;
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(use_work_area ? viewport->WorkPos : viewport->Pos);
        ImGui::SetNextWindowSize(use_work_area ? viewport->WorkSize : viewport->Size);
        ShowWindow(::GetConsoleWindow(), SW_HIDE);
        static bool G1G = false;
        static bool ExperimentalVmOptions = true;
        static bool NOGUI = false;

        ImGui::Begin("Window", NULL, ImGuiWindowFlags_AlwaysAutoResize);
        static float f0 = 0.0f;


        static char str1[128] = "";
        static char str2[128] = "";
        static char str3[128] = "";
        static char str4[128] = "";
        static char str5[128] = "";
        static char str6[128] = "";
        static char str7[128] = "";
        static char str8[128] = "";
        static char str9[128] = "";
        static char str10[128] = "";
        string version = str1;
        string MXram = str3;
        string MNram = str4;
        string glintvalue = str6;
        string g1youngvalue = str7;
        string g1reservevalue = str8;
        string pauseintvalue = str9;
        string g1regionvalue = str10;
        string exmvmo;
        string nogui;
        string g1g;
        string parallelt;
        string g1int;
        string g1young;
        string g1reserve;
        string pauseint;
        string g1region;
        string megabyte;

        ImGui::InputTextWithHint("Directory of java .exe file.", "Default is latest version.", str1, IM_ARRAYSIZE(str1));
        ImGui::SameLine(); HelpMarker("Older minecraft versions cannot run on newer java versions such as Java 16 or Java 17. When your server is unable to run this might be the reason. You need to specify the directory of java .exe file. Normally it has to be between quotation marks but this program will do it for you automatically. Example: C:\\Program Files\\Java\\jdk1.8.0_321\\bin\\java.exe");

        ImGui::InputTextWithHint("Name of the server file without the extension.", "Server file name.", str2, IM_ARRAYSIZE(str2));
        ImGui::SameLine(); HelpMarker("The .bat file opens itself and java server file. They both run together at the same time. That's why it's needed to include the name of the server file.");

        ImGui::InputTextWithHint("How much max RAM do you want?", "Default is 4GB RAM.", str3, IM_ARRAYSIZE(str3), ImGuiInputTextFlags_CharsDecimal);
        ImGui::SameLine(); HelpMarker("Sets specified amount to be maximum limit for RAM allocation to the server. 4GB is recommended for vanilla servers and 6GB is for modpacks. The value varies depending on the player count and the amount of mods or the size of a modpack.");

        ImGui::InputTextWithHint("How much min RAM do you want?", "Default is 1GB RAM.", str4, IM_ARRAYSIZE(str4), ImGuiInputTextFlags_CharsDecimal);
        ImGui::SameLine(); HelpMarker("Sets specified amount to be minimum limit for RAM allocation to the server. 1GB is recommended. Lower value is better because if it were higher your operating system would have less RAM to process with, resulting in more lag.");

        ImGui::Checkbox("Unlock experimental flags.", &ExperimentalVmOptions);
        ImGui::SameLine(); HelpMarker("Some JVM arguments are experimental flags. This function unlocks them making them possible to edit.");

        ImGui::Checkbox("No GUI.", &NOGUI);
        ImGui::SameLine(); HelpMarker("Disables java GUI and leaves .bat file opened only. Like mentioned above, the .bat file runs together with java file. Disabled GUI makes the java file invisible and leaves only .bat file opened making it look cleaner. It's recommended to have GUI disabled, especially for modded servers.");

        ImGui::Checkbox("G1 Garbage Collector.", &G1G);
        ImGui::SameLine(); HelpMarker("Used for allocation of memory and to release and prevent memory leak. Usueally results in lower RAM usage.");


        if (G1G == true)
        {
            ImGui::InputTextWithHint("On how many threads should G1 Garbage Collector run on?", "Threads amount.", str5, IM_ARRAYSIZE(str5), ImGuiInputTextFlags_CharsDecimal);
            ImGui::SameLine(); HelpMarker("Recommended is 50% of your CPU's threads if you have a powerful CPU. Otherwise 25% is recommended.");

            ImGui::InputTextWithHint("How many seconds should it take for each automatic full garbage collection to happen?", "Default is never.", str6, IM_ARRAYSIZE(str6), ImGuiInputTextFlags_CharsDecimal);
            ImGui::SameLine(); HelpMarker("Sets the amount of milliseconds between each automatic full garbage collection. Default is never. Recommended is 3600000ms with five zeros (1 hour) or never depending on the hardware.");

            ImGui::InputTextWithHint("How much percentage of the heap should be used as the minimum for the young generation size?", "Default is 5.", str7, IM_ARRAYSIZE(str7), ImGuiInputTextFlags_CharsDecimal);
            ImGui::SameLine(); HelpMarker("Higher value means less minor and more major collections will happen. Lower value means more minor and less major collections will happen. Recommendation varies depending on hardware.");

            ImGui::InputTextWithHint("How much percentage of reserve memory should be kept free to reduce the risk of to-space overflows?", "Default is 10.", str8, IM_ARRAYSIZE(str8), ImGuiInputTextFlags_CharsDecimal);
            ImGui::SameLine(); HelpMarker("Reduces the risk of to-space overflows. You can change the maximum heap size of java according to the value of this function if you want to.");

            ImGui::InputTextWithHint("How much milliseconds should be set as the peak pause time in the environment?", "Default is 500.", str9, IM_ARRAYSIZE(str9), ImGuiInputTextFlags_CharsDecimal);
            ImGui::SameLine(); HelpMarker("Lowering it results in decreased latency and throughput. Making it higher results in increased latency and throughput. Recommended is between 500 - 2000. Go below 500 with caution, the effects might be less efficent and garbage collector will run more agressively.");

            ImGui::InputTextWithHint("Size of G1 region.", "Default is 32.", str10, IM_ARRAYSIZE(str10), ImGuiInputTextFlags_CharsDecimal);
            ImGui::SameLine(); HelpMarker("The value will be a power of two and can range from 1MB to 32MB. The goal is to have around 2048 regions based on the minimum Java heap size (To be honest I don't understand this that much).");

            parallelt = "-XX:ParallelGCThreads=";
            g1int = " -Dsun.rmi.dgc.server.gcInterval=";
            g1young = " -XX:G1NewSizePercent=";
            g1reserve = " -XX:G1ReservePercent=";
            pauseint = " -XX:MaxGCPauseMillis=";
            g1region = " -XX:G1HeapRegionSize=";
            megabyte = "M ";

            if (!*str3)
            {
                MXram = "4";
            }

            if (!*str4)
            {
                MNram = "1";
            }

            if (!*str6)
            {
                glintvalue = "2147483647";
            }

            if (!*str7)
            {
                g1youngvalue = "5";
            }

            if (!*str8)
            {
                g1reservevalue = "10";
            }

            if (!*str9)
            {
                pauseintvalue = "500";
            }

            if (!*str10)
            {
                g1regionvalue = "32";
            }
        }

        else
        {
            parallelt;
            g1int;
            g1young;
            g1reserve;
            pauseint;
            g1region;
            megabyte;
        }

        if (!*str1)
        {
            version = "java";
        }

        if (ExperimentalVmOptions == true)
        {
            exmvmo = "-XX:+UnlockExperimentalVMOptions ";
        }

        else
        {
            exmvmo;
        }

        if (NOGUI == true)
        {
            nogui = "nogui";
        }

        else
        {
            nogui;
        }

        if (G1G == true)
        {
            g1g = "-XX:+UseG1GC ";
        }

        else
        {
            g1g;
        }


        {
        
            if (ImGui::Button("Create .bat file"))
            {
                ofstream MyFile("launch.bat");
                MyFile << "\"" << version << "\"" << " -Xmx"  << MXram << "G -Xmx" << MNram << "G " << exmvmo << g1g << parallelt << str5 << g1int << glintvalue << g1young << g1youngvalue << g1reserve << g1reservevalue << pauseint << pauseintvalue << g1region << g1regionvalue << megabyte << "-jar " << str2 << ".jar " << nogui;
                MyFile.close();
            }
        }
        ImGui::End();
    }
}
