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
* @brief 名前とビットを登録する
* @param[in] name コンポーネント名
* @param[in] bit 識別ビット
*/
void RegisterName(std::string name, ComponentBits bit)
{
    if (!nameToBit.contains(name))
    {
        nameToBit[name] = bit;
    }
}

/**
* @brief コンポーネント名から識別ビットを取得する
* @param[in] name コンポーネント名
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
* @brief 複数のコンポーネント名から複合ビットを取得する
* @param[in] names コンポーネント名のリスト
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
* @brief 配列作成関数を登録する
* @param[in] bit 識別ビット
* @param[in] placementNewArray 配列作成関数
*/
void RegisterPlacementNewArray(ComponentBits bit, std::function<void(void*, size_t)> placementNewArray)
{
    if (!bitToPlacementNewArray.contains(bit))
    {
        bitToPlacementNewArray[bit] = placementNewArray;
    }
}

/**
* @brief 配列作成関数を使用して配列を生成する
* @param[in] bit 識別ビット
* @param[in] buffer 配列を格納するバッファ
* @param[in] size 配列のサイズ
*/
void PlacementNewArray(ComponentBits bit, void* buffer, size_t size)
{
    if (bitToPlacementNewArray.contains(bit))
    {
        bitToPlacementNewArray[bit](buffer, size);
    }
}

/**
* @brief インスタンスコピー関数を登録する
* @param[in] bit 識別ビット
* @param[in] allocateInstance コピー関数
*/
void RegisterAllocateInstance(ComponentBits bit, std::function<void(void*, ComponentDataBase*)> allocateInstance)
{
    if (!bitToAllocateInstance.contains(bit))
    {
        bitToAllocateInstance[bit] = allocateInstance;
    }
}

/**
* @brief コピー関数を使用してインスタンスを生成する
* @param[in] bit 識別ビット
* @param[in] buffer インスタンスを格納するバッファ
* @param[in] component コピー元のコンポーネント
*/
void AllocateInstance(ComponentBits bit, void* buffer, ComponentDataBase* component)
{
    if (bitToAllocateInstance.contains(bit))
    {
        bitToAllocateInstance[bit](buffer, component);
    }
}

/**
* @brief コンポーネントのサイズを登録
* @param[in] bit 識別ビット
* @param[in] size コンポーネントサイズ
*/
void RegisterSize(ComponentBits bit, size_t size)
{
    if (!bitToSize.contains(bit))
    {
        bitToSize[bit] = size;
    }
}

/**
* @brief コンポーネントのサイズを取得
* @param[in] bit 識別ビット
*/
size_t GetSize(ComponentBits bit)
{
    if (bitToSize.contains(bit))
    {
        return bitToSize[bit];
    }
}

/**
* @brief コンストラクタ登録
*/
void RegisterConstructor(ComponentBits bit, std::function<ComponentDataBase* ()> constructor)
{
    if (!bitToConstructor.contains(bit))
    {
        bitToConstructor[bit] = constructor;
    }
}

/**
* @brief コンストラクタ実行
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
* @brief コピーコンストラクタ登録
*/
void RegisterCopyConstructor(ComponentBits bit, std::function<ComponentDataBase* (ComponentDataBase*)> copyConstructor)
{
    if (!bitToCopyConstructor.contains(bit))
    {
        bitToCopyConstructor[bit] = copyConstructor;
    }
}

/**
* @brief コピーコンストラクタ実行
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
* @brief 全コンポーネントデータ各種登録処理
*/
void RegisterAllComponentData()
{
    //------------------------------------------------------------------------------------
    // コンポーネントデータ登録欄
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
