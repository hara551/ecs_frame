#include "UITextureManager.h"
#include "FileUtil.h"

namespace HaraProject::Framework {

/**
* @brief �e�N�X�`���Ǎ�
* @param[in] fileName �t�@�C����
*/
bool UITextureManager::LoadTexture(std::string fileName)
{
	// ���łɃ��[�h�ςȂ琬����Ԃ�
	if (m_name_to_texture.contains(fileName))return true;

	// �t�@�C�������݂��Ȃ���Ύ��s��Ԃ�
	if (!FileExists(FileType::UITexture, fileName.c_str()))
	{
		return false;
	}

	std::string path = CreatePath(FileType::UITexture, fileName.c_str());

	Texture* texture = new Texture();
	if (!FAILED(texture->Create(path.c_str())))
	{
		m_name_to_texture[fileName] = texture;
		return true;
	}
	
	SAFE_DELETE(texture);
	return false;
}

/**
* @brief �e�N�X�`���擾
* @param[in] fileEntityName �t�@�C����
*/
Texture* UITextureManager::FindTexture(std::string fileName)
{
	if (m_name_to_texture.contains(fileName))
	{
		return m_name_to_texture[fileName];
	}
	return nullptr;
}

/**
* @brief �e�N�X�`�����
* @param[in] fileName �t�@�C����
*/
void UITextureManager::ReleaseTexture(std::string fileName)
{
	if (!m_name_to_texture.contains(fileName)) return;

	SAFE_DELETE(m_name_to_texture[fileName]);

	std::erase_if(m_name_to_texture,
		[&](const auto& itr)
		{
			return itr.first == fileName;
		});
}

/**
* @brief �S�e�N�X�`�����
*/
void UITextureManager::ReleaseAllTexture()
{
	for (auto& itr : m_name_to_texture)
	{
		SAFE_DELETE(itr.second);
	}
	m_name_to_texture.clear();
}

/**
* @brief �f�X�g���N�^
*/
UITextureManager::~UITextureManager()
{
	ReleaseAllTexture();
}

}// !namespace HaraProject::Framework