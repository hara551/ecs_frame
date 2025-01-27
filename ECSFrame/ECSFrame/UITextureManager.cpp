#include "UITextureManager.h"
#include "FileUtil.h"

namespace HaraProject::Framework {

/**
* @brief テクスチャ読込
* @param[in] fileName ファイル名
*/
bool UITextureManager::LoadTexture(std::string fileName)
{
	// すでにロード済なら成功を返す
	if (m_name_to_texture.contains(fileName))return true;

	// ファイルが存在しなければ失敗を返す
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
* @brief テクスチャ取得
* @param[in] fileEntityName ファイル名
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
* @brief テクスチャ解放
* @param[in] fileName ファイル名
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
* @brief 全テクスチャ解放
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
* @brief デストラクタ
*/
UITextureManager::~UITextureManager()
{
	ReleaseAllTexture();
}

}// !namespace HaraProject::Framework