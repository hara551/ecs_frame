/**
* @file   IChunkProvider.h
* @brief  �`�����N�擾����C���^�[�t�F�[�X.
* @author Hara Sota.
* @date   2024/10/14.
*/
#ifndef _ICHUNK_PROVIDER_H_
#define _ICHUNK_PROVIDER_H_

#include <cstdint>
#include <vector>

#include "ComponentMask.h"
#include "ComponentDataChunk.h"

namespace HaraProject::Framework
{

/**
* @brief�@�R���|�[�l���g�f�[�^����C���^�[�t�F�[�X
*/
class IChunkProvider
{
public:
	/**
	* @brief �f�X�g���N�^
	*/
	virtual ~IChunkProvider() = default;

	/**
	* @brief �w��̑g�̃R���|�[�l���g�f�[�^����舵���`�����N���擾
	*/
	virtual std::vector<ComponentDataChunk*> FindChunks(ComponentBits mask) = 0;
};

}// !namespace HaraProject::Framework

#endif // !_ICHUNK_PROVIDER_H_