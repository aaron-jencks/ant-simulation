#ifndef ENTITY_H
#define ENTITY_H

#include <engine/context.hpp>
#include <engine/typing.hpp>
#include <engine/vector.hpp>

namespace engine {
    template<Numeric T>
    class Entity {
    public:
        Vector2<T> position{T(0), T(0)};
        bool is_solid = false;

        Entity() = default;
        explicit Entity(bool is_solid) : is_solid(is_solid) {}
        explicit Entity(const Vector2<T>& position) : position(position) {}
        explicit Entity(const Vector2<T>& position, bool is_solid) : position(position), is_solid(is_solid) {}

        virtual ~Entity() = default;

        Entity& operator+=(const Vector2<T>& other) {
            position += other;
            return *this;
        }

        Entity& operator-=(const Vector2<T>& other) {
            position -= other;
            return *this;
        }

        Entity& operator*=(const Vector2<T>& other) {
            position *= other;
            return *this;
        }

        Entity& operator/=(const Vector2<T>& other) {
            position /= other;
            return *this;
        }
    };
}

#endif
