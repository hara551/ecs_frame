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
* @brief �R���X�g���N�^
* @param[in] editorManager �G�f�B�^�[�}�l�[�W���[
*/
SubsceneManager::SubsceneManager(EditorManager* editorManager)
	: m_editor_manager(editorManager)
{
}

/**
* @brief �V�����T�u�V�[����ǉ�
* @param[in] subsceneName �T�u�V�[����
* @param[in] transform �g�����X�t�H�[��
* @param[in] entities �������Ă���G���e�B�e�BID
*/
void SubsceneManager::AddSubscene(std::string subsceneName, Transform transform, std::vector<uint32_t> entities)
{
	// �d�����Ȃ����O�ɒ���
	std::string unique_subscene_name = ConvertToUniqueSubsceneName(subsceneName);

	m_name_to_subsceneData.emplace(unique_subscene_name, SubsceneData(transform, entities));
	m_name_to_old_transform.emplace(unique_subscene_name, transform);
}

/**
* @brief �T�u�V�[���ɃG���e�B�e�B��ǉ�
* @param[in] subsceneName �T�u�V�[����
* @param[in] entityId �G���e�B�e�BID
*/
void SubsceneManager::AddEntityToSubscene(std::string subsceneName, uint32_t entityId)
{
	if (m_name_to_subsceneData.contains(subsceneName))
	{
		m_name_to_subsceneData[subsceneName].entities.push_back(entityId);
	}
}

/**
* @brief �T�u�V�[�����폜
* @param[in] subsceneName �T�u�V�[����
*/
void SubsceneManager::DeleteSubscene(std::string subsceneName)
{
	if (!m_name_to_subsceneData.contains(subsceneName))return;

	EntityManager* entity_manager = m_editor_manager->GetEntityManager();

	// �w��T�u�V�[�����̑S�G���e�B�e�B���폜
	for (const auto& entity : m_name_to_subsceneData[subsceneName].entities)
	{
		entity_manager->DeleteEntity(entity);
	}

	// �T�u�V�[�����폜
	std::erase_if(m_name_to_subsceneData, [subsceneName](auto& itr){ return itr.first == subsceneName; });
	std::erase_if(m_name_to_old_transform, [subsceneName](auto& itr) { return itr.first == subsceneName; });
}

/**
* @brief �T�u�V�[������ύX
* @param[in] subsceneName �ύX�������T�u�V�[���̖��O
* @param[in] newName �V�������O
*/
void SubsceneManager::RenameSubscene(std::string subsceneName, std::string newName)
{
	// �w�肵���T�u�V�[�������݂��Ȃ���ΏI��
	if (!m_name_to_subsceneData.contains(subsceneName))return;

	newName = ConvertToUniqueSubsceneName(newName);

	// ���̖��O�̒l��V�������O�̒l�ɃR�s�[����
	m_name_to_subsceneData[newName] = m_name_to_subsceneData[subsceneName];
	m_name_to_old_transform[newName] = m_name_to_old_transform[subsceneName];

	// ���̖��O�̗v�f���폜
	std::erase_if(m_name_to_subsceneData, [&](auto& itr) {return itr.first == subsceneName; });
	std::erase_if(m_name_to_old_transform, [&](auto& itr) {return itr.first == subsceneName; });
}
/**
* @brief �T�u�V�[���S�̂̈ړ����X�V
*/
void SubsceneManager::UpdateSubScenesTransform()
{
	EntityManager* entity_manager = m_editor_manager->GetEntityManager();

	for (const auto& [subscene_name, subscene_data] : m_name_to_subsceneData)
	{
		// �T�u�V�[���̃g�����X�t�H�[�����ύX����Ă���΍X�V���s��
		if (m_name_to_old_transform[subscene_name] != subscene_data.transform)
		{
			Transform old_transform = m_name_to_old_transform[subscene_name];
			Transform current_transform = subscene_data.transform;

			// �O��̃g�����X�t�H�[���Ƃ̍���
			DirectX::XMFLOAT3 position_diff = MathUtil::SubtractFloat3(current_transform.position, old_transform.position);
			DirectX::XMFLOAT3 rotation_diff = MathUtil::SubtractFloat3(current_transform.rotation, old_transform.rotation);
			DirectX::XMFLOAT3 scale_diff = MathUtil::SubtractFloat3(current_transform.scale, old_transform.scale);

			// �T�u�V�[���̉�]�s����쐬
			DirectX::XMMATRIX subscene_rotation_matrix =
				DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(rotation_diff.x)) *
				DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(rotation_diff.y)) *
				DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(rotation_diff.z));

			for (const auto& entity : subscene_data.entities)
			{
				Transform* entity_transform = reinterpret_cast<Transform*>(
					entity_manager->GetComponentData(entity, ComponentMask<Transform>::bit));

				// �T�u�V�[���̈ړ����G���e�B�e�B�ɓK�p
				DirectX::XMFLOAT3 local_position = MathUtil::SubtractFloat3(entity_transform->position, old_transform.position);
				DirectX::XMVECTOR local_position_vector = DirectX::XMLoadFloat3(&local_position);
				local_position_vector = DirectX::XMVector3Transform(local_position_vector, subscene_rotation_matrix);
				DirectX::XMStoreFloat3(&local_position, local_position_vector);

				entity_transform->position = MathUtil::AddFloat3(local_position, current_transform.position);

				// ��]�𔽉f
				entity_transform->rotation.x += rotation_diff.x;
				entity_transform->rotation.y += rotation_diff.y;
				entity_transform->rotation.z += rotation_diff.z;

				// �X�P�[���𔽉f
				entity_transform->scale.x *= (1.0f + scale_diff.x);
				entity_transform->scale.y *= (1.0f + scale_diff.y);
				entity_transform->scale.z *= (1.0f + scale_diff.z);
			}

			// ����̃g�����X�t�H�[����ۑ�
			m_name_to_old_transform[subscene_name] = current_transform;
		}
	}
}




/**
* @brief �T�u�V�[������G���e�B�e�B���폜
*/
void SubsceneManager::RemoveEntityFromSubscene(uint32_t entityId)
{
	// �G���e�B�e�B����������T�u�V�[�������
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

	// �T�u�V�[������G���e�B�e�B���폜
	std::erase_if(m_name_to_subsceneData[subscene_name].entities, [entityId](uint32_t id) {return id == entityId; });
}

/**
* @brief �ێ����Ă���T�u�V�[����S�Ĕp��
*/
void SubsceneManager::CleanUpSubscenes()
{
	m_name_to_subsceneData.clear();
	m_name_to_old_transform.clear();
}

/**
* @brief �T�u�V�[���̃g�����X�t�H�[�����Q�ƂŎ擾
* @param[in] subsceneName �T�u�V�[����
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
* @brief �T�u�V�[�����Ƃ̃G���e�B�e�B���擾
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
* @brief ���Ȃ��T�u�V�[�����ɕϊ�
* @param[in] subsceneName �T�u�V�[����
*/
std::string SubsceneManager::ConvertToUniqueSubsceneName(std::string subsceneName)
{
	// �T�u�V�[�������d�����Ă�����
	if (m_name_to_subsceneData.contains(subsceneName))
	{
		// �����ɐ����������Ȃ����O�ɕύX
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