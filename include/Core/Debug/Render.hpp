#pragma once

#include <Collision/ColliderComponent.hpp>
#include <Graphics/Color.hpp>
#include <Graphics/RenderTarget.hpp>
#include <Transform/Polygon.hpp>
#include <Transform/UnitVector.hpp>

namespace obe::debug::render
{
    void draw_polygon(const graphics::RenderTarget target, transform::Polygon& polygon,
        bool draw_lines, bool draw_points, bool draw_centroid, bool draw_skeleton,
        transform::UnitVector offset);

    struct ColliderRenderOptions
    {
        const graphics::Color color = graphics::Color(255, 0, 0, 150);
    };

    void draw_collider(const graphics::RenderTarget target, const collision::ColliderComponent& collider, const ColliderRenderOptions& render_options);
}
