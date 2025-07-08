#pragma once
#include <iosfwd>

using namespace std;

class vec3 {
public:
    double vec[3];

    vec3();
    vec3(double x, double y, double z);

    double x() const;
    double y() const;
    double z() const;

    vec3 operator-() const;
    double& operator[](int i);

    vec3& operator+=(const vec3& other);
    vec3& operator-=(const vec3& other);
    vec3& operator*=(double scalar);
    vec3& operator/=(double scalar);
    vec3& operator*=(const vec3& other);

    double dot(const vec3& other) const;
    vec3 cross(const vec3& other) const;

    double length() const;
    double length_squared() const;
    vec3 unit_vector() const;
};

using point3 = vec3;

// Opérateurs externes
std::ostream &operator<<(std::ostream &out, const vec3 &v);
vec3 operator+(const vec3& u, const vec3& v);
vec3 operator+(const vec3& u, double other);
vec3 operator-(const vec3& u, const vec3& v);
vec3 operator*(const vec3& u, const vec3& v);
vec3 operator*(double t, const vec3& v);
vec3 operator*(const vec3& v, double t);
vec3 operator/(const vec3& v, double t);