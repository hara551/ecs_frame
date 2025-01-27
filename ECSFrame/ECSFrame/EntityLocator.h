/**
* @file   EntityLocator.h
* @brief  �G���e�B�e�B�i�[�ʒu�Ǘ�
* @author Hara Sota.
* @date   2024/10/14.
*/
#ifndef _ENTITY_LOCATOR_H_
#define _ENTITY_LOCATOR_H_

#include <cstdint>
#include <unordered_map>

#include "ComponentDataChunk.h"

namespace HaraProject::Framework
{

/**
* @brief �G���e�B�e�B�i�[�ʒu�Ǘ�
*/
class EntityLocator
{
public:
	/**
	* @brief �G���e�B�e�B�̊i�[�ʒu
	*/
	struct EntityLocation
	{
		/**
		* @brief �i�[����Ă���`�����N�ւ̃|�C���^
		*/
		ComponentDataChunk* chunk;

		/**
		* @brief �`�����N���ł̃C���f�b�N�X
		*/
		uint32_t indexInChunk;
	};

	/**
	* @brief �i�[�ʒu�o�^
	* @param[in] id �G���e�B�e�BID
	* @param[in] chunk �`�����N�ւ̃|�C���^
	* @param[in] indexInChunk �`�����N���̃C���f�b�N�X
	*/
	void RegisterLocation(uint32_t id, ComponentDataChunk* chunk, uint32_t indexInChunk);

	/**
	* @brief �i�[�ʒu�o�^
	* @param[in] id �G���e�B�e�BID
	*/
	EntityLocation GetLocation(uint32_t id);

private:
	/**
	* @brief �G���e�B�e�BID�Ɗi�[�ʒu�̃}�b�v
	*/
	std::unordered_map<uint32_t, EntityLocation> m_id_to_location;
};

}// !namespace HaraProject::Framework

#endif // !_ENTITY_LOCATOR_H_
