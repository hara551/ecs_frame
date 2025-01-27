#include <vector>
#include <tuple>

#include "SystemBase.h"

#include "IEntityOperator.h"
#include "ISystemDistributor.h"
#include "IChunkProvider.h"
#include "ComponentMask.h"
#include "ComponentDataChunk.h"
#include "Velocity.h"
#include "Transform.h"
#include "CollisionCircle2D.h"
#include "Circle2DCollisionSystem.h"
namespace HaraProject::Framework {

/**
* @brief �R���X�g���N�^
*/
Circle2DCollisionSystem::Circle2DCollisionSystem(IEntityOperator* entityOperator, ISystemDistributor* systemDistributor, IChunkProvider* chunkProvider)
    : SystemBase(entityOperator, systemDistributor, chunkProvider)
{
}

/**
* @brief �V�X�e���X�V
*/
void Circle2DCollisionSystem::UpdateSystem(float deltaTime)
{
    std::vector<ComponentDataChunk*> chunks = FindChunks<Transform, CollisionCircle2D, Velocity>();
    if (chunks.empty()) return;

    std::vector<std::tuple<uint32_t, CollisionCircle2D*, Transform*, Velocity*>> entities{};

    // �ΏۃG���e�B�e�B��z��ɂ܂Ƃ߂�
    for (auto& chunk : chunks)
    {
        CollisionCircle2D* collision_circle = reinterpret_cast<CollisionCircle2D*>(chunk->CalculateComponentDataPointer(ComponentMask<CollisionCircle2D>::bit, 0));
        Transform* transform = reinterpret_cast<Transform*>(chunk->CalculateComponentDataPointer(ComponentMask<Transform>::bit, 0));
        Velocity* velocity = reinterpret_cast<Velocity*>(chunk->CalculateComponentDataPointer(ComponentMask<Velocity>::bit, 0));

        int32_t num_entities = chunk->GetNumEntities();
        for (int i = 0; i < num_entities; ++i)
        {
            if (transform->IsAble() && transform != nullptr)
            {
                entities.emplace_back(chunk->GetIdByIndex(i), collision_circle, transform, velocity);
            }
            ++collision_circle;
            ++transform;
            ++velocity;
        }
    }

    // �ǂƂ̏Փˏ���
    for (auto& [id, circle, transform, velocity] : entities)
    {
        DirectX::XMFLOAT3 pos = MathUtil::AddFloat3(transform->position, DirectX::XMFLOAT3(circle->center.x, circle->center.y, 0.0f));
        float radius = circle->radius;

        // ���[
        if (pos.x - radius <= 0.0f)
        {
            velocity->linearVelocity.x *= -1.0f; // �������x�𔽓]
            transform->position.x = radius; // �ʒu�␳
        }

        // �E�[
        if (pos.x + radius >= 1280.0f)
        {
            velocity->linearVelocity.x *= -1.0f; // �������x�𔽓]
            transform->position.x = 1280.0f - radius; // �ʒu�␳
        }

        // ��[
        if (pos.y - radius <= 0.0f)
        {
            velocity->linearVelocity.y *= -1.0f; // �������x�𔽓]
            transform->position.y = radius; // �ʒu�␳
        }

        // ���[
        if (pos.y + radius >= 720.0f)
        {
            velocity->linearVelocity.y *= -1.0f; // �������x�𔽓]
            transform->position.y = 720.0f - radius; // �ʒu�␳
        }
    }

    // �Փ˔���Ɣ��ˏ���
    for (int i = 0; i < entities.size(); ++i)
    {
        auto& [id_a, circle_a, transform_a, velocity_a] = entities[i];
        for (int j = i + 1; j < entities.size(); ++j)
        {
            auto& [id_b, circle_b, transform_b, velocity_b] = entities[j];

            if (CheckCollisionCircle(circle_a, transform_a, circle_b, transform_b))
            {
                // === �Փ˂̈ʒu�␳ ===
                DirectX::XMFLOAT3 pos_a = MathUtil::AddFloat3(transform_a->position, DirectX::XMFLOAT3(circle_a->center.x, circle_a->center.y, 0.0f));
                DirectX::XMFLOAT3 pos_b = MathUtil::AddFloat3(transform_b->position, DirectX::XMFLOAT3(circle_b->center.x, circle_b->center.y, 0.0f));
                DirectX::XMFLOAT3 impact_axis = MathUtil::SubtractFloat3(pos_a, pos_b);

                float distance = sqrt(impact_axis.x * impact_axis.x + impact_axis.y * impact_axis.y);
                float overlap = circle_a->radius + circle_b->radius - distance;

                // ���K��
                impact_axis.x /= distance;
                impact_axis.y /= distance;

                // �d�Ȃ���C��
                DirectX::XMFLOAT3 correction = MathUtil::ScalingFloat3(impact_axis, overlap * 0.5f);
                transform_a->position = MathUtil::AddFloat3(transform_a->position, correction);
                transform_b->position = MathUtil::SubtractFloat3(transform_b->position, correction);

                // === �Փ˂̑��x�X�V ===
                float dot_a = velocity_a->linearVelocity.x * impact_axis.x + velocity_a->linearVelocity.y * impact_axis.y;
                float dot_b = velocity_b->linearVelocity.x * impact_axis.x + velocity_b->linearVelocity.y * impact_axis.y;

                float mass_a = 1;
                float mass_b = 1;

                // �Փˌ�̑��x�i���ˌW�� kRepulsionCoefficient ���l���j
                float new_velocity_a = (dot_a * (mass_a - mass_b) + 2.0f * mass_b * dot_b) / (mass_a + mass_b);
                float new_velocity_b = (dot_b * (mass_b - mass_a) + 2.0f * mass_a * dot_a) / (mass_a + mass_b);

                DirectX::XMFLOAT3 velocity_change_a = MathUtil::ScalingFloat3(impact_axis, new_velocity_a - dot_a);
                DirectX::XMFLOAT3 velocity_change_b = MathUtil::ScalingFloat3(impact_axis, new_velocity_b - dot_b);

                velocity_a->linearVelocity = MathUtil::AddFloat3(velocity_a->linearVelocity, velocity_change_a);
                velocity_b->linearVelocity = MathUtil::AddFloat3(velocity_b->linearVelocity, velocity_change_b);
            }
        }
    }
}

/**
* @brief �~�Փ˔���
*/
bool Circle2DCollisionSystem::CheckCollisionCircle(CollisionCircle2D* collisionCircleA, Transform* transformA, CollisionCircle2D* collisionCircleB, Transform* transformB)
{
    DirectX::XMFLOAT3 pos_a = MathUtil::AddFloat3(transformA->position, DirectX::XMFLOAT3(collisionCircleA->center.x, collisionCircleA->center.y, 0.0f));
    DirectX::XMFLOAT3 pos_b = MathUtil::AddFloat3(transformB->position, DirectX::XMFLOAT3(collisionCircleB->center.x, collisionCircleB->center.y, 0.0f));

    DirectX::XMFLOAT3 distance = MathUtil::SubtractFloat3(pos_a, pos_b);
    float distanceSq = distance.x * distance.x + distance.y * distance.y;

    float impactDistanceSq = (collisionCircleA->radius + collisionCircleB->radius) * (collisionCircleA->radius + collisionCircleB->radius);

    return distanceSq < impactDistanceSq;
}

} // namespace HaraProject::Framework
