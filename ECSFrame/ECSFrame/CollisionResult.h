/**
* @file   CollisionResult.h
* @brief　当たり判定用ボックス
* @author Hara Sota.
* @date   2024/10/14.
*/
#ifndef _COLLISION_RESULT_H_
#define _COLLISION_RESULT_H_

#include <DirectXMath.h>

#include <memory>

#ifdef _DEBUG
#include "GuiManager.h"
#include "GuiItemBase.h"
#include "GuiTreeNode.h"
#include "GuiInputFloat3.h"
#endif // _DEBUG

#include "ComponentDataBase.h"

namespace HaraProject::Framework
{

class CollisionResult : public ComponentDataBase
{
public:
	/**
	* @brief データ名
	*/
	static constexpr const char* COLLISION_RESULT_NAME = "CollisionResult";
	static constexpr const char* COLLISION_RESULT_COLLIDED_ENTITIES_NAME = "collidedEntities";
	static constexpr const char* COLLISION_RESULT_COLLISION_COUNT_NAME = "collisionCount";

	static constexpr const char* COLLIDED_ENTITY_ID = "entityId";
	static constexpr const char* COLLIDED_COLLISION_POINT = "collisionPoint";
	static constexpr const char* COLLIDED_COLLISION_NORMAL = "collisionNormal";

	/**
	* @brief 衝突情報
	*/
	struct CollisionInfo
	{
		/**
		* @brief 衝突したエンティティのID
		*/
		uint32_t entityId;

		/**
		* @brief 衝突が起きた座標
		*/
		DirectX::XMFLOAT3 collisionPoint;

		/**
		* @brief 衝突方向
		*/
		DirectX::XMFLOAT3 collisionNormal;
	};

	/**
	* @brief 衝突情報を保持できる最大数
	*/
	static constexpr uint8_t MAX_COLLISIONS = 8;

	/**
	* @brief デフォルトコンストラクタ
	*/
	CollisionResult() :isCollided(false),collisionCount(0) {};

	/**
	* @brief コピーコンストラクタ
	* @param[in] base Transformが入った基底クラスポインタ
	*/
	CollisionResult(ComponentDataBase* base)
	{
		auto* value = dynamic_cast<CollisionResult*>(base);
		for (int i = 0; i < MAX_COLLISIONS; ++i)
		{
			collidedDatas[i] = value->collidedDatas[i];
		}
		collisionCount = value->collisionCount;
	}

	/**
	* @brief Jsonデータから値を設定する
	* @param[in] json jsonオブジェクト
	*/
	void SetDataFromJson(nlohmann::json jsonData)override{}

	/**
	* @brief 衝突情報をクリア
	*/
	void Clear() {
		for (int i = 0; i < MAX_COLLISIONS; ++i)
		{
			collidedDatas[i] = CollisionInfo();
		}
		collisionCount = 0;
		isCollided = false;
	}

	/**
	* @brief 衝突情報を追加
	*/
	void AddCollidedEntity(uint32_t id, DirectX::XMFLOAT3 point, DirectX::XMFLOAT3 normal) {
		isCollided = true;
		if(collisionCount < MAX_COLLISIONS)
		{ 
			collidedDatas[collisionCount] = CollisionInfo(id, point, normal);
			++collisionCount;
		}
	}

#ifdef _DEBUG
	/**
	* @brief 現在の値をJsonデータに変換する
	*/
	nlohmann::json WriteDataToJson()override { nlohmann::json def{}; def[COLLISION_RESULT_NAME] = "no save"; return def; }

	/**
	* @brief インスペクタ―表示作成
	*/
	GuiItemBase* CreateDetailContent(GuiManager* guiManager)override
	{
		GuiTreeNode* collision_result_name = guiManager->CreateGuiTreeNode(COLLISION_RESULT_NAME, "id");
		collision_result_name->AddChild(guiManager->CreateGuiText(COLLIDED_ENTITY_ID));

		return collision_result_name;
	};
#endif // _DEBUG

	/**
	* @brief 衝突情報
	*/
	CollisionInfo collidedDatas[MAX_COLLISIONS]{};

	/**
	* @brief 衝突エンティティ数
	*/
	uint32_t collisionCount;

	/**
	* @brief 衝突があったか
	*/
	bool isCollided;
};

}// !namespace HaraProject::Framework

#endif // !_COLLISION_RESULT_H_