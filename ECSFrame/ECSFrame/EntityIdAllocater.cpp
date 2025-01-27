#include <cstdint>

#include "ComponentMask.h"
#include "EditDataUtil.h"

#include "EntityIdAllocater.h"

namespace HaraProject::Framework {

/**
* @brief �R���X�g���N�^
*/
EntityIdAllocater::EntityIdAllocater()
	: m_next_id(0)
{
}

/**
* @brief �G���e�B�e�BID���󂯂�
* @param[in] id �G���e�B�e�BID
*/
void EntityIdAllocater::FreeUpId(uint32_t id)
{
	// �L���Ƃ���o�[�W�������グ��
	IncreaceValidVersion(id);

	// �t���[ID�Ƃ��Ēǉ�
	m_free_ids.push_back(id);
}

/**
* @brief �g����ID�����蓖�Ă�
*/
EntityIdAllocater::EntityHandle EntityIdAllocater::AssignUsableId()
{
	EntityHandle entity_handle{};
	// ��ID������΍ė��p
	if (!m_free_ids.empty())
	{
		entity_handle.id = m_free_ids.front();
		m_free_ids.erase(m_free_ids.begin());

		entity_handle.version = m_latest_versions[entity_handle.id];
		return entity_handle;
	}

	// ������ΐV�������s
	return IssueNewId();
}

/**
* @brief �V����ID�𔭍s����
*/
EntityIdAllocater::EntityHandle EntityIdAllocater::IssueNewId()
{
	// �V����ID���쐬
	EntityHandle entity_handle{ m_next_id, 0 };
	// �o�[�W�������X�g�ɒǉ�
	m_latest_versions.push_back(0);

	++m_next_id;

	return entity_handle;
}

/**
* @brief ID���L����
* @param[in] id �G���e�B�e�BID
* @param[in] version �o�[�W����
*/
bool EntityIdAllocater::IsValidId(uint32_t id, uint32_t version)
{
	return m_latest_versions[id] == version;
}

/**
* @brief �L���Ƃ���o�[�W�������グ��
* @param[in] �G���e�B�e�BID
*/
uint32_t EntityIdAllocater::IncreaceValidVersion(uint32_t id)
{
	if (m_latest_versions.size() - 1 >= id)
	{
		return ++m_latest_versions[id];
	}
	return 0;
}

}// !namespace HaraProject::Framework