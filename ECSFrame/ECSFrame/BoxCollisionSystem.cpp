#include <vector>
#include <tuple>

#include "SystemBase.h"
#include "ComponentMask.h"
#include "ComponentDataChunk.h"
#include "DirectX.h"
#include "IEntityOperator.h"
#include "ISystemDistributor.h"
#include "IChunkProvider.h"
#include "BoxCollisionSystem.h"
#include "CollisionBox.h"
#include "CollisionBase.h"
#include "Transform.h"
#include "CollisionResult.h"
#include "MathUtil.h"

namespace HaraProject::Framework {

/**
* @brief �R���X�g���N�^
*/
HaraProject::Framework::BoxCollisionSystem::BoxCollisionSystem(IEntityOperator* entityOperator, ISystemDistributor* systemDistributor, IChunkProvider* chunkProvider)
	:SystemBase(entityOperator, systemDistributor, chunkProvider) {}

/**
* @brief �V�X�e���X�V
*/
void BoxCollisionSystem::UpdateSystem(float deltaTime)
{
	std::vector<ComponentDataChunk*> chunks = FindChunks<Transform, CollisionBox, CollisionResult>();
	if (chunks.empty())return;

	std::vector<std::tuple<uint32_t, CollisionBox*, Transform*, CollisionResult*, bool>> entities{};
	int i = 0;
	// �ΏۃG���e�B�e�B��z��ɂ܂Ƃ߂�
	for (auto& chunk : chunks)
	{
		CollisionBox* collision_box = reinterpret_cast<CollisionBox*>(chunk->CalculateComponentDataPointer(ComponentMask<CollisionBox>::bit, 0));
		Transform* transform = reinterpret_cast<Transform*>(chunk->CalculateComponentDataPointer(ComponentMask<Transform>::bit, 0));
		CollisionResult* collision_result = reinterpret_cast<CollisionResult*>(chunk->CalculateComponentDataPointer(ComponentMask<CollisionResult>::bit, 0));
		
		int32_t num_entities_a = chunk->GetNumEntities();
		for (int i = 0; i < num_entities_a; ++i)
		{
			if (transform->IsAble() && transform != nullptr)
			{
				entities.emplace_back(chunk->GetIdByIndex(i), collision_box, transform, collision_result, false);
			}
			++collision_box;
			++transform;
			++collision_result;
		}
	}

	// �����蔻��
	for (int i = 0; i < entities.size(); ++i)
	{
		auto& [id_a, box_a, transform_a, result_a, is_collided_a] = entities[i];
		for (int j = i + 1; j < entities.size(); ++j)
		{
			auto& [id_b, box_b, transform_b, result_b, is_collided_b] = entities[j];

			if (CheckcollisionOBB(box_a, transform_a, box_b, transform_b))
			{
				result_a->AddCollidedEntity(id_b, DirectX::XMFLOAT3(), DirectX::XMFLOAT3());
				result_b->AddCollidedEntity(id_a, DirectX::XMFLOAT3(), DirectX::XMFLOAT3());
				is_collided_a = true;
				is_collided_b = true;
			}
		}
	}

	// �Փ˂̖����������̂����Z�b�g
	for (auto& [id, box, transform, result, is_collided] : entities)
	{
		if (!is_collided)
		{
			result->Clear();
		}
	}
}

/**
* @brief AABB�Փ˔���
*/
bool BoxCollisionSystem::CheckCollisionAABB(CollisionBox* collisionBoxA, Transform* transformA, CollisionBox* collisionBoxB, Transform* transformB)
{
	// AABB�̍ŏ��_�ƍő�_���v�Z
	DirectX::XMFLOAT3 half_size_a = MathUtil::ScalingFloat3(MathUtil::MultiplyFloat3(collisionBoxA->size, transformA->scale), 0.5f);
	DirectX::XMFLOAT3 half_size_b = MathUtil::ScalingFloat3(MathUtil::MultiplyFloat3(collisionBoxB->size, transformB->scale), 0.5f);

	DirectX::XMFLOAT3 min_a = MathUtil::SubtractFloat3(MathUtil::AddFloat3(transformA->position, collisionBoxA->center), half_size_a);
	DirectX::XMFLOAT3 max_a = MathUtil::AddFloat3(MathUtil::AddFloat3(transformA->position, collisionBoxA->center), half_size_a);

	DirectX::XMFLOAT3 min_b = MathUtil::SubtractFloat3(MathUtil::AddFloat3(transformB->position, collisionBoxB->center), half_size_b);
	DirectX::XMFLOAT3 max_b = MathUtil::AddFloat3(MathUtil::AddFloat3(transformB->position, collisionBoxB->center), half_size_b);

	// �Փ˔���
	return !(max_a.x <= min_b.x || min_a.x >= max_b.x ||
		max_a.y <= min_b.y || min_a.y >= max_b.y ||
		max_a.z <= min_b.z || min_a.z >= max_b.z);
}

/**
* @brief OBB�Փ˔���
*/
bool BoxCollisionSystem::CheckcollisionOBB(CollisionBox* collisionBoxA, Transform* transformA, CollisionBox* collisionBoxB, Transform* transformB)
{
	// ���[���h�}�g���b�N�X�擾
	DirectX::XMFLOAT4X4 worldMatrixA = transformA->CaluculateWorldMatrix();
	DirectX::XMFLOAT4X4 worldMatrixB = transformB->CaluculateWorldMatrix();
	DirectX::XMMATRIX matrixA = DirectX::XMLoadFloat4x4(&worldMatrixA);
	DirectX::XMMATRIX matrixB = DirectX::XMLoadFloat4x4(&worldMatrixB);

	// ���S���W���v�Z
	DirectX::XMVECTOR centerA = DirectX::XMVector3TransformCoord(DirectX::XMLoadFloat3(&collisionBoxA->center), matrixA);
	DirectX::XMVECTOR centerB = DirectX::XMVector3TransformCoord(DirectX::XMLoadFloat3(&collisionBoxB->center), matrixB);

	// ���a�i�T�C�Y�̔����j���v�Z
	DirectX::XMFLOAT3 halfSizeA = MathUtil::ScalingFloat3(MathUtil::MultiplyFloat3(collisionBoxA->size,transformA->scale), 0.5f);
	DirectX::XMFLOAT3 halfSizeB = MathUtil::ScalingFloat3(MathUtil::MultiplyFloat3(collisionBoxB->size,transformB->scale), 0.5f);

	// ���[�J�����x�N�g�����擾
	DirectX::XMVECTOR axesA[3] = {
		DirectX::XMVector3Normalize(DirectX::XMVectorSet(worldMatrixA._11, worldMatrixA._12, worldMatrixA._13, 0.0f)),
		DirectX::XMVector3Normalize(DirectX::XMVectorSet(worldMatrixA._21, worldMatrixA._22, worldMatrixA._23, 0.0f)),
		DirectX::XMVector3Normalize(DirectX::XMVectorSet(worldMatrixA._31, worldMatrixA._32, worldMatrixA._33, 0.0f))
	};
	DirectX::XMVECTOR axesB[3] = {
		DirectX::XMVector3Normalize(DirectX::XMVectorSet(worldMatrixB._11, worldMatrixB._12, worldMatrixB._13, 0.0f)),
		DirectX::XMVector3Normalize(DirectX::XMVectorSet(worldMatrixB._21, worldMatrixB._22, worldMatrixB._23, 0.0f)),
		DirectX::XMVector3Normalize(DirectX::XMVectorSet(worldMatrixB._31, worldMatrixB._32, worldMatrixB._33, 0.0f))
	};

	// ���S�ԋ����x�N�g��
	DirectX::XMVECTOR d = DirectX::XMVectorSubtract(centerB, centerA);

	// �������e�X�g
	for (int i = 0; i < 3; ++i)
	{
		// �� A[i]
		float rA = halfSizeA.x * fabsf(DirectX::XMVectorGetX(DirectX::XMVector3Dot(axesA[0], axesA[i]))) +
			halfSizeA.y * fabsf(DirectX::XMVectorGetX(DirectX::XMVector3Dot(axesA[1], axesA[i]))) +
			halfSizeA.z * fabsf(DirectX::XMVectorGetX(DirectX::XMVector3Dot(axesA[2], axesA[i])));

		float rB = halfSizeB.x * fabsf(DirectX::XMVectorGetX(DirectX::XMVector3Dot(axesB[0], axesA[i]))) +
			halfSizeB.y * fabsf(DirectX::XMVectorGetX(DirectX::XMVector3Dot(axesB[1], axesA[i]))) +
			halfSizeB.z * fabsf(DirectX::XMVectorGetX(DirectX::XMVector3Dot(axesB[2], axesA[i])));

		float dist = fabsf(DirectX::XMVectorGetX(DirectX::XMVector3Dot(d, axesA[i])));

		if (dist > rA + rB)
		{
			return false; // �����������������ꍇ
		}
	}

	for (int i = 0; i < 3; ++i)
	{
		// �� B[i]
		float rA = halfSizeA.x * fabsf(DirectX::XMVectorGetX(DirectX::XMVector3Dot(axesA[0], axesB[i]))) +
			halfSizeA.y * fabsf(DirectX::XMVectorGetX(DirectX::XMVector3Dot(axesA[1], axesB[i]))) +
			halfSizeA.z * fabsf(DirectX::XMVectorGetX(DirectX::XMVector3Dot(axesA[2], axesB[i])));

		float rB = halfSizeB.x * fabsf(DirectX::XMVectorGetX(DirectX::XMVector3Dot(axesB[0], axesB[i]))) +
			halfSizeB.y * fabsf(DirectX::XMVectorGetX(DirectX::XMVector3Dot(axesB[1], axesB[i]))) +
			halfSizeB.z * fabsf(DirectX::XMVectorGetX(DirectX::XMVector3Dot(axesB[2], axesB[i])));

		float dist = fabsf(DirectX::XMVectorGetX(DirectX::XMVector3Dot(d, axesB[i])));

		if (dist > rA + rB)
		{
			return false; // �����������������ꍇ
		}
	}

	return true; // ��������������Ȃ������ꍇ�A�Փ˂��Ă���
}




} // namespace HaraProject::Framework