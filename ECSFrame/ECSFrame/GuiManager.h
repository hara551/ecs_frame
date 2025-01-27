/**
* @file   GuiStructureManager.h
* @brief  GUI�\���Ǘ�.
* @author Hara Sota.
* @date   2024/11/15
*/
#ifndef _GUI_STRUCTURE_MANAGER_H_
#define _GUI_STRUCTURE_MANAGER_H_

#include <string>
#include <unordered_map>
#include <vector>

#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"

#include "GuiWindow.h"
#include "GuiPopup.h"
#include "GuiSelectable.h"
#include "GuiButton.h"
#include "GuiText.h"
#include "GuiTreeNode.h"
#include "GuiInputBase.h"
#include "GuiInputText.h"
#include "GuiCheckBox.h"
#include "GuiInputInt.h"
#include "GuiInputFloat.h"
#include "GuiInputFloat2.h"
#include "GuiInputFloat3.h"
#include "GuiInputColor.h"
#include "GuiInputDragFloat.h"
#include "GuiInputDragFloat3.h"
#include "FileUtil.h"

namespace HaraProject::Framework {

class GuiManager
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	GuiManager();

	/**
	* @brief �f�X�g���N�^
	*/
	~GuiManager();

	/**
	* @brief GUI�`��
	*/
	void DrawGUI();

	/**
	* @brief �A�C�e���擾
	* @tparam GuiType �󂯎�肽���^
	* @param[in] path �K�w
	*/
	template<typename GuiType> GuiType* GetGuiItem(const char* path);

	/**
	* @brief �A�C�e���폜
	* @param[in] item GUI�A�C�e��
	*/
	void DeleteGuiItem(GuiItemBase* item) {
		// �E�B���h�E���|�b�v�A�b�v�Ȃ�R���e�i������폜
		auto sort = [item](auto& itr)
		{
			return itr.first == item->GetLabel();
		};
		std::erase_if(m_name_to_root_window, sort);
		std::erase_if(m_name_to_popup, sort);

		// �e����؂藣���ĉ��
		item->DetachParent();
		delete item;
	}

	/**
	* @brief �E�B���h�E���쐬���o�^
	* @param[in] title �E�B���h�E�^�C�g��
	* @param[in] id ����ID�d���h�~�p�̔C�ӂ̎��ʎq
	* @param[in] isShow �\���t���O
	* @param[in] pos �\���ʒu
	* @param[in] size �T�C�Y
	*/
	GuiWindow* RegisterGuiWindow(std::string title, std::string id, bool isShow, ImVec2 pos, ImVec2 size);

	/**
	* @brief �|�b�v�A�b�v���쐬���o�^
	* @param[in] title �|�b�v�A�b�v�^�C�g��
	* @param[in] id ����ID�d���h�~�p�̔C�ӂ̎��ʎq
	* @param[in] isShow �\���t���O
	*/
	GuiPopup* RegisterGuiPopup(std::string title, std::string id, bool isShow = false);

	/**
	* @brief �I�����ڃA�C�e�����쐬
	* @param[in] label ���x��
	* @param[in] id ����ID�d���h�~�p�̔C�ӂ̎��ʎq
	* @param[in] onSelect �I�����Ɏ��s����֐�
	*/
	GuiSelectable* CreateGuiSelectable(std::string label, std::string id, std::function<void()> onSelect) {
		return new GuiSelectable(label, id, onSelect);
	}

	/**
	* @brief �{�^�����쐬
	* @param[in] label ���x��
	* @param[in] id ����ID�d���h�~�p�̔C�ӂ̎��ʎq
	* @param[in] onSelect �I�����Ɏ��s����֐�
	*/
	GuiButton* CreateGuiButton(std::string label, std::string id, std::function<void()> onClick){
		return new GuiButton(label, id, onClick);
	}

	/**
	* @brief �e�L�X�g���쐬
	* @param[in] text �e�L�X�g
	* @param[in] id ����ID�d���h�~�p�̔C�ӂ̎��ʎq
	*/
	GuiText* CreateGuiText(std::string text) {
		return new GuiText(text);
	}

	/**
	* @brief �c���[�m�[�h���쐬
	* @param[in] label ���x��
	* @param[in] id ����ID�d���h�~�p�̔C�ӂ̎��ʎq
	* @param[in] isDefaultOpen �����m�[�h�J�t���O
	* @param[in] onSelect �I�����Ɏ��s����֐�
	*/
	GuiTreeNode* CreateGuiTreeNode(std::string label, std::string id, bool isDefaultOpen = true, 
		std::function<void()> onSelect = nullptr, std::function<void()> onClickRight = nullptr, bool isLeaf = false) {
		return new GuiTreeNode(label, id, isDefaultOpen, onSelect, onClickRight, isLeaf);
	}

	/**
	* @brief �e�L�X�g���̓A�C�e���쐬
	* @param[in] title �m�[�h���x��
	* @param[in] id ����ID�d���h�~�p�̔C�ӂ̎��ʎq
	* @param[in] overWriteMode ���������^�C�~���O�I�v�V����
	* @param[in] outputBuffer �l�ύX���ɒl���i�[����o�b�t�@
	*/
	GuiInputText* CreateGuiInputText(std::string label, std::string id, GuiInputBase::OverWriteMode overWriteMode, char* outputBuffer) {
		return new GuiInputText(label, id, overWriteMode, outputBuffer);
	}

	/**
	* @brief �`�F�b�N�{�b�N�X�쐬
	* @param[in] label ���x��
	* @param[in] id ����ID�d���h�~�p�̔C�ӂ̎��ʎq
	* @param[in] outputBuffer �l�ύX���ɒl���i�[����o�b�t�@
	* @param[in] onChage �`�F�b�N��ԕύX���Ɏ��s����֐�
	*/
	GuiCheckBox* CreateGuiCheckBox(std::string label, std::string id, bool* outputBuffer, std::function<void()> onChange = nullptr) {
		return new GuiCheckBox(label, id, outputBuffer, onChange);
	}

	/**
	* @brief int���̓A�C�e���쐬
	* @param[in] label ���x��
	* @param[in] id ����ID�d���h�~�p�̔C�ӂ̎��ʎq
	* @param[in] outputBuffer �l�ύX���ɒl���i�[����o�b�t�@
	* @param[in] overWriteMode ���������^�C�~���O�I�v�V����
	*/
	GuiInputInt* CreateGuiInputInt(std::string label, std::string id, int* outputBuffer, GuiInputBase::OverWriteMode overWriteMode = GuiInputBase::Always) {
		return new GuiInputInt(label, id, outputBuffer, overWriteMode);
	}

	/**
	* @brief float���̓A�C�e���쐬
	* @param[in] label ���x��
	* @param[in] id ����ID�d���h�~�p�̔C�ӂ̎��ʎq
	* @param[in] outputBuffer �l�ύX���ɒl���i�[����o�b�t�@
	* @param[in] decimalPlaces �\�����鏭������
	* @param[in] overWriteMode ���������^�C�~���O�I�v�V����
	*/
	GuiInputFloat* CreateGuiInputFloat(std::string label, std::string id, float* outputBuffer,
		int decimalPlaces = GuiInputFloat::DEFAULT_DECIMAL_PLACES, GuiInputBase::OverWriteMode overWriteMode = GuiInputBase::Always) {
		return new GuiInputFloat(label, id, outputBuffer, decimalPlaces, overWriteMode);
	}

	/**
	* @brief float2���̓A�C�e���쐬
	* @param[in] label ���x��
	* @param[in] id ����ID�d���h�~�p�̔C�ӂ̎��ʎq
	* @param[in] outputBuffer �l�ύX���ɒl���i�[����o�b�t�@
	* @param[in] decimalPlaces �\�����鏭������
	* @param[in] overWriteMode ���������^�C�~���O�I�v�V����
	*/
	GuiInputFloat2* CreateGuiInputFloat2(std::string label, std::string id, DirectX::XMFLOAT2* outputBuffer,
		int decimalPlaces = GuiInputFloat::DEFAULT_DECIMAL_PLACES, GuiInputBase::OverWriteMode overWriteMode = GuiInputBase::Always) {
		return new GuiInputFloat2(label, id, outputBuffer, decimalPlaces, overWriteMode);
	}

	/**
	* @brief float3���̓A�C�e���쐬
	* @param[in] label ���x��
	* @param[in] id ����ID�d���h�~�p�̔C�ӂ̎��ʎq
	* @param[in] outputBuffer �l�ύX���ɒl���i�[����o�b�t�@
	* @param[in] decimalPlaces �\�����鏭������
	* @param[in] overWriteMode ���������^�C�~���O�I�v�V����
	*/
	GuiInputFloat3* CreateGuiInputFloat3(std::string label, std::string id, DirectX::XMFLOAT3* outputBuffer,
		int decimalPlaces = GuiInputFloat::DEFAULT_DECIMAL_PLACES, GuiInputBase::OverWriteMode overWriteMode = GuiInputBase::Always){
		return new GuiInputFloat3(label, id, outputBuffer, decimalPlaces, overWriteMode);
	}

	/**
	* @brief Color���̓A�C�e���쐬
	* @param[in] label ���x��
	* @param[in] id ����ID�d���h�~�p�̔C�ӂ̎��ʎq
	* @param[in] outputBuffer �l�ύX���ɒl���i�[����o�b�t�@
	*/
	GuiInputColor* CreateGuiInputColor(std::string label, std::string id, DirectX::XMFLOAT4* outputBuffer) {
		return new GuiInputColor(label, id, outputBuffer);
	}

	/**
	* @brief �h���b�O�ł�Float���̓A�C�e���쐬
	* @param[in] label ���x��
	* @param[in] id ����ID�d���h�~�p�̔C�ӂ̎��ʎq
	* @param[in] outputBuffer �l�ύX���ɒl���i�[����o�b�t�@
	* @param[in] dragSpeed �h���b�O�ŕς��l�̑傫���ɂ��Ẵp�����[�^
	* @param[in] min �ŏ��l
	* @param[in] min �ő�l
	*/
	GuiInputDragFloat* CreateGuiInputDragFloat(std::string label, std::string id, float* outputBuffer, float dragSpeed,
		float min, float max) {
		return new GuiInputDragFloat(label, id, outputBuffer, dragSpeed, min, max);
	}

	/**
	* @brief �h���b�O�ł�Float3���̓A�C�e���쐬
	* @param[in] label ���x��
	* @param[in] id ����ID�d���h�~�p�̔C�ӂ̎��ʎq
	* @param[in] outputBuffer �l�ύX���ɒl���i�[����o�b�t�@
	* @param[in] dragSpeed �h���b�O�ŕς��l�̑傫���ɂ��Ẵp�����[�^
	*/
	GuiInputDragFloat3* CreateGuiInputDragFloat3(std::string label, std::string id, DirectX::XMFLOAT3* outputBuffer, float dragSpeed){
		return new GuiInputDragFloat3(label, id, outputBuffer, dragSpeed);
	}

private:
	/**
	* @brief GUI�`�揀��
	*/
	void BeginDrawImGui() {
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
	}

	/**
	* @brief GUI�`��I��
	*/
	void EndDrawImGui() {
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}

	/**
	* @brief �E�B���h�E���ƃE�B���h�E�̃}�b�v
	*/
	std::unordered_map<std::string, GuiWindow*> m_name_to_root_window;

	/**
	* @brief �|�b�v�A�b�v���ƃ|�b�v�A�b�v���j���[�̃}�b�v
	*/
	std::unordered_map<std::string, GuiPopup*> m_name_to_popup;
};

/**
* @brief �A�C�e���擾
* @tparam GuiType �󂯎�肽���^
* @param[in] path �K�w
*/
template<typename GuiType>
inline GuiType* GuiManager::GetGuiItem(const char* path)
{
	// �p�X�𕪊�
	std::vector<std::string> parts = SplitPath(path);

	GuiItemBase* item{};

	if (m_name_to_root_window.contains(parts[0]))
	{
		// �ォ�牺�ɖ��O�ŒH���Ă���
		item = m_name_to_root_window[parts[0]];
		for (int current = 1; current < parts.size(); ++current)
		{
			if (item != nullptr)
			{
				item = item->GetChild(parts[current]);
			}
		}
		return  dynamic_cast<GuiType*>(item);
	}

	if (m_name_to_popup.contains(parts[0]))
	{
		item = m_name_to_popup[parts[0]];
		for (int current = 1; current < parts.size(); ++current)
		{
			if (item != nullptr)
			{
				item = item->GetChild(parts[current]);
			}
		}
		return dynamic_cast<GuiType*>(item);
	}
	return nullptr;
}

}// !namespace HaraProject::Framework

#endif // !_GUI_STRUCTURE_MANAGER_H_
