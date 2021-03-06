#pragma once

#include "../common.h"
#include "rigidbody.h"
#include "circle.h"
#include "polygon.h"
#include "box.h"

namespace spe
{
    struct AABB
    {
        AABB(glm::vec2 _min, glm::vec2 _max);
        ~AABB() noexcept = default;

        AABB(const AABB&) noexcept = delete;
        AABB& operator=(const AABB&) noexcept = delete;

        AABB(AABB&&) noexcept = default;
        AABB& operator=(AABB&&) noexcept = default;

        glm::vec2 min;
        glm::vec2 max;
    };

    inline float area(const AABB& aabb)
    {
        return (aabb.max.x - aabb.min.x) * (aabb.max.y - aabb.min.y);
    }

    inline float perimeter(const AABB& aabb)
    {
        glm::vec2 w = aabb.max - aabb.min;
        return 2.0f * (w.x + w.y);
    }

    inline void fix(AABB& aabb)
    {
        auto a = glm::max(aabb.min, aabb.max);

        glm::vec2 newMin = glm::min(aabb.min, aabb.max);
        glm::vec2 newMax = glm::max(aabb.min, aabb.max);

        aabb.min = newMin;
        aabb.max = newMax;
    }

    inline AABB union_of(const AABB& b1, const AABB& b2)
    {
        glm::vec2 min = glm::min(b1.min, b2.min);
        glm::vec2 max = glm::max(b1.max, b2.max);

        return AABB{ min, max };
    }

    inline bool test_point_inside_AABB(const AABB& aabb, const glm::vec2& point)
    {
        if (aabb.min.x > point.x || aabb.max.x < point.x) return false;
        if (aabb.min.y > point.y || aabb.max.y < point.y) return false;

        return true;
    }

    inline bool detect_collision_AABB(const AABB& a, const AABB& b)
    {
        if (a.min.x > b.max.x || a.max.x < b.min.x) return false;
        if (a.min.y > b.max.y || a.max.y < b.min.y) return false;

        return true;
    }

    inline bool contains_AABB(const AABB& container, const AABB& testee)
    {
        return container.min.x <= testee.min.x
            && container.min.y <= testee.min.y
            && container.max.x >= testee.max.x
            && container.max.y >= testee.max.y;
    }

    AABB create_AABB(RigidBody* body, float margin = 0.0f);
}
