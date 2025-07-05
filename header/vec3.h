#ifndef VEC3_H
#define VEC3_H
#include <cmath>
using namespace std;


class vec3 {
public:
    double vec[3];

    vec3() {
        vec[0] = 0;
        vec[1] = 0;
        vec[2] = 0;
    }

    vec3(double x, double y, double z) {
        vec[0] = x;
        vec[1] = y;
        vec[2] = z;
    }

    double x() const {
        return vec[0];
    }

    double y() const {
        return vec[1];
    }

    double z() const {
        return vec[2];
    }

    vec3 operator-() const {
        return vec3(-vec[0], -vec[1], -vec[2]);
    }

    vec3& operator+=(vec3 const& other) {
        this->vec[0] = vec[0] + other.vec[0];
        this->vec[1] = vec[1] + other.vec[1];
        this->vec[2] = vec[2] + other.vec[2];
        return *this;
    }

    vec3& operator-=(vec3 const& other) {
        this->vec[0] = vec[0] - other.vec[0];
        this->vec[1] = vec[1] - other.vec[1];
        this->vec[2] = vec[2] - other.vec[2];
        return *this;
    }

    vec3& operator*=(const double scalar) {
        this->vec[0] = vec[0] * scalar;
        this->vec[1] = vec[1] * scalar;
        this->vec[2] = vec[2] * scalar;
        return *this;
    }

    vec3& operator/=(const double scalar) {
        this->vec[0] = vec[0] / scalar;
        this->vec[1] = vec[1] / scalar;
        this->vec[2] = vec[2] / scalar;
        return *this;
    }

    vec3& operator*=(vec3 const& other) {
        this->vec[0] = vec[0] * other.vec[0];
        this->vec[1] = vec[1] * other.vec[1];
        this->vec[2] = vec[2] * other.vec[2];
        return *this;
    }

    double dot(vec3 const& other) const {
        return vec[0] * other.vec[0] + vec[1] * other.vec[1] + vec[2] * other.vec[2];
    }


    vec3 cross(vec3 const& other) const {
        vec3 res;
        res.vec[0] = vec[1] * other.vec[2] - vec[2] * other.vec[1];
        res.vec[1] = vec[2] * other.vec[0] - vec[0] * other.vec[2];
        res.vec[2] = vec[0] * other.vec[1] - vec[1] * other.vec[0];
        return res;
    }

    double length() const {
        return sqrt(this->length_squared());
    }

    double length_squared() const {
        return vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2];

    }

    vec3 unit_vector() const {
        vec3 res;
        double length = this->length();
        res.vec[0] = vec[0] / length;
        res.vec[1] = vec[1] / length;
        res.vec[2] = vec[2] / length;
        return res;
    }

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

#endif //VEC3_H
