#include <vector>

#include "MovementSystem.h"
#include "SystemBase.h"
#include "Transform.h"
#include "Velocity.h"
#include "ComponentDataChunk.h"
#include "ComponentMask.h"
#include "MathUtil.h"

namespace HaraProject::Framework {


MovementSystem::MovementSystem(IEntityOperator* entityOperator, ISystemDistributor* systemDistributor, IChunkProvider* chunkProvider)
	: SystemBase(entityOperator, systemDistributor, chunkProvider)
{
}

void MovementSystem::UpdateSystem(float deltaTime)
{
	// トランスフォームと速度を持つチャンクを全て取得
	std::vector<ComponentDataChunk*> chunks = FindChunks<Transform, Velocity>();
	if (chunks.empty())return;

	for (auto& chunk : chunks)
	{
		Transform* transform = reinterpret_cast<Transform*>(chunk->CalculateComponentDataPointer(ComponentMask<Transform>::bit, 0));
		Velocity* velocity = reinterpret_cast<Velocity*>(chunk->CalculateComponentDataPointer(ComponentMask<Velocity>::bit, 0));
		
		uint32_t num_entities = chunk->GetNumEntities();
		for (int i = 0; i < num_entities; ++i)
		{
			if (transform->IsAble() && transform != nullptr)
			{
				transform->position = MathUtil::AddFloat3(transform->position,
					MathUtil::ScalingFloat3(velocity->linearVelocity, deltaTime)
				);

				transform->rotation = MathUtil::AddFloat3(transform->rotation, 
					MathUtil::ScalingFloat3(velocity->angularVelocity, deltaTime)
				);
			}

			++transform;
			++velocity;
		}
	}
}

}//!namespace HaraProject::Framework
