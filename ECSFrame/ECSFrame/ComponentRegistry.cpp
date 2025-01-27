#include <string>
#include <unordered_map>
#include <vector>

#include "ComponentMask.h"
#include "ComponentRegistry.h"
#include "ComponentDataBase.h"

#include "Transform.h"
#include "EntityName.h"
#include "Sprite.h"
#include "ModelHandle.h"
#include "CollisionBox.h"
#include "Velocity.h"
#include "CollisionResult.h"
#include "GeometrySolid.h"
#include "CollisionCircle2D.h"

namespace HaraProject::Framework {

namespace ComponentRegistry {

/**
* @brief ���O�ƃr�b�g��o�^����
* @param[in] name �R���|�[�l���g��
* @param[in] bit ���ʃr�b�g
*/
void RegisterName(std::string name, ComponentBits bit)
{
    if (!nameToBit.contains(name))
    {
        nameToBit[name] = bit;
    }
}

/**
* @brief �R���|�[�l���g�����环�ʃr�b�g���擾����
* @param[in] name �R���|�[�l���g��
*/
ComponentBits GetBitByName(std::string name)
{
    if (nameToBit.contains(name))
    {
        return nameToBit[name];
    }
    return ComponentBits(0);
}

/**
* @brief �����̃R���|�[�l���g�����畡���r�b�g���擾����
* @param[in] names �R���|�[�l���g���̃��X�g
*/
ComponentBits GetConbinedMaskByNames(std::vector<std::string> names)
{
    ComponentBits mask{};
    for (std::string& name : names)
    {
        mask |= GetBitByName(name);
    }
    return mask;
}

/**
* @brief �z��쐬�֐���o�^����
* @param[in] bit ���ʃr�b�g
* @param[in] placementNewArray �z��쐬�֐�
*/
void RegisterPlacementNewArray(ComponentBits bit, std::function<void(void*, size_t)> placementNewArray)
{
    if (!bitToPlacementNewArray.contains(bit))
    {
        bitToPlacementNewArray[bit] = placementNewArray;
    }
}

/**
* @brief �z��쐬�֐����g�p���Ĕz��𐶐�����
* @param[in] bit ���ʃr�b�g
* @param[in] buffer �z����i�[����o�b�t�@
* @param[in] size �z��̃T�C�Y
*/
void PlacementNewArray(ComponentBits bit, void* buffer, size_t size)
{
    if (bitToPlacementNewArray.contains(bit))
    {
        bitToPlacementNewArray[bit](buffer, size);
    }
}

/**
* @brief �C���X�^���X�R�s�[�֐���o�^����
* @param[in] bit ���ʃr�b�g
* @param[in] allocateInstance �R�s�[�֐�
*/
void RegisterAllocateInstance(ComponentBits bit, std::function<void(void*, ComponentDataBase*)> allocateInstance)
{
    if (!bitToAllocateInstance.contains(bit))
    {
        bitToAllocateInstance[bit] = allocateInstance;
    }
}

/**
* @brief �R�s�[�֐����g�p���ăC���X�^���X�𐶐�����
* @param[in] bit ���ʃr�b�g
* @param[in] buffer �C���X�^���X���i�[����o�b�t�@
* @param[in] component �R�s�[���̃R���|�[�l���g
*/
void AllocateInstance(ComponentBits bit, void* buffer, ComponentDataBase* component)
{
    if (bitToAllocateInstance.contains(bit))
    {
        bitToAllocateInstance[bit](buffer, component);
    }
}

/**
* @brief �R���|�[�l���g�̃T�C�Y��o�^
* @param[in] bit ���ʃr�b�g
* @param[in] size �R���|�[�l���g�T�C�Y
*/
void RegisterSize(ComponentBits bit, size_t size)
{
    if (!bitToSize.contains(bit))
    {
        bitToSize[bit] = size;
    }
}

/**
* @brief �R���|�[�l���g�̃T�C�Y���擾
* @param[in] bit ���ʃr�b�g
*/
size_t GetSize(ComponentBits bit)
{
    if (bitToSize.contains(bit))
    {
        return bitToSize[bit];
    }
}

/**
* @brief �R���X�g���N�^�o�^
*/
void RegisterConstructor(ComponentBits bit, std::function<ComponentDataBase* ()> constructor)
{
    if (!bitToConstructor.contains(bit))
    {
        bitToConstructor[bit] = constructor;
    }
}

/**
* @brief �R���X�g���N�^���s
*/
ComponentDataBase* Constructor(ComponentBits bit)
{
    if (bitToConstructor.contains(bit))
    {
        return bitToConstructor[bit]();
    }
    return nullptr;
}

/**
* @brief �R�s�[�R���X�g���N�^�o�^
*/
void RegisterCopyConstructor(ComponentBits bit, std::function<ComponentDataBase* (ComponentDataBase*)> copyConstructor)
{
    if (!bitToCopyConstructor.contains(bit))
    {
        bitToCopyConstructor[bit] = copyConstructor;
    }
}

/**
* @brief �R�s�[�R���X�g���N�^���s
*/
ComponentDataBase* CopyConstructor(ComponentBits bit, ComponentDataBase* original)
{
    if (bitToCopyConstructor.contains(bit))
    {
        return bitToCopyConstructor[bit](original);
    }
    return nullptr;
}


/**
* @brief �S�R���|�[�l���g�f�[�^�e��o�^����
*/
void RegisterAllComponentData()
{
    //------------------------------------------------------------------------------------
    // �R���|�[�l���g�f�[�^�o�^��
    //------------------------------------------------------------------------------------
    RegisterComponentData<Transform>(Transform::TRANSFORM_NAME);
    RegisterComponentData<EntityName>(EntityName::ENTITY_NAME_NAME);
    RegisterComponentData<Sprite>(Sprite::SPRITE_NAME);
    RegisterComponentData<ModelHandle>(ModelHandle::MODEL_HANDLE_NAME);
    RegisterComponentData<CollisionBox>(CollisionBox::COLLISION_BOX_NAME);
    RegisterComponentData<Velocity>(Velocity::VELOCITY_NAME);
    RegisterComponentData<CollisionResult>(CollisionResult::COLLISION_RESULT_NAME);
    RegisterComponentData<GeometrySolid>(GeometrySolid::GEOMETRY_SOLID_NAME);
    RegisterComponentData<CollisionCircle2D>(CollisionCircle2D::COLLISION_CIRCLE_2D_NAME);
    //------------------------------------------------------------------------------------
}

} // namespace ComponentRegistry

} // namespace HaraProject::Framework
