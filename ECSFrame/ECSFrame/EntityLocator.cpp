#include "EntityLocator.h"

namespace HaraProject::Framework
{

/**
* @brief �i�[�ʒu�o�^
* @param[in] id �G���e�B�e�BID
* @param[in] chunk �`�����N�ւ̃|�C���^
* @param[in] indexInChunk �`�����N���̃C���f�b�N�X
*/
void EntityLocator::RegisterLocation(uint32_t id, ComponentDataChunk* chunk, uint32_t indexInChunk)
{
	m_id_to_location[id] = EntityLocation{ chunk,indexInChunk };
}

/**
* @brief �i�[�ʒu�o�^
* @param[in] id �G���e�B�e�BID
*/
EntityLocator::EntityLocation EntityLocator::GetLocation(uint32_t id)
{
	if (m_id_to_location.contains(id))
	{
		return m_id_to_location[id];
	}
	return EntityLocation{};
}

}// !namespace HaraProject::Framework