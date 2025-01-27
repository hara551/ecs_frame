#ifdef _DEBUG
#include <DirectXMath.h>
#include <cmath>

#include "SubsceneManager.h"
#include "MathUtil.h"
#include "EntityManager.h"
#include "EditorManager.h"
#include "ComponentMask.h"
#include "Transform.h"

namespace HaraProject::Framework {

/**
* @brief コンストラクタ
* @param[in] editorManager エディターマネージャー
*/
SubsceneManager::SubsceneManager(EditorManager* editorManager)
	: m_editor_manager(editorManager)
{
}

/**
* @brief 新しいサブシーンを追加
* @param[in] subsceneName サブシーン名
* @param[in] transform トランスフォーム
* @param[in] entities 所属しているエンティティID
*/
void SubsceneManager::AddSubscene(std::string subsceneName, Transform transform, std::vector<uint32_t> entities)
{
	// 重複しない名前に調整
	std::string unique_subscene_name = ConvertToUniqueSubsceneName(subsceneName);

	m_name_to_subsceneData.emplace(unique_subscene_name, SubsceneData(transform, entities));
	m_name_to_old_transform.emplace(unique_subscene_name, transform);
}

/**
* @brief サブシーンにエンティティを追加
* @param[in] subsceneName サブシーン名
* @param[in] entityId エンティティID
*/
void SubsceneManager::AddEntityToSubscene(std::string subsceneName, uint32_t entityId)
{
	if (m_name_to_subsceneData.contains(subsceneName))
	{
		m_name_to_subsceneData[subsceneName].entities.push_back(entityId);
	}
}

/**
* @brief サブシーンを削除
* @param[in] subsceneName サブシーン名
*/
void SubsceneManager::DeleteSubscene(std::string subsceneName)
{
	if (!m_name_to_subsceneData.contains(subsceneName))return;

	EntityManager* entity_manager = m_editor_manager->GetEntityManager();

	// 指定サブシーン内の全エンティティを削除
	for (const auto& entity : m_name_to_subsceneData[subsceneName].entities)
	{
		entity_manager->DeleteEntity(entity);
	}

	// サブシーンを削除
	std::erase_if(m_name_to_subsceneData, [subsceneName](auto& itr){ return itr.first == subsceneName; });
	std::erase_if(m_name_to_old_transform, [subsceneName](auto& itr) { return itr.first == subsceneName; });
}

/**
* @brief サブシーン名を変更
* @param[in] subsceneName 変更したいサブシーンの名前
* @param[in] newName 新しい名前
*/
void SubsceneManager::RenameSubscene(std::string subsceneName, std::string newName)
{
	// 指定したサブシーンが存在しなければ終了
	if (!m_name_to_subsceneData.contains(subsceneName))return;

	newName = ConvertToUniqueSubsceneName(newName);

	// 元の名前の値を新しい名前の値にコピーする
	m_name_to_subsceneData[newName] = m_name_to_subsceneData[subsceneName];
	m_name_to_old_transform[newName] = m_name_to_old_transform[subsceneName];

	// 元の名前の要素を削除
	std::erase_if(m_name_to_subsceneData, [&](auto& itr) {return itr.first == subsceneName; });
	std::erase_if(m_name_to_old_transform, [&](auto& itr) {return itr.first == subsceneName; });
}
/**
* @brief サブシーン全体の移動を更新
*/
void SubsceneManager::UpdateSubScenesTransform()
{
	EntityManager* entity_manager = m_editor_manager->GetEntityManager();

	for (const auto& [subscene_name, subscene_data] : m_name_to_subsceneData)
	{
		// サブシーンのトランスフォームが変更されていれば更新を行う
		if (m_name_to_old_transform[subscene_name] != subscene_data.transform)
		{
			Transform old_transform = m_name_to_old_transform[subscene_name];
			Transform current_transform = subscene_data.transform;

			// 前回のトランスフォームとの差分
			DirectX::XMFLOAT3 position_diff = MathUtil::SubtractFloat3(current_transform.position, old_transform.position);
			DirectX::XMFLOAT3 rotation_diff = MathUtil::SubtractFloat3(current_transform.rotation, old_transform.rotation);
			DirectX::XMFLOAT3 scale_diff = MathUtil::SubtractFloat3(current_transform.scale, old_transform.scale);

			// サブシーンの回転行列を作成
			DirectX::XMMATRIX subscene_rotation_matrix =
				DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(rotation_diff.x)) *
				DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(rotation_diff.y)) *
				DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(rotation_diff.z));

			for (const auto& entity : subscene_data.entities)
			{
				Transform* entity_transform = reinterpret_cast<Transform*>(
					entity_manager->GetComponentData(entity, ComponentMask<Transform>::bit));

				// サブシーンの移動をエンティティに適用
				DirectX::XMFLOAT3 local_position = MathUtil::SubtractFloat3(entity_transform->position, old_transform.position);
				DirectX::XMVECTOR local_position_vector = DirectX::XMLoadFloat3(&local_position);
				local_position_vector = DirectX::XMVector3Transform(local_position_vector, subscene_rotation_matrix);
				DirectX::XMStoreFloat3(&local_position, local_position_vector);

				entity_transform->position = MathUtil::AddFloat3(local_position, current_transform.position);

				// 回転を反映
				entity_transform->rotation.x += rotation_diff.x;
				entity_transform->rotation.y += rotation_diff.y;
				entity_transform->rotation.z += rotation_diff.z;

				// スケールを反映
				entity_transform->scale.x *= (1.0f + scale_diff.x);
				entity_transform->scale.y *= (1.0f + scale_diff.y);
				entity_transform->scale.z *= (1.0f + scale_diff.z);
			}

			// 今回のトランスフォームを保存
			m_name_to_old_transform[subscene_name] = current_transform;
		}
	}
}




/**
* @brief サブシーンからエンティティを削除
*/
void SubsceneManager::RemoveEntityFromSubscene(uint32_t entityId)
{
	// エンティティが所属するサブシーンを特定
	std::string subscene_name{};
	for (auto& [name, subscene_data] : m_name_to_subsceneData)
	{
		for (const auto& id : subscene_data.entities)
		{
			if (id == entityId)
			{
				subscene_name = name;
			}
		}
	}

	// サブシーンからエンティティを削除
	std::erase_if(m_name_to_subsceneData[subscene_name].entities, [entityId](uint32_t id) {return id == entityId; });
}

/**
* @brief 保持しているサブシーンを全て廃棄
*/
void SubsceneManager::CleanUpSubscenes()
{
	m_name_to_subsceneData.clear();
	m_name_to_old_transform.clear();
}

/**
* @brief サブシーンのトランスフォームを参照で取得
* @param[in] subsceneName サブシーン名
*/
Transform& SubsceneManager::GetSubscenesTransform(std::string subsceneName)
{
	if (m_name_to_subsceneData.contains(subsceneName))
	{
		return m_name_to_subsceneData[subsceneName].transform;
	}
	Transform dummy{};
	return dummy;
}

/**
* @brief サブシーンごとのエンティティを取得
*/
std::unordered_map<std::string, std::vector<uint32_t>> SubsceneManager::GetEntitiesBySubscene()
{
	std::unordered_map<std::string, std::vector<uint32_t>> entities_by_subscene{};
	for (const auto& [subscene_name, subscene_data] : m_name_to_subsceneData)
	{
		entities_by_subscene[subscene_name] = subscene_data.entities;
	}
	return entities_by_subscene;
}

/**
* @brief 被らないサブシーン名に変換
* @param[in] subsceneName サブシーン名
*/
std::string SubsceneManager::ConvertToUniqueSubsceneName(std::string subsceneName)
{
	// サブシーン名が重複していたら
	if (m_name_to_subsceneData.contains(subsceneName))
	{
		// 末尾に数字をつけ被らない名前に変更
		int num = 1;
		while (m_name_to_subsceneData.contains(subsceneName + std::to_string(num)))
		{
			++num;
		}
		subsceneName = subsceneName + std::to_string(num);
	}
	return subsceneName;
}

}// !namespace HaraProject::Framework
#endif // _DEBUG