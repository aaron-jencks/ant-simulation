#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>

#include <engine/typing.hpp>

namespace engine {
    template <Numeric T>
    class Vector2 {
    public:
        T x;
        T y;

        Vector2(T x = 0, T y = 0) : x(x), y(y) {}

        template<Numeric U>
        explicit operator Vector2<U>() const {
            return Vector2<U>(static_cast<U>(x), static_cast<U>(y));
        }

        Vector2 operator+(Numeric auto scalar) const {
            return Vector2(x + scalar, y + scalar);
        }

        Vector2& operator+=(Numeric auto scalar) {
            x += scalar;
            y += scalar;
            return *this;
        }

        Vector2 operator+(const Vector2& other) const {
            return Vector2(x + other.x, y + other.y);
        }

        Vector2& operator+=(const Vector2& other) {
            x += other.x;
            y += other.y;
            return *this;
        }

        Vector2 operator-(Numeric auto scalar) const {
            return Vector2(x - scalar, y - scalar);
        }

        Vector2& operator-=(Numeric auto scalar) {
            x -= scalar;
            y -= scalar;
            return *this;
        }

        Vector2 operator-(const Vector2& other) const {
            return Vector2(x - other.x, y - other.y);
        }

        Vector2& operator-=(const Vector2& other) {
            x -= other.x;
            y -= other.y;
            return *this;
        }

        Vector2 operator*(Numeric auto scalar) const {
            return Vector2(x * scalar, y * scalar);
        }

        Vector2& operator*=(Numeric auto scalar) {
            x *= scalar;
            y *= scalar;
            return *this;
        }

        Vector2 operator*(const Vector2& other) const {
            return Vector2(x * other.x, y * other.y);
        }

        Vector2& operator*=(const Vector2& other) {
            x *= other.x;
            y *= other.y;
            return *this;
        }

        Vector2 operator/(Numeric auto scalar) const {
            return Vector2(x / scalar, y / scalar);
        }

        Vector2& operator/=(Numeric auto scalar) {
            x /= scalar;
            y /= scalar;
            return *this;
        }

        Vector2 operator/(const Vector2& other) const {
            return Vector2(x / other.x, y / other.y);
        }

        Vector2& operator/=(const Vector2& other) {
            x /= other.x;
            y /= other.y;
            return *this;
        }

        T magnitude() const {
            return static_cast<T>(std::hypot(x, y));
        }

        Vector2<std::common_type_t<T, double>> unit() const {
            using R = std::common_type_t<T, double>;
            R magnitude = std::hypot(R(x), R(y));
            if(magnitude == R(0)) return Vector2<R>(0, 0);
            return Vector2<R>(R(x) / magnitude, R(y) / magnitude);
        }
    };
}

#endif
