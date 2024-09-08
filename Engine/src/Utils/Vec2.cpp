#include "Vec2.h"

#include <cmath>
#include <sys/stat.h>
# define M_PI           3.14159265358979323846  /* pi */


Vec2::Vec2(): x(0.f), y(0.f), z(0), a(1)
{
}

Vec2::Vec2(float x): x(x), y(x), z(x), a(1)
{
}

Vec2::Vec2(float x, float y): x(x), y(y), z(0), a(1)
{
}

Vec2::Vec2(float R, float G, float B, float A): x(R), y(G), z(B), a(A)
{
}

Vec2 Vec2::operator+(const Vec2& b) const
{
    Vec2 vec;
    vec.x = this->x + b.x;
    vec.y = this->y + b.y;
    vec.z = this->z + b.z;
    vec.a = this->a + b.a;
    return vec;
}

void Vec2::operator+=(const Vec2& b)
{
    this->x += b.x;
    this->y += b.y;
    this->z += b.z;
    this->a += b.a;
}

Vec2 Vec2::operator-(const Vec2& b) const
{
    Vec2 vec;
    vec.x = this->x - b.x;
    vec.y = this->y - b.y;
    vec.z = this->z - b.z;
    vec.a = this->a - b.a;
    return vec;
}

void Vec2::operator-=(const Vec2& b)
{
    this->x -= b.x;
    this->y -= b.y;
    this->z -= b.z;
    this->a -= b.a;
}

Vec2 Vec2::operator*(float val) const
{
    Vec2 vec;
    vec.x = this->x * val;
    vec.y = this->y * val;
    vec.z = this->z * val;
    vec.a = this->a * val;
    return vec;
}

Vec2 Vec2::operator*(double val) const
{
    Vec2 vec;
    vec.x = this->x * static_cast<float>(val);
    vec.y = this->y * static_cast<float>(val);
    vec.z = this->z * static_cast<float>(val);
    vec.a = this->a * static_cast<float>(val);
    return vec;
}

Vec2 Vec2::operator*(int val) const
{
    Vec2 vec;
    vec.x = this->x * static_cast<float>(val);
    vec.y = this->y * static_cast<float>(val);
    vec.z = this->z * static_cast<float>(val);
    vec.a = this->a * static_cast<float>(val);
    return vec;
}

Vec2 Vec2::operator*(Vec2 val) const
{
    Vec2 vec;
    vec.x = this->x * val.x;
    vec.y = this->y * val.y;
    vec.z = this->z * val.z;
    vec.a = this->a * val.a;
    return vec;
}

void Vec2::operator*=(float val)
{
    this->x *= val;
    this->y *= val;
    this->z *= val;
    this->a *= val;
}

void Vec2::operator*=(double val)
{
    this->x *= static_cast<float>(val);
    this->y *= static_cast<float>(val);
    this->z *= static_cast<float>(val);
    this->a *= static_cast<float>(val);
}

void Vec2::operator*=(int val)
{
    this->x *= static_cast<float>(val);
    this->y *= static_cast<float>(val);
    this->z *= static_cast<float>(val);
    this->a *= static_cast<float>(val);
}

Vec2 Vec2::operator*=(Vec2 val) const
{
    Vec2 vec;
    vec.x *= this->x * val.x;
    vec.y *= this->y * val.y;
    vec.z *= this->z * val.z;
    vec.a *= this->a * val.a;
    return vec;
}

Vec2 Vec2::operator/(float val) const
{
    Vec2 vec;
    vec.x = this->x / val;
    vec.y = this->y / val;
    vec.z = this->z / val;
    vec.a = this->a / val;
    return vec;
}

Vec2 Vec2::operator/(double val) const
{
    Vec2 vec;
    vec.x = this->x / static_cast<float>(val);
    vec.y = this->y / static_cast<float>(val);
    vec.z = this->z / static_cast<float>(val);
    vec.a = this->a / static_cast<float>(val);
    return vec;
}

Vec2 Vec2::operator/(int val) const
{
    Vec2 vec;
    vec.x = this->x / static_cast<float>(val);
    vec.y = this->y / static_cast<float>(val);
    vec.z = this->z / static_cast<float>(val);
    vec.a = this->a / static_cast<float>(val);
    return vec;
}

void Vec2::operator/=(float val)
{
    this->x /= val;
    this->y /= val;
    this->z /= val;
    this->a /= val;
}

void Vec2::operator/=(double val)
{
    this->x *= static_cast<float>(val);
    this->y *= static_cast<float>(val);
    this->z *= static_cast<float>(val);
    this->a *= static_cast<float>(val);
}

void Vec2::operator/=(int val)
{
    this->x *= static_cast<float>(val);
    this->y *= static_cast<float>(val);
    this->z *= static_cast<float>(val);
    this->a *= static_cast<float>(val);
}

float Vec2::R() const
{
    return x;
}

float Vec2::G() const
{
    return y;
}

float Vec2::B() const
{
    return z;
}

float Vec2::A() const
{
    return a;
}

bool Vec2::operator==(const Vec2& b) const
{
    float xValue = std::abs(this->x - b.x) < 0.001f;
    float yValue = std::abs(this->y - b.y) < 0.001f;
    return xValue && yValue;
}

float Vec2::Dot(const Vec2& b) const
{
    return this->x * b.x + this->y * b.y;
}

float Vec2::Magnitude() const
{
    return sqrtf(powf(this->x, 2) + powf(this->y, 2));
}

Vec2 Vec2::Normalized() const
{
    Vec2 normalized;
    float magnitude = Magnitude();
    //return vec 0 to avoid dividing by 0
    if (magnitude == 0)
    {
        return Vec2();
    }
    normalized.x = this->x / magnitude;
    normalized.y = this->y / magnitude;
    return normalized;
}

float Vec2::angle(Vec2& other) const
{
    Vec2 dir = (other - *this).Normalized();
    return atan2(dir.y, dir.x) * 180.f / static_cast<float> (M_PI);
}

float Vec2::distance(const Vec2& other) const
{
    return (other - *this).Magnitude();
}

Vec2 Vec2::DirectionByAngle(float angle)
{
    return Vec2(cos(angle * (static_cast<float>(M_PI) / 180.f)),
                sin(angle * (static_cast<float>(M_PI) / 180.f)));
}

bool Vec2::equals(Vec2 other )
{
    return distance(other) < 0.1f;
}
