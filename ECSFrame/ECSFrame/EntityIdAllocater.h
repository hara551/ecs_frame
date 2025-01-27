/**
* @file   EntityIdAllocater.h
* @brief  �G���e�B�e�BID�Ǘ��N���X��`.
* @author Hara Sota.
* @date   2024/10/14.
*/
#ifndef _ENTITY_ID_ALLOCATER_H_
#define _ENTITY_ID_ALLOCATER_H_

#include <cstdint>
#include <vector>

namespace HaraProject::Framework
{

/**
* @brief �G���e�B�e�BID���蓖��
*/
class EntityIdAllocater
{
public:
	/**
	* @brief �G���e�B�e�B���ʏ��
	*/
	struct EntityHandle
	{
		/**
		* @brief �G���e�B�e�BID
		*/
		uint32_t id;

		/**
		* @brief �o�[�W����
		*/
		uint32_t version;
	};

	/**
	* @brief �R���X�g���N�^
	*/
	EntityIdAllocater();

	/**
	* @brief �G���e�B�e�BID���󂯂�
	* @param[in] id �G���e�B�e�BID
	*/
	void FreeUpId(uint32_t id);

	/**
	* @brief �g����ID�����蓖�Ă�
	*/
	EntityHandle AssignUsableId();

	/**
	* @brief �V����ID�𔭍s����
	*/
	EntityHandle IssueNewId();

	/**
	* @brief ID���L����
	* @param[in] id �G���e�B�e�BID
	* @param[in] version �o�[�W����
	*/
	bool IsValidId(uint32_t id, uint32_t version);

	/**
	* @brief �L���Ƃ���o�[�W�������グ��
	* @param[in] �G���e�B�e�BID
	*/
	uint32_t IncreaceValidVersion(uint32_t id);

	/**
	* @brief ���Ɋ��蓖�Ă�ID
	*/
	uint32_t m_next_id;

	/**
	* @brief �G���e�B�e�B�̍ŐV�o�[�W����
	* @attention �C���f�b�N�X��ID�Ƃ����Ƃ��̃o�[�W����
	*/
	std::vector<uint32_t> m_latest_versions;

	/**
	* @brief ��ID���X�g
	*/
	std::vector<uint32_t>m_free_ids;
};

}// !namespace HaraProject::Framework

#endif // !_ENTITY_ID_ALLOCATER_H_
