#include <string>

#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"

#include "DirectX.h"
#include "GuiWindow.h"
#include "GuiPopup.h"
#include "GuiSelectable.h"
#include "GuiTreeNode.h"
#include "GuiInputBase.h"
#include "GuiInputText.h"
#include "GuiCheckBox.h"
#include "GuiInputInt.h"
#include "GuiInputFloat.h"
#include "GuiInputFloat3.h"

#include "GuiManager.h"
#include "Main.h"
namespace HaraProject::Framework {

/**
* @brief コンストラクタ
*/
GuiManager::GuiManager()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui::StyleColorsDark();
    ImGui_ImplWin32_Init(GetActiveWindow());
    ImGui_ImplDX11_Init(GetDevice(), GetContext());
}

/**
* @brief デストラクタ
*/
GuiManager::~GuiManager()
{
    // 全アイテム解放
    for (auto& window : m_name_to_root_window)
    {
        if (window.second != nullptr)
        {
            delete window.second;
            window.second = nullptr;
        }
    }
    for (auto& popup : m_name_to_popup)
    {
        if (popup.second != nullptr)
        {
            delete popup.second;
            popup.second = nullptr;
        }
    }
    m_name_to_root_window.clear();
    m_name_to_popup.clear();

    // ImGui終了処理
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

/**
* @brief GUI描画
*/
void GuiManager::DrawGUI()
{
    BeginDrawImGui();

    // ウィンドウ描画
    for (const auto& window : m_name_to_root_window)
    {
        if (window.second != nullptr)
        {
            window.second->Draw();
        }
    }
    // ポップアップ描画
    for (const auto& popup : m_name_to_popup)
    {
        if (popup.second->HasChild())
        {
            popup.second->Draw();
        }
    }

    EndDrawImGui();
}

/**
* @brief ウィンドウを作成し登録
* @param[in] title ウィンドウタイトル
* @param[in] id 内部ID重複防止用の任意の識別子
* @param[in] isShow 表示フラグ
* @param[in] pos 表示位置
* @param[in] size サイズ
*/
GuiWindow* GuiManager::RegisterGuiWindow(std::string title, std::string id, bool isShow, ImVec2 pos, ImVec2 size)
{
    if (!m_name_to_root_window.contains(title))
    {
        m_name_to_root_window[title] = new GuiWindow(title, id, isShow, pos, size);
        return m_name_to_root_window[title];
    }
    return nullptr;
}

/**
* @brief ポップアップを作成し登録
* @param[in] title ポップアップタイトル
* @param[in] id 内部ID重複防止用の任意の識別子
* @param[in] isShow 表示フラグ
*/
GuiPopup* GuiManager::RegisterGuiPopup(std::string title, std::string id, bool isShow)
{
    if (!m_name_to_popup.contains(title))
    {
        m_name_to_popup[title] = new GuiPopup(title, id, isShow);
        return m_name_to_popup[title];
    }
    return nullptr;
}

}// !namespace HaraProject::Framework