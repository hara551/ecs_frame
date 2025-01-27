/**
* @file   ClipboardHolder.h
* @brief  エディターのコピペ機能管理.
* @author Hara Sota.
* @date   2024/11/15
*/
#ifndef _CLIP_BOARD_HOLDER_H_
#define _CLIP_BOARD_HOLDER_H_

#include <string>
#include <unordered_map>

#include "ComponentMask.h"
#include "ComponentDataBase.h"

namespace HaraProject::Framework {

class ClipboardHolder
{
public:
	/**
	* @brief コンストラクタ
	*/
	ClipboardHolder() = default;

	/**
	* @brief デストラクタ
	*/
	~ClipboardHolder() = default;

	/**
	* @brief コピーされたエンティティデータを取得
	*/
	std::unordered_map<ComponentBits, ComponentDataBase*> GetCopyEntityData() {
		return m_copy_entity_data;
	}

	/**
	* @brief コピー用エンティティデータを設定
	* @param[in] copyEntityData コピーしたエンティティデータ
	*/
	void SetCopyEntityData(std::unordered_map<ComponentBits, ComponentDataBase*> copyEntityData) {
		m_copy_entity_data = copyEntityData;
	}

private:
	/**
	* @brief コピーしたエンティティデータ
	*/
	std::unordered_map<ComponentBits, ComponentDataBase*> m_copy_entity_data;


};

}// !namespace HaraProject::Framework

#endif // !_CLIP_BOARD_HOLDER_H_