/**
* @file   UITextureManager.h
* @brief  UI�e�N�X�`���Ǘ��N���X��`.
* @author Hara Sota.
* @date   2024/10/17
*/
#ifndef _UI_TEXTURE_MANAGER_H_
#define _UI_TEXTURE_MANAGER_H_

#include <string>
#include <unordered_map>

#include "Texture.h"

namespace HaraProject::Framework {

class UITextureManager
{
public:
	/**
	* @brief �C���X�^���X�擾
	*/
	static UITextureManager& Instance() {
		static UITextureManager instance;
		return instance;
	}

	/**
	* @brief �e�N�X�`���Ǎ�
	* @param[in] fileEntityName �t�@�C����
	*/
	bool LoadTexture(std::string fileName);

	/**
	* @brief �e�N�X�`���擾
	* @param[in] fileEntityName �t�@�C����
	*/
	Texture* FindTexture(std::string fileName);

	/**
	* @brief �e�N�X�`�����
	* @param[in] fileEntityName �t�@�C����
	*/
	void ReleaseTexture(std::string fileEntityName);

	/**
	* @brief �S�e�N�X�`�����
	*/
	void ReleaseAllTexture();

private:
	UITextureManager() = default;
	UITextureManager(const UITextureManager&) = delete;
	UITextureManager& operator=(const UITextureManager&) = delete;

	/**
	* @brief �f�X�g���N�^
	*/
	~UITextureManager();

	/**
	* @brief �t�@�C�����ƃe�N�X�`���̃}�b�v
	*/
	std::unordered_map<std::string, Texture*> m_name_to_texture;
};

}// !namespace HaraProject::Framework

#endif // !_UI_TEXTURE_MANAGER_H_
