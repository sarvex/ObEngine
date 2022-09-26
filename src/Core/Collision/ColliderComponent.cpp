#include <Collision/ColliderComponent.hpp>
#include <Collision/Exceptions.hpp>

namespace obe::collision
{
    void ColliderComponent::load_capsule(const vili::node& data)
    {
    }

    void ColliderComponent::load_circle(const vili::node& data)
    {
        auto new_collider = CircleCollider();
        new_collider.set_radius(data.at("radius").as<vili::number>());
        m_collider = new_collider;
    }

    void ColliderComponent::load_polygon(const vili::node& data)
    {
        auto new_collider = PolygonCollider();
        for (const auto& point : data.at("points").as<vili::array>())
        {
            const transform::UnitVector point_position(point.at("x"), point.at("y"));
            new_collider.add_point(point_position);
        }
        m_collider = new_collider;
    }

    void ColliderComponent::load_rectangle(const vili::node& data)
    {
        auto new_collider = RectangleCollider();
        const transform::UnitVector size(data.at("width"), data.at("height"));
        new_collider.set_size(size);
        m_collider = new_collider;
    }

    vili::node ColliderComponent::schema() const
    {
        return vili::object {
            { "x", vili::object { { "type", vili::number_typename } } },
            { "y", vili::object { { "type", vili::number_typename } } },
            { "type", vili::object {
                { "type", vili::string_typename },
                { "values", vili::array { "Capsule", "Circle", "Polygon", "Rectangle" } }
            } }
        };
    }

    ColliderComponent::ColliderComponent(const std::string& id)
        : Component(id)
    {
    }

    vili::node ColliderComponent::dump() const
    {
        return vili::node {};
    }

    void ColliderComponent::load(const vili::node& data)
    {
        const double x = data.at("x");
        const double y = data.at("y");
        std::string tag;
        if (data.contains("tag"))
        {
            tag = data.at("tag");
        }
        const std::string collider_type_str = data.at("type");
            
        switch (ColliderTypeMeta::from_string(collider_type_str))
        {
        case ColliderType::Capsule:
            load_capsule(data);
            break;
        case ColliderType::Circle:
            load_circle(data);
            break;
        case ColliderType::Rectangle:
            load_rectangle(data);
            break;
        case ColliderType::Polygon:
            load_polygon(data);
            break;
        case ColliderType::Collider:
            throw exceptions::InvalidColliderComponentType(m_id, collider_type_str, EXC_INFO);
        }
        std::visit([x, y, tag](auto&& collider)
            {
                collider.set_position(transform::UnitVector(x, y));
                collider.set_tag(tag);
            }
            , m_collider
        );
    }

    ColliderType ColliderComponent::get_collider_type() const
    {
        if (std::holds_alternative<CapsuleCollider>(m_collider))
        {
            return ColliderType::Capsule;
        }
        else if (std::holds_alternative<CircleCollider>(m_collider))
        {
            return ColliderType::Circle;
        }
        else if (std::holds_alternative<PolygonCollider>(m_collider))
        {
            return ColliderType::Polygon;
        }
        else if (std::holds_alternative<RectangleCollider>(m_collider))
        {
            return ColliderType::Rectangle;
        }
        return ColliderType::Collider;
    }

    std::string_view ColliderComponent::type() const
    {
        return ColliderComponent::ComponentType;
    }

    Collider* ColliderComponent::get_inner_collider()
    {
        Collider* collider = std::visit([](auto& collider_variant) -> Collider*
            { return &collider_variant; },
            m_collider);
        return collider;
    }
}
