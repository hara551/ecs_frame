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
* @brief �R���X�g���N�^
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
* @brief �f�X�g���N�^
*/
GuiManager::~GuiManager()
{
    // �S�A�C�e�����
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

    // ImGui�I������
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

/**
* @brief GUI�`��
*/
void GuiManager::DrawGUI()
{
    BeginDrawImGui();

    // �E�B���h�E�`��
    for (const auto& window : m_name_to_root_window)
    {
        if (window.second != nullptr)
        {
            window.second->Draw();
        }
    }
    // �|�b�v�A�b�v�`��
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
* @brief �E�B���h�E���쐬���o�^
* @param[in] title �E�B���h�E�^�C�g��
* @param[in] id ����ID�d���h�~�p�̔C�ӂ̎��ʎq
* @param[in] isShow �\���t���O
* @param[in] pos �\���ʒu
* @param[in] size �T�C�Y
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
* @brief �|�b�v�A�b�v���쐬���o�^
* @param[in] title �|�b�v�A�b�v�^�C�g��
* @param[in] id ����ID�d���h�~�p�̔C�ӂ̎��ʎq
* @param[in] isShow �\���t���O
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