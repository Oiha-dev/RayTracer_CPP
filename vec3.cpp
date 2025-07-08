#include "header/vec3.h"
#include <cmath>
#include <ostream>


vec3::vec3() {
    vec[0] = 0;
    vec[1] = 0;
    vec[2] = 0;
}

vec3::vec3(double x, double y, double z) {
    vec[0] = x;
    vec[1] = y;
    vec[2] = z;
}

double vec3::x() const { return vec[0]; }
double vec3::y() const { return vec[1]; }
double vec3::z() const { return vec[2]; }



vec3 vec3::operator-() const {
    return vec3(-vec[0], -vec[1], -vec[2]);
}

double& vec3::operator[](int i) {
    return vec[i];
}

vec3& vec3::operator+=(const vec3& other) {
    vec[0] += other.vec[0];
    vec[1] += other.vec[1];
    vec[2] += other.vec[2];
    return *this;
}

vec3& vec3::operator-=(const vec3& other) {
    vec[0] -= other.vec[0];
    vec[1] -= other.vec[1];
    vec[2] -= other.vec[2];
    return *this;
}

vec3& vec3::operator*=(const double scalar) {
    vec[0] *= scalar;
    vec[1] *= scalar;
    vec[2] *= scalar;
    return *this;
}

vec3& vec3::operator/=(const double scalar) {
    vec[0] /= scalar;
    vec[1] /= scalar;
    vec[2] /= scalar;
    return *this;
}

vec3& vec3::operator*=(const vec3& other) {
    vec[0] *= other.vec[0];
    vec[1] *= other.vec[1];
    vec[2] *= other.vec[2];
    return *this;
}



double vec3::dot(const vec3& other) const {
    return vec[0]*other.vec[0] + vec[1]*other.vec[1] + vec[2]*other.vec[2];
}

vec3 vec3::cross(const vec3& other) const {
    return vec3(
        vec[1]*other.vec[2] - vec[2]*other.vec[1],
        vec[2]*other.vec[0] - vec[0]*other.vec[2],
        vec[0]*other.vec[1] - vec[1]*other.vec[0]
    );
}



double vec3::length() const {
    return std::sqrt(length_squared());
}

double vec3::length_squared() const {
    return vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2];
}

vec3 vec3::unit_vector() const {
    return *this / this->length();
}

vec3 lerp(vec3& a, vec3& b, double t) {
    return vec3(
        a.x() + (b.x() - a.x()) * t,
        a.y() + (b.y() - a.y()) * t,
        a.z() + (b.z() - a.z()) * t
    );
}

std::ostream& operator<<(std::ostream& out, const vec3& v){
    return out << v.x() << " " << v.y() << " " << v.z();
}

vec3 operator+(const vec3& u, const vec3& v) {
    return vec3(u.x() + v.x(), u.y() + v.y(), u.z() + v.z());
}
vec3 operator+(const vec3& u, double other) {
    return vec3(u.x() + other, u.y() + other, u.z() + other);
}
vec3 operator-(const vec3& u, const vec3& v) {
    return vec3(u.x() - v.x(), u.y() - v.y(), u.z() - v.z());
}
vec3 operator*(const vec3& u, const vec3& v) {
    return vec3(u.x() * v.x(), u.y() * v.y(), u.z() * v.z());
}
vec3 operator*(double t, const vec3& v) {
    return vec3(t * v.x(), t * v.y(), t * v.z());
}
vec3 operator*(const vec3& v, double t) {
    return t * v;
}
vec3 operator/(const vec3& v, double t) {
    return (1 / t) * v;
}
