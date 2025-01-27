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
* @brief 必要なモデルデータの名前を取得
* @param[in] componentDataManager コンポーネントデータマネージャー
*/
std::set<std::string> GetNeedsModelNames(ComponentDataManager* componentDataManager)
{
	// モデルハンドルを含むチャンクを全て取得
	ComponentBits bit = ComponentMask<ModelHandle>::bit;
	std::vector<ComponentDataChunk*> model_chunks = componentDataManager->FindChunks(bit);

	// チャンクが無ければ終了
	if (model_chunks.empty())return std::set<std::string>();

	std::set<std::string> need_model_names;
	for (auto& chunk : model_chunks)
	{
		// チャンク内にある先頭のモデルハンドルコンポーネントを取得
		ModelHandle* model_handle = reinterpret_cast<ModelHandle*>(chunk->CalculateComponentDataPointer(bit, 0));

		uint32_t num_entities = chunk->GetNumEntities();
		for (int i = 0; i < num_entities; ++i)
		{
			if (!model_handle->IsAble() || model_handle == nullptr)
			{
				++model_handle;
				continue;
			}
			// 結果へ追加(重複しない)
			need_model_names.insert(model_handle->modelName);

			// 次へ
			++model_handle;
		}
	}
	return need_model_names;
}

/**
* @brief 必要なテクスチャの名前を取得
* @param[in] componentDataManager コンポーネントデータマネージャー
*/
std::set<std::string> GetNeedsTextureNames(ComponentDataManager* componentDataManager)
{
	// スプライトを含むチャンクを全て取得
	ComponentBits bit = ComponentMask<Sprite>::bit;
	std::vector<ComponentDataChunk*> sprite_chunks = componentDataManager->FindChunks(bit);

	// チャンクが無ければ終了
	if (sprite_chunks.empty())return std::set<std::string>();

	std::set<std::string> need_texture_names;
	for (auto& chunk : sprite_chunks)
	{
		// チャンク内にある先頭のスプライトコンポーネントを取得
		Sprite* sprite = reinterpret_cast<Sprite*>(chunk->CalculateComponentDataPointer(bit, 0));

		uint32_t num_entities = chunk->GetNumEntities();
		for (int i = 0; i < num_entities; ++i)
		{
			if (!sprite->IsAble() || sprite == nullptr)
			{
				++sprite;
				continue;
			}
			// 結果へ追加(重複しない)
			need_texture_names.insert(sprite->textureName);

			// 次へ
			++sprite;
		}
	}
	return need_texture_names;
}

}// namespace HaraProject::Framework