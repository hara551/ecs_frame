/**
* @file   UITextureManager.h
* @brief  UIテクスチャ管理クラス定義.
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
	* @brief インスタンス取得
	*/
	static UITextureManager& Instance() {
		static UITextureManager instance;
		return instance;
	}

	/**
	* @brief テクスチャ読込
	* @param[in] fileEntityName ファイル名
	*/
	bool LoadTexture(std::string fileName);

	/**
	* @brief テクスチャ取得
	* @param[in] fileEntityName ファイル名
	*/
	Texture* FindTexture(std::string fileName);

	/**
	* @brief テクスチャ解放
	* @param[in] fileEntityName ファイル名
	*/
	void ReleaseTexture(std::string fileEntityName);

	/**
	* @brief 全テクスチャ解放
	*/
	void ReleaseAllTexture();

private:
	UITextureManager() = default;
	UITextureManager(const UITextureManager&) = delete;
	UITextureManager& operator=(const UITextureManager&) = delete;

	/**
	* @brief デストラクタ
	*/
	~UITextureManager();

	/**
	* @brief ファイル名とテクスチャのマップ
	*/
	std::unordered_map<std::string, Texture*> m_name_to_texture;
};

}// !namespace HaraProject::Framework

#endif // !_UI_TEXTURE_MANAGER_H_
