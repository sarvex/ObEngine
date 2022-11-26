#pragma once

#include <unordered_map>

#include <Collision/Collider.hpp>

namespace obe::collision
{
    struct CollisionRejectionPair
    {
        const Collider* collider1 = nullptr;
        const Collider* collider2 = nullptr;

        bool operator()(CollisionRejectionPair const* lhs, CollisionRejectionPair const* rhs) const
        {
            return lhs->collider1 == rhs->collider1 && lhs->collider2 == rhs->collider2;
        }
    };

    class CollisionSpace
    {
    private:
        std::unordered_set<Collider*> m_colliders;
        std::unordered_map<std::string, std::unordered_set<std::string>> m_tags_blacklists;
    protected:
        static bool matches_any_tag(const std::unordered_set<std::string>& input_tags,
            const std::unordered_set<std::string>& whitelist_or_blacklist);
        bool can_collide_with(const Collider& collider1, const Collider& collider2, bool check_both_directions = true) const;
    public:
        CollisionSpace() = default;

        /**
         * \brief Adds a Collider in the CollisionSpace
         * \param collider Pointer to the collider to add to the CollisionSpace
         */
        void add_collider(Collider* collider);
        /**
         * \brief Get how many Colliders are present in the Scene
         * \return The amount of Colliders present in the Scene
         */
        [[nodiscard]] std::size_t get_collider_amount() const;
        /**
         * \brief Get all the pointers of the Colliders in the Scene
         * \return A std::vector containing all the pointers of the Colliders
         *         present in the Scene
         */
        [[nodiscard]] std::unordered_set<Collider*> get_all_colliders() const;
        /**
         * \brief Removes the Collider with the given Id from the Scene
         * \param collider Pointer to the collider to remove from the CollisionSpace
         */
        void remove_collider(Collider* collider);

        [[nodiscard]] bool collides(const Collider& collider) const;
        [[nodiscard]] transform::Vector2 get_offset_before_collision(const Collider& collider,
            const transform::Vector2& offset = transform::Vector2(0, 0)) const;

        void add_tag_to_blacklist(const std::string& source_tag, const std::string& rejected_tag);
        void remove_tag_to_blacklist(
            const std::string& source_tag, const std::string& rejected_tag);
        void clear_blacklist(const std::string& source_tag);
        [[nodiscard]] const std::unordered_set<std::string>& get_blacklist(
            const std::string& source_tag) const;
    };
}
