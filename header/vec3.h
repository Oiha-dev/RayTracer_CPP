#pragma once

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

inline vec3 lerp(vec3 &a, vec3 &b, double t) {
    double x = a.x() + (b.x() - a.x()) * t;
    double y = a.y() + (b.y() - a.y()) * t;
    double z = a.z() + (b.z() - a.z()) * t;
    return vec3(x, y, z);
}

inline vec3 operator+(const vec3& u, const vec3& v) {
    return vec3(u.vec[0] + v.vec[0], u.vec[1] + v.vec[1], u.vec[2] + v.vec[2]);
}

inline vec3 operator+(const vec3& u, const double other) {
    return vec3(u.vec[0] + other, u.vec[1] + other, u.vec[2] + other);
}

inline vec3 operator-(const vec3& u, const vec3& v) {
    return vec3(u.vec[0] - v.vec[0], u.vec[1] - v.vec[1], u.vec[2] - v.vec[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v) {
    return vec3(u.vec[0] * v.vec[0], u.vec[1] * v.vec[1], u.vec[2] * v.vec[2]);
}

inline vec3 operator*(double t, const vec3& v) {
    return vec3(t*v.vec[0], t*v.vec[1], t*v.vec[2]);
}

inline vec3 operator*(const vec3& v, double t) {
    return t * v;
}

inline vec3 operator/(const vec3& v, double t) {
    return (1/t) * v;
}

// // Opérateurs externes
// vec3 operator+(const vec3& u, const vec3& v);
// vec3 operator+(const vec3& u, double other);
// vec3 operator-(const vec3& u, const vec3& v);
// vec3 operator*(const vec3& u, const vec3& v);
// vec3 operator*(double t, const vec3& v);
// vec3 operator*(const vec3& v, double t);
// vec3 operator/(const vec3& v, double t);