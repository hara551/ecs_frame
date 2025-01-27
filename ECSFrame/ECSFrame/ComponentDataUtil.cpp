#include <string>
#include <vector>
#include <set>

#include "ComponentDataManager.h"
#include "ComponentDataChunk.h"
#include "ComponentMask.h"
#include "Sprite.h"
#include "ModelHandle.h"
#include "ComponentDataUtil.h"

namespace HaraProject::Framework {

/**
* @brief �K�v�ȃ��f���f�[�^�̖��O���擾
* @param[in] componentDataManager �R���|�[�l���g�f�[�^�}�l�[�W���[
*/
std::set<std::string> GetNeedsModelNames(ComponentDataManager* componentDataManager)
{
	// ���f���n���h�����܂ރ`�����N��S�Ď擾
	ComponentBits bit = ComponentMask<ModelHandle>::bit;
	std::vector<ComponentDataChunk*> model_chunks = componentDataManager->FindChunks(bit);

	// �`�����N��������ΏI��
	if (model_chunks.empty())return std::set<std::string>();

	std::set<std::string> need_model_names;
	for (auto& chunk : model_chunks)
	{
		// �`�����N���ɂ���擪�̃��f���n���h���R���|�[�l���g���擾
		ModelHandle* model_handle = reinterpret_cast<ModelHandle*>(chunk->CalculateComponentDataPointer(bit, 0));

		uint32_t num_entities = chunk->GetNumEntities();
		for (int i = 0; i < num_entities; ++i)
		{
			if (!model_handle->IsAble() || model_handle == nullptr)
			{
				++model_handle;
				continue;
			}
			// ���ʂ֒ǉ�(�d�����Ȃ�)
			need_model_names.insert(model_handle->modelName);

			// ����
			++model_handle;
		}
	}
	return need_model_names;
}

/**
* @brief �K�v�ȃe�N�X�`���̖��O���擾
* @param[in] componentDataManager �R���|�[�l���g�f�[�^�}�l�[�W���[
*/
std::set<std::string> GetNeedsTextureNames(ComponentDataManager* componentDataManager)
{
	// �X�v���C�g���܂ރ`�����N��S�Ď擾
	ComponentBits bit = ComponentMask<Sprite>::bit;
	std::vector<ComponentDataChunk*> sprite_chunks = componentDataManager->FindChunks(bit);

	// �`�����N��������ΏI��
	if (sprite_chunks.empty())return std::set<std::string>();

	std::set<std::string> need_texture_names;
	for (auto& chunk : sprite_chunks)
	{
		// �`�����N���ɂ���擪�̃X�v���C�g�R���|�[�l���g���擾
		Sprite* sprite = reinterpret_cast<Sprite*>(chunk->CalculateComponentDataPointer(bit, 0));

		uint32_t num_entities = chunk->GetNumEntities();
		for (int i = 0; i < num_entities; ++i)
		{
			if (!sprite->IsAble() || sprite == nullptr)
			{
				++sprite;
				continue;
			}
			// ���ʂ֒ǉ�(�d�����Ȃ�)
			need_texture_names.insert(sprite->textureName);

			// ����
			++sprite;
		}
	}
	return need_texture_names;
}

}// namespace HaraProject::Framework