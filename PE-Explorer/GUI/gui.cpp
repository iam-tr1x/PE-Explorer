#include "gui.h"

void gui::render_ui()
{
    ImGui::Begin("PE Inspector", nullptr, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);
    {
        this->render_menubar();


        this->render_pagebar();
        {
            
         
        }
    }

    ImGui::End();
}

void gui::render_menubar()
{
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Open...", "Ctrl+O")) open_file();
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }
}

void gui::render_pagebar()
{


    ImGui::ShowDemoWindow();
    if (ImGui::BeginTabBar("###pagebar"))
    {
        if (ImGui::BeginTabItem("Overview"))
        {
            page = 0;
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Test"))
        {
            page = 1;



            ImGui::EndTabItem();
        }
    }
    ImGui::EndTabBar();
}

PWSTR gui::open_file()
{
    IFileOpenDialog* fileOpen = nullptr;
    IShellItem* item = nullptr;
    PWSTR filePath = nullptr;

    const HRESULT initResult = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    if (FAILED(initResult))
    {
        return nullptr;
    }

    const HRESULT instanceResult = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog, reinterpret_cast<void**>(&fileOpen));
    if (FAILED(instanceResult))
    {
        CoUninitialize();
        return nullptr;
    }

    const HRESULT showDialog = fileOpen->Show(NULL);
    const HRESULT getItemFromDialog = fileOpen->GetResult(&item);

    if (FAILED(showDialog) || FAILED(getItemFromDialog))
    {
        fileOpen->Release();
        CoUninitialize();
        return nullptr;
    }

    item->GetDisplayName(SIGDN_FILESYSPATH, &filePath);

    item->Release();
    fileOpen->Release();
    CoUninitialize();
    return filePath;
}
