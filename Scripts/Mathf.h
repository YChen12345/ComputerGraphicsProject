#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include <random>
#include <iostream>
#include <algorithm>

const float PI = 3.1415926f;
inline float angle_radians(float angle) {
    return angle * PI / 180.f;
}
inline int ceilDiv(int a, int b) {
    if (a % b > 0) {
        return 1 + a / b;
    }
    else
    {
        return a / b;
    }
}

enum dir {
    zero = 0,
    up = 1,
    down = 2,
    left = 3,
    right = 4,
    one = 5
};
class Vec3;
class Vec2 {
public:
    float x;
    float y;
public:
    Vec2() :x(0), y(0) {}
    Vec2(dir d) {
        switch (d)
        {
        case zero:
            x = 0;
            y = 0;
            break;
        case up:
            x = 0;
            y = 1;
            break;
        case down:
            x = 0;
            y = -1;
            break;
        case left:
            x = -1;
            y = 0;
            break;
        case right:
            x = 1;
            y = 0;
            break;
        case one:
            x = 1;
            y = 1;
            break;
        default:
            x = 0;
            y = 0;
            break;
        }
    }
    Vec2(float a, float b) :x(a), y(b) {}
    Vec2(const Vec2& v) {
        x = v.x;
        y = v.y;
    }
    Vec2& operator = (const Vec2& v) {
        x = v.x;
        y = v.y;
        return *this;
    }
    Vec2 operator + (const Vec2& v) {
        Vec2 res;
        res.x = x + v.x;
        res.y = y + v.y;
        return res;
    }
    Vec2 operator - (const Vec2& v) {
        Vec2 res;
        res.x = x - v.x;
        res.y = y - v.y;
        return res;
    }
    Vec2 operator * (float f) {
        Vec2 res;
        res.x = x * f;
        res.y = y * f;
        return res;
    }
    void Set(float a, float b) {
        x = a;
        y = b;
    }
    Vec2 Normalize() {
        Vec2 v;
        if (x * x + y * y > 0.f) {
            v.x = x / sqrt(x * x + y * y);
            v.y = y / sqrt(x * x + y * y);
        }
        return v;
    }
    float magnitude() {
        return sqrt(x * x + y * y);
    }
    Vec3 Vec2toVec3(float z = 0);
};

inline int MMin(int a, int b) {
    if (a > b) {
        return b;
    }
    else
    {
        return a;
    }
}
inline int MMin(int a, int b, int c) {
    return MMin(MMin(a, b), c);
}
inline float MMin(float a, float b) {
    if (a > b) {
        return b;
    }
    else
    {
        return a;
    }
}
inline float MMin(float a, float b, float c) {
    return MMin(MMin(a, b), c);
}

inline int MMax(int a, int b) {
    if (a < b) {
        return b;
    }
    else
    {
        return a;
    }
}

inline int MMax(int a, int b, int c) {
    return MMax(MMax(a, b), c);
}

inline float MMax(float a, float b) {
    if (a < b) {
        return b;
    }
    else
    {
        return a;
    }
}

inline float MMax(float a, float b, float c) {
    return MMax(MMax(a, b), c);
}

inline unsigned int MMin(unsigned int a, unsigned int b) {
    if (a > b) {
        return b;
    }
    else
    {
        return a;
    }
}

inline unsigned int MMax(unsigned int a, unsigned int b) {
    if (a < b) {
        return b;
    }
    else
    {
        return a;
    }
}

inline int MCeil(float a) {
    if (a - static_cast<int>(a) < 0.01f) {
        return static_cast<int>(a);
    }
    else
    {
        return static_cast<int>(a) + 1;
    }
}

inline int MFloor(float a) {
    return static_cast<int> (a);
}

template<typename T>
inline T lerp(const T& a, const T& b, float t) {
    return a * (1.0f - t) + (b * t);
}

#define SQ(x) ((x) * (x))

class Vec3 {
public:
    union {
        float v[3];
        struct { float x, y, z; };
    };

    Vec3() : x(0), y(0), z(0) {}
    Vec3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
    explicit Vec3(float val) : x(val), y(val), z(val) {}
    Vec3(const Vec3& other) : x(other.x), y(other.y), z(other.z) {}
    float& operator[](const int index)
    {
        return v[index];
    }
    Vec3& operator=(const Vec3& other) {
        if (this != &other) {
            x = other.x; y = other.y; z = other.z;
        }
        return *this;
    }

    Vec3 operator+(const Vec3& pVec) const {
        return Vec3(v[0] + pVec.v[0], v[1] + pVec.v[1], v[2] + pVec.v[2]);
    }

    Vec3 operator-(const Vec3& pVec) const {
        return Vec3(v[0] - pVec.v[0], v[1] - pVec.v[1], v[2] - pVec.v[2]);
    }

    Vec3 operator*(const Vec3& pVec) const {
        return Vec3(v[0] * pVec.v[0], v[1] * pVec.v[1], v[2] * pVec.v[2]);
    }

    Vec3 operator*(float val) const {
        return Vec3(v[0] * val, v[1] * val, v[2] * val);
    }

    Vec3 operator/(float val) const {
        float inv = 1.0f / val;
        return Vec3(v[0] * inv, v[1] * inv, v[2] * inv);
    }

    Vec3 operator-() const {
        return Vec3(-v[0], -v[1], -v[2]);
    }

    Vec3& operator+=(const Vec3& pVec) {
        v[0] += pVec.v[0]; v[1] += pVec.v[1]; v[2] += pVec.v[2];
        return *this;
    }

    Vec3& operator-=(const Vec3& pVec) {
        v[0] -= pVec.v[0]; v[1] -= pVec.v[1]; v[2] -= pVec.v[2];
        return *this;
    }

    Vec3& operator*=(float val) {
        v[0] *= val; v[1] *= val; v[2] *= val;
        return *this;
    }

    Vec3& operator/=(float val) {
        float inv = 1.0f / val;
        v[0] *= inv; v[1] *= inv; v[2] *= inv;
        return *this;
    }

    float Dot(const Vec3& pVec) const {
        return v[0] * pVec.v[0] + v[1] * pVec.v[1] + v[2] * pVec.v[2];
    }

    Vec3 Cross(const Vec3& v1) const {
        return Vec3(v1.v[1] * v[2] - v1.v[2] * v[1],
            v1.v[2] * v[0] - v1.v[0] * v[2],
            v1.v[0] * v[1] - v1.v[1] * v[0]);
    }

    static Vec3 Cross(const Vec3& v1, const Vec3& v2) {
        return Vec3(v1.y * v2.z - v1.z * v2.y,
            v1.z * v2.x - v1.x * v2.z,
            v1.x * v2.y - v1.y * v2.x);
    }
    float Length() const {
        return std::sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    }
    float magnitude() const {
        return std::sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    }

    float LengthSq() const {
        return v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
    }

    Vec3 Normalize() const {
        float len = Length();
        if (len > 0) {
            float invLen = 1.0f / len;
            return Vec3(v[0] * invLen, v[1] * invLen, v[2] * invLen);
        }
        return *this;
    }

    float Normalize_GetLength() {
        float len = Length();
        if (len > 0) {
            float invLen = 1.0f / len;
            v[0] *= invLen; v[1] *= invLen; v[2] *= invLen;
        }
        return len;
    }

    void Print() const {
        printf("Vec3(%.3f, %.3f, %.3f)\n", x, y, z);
    }

    std::string ToString() const {
        char buf[64];
        snprintf(buf, sizeof(buf), "Vec3(%.3f, %.3f, %.3f)", x, y, z);
        return std::string(buf);
    }

    float Max() const {
        return MMax(x, MMax(y, z));
    }

    float Min() const {
        return MMin(x, MMin(y, z));
    }

    static Vec3 Max(const Vec3& v1, const Vec3& v2) {
        return Vec3(MMax(v1.x, v2.x), MMax(v1.y, v2.y), MMax(v1.z, v2.z));
    }

    static Vec3 Min(const Vec3& v1, const Vec3& v2) {
        return Vec3(MMin(v1.x, v2.x), MMin(v1.y, v2.y), MMin(v1.z, v2.z));
    }
    static float Dot(const Vec3& v1, const Vec3& v2) {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    }
};


class Vec4 {
public:
    union {
        float v[4];
        struct { float x, y, z, w; };
    };

    Vec4() : x(0), y(0), z(0), w(1) {}
    Vec4(float x_, float y_, float z_, float w_ = 1.0f) : x(x_), y(y_), z(z_), w(w_) {}
    explicit Vec4(const Vec3& vec3, float w_ = 1.0f) : x(vec3.x), y(vec3.y), z(vec3.z), w(w_) {}
    float& operator[](const int index)
    {
        return v[index];
    }
    Vec4 operator+(const Vec4& pVec) const {
        return Vec4(v[0] + pVec.v[0], v[1] + pVec.v[1], v[2] + pVec.v[2], v[3] + pVec.v[3]);
    }
    Vec4& operator+=(const Vec4& pVec)
    {
        v[0] += pVec.v[0];
        v[1] += pVec.v[1];
        v[2] += pVec.v[2];
        v[3] += pVec.v[3];
        return *this;
    }
    Vec4 operator*(const Vec4& pVec) const
    {
        return Vec4(v[0] * pVec.v[0], v[1] * pVec.v[1], v[2] * pVec.v[2], v[3] * pVec.v[3]);
    }
    Vec4 operator*(float val) const {
        return Vec4(v[0] * val, v[1] * val, v[2] * val, v[3] * val);
    }
    Vec4 operator-() const
    {
        return Vec4(-v[0], -v[1], -v[2], -v[3]);
    }
    Vec4 operator-(const Vec4& pVec) const
    {
        return Vec4(v[0] - pVec.v[0], v[1] - pVec.v[1], v[2] - pVec.v[2], v[3] - pVec.v[3]);
    }
    Vec4& operator-=(const Vec4& pVec)
    {
        v[0] -= pVec.v[0];
        v[1] -= pVec.v[1];
        v[2] -= pVec.v[2];
        v[3] -= pVec.v[3];
        return *this;
    }
    Vec4& operator*=(const Vec4& pVec)
    {
        v[0] *= pVec.v[0];
        v[1] *= pVec.v[1];
        v[2] *= pVec.v[2];
        v[3] *= pVec.v[3];
        return *this;
    }
    Vec4& operator*=(const float val)
    {
        v[0] *= val;
        v[1] *= val;
        v[2] *= val;
        v[3] *= val;
        return *this;
    }
    Vec4 operator/(const Vec4& pVec) const
    {
        return Vec4(v[0] / pVec.v[0], v[1] / pVec.v[1], v[2] / pVec.v[2], v[3] / pVec.v[3]);
    }
    Vec4 operator/(const float val) const
    {
        return Vec4(v[0] / val, v[1] / val, v[2] / val, v[3] / val);
    }
    Vec4& operator/=(const Vec4& pVec)
    {
        v[0] /= pVec.v[0];
        v[1] /= pVec.v[1];
        v[2] /= pVec.v[2];
        v[3] /= pVec.v[3];
        return *this;
    }
    Vec4& operator/=(const float val)
    {
        v[0] /= val;
        v[1] /= val;
        v[2] /= val;
        v[3] /= val;
        return *this;
    }
    Vec3 toVec3() const { return Vec3(x / w, y / w, z / w); }
    float length() {
        return sqrt(SQ(v[0]) + SQ(v[1]) + SQ(v[2]) + SQ(v[3]));
    }
    float magnitude() {
        return sqrt(SQ(v[0]) + SQ(v[1]) + SQ(v[2]) + SQ(v[3]));
    }
    float lengthSquare() {
        return SQ(v[0]) + SQ(v[1]) + SQ(v[2]) + SQ(v[3]);
    }
    Vec4 normalize()
    {
        float len = 1.0f / sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2] + v[3] * v[3]);
        return Vec4(x * len, y * len, z * len, w * len);
    }
    float normalize_GetLength()
    {
        float length = sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2] + v[3] * v[3]);
        float len = 1.0f / length;
        v[0] *= len; v[1] *= len; v[2] *= len; v[3] *= len;
        return length;
    }
    float Dot(const Vec4& pVec) const {
        return v[0] * pVec.v[0] + v[1] * pVec.v[1] + v[2] * pVec.v[2] + v[3] * pVec.v[3];
    }
    Vec4 Max(const Vec4& v1, const Vec4& v2)
    {
        return Vec4(MMax(v1.v[0], v2.v[0]),
            MMax(v1.v[1], v2.v[1]),
            MMax(v1.v[2], v2.v[2]),
            MMax(v1.v[3], v2.v[3]));
    }
    Vec4 getScreenPos(int screenWidth, int screenHeight) const {
        return Vec4(
            (x + 1.0f) * 0.5f * screenWidth,
            (1.0f - y) * 0.5f * screenHeight,
            z,
            1
        );
    }
    float Max() const
    {
        return MMax(x, MMax(y, MMax(z, w)));
    }
    void print() {
        std::cout << '(' << x << ',' << y << ',' << z << ',' << w << ')' << std::endl;
    }
};
inline float Dot(const Vec3& v1, const Vec3& v2) {
    return Vec3::Dot(v1, v2);
}

inline Vec3 Cross(const Vec3& v1, const Vec3& v2) {
    return Vec3::Cross(v1, v2);
}

inline Vec3 Max(const Vec3& v1, const Vec3& v2) {
    return Vec3::Max(v1, v2);
}

inline Vec3 Min(const Vec3& v1, const Vec3& v2) {
    return Vec3::Min(v1, v2);
}
class alignas(64) Matrix
{
public:
    union
    {
        float a[4][4];
        float m[16];
    };
    Matrix() { SetIdentity(); }
    Matrix(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33)
    {
        a[0][0] = m00;
        a[0][1] = m01;
        a[0][2] = m02;
        a[0][3] = m03;
        a[1][0] = m10;
        a[1][1] = m11;
        a[1][2] = m12;
        a[1][3] = m13;
        a[2][0] = m20;
        a[2][1] = m21;
        a[2][2] = m22;
        a[2][3] = m23;
        a[3][0] = m30;
        a[3][1] = m31;
        a[3][2] = m32;
        a[3][3] = m33;
    }
    void SetIdentity()
    {
        memset(m, 0, 16 * sizeof(float));
        m[0] = 1.0f;
        m[5] = 1.0f;
        m[10] = 1.0f;
        m[15] = 1.0f;
    }
    Matrix Transpose()
    {
        return Matrix(a[0][0], a[1][0], a[2][0], a[3][0],
            a[0][1], a[1][1], a[2][1], a[3][1],
            a[0][2], a[1][2], a[2][2], a[3][2],
            a[0][3], a[1][3], a[2][3], a[3][3]);
    }
    float& operator[](int index)
    {
        return m[index];
    }
    static Matrix CreateTranslation(const Vec3& v)
    {
        Matrix mat;
        mat.a[0][3] = v.x;
        mat.a[1][3] = v.y;
        mat.a[2][3] = v.z;
        return mat;
    }
    static Matrix CreateScaling(const Vec3& v)
    {
        Matrix mat;
        mat.m[0] = v.x;
        mat.m[5] = v.y;
        mat.m[10] = v.z;
        return mat;
    }
    static Matrix CreateRotateX(float theta)
    {
        Matrix mat;
        float ct = cosf(theta);
        float st = sinf(theta);
        mat.m[5] = ct;
        mat.m[6] = st;
        mat.m[9] = -st;
        mat.m[10] = ct;
        return mat;
    }
    static Matrix CreateRotateY(float theta)
    {
        Matrix mat;
        float ct = cosf(theta);
        float st = sinf(theta);
        mat.m[0] = ct;
        mat.m[2] = -st;
        mat.m[8] = st;
        mat.m[10] = ct;
        return mat;
    }
    static Matrix CreateRotateZ(float theta)
    {
        Matrix mat;
        float ct = cosf(theta);
        float st = sinf(theta);
        mat.m[0] = ct;
        mat.m[1] = st;
        mat.m[4] = -st;
        mat.m[5] = ct;
        return mat;
    }
    Matrix mul(const Matrix& matrix) const
    {
        Matrix ret;

        ret.m[0] = m[0] * matrix.m[0] + m[4] * matrix.m[1] + m[8] * matrix.m[2] + m[12] * matrix.m[3];
        ret.m[1] = m[1] * matrix.m[0] + m[5] * matrix.m[1] + m[9] * matrix.m[2] + m[13] * matrix.m[3];
        ret.m[2] = m[2] * matrix.m[0] + m[6] * matrix.m[1] + m[10] * matrix.m[2] + m[14] * matrix.m[3];
        ret.m[3] = m[3] * matrix.m[0] + m[7] * matrix.m[1] + m[11] * matrix.m[2] + m[15] * matrix.m[3];

        ret.m[4] = m[0] * matrix.m[4] + m[4] * matrix.m[5] + m[8] * matrix.m[6] + m[12] * matrix.m[7];
        ret.m[5] = m[1] * matrix.m[4] + m[5] * matrix.m[5] + m[9] * matrix.m[6] + m[13] * matrix.m[7];
        ret.m[6] = m[2] * matrix.m[4] + m[6] * matrix.m[5] + m[10] * matrix.m[6] + m[14] * matrix.m[7];
        ret.m[7] = m[3] * matrix.m[4] + m[7] * matrix.m[5] + m[11] * matrix.m[6] + m[15] * matrix.m[7];

        ret.m[8] = m[0] * matrix.m[8] + m[4] * matrix.m[9] + m[8] * matrix.m[10] + m[12] * matrix.m[11];
        ret.m[9] = m[1] * matrix.m[8] + m[5] * matrix.m[9] + m[9] * matrix.m[10] + m[13] * matrix.m[11];
        ret.m[10] = m[2] * matrix.m[8] + m[6] * matrix.m[9] + m[10] * matrix.m[10] + m[14] * matrix.m[11];
        ret.m[11] = m[3] * matrix.m[8] + m[7] * matrix.m[9] + m[11] * matrix.m[10] + m[15] * matrix.m[11];

        ret.m[12] = m[0] * matrix.m[12] + m[4] * matrix.m[13] + m[8] * matrix.m[14] + m[12] * matrix.m[15];
        ret.m[13] = m[1] * matrix.m[12] + m[5] * matrix.m[13] + m[9] * matrix.m[14] + m[13] * matrix.m[15];
        ret.m[14] = m[2] * matrix.m[12] + m[6] * matrix.m[13] + m[10] * matrix.m[14] + m[14] * matrix.m[15];
        ret.m[15] = m[3] * matrix.m[12] + m[7] * matrix.m[13] + m[11] * matrix.m[14] + m[15] * matrix.m[15];

        return ret;
    }
    Matrix operator*(const Matrix& matrix)
    {
        return mul(matrix);
    }
    Vec4 mul(const Vec4& v) const {
        return Vec4(
            v.x * m[0] + v.y * m[1] + v.z * m[2] + v.w * m[3],
            v.x * m[4] + v.y * m[5] + v.z * m[6] + v.w * m[7],
            v.x * m[8] + v.y * m[9] + v.z * m[10] + v.w * m[11],
            v.x * m[12] + v.y * m[13] + v.z * m[14] + v.w * m[15]
        );
    }
    Vec3 mulVec(const Vec3& v)
    {
        return Vec3(
            (v.x * m[0] + v.y * m[1] + v.z * m[2]),
            (v.x * m[4] + v.y * m[5] + v.z * m[6]),
            (v.x * m[8] + v.y * m[9] + v.z * m[10]));
    }
    Vec3 mulPoint(const Vec3& v)
    {
        Vec3 v1 = Vec3(
            (v.x * m[0] + v.y * m[1] + v.z * m[2]) + m[3],
            (v.x * m[4] + v.y * m[5] + v.z * m[6]) + m[7],
            (v.x * m[8] + v.y * m[9] + v.z * m[10]) + m[11]);
        float w;
        w = (m[12] * v.x) + (m[13] * v.y) + (m[14] * v.z) + m[15];
        w = 1.0f / w;
        return (v1 * w);
    }
    Vec4 mvp(const Vec4& v) const {
        Vec4 res = Vec4(
            a[0][0] * v.x + a[0][1] * v.y + a[0][2] * v.z + a[0][3] * v.w,
            a[1][0] * v.x + a[1][1] * v.y + a[1][2] * v.z + a[1][3] * v.w,
            a[2][0] * v.x + a[2][1] * v.y + a[2][2] * v.z + a[2][3] * v.w,
            a[3][0] * v.x + a[3][1] * v.y + a[3][2] * v.z + a[3][3] * v.w
        );
        res.x = res.x / res.w;
        res.y = res.y / res.w;
        res.z = res.z / res.w;
        res.w = 1 / res.w;
        return res;
    }
    Matrix operator=(const Matrix& matrix)
    {
        memcpy(m, matrix.m, sizeof(float) * 16);
        return (*this);
    }
    Matrix Inverse() // Unrolled inverse from MESA library
    {
        Matrix inv;
        inv[0] = m[5] * m[10] * m[15] -
            m[5] * m[11] * m[14] -
            m[9] * m[6] * m[15] +
            m[9] * m[7] * m[14] +
            m[13] * m[6] * m[11] -
            m[13] * m[7] * m[10];
        inv[4] = -m[4] * m[10] * m[15] +
            m[4] * m[11] * m[14] +
            m[8] * m[6] * m[15] -
            m[8] * m[7] * m[14] -
            m[12] * m[6] * m[11] +
            m[12] * m[7] * m[10];
        inv[8] = m[4] * m[9] * m[15] -
            m[4] * m[11] * m[13] -
            m[8] * m[5] * m[15] +
            m[8] * m[7] * m[13] +
            m[12] * m[5] * m[11] -
            m[12] * m[7] * m[9];
        inv[12] = -m[4] * m[9] * m[14] +
            m[4] * m[10] * m[13] +
            m[8] * m[5] * m[14] -
            m[8] * m[6] * m[13] -
            m[12] * m[5] * m[10] +
            m[12] * m[6] * m[9];
        inv[1] = -m[1] * m[10] * m[15] +
            m[1] * m[11] * m[14] +
            m[9] * m[2] * m[15] -
            m[9] * m[3] * m[14] -
            m[13] * m[2] * m[11] +
            m[13] * m[3] * m[10];
        inv[5] = m[0] * m[10] * m[15] -
            m[0] * m[11] * m[14] -
            m[8] * m[2] * m[15] +
            m[8] * m[3] * m[14] +
            m[12] * m[2] * m[11] -
            m[12] * m[3] * m[10];
        inv[9] = -m[0] * m[9] * m[15] +
            m[0] * m[11] * m[13] +
            m[8] * m[1] * m[15] -
            m[8] * m[3] * m[13] -
            m[12] * m[1] * m[11] +
            m[12] * m[3] * m[9];
        inv[13] = m[0] * m[9] * m[14] -
            m[0] * m[10] * m[13] -
            m[8] * m[1] * m[14] +
            m[8] * m[2] * m[13] +
            m[12] * m[1] * m[10] -
            m[12] * m[2] * m[9];
        inv[2] = m[1] * m[6] * m[15] -
            m[1] * m[7] * m[14] -
            m[5] * m[2] * m[15] +
            m[5] * m[3] * m[14] +
            m[13] * m[2] * m[7] -
            m[13] * m[3] * m[6];
        inv[6] = -m[0] * m[6] * m[15] +
            m[0] * m[7] * m[14] +
            m[4] * m[2] * m[15] -
            m[4] * m[3] * m[14] -
            m[12] * m[2] * m[7] +
            m[12] * m[3] * m[6];
        inv[10] = m[0] * m[5] * m[15] -
            m[0] * m[7] * m[13] -
            m[4] * m[1] * m[15] +
            m[4] * m[3] * m[13] +
            m[12] * m[1] * m[7] -
            m[12] * m[3] * m[5];
        inv[14] = -m[0] * m[5] * m[14] +
            m[0] * m[6] * m[13] +
            m[4] * m[1] * m[14] -
            m[4] * m[2] * m[13] -
            m[12] * m[1] * m[6] +
            m[12] * m[2] * m[5];
        inv[3] = -m[1] * m[6] * m[11] +
            m[1] * m[7] * m[10] +
            m[5] * m[2] * m[11] -
            m[5] * m[3] * m[10] -
            m[9] * m[2] * m[7] +
            m[9] * m[3] * m[6];
        inv[7] = m[0] * m[6] * m[11] -
            m[0] * m[7] * m[10] -
            m[4] * m[2] * m[11] +
            m[4] * m[3] * m[10] +
            m[8] * m[2] * m[7] -
            m[8] * m[3] * m[6];
        inv[11] = -m[0] * m[5] * m[11] +
            m[0] * m[7] * m[9] +
            m[4] * m[1] * m[11] -
            m[4] * m[3] * m[9] -
            m[8] * m[1] * m[7] +
            m[8] * m[3] * m[5];
        inv[15] = m[0] * m[5] * m[10] -
            m[0] * m[6] * m[9] -
            m[4] * m[1] * m[10] +
            m[4] * m[2] * m[9] +
            m[8] * m[1] * m[6] -
            m[8] * m[2] * m[5];
        float det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];
        if (det == 0)
        {
            exit(0); // Perhaps add logging here. This should not happen in a games context
        }
        det = 1.0 / det;
        for (int i = 0; i < 16; i++)
        {
            inv[i] = inv[i] * det;
        }
        return inv;
    }
    static Matrix lookAt(const Vec3& from, const Vec3& to, const Vec3& up)
    {
        Matrix mat;
        Vec3 dir = (to - from).Normalize();
        Vec3 left = Cross(up, dir).Normalize();
        Vec3 newUp = Cross(dir, left);
        mat.a[0][0] = left.x;
        mat.a[0][1] = left.y;
        mat.a[0][2] = left.z;
        mat.a[1][0] = newUp.x;
        mat.a[1][1] = newUp.y;
        mat.a[1][2] = newUp.z;
        mat.a[2][0] = dir.x;
        mat.a[2][1] = dir.y;
        mat.a[2][2] = dir.z;
        mat.a[0][3] = -Dot(from, left);
        mat.a[1][3] = -Dot(from, newUp);
        mat.a[2][3] = -Dot(from, dir);
        mat.a[3][3] = 1;
        return mat;
    }
    static Matrix perspective(const float n, const float f, float aspect, const float fov) // FOV in degrees, outputs transposed Matrix for DX
    {
        Matrix pers;
        memset(pers.m, 0, sizeof(float) * 16);
        float t = 1.0f / (tanf(fov * 0.5f * 3.141592654f / 180.0f));
        pers.a[0][0] = t / aspect;
        pers.a[1][1] = t;
        pers.a[2][2] = f / (f - n);
        pers.a[2][3] = -(f * n) / (f - n);
        pers.a[3][2] = 1.0f;
        return pers;
    }
    static Matrix rotateAxis(const Vec3& axis, float angle)
    {
        Vec3 u = axis.Normalize();
        float c = cosf(angle);
        float s = sinf(angle);
        float t = 1.0f - c;

        return Matrix(
            t * u.x * u.x + c, t * u.x * u.y + s * u.z, t * u.x * u.z - s * u.y, 0,
            t * u.x * u.y - s * u.z, t * u.y * u.y + c, t * u.y * u.z + s * u.x, 0,
            t * u.x * u.z + s * u.y, t * u.y * u.z - s * u.x, t * u.z * u.z + c, 0,
            0, 0, 0, 1
        );
    }
    void Print() const {
        printf("Matrix:\n");
        for (int i = 0; i < 4; i++) {
            printf("| %.3f %.3f %.3f %.3f |\n", a[i][0], a[i][1], a[i][2], a[i][3]);
        }
    }
};

class Quaternion {
public:
    union {
        struct { float a, b, c, d; };  // a + bi + cj + dk
        float q[4];
    };

    Quaternion() : a(1), b(0), c(0), d(0) {}
    Quaternion(float a_, float b_, float c_, float d_) : a(a_), b(b_), c(c_), d(d_) {}
    Quaternion(const Quaternion& other) : a(other.a), b(other.b), c(other.c), d(other.d) {}

    Quaternion operator+(const Quaternion& other) const {
        return Quaternion(a + other.a, b + other.b, c + other.c, d + other.d);
    }

    Quaternion operator-(const Quaternion& other) const {
        return Quaternion(a - other.a, b - other.b, c - other.c, d - other.d);
    }

    Quaternion operator*(float scalar) const {
        return Quaternion(a * scalar, b * scalar, c * scalar, d * scalar);
    }
    Vec3 operator*(Vec3 dir) const {
        Quaternion qv(0, dir.x, dir.y, dir.z);
        Quaternion qr = (*this) * qv * this->Inverse();
        return Vec3(qr.b, qr.c, qr.d);
    }

    Quaternion operator*(const Quaternion& other) const {
        return Quaternion(
            a * other.a - b * other.b - c * other.c - d * other.d,
            a * other.b + b * other.a + c * other.d - d * other.c,
            a * other.c - b * other.d + c * other.a + d * other.b,
            a * other.d + b * other.c - c * other.b + d * other.a
        );
    }

    float Magnitude() const {
        return std::sqrt(a * a + b * b + c * c + d * d);
    }

    Quaternion Normalize() const {
        float mag = Magnitude();
        if (mag > 0) {
            float invMag = 1.0f / mag;
            return Quaternion(a * invMag, b * invMag, c * invMag, d * invMag);
        }
        return *this;
    }

    Quaternion& Normalize() {
        float mag = Magnitude();
        if (mag > 0) {
            float invMag = 1.0f / mag;
            a *= invMag; b *= invMag; c *= invMag; d *= invMag;
        }
        return *this;
    }

    Quaternion Conjugate() const {
        return Quaternion(a, -b, -c, -d);
    }

    Quaternion Inverse() const {
        float magSq = a * a + b * b + c * c + d * d;
        if (magSq > 0) {
            float invMagSq = 1.0f / magSq;
            return Quaternion(a * invMagSq, -b * invMagSq, -c * invMagSq, -d * invMagSq);
        }
        return *this;
    }

    static Quaternion angleAxisX(float theta) {
        float half = theta / 2.0f;
        return { std::cosf(half), std::sinf(half), 0.0f, 0.0f };
    }

    static Quaternion angleAxisY(float theta) {
        float half = theta / 2.0f;
        return { std::cosf(half), 0.0f, std::sinf(half), 0.0f };
    }

    static Quaternion angleAxisZ(float theta) {
        float half = theta / 2.0f;
        return { std::cosf(half), 0.0f, 0.0f, std::sinf(half) };
    }

    static Quaternion rotateByEulerAngles(const Quaternion& q, float tx, float ty, float tz) {
        return angleAxisZ(tz) * angleAxisY(ty) * angleAxisX(tx) * q;
    }
    static Quaternion FromAxisAngle(float angleDegrees, float axisX, float axisY, float axisZ) {
        float angleRad = angle_radians(angleDegrees);
        float halfAngle = angleRad * 0.5f;
        float sinHalf = sinf(halfAngle);

        Quaternion q;
        q.a = cosf(halfAngle);
        q.b = axisX * sinHalf;
        q.c = axisY * sinHalf;
        q.d = axisZ * sinHalf;
        return q.Normalize();
    }
    Vec3 front() {
        return (*this * Vec3(0, 0, 1)).Normalize();
    }
    Vec3 right() {
        return (*this * Vec3(1, 0, 0)).Normalize();
    }
    Vec3 up() {
        return (*this * Vec3(0, 1, 0)).Normalize();
    }
    static Quaternion FromAxisAngle(const Vec3& axis, float angle) {
        float angleRad = angle_radians(angle);
        float halfAngle = angleRad * 0.5f;
        float s = std::sin(halfAngle);
        Vec3 normAxis = axis.Normalize();
        return Quaternion(std::cos(halfAngle), normAxis.x * s, normAxis.y * s, normAxis.z * s);
    }
    static Quaternion FromEulerYXZ(float rotX, float rotY, float rotZ) {
        Quaternion qx = FromAxisAngle(rotX, 1.0f, 0.0f, 0.0f); 
        Quaternion qy = FromAxisAngle(rotY, 0.0f, 1.0f, 0.0f); 
        Quaternion qz = FromAxisAngle(rotZ, 0.0f, 0.0f, 1.0f); 
        return (qz * qx * qy).Normalize();
    }
    void rotateAboutAxis(Vec3 pt, float angle, Vec3 axis)
    {
        Quaternion q1, p, qinv;
        q1.a = sinf(0.5f * angle) * axis.x;
        q1.b = sinf(0.5f * angle) * axis.y;
        q1.c = sinf(0.5f * angle) * axis.z;
        q1.d = cosf(0.5f * angle);
        p.a = pt.x;
        p.b = pt.y;
        p.c = pt.z;
        p.d = 0;
        qinv = q1;
        qinv.Inverse();
        q1 = q1 * p;
        q1 = q1 * qinv;
        a = q1.a;
        b = q1.b;
        c = q1.c;
        d = q1.d;
    }

    static Quaternion Slerp(const Quaternion& q1, const Quaternion& q2, float t) {
        Quaternion qu1 = q1.Normalize();
        Quaternion qu2 = q2.Normalize();

        float dot = qu1.a * qu2.a + qu1.b * qu2.b + qu1.c * qu2.c + qu1.d * qu2.d;

        if (dot < 0) {
            dot = -dot;
            qu2 = qu2 * -1.0f;
        }

        const float DOT_THRESHOLD = 0.9995f;
        if (dot > DOT_THRESHOLD) {
            return (qu1 * (1.0f - t) + qu2 * t).Normalize();
        }

        float angle = std::acos(dot);
        float sinAngle = std::sin(angle);
        float factor1 = std::sin((1.0f - t) * angle) / sinAngle;
        float factor2 = std::sin(t * angle) / sinAngle;

        return (qu1 * factor1 + qu2 * factor2).Normalize();
    }

    Matrix toMatrix() const {
        float aa = a * a;
        float ab = a * b;
        float ac = a * c;
        float bb = b * b;
        float cc = c * c;
        float bc = b * c;
        float da = d * a;
        float db = d * b;
        float dc = d * c;
        Matrix matrix;
        matrix[0] = 1.0f - 2.0f * (bb + cc);
        matrix[1] = 2.0f * (ab - dc);
        matrix[2] = 2.0f * (ac + db);
        matrix[3] = 0.0;
        matrix[4] = 2.0f * (ab + dc);
        matrix[5] = 1.0f - 2.0f * (aa + cc);
        matrix[6] = 2.0f * (bc - da);
        matrix[7] = 0.0;
        matrix[8] = 2.0f * (ac - db);
        matrix[9] = 2.0f * (bc + da);
        matrix[10] = 1.0f - 2.0f * (aa + bb);
        matrix[11] = 0.0;
        matrix[12] = 0;
        matrix[13] = 0;
        matrix[14] = 0;
        matrix[15] = 1;
        return matrix;
    }
    Matrix toLMatrix() const {
        Quaternion q = Normalize();
        float aa = q.a * q.a, ab = q.a * q.b, ac = q.a * q.c, ad = q.a * q.d;
        float bb = q.b * q.b, bc = q.b * q.c, bd = q.b * q.d;
        float cc = q.c * q.c, cd = q.c * q.d;
        float dd = q.d * q.d;

        Matrix m;
        m.SetIdentity();

        m.m[0] = 1.0f - 2.0f * (bb + cc);
        m.m[5] = 1.0f - 2.0f * (aa + cc);
        m.m[10] = 1.0f - 2.0f * (aa + bb);

        m.m[1] = 2.0f * (ab + cd);
        m.m[2] = 2.0f * (ac - bd);
        m.m[4] = 2.0f * (ab - cd);
        m.m[6] = 2.0f * (bc + ad);
        m.m[8] = 2.0f * (ac + bd);
        m.m[9] = 2.0f * (bc - ad);

        return m;
    }

    Vec3 RotatePoint(const Vec3& point) const {
        Quaternion p(0, point.x, point.y, point.z);
        Quaternion rotated = (*this) * p * Conjugate();
        return Vec3(rotated.b, rotated.c, rotated.d);
    }
};

class Colour {
public:
    float r, g, b, a;

    Colour() : r(0), g(0), b(0), a(1) {}
    Colour(float r_, float g_, float b_, float a_ = 1.0f) : r(r_), g(g_), b(b_), a(a_) {}

    Colour(unsigned char r_, unsigned char g_, unsigned char b_, unsigned char a_ = 255) {
        r = r_ / 255.0f;
        g = g_ / 255.0f;
        b = b_ / 255.0f;
        a = a_ / 255.0f;
    }
    Colour(const Colour& c) {
        r = c.r;
        g = c.g;
        b = c.b;
        a = c.a;
    }

    Colour operator+(const Colour& colour) const {
        return Colour(r + colour.r, g + colour.g, b + colour.b, a + colour.a);
    }

    Colour operator-(const Colour& colour) const {
        return Colour(r - colour.r, g - colour.g, b - colour.b, a - colour.a);
    }

    Colour operator*(const Colour& colour) const {
        return Colour(r * colour.r, g * colour.g, b * colour.b, a * colour.a);
    }

    Colour operator*(float scalar) const {
        return Colour(r * scalar, g * scalar, b * scalar, a * scalar);
    }

    Colour operator/(float scalar) const {
        float inv = 1.0f / scalar;
        return Colour(r * inv, g * inv, b * inv, a * inv);
    }

    void Clamp() {
        r = MMax(0.0f, MMin(1.0f, r));
        g = MMax(0.0f, MMin(1.0f, g));
        b = MMax(0.0f, MMin(1.0f, b));
        a = MMax(0.0f, MMin(1.0f, a));
    }

    unsigned char R_UChar() const { return static_cast<unsigned char>(MMin(255.0f, r * 255.0f)); }
    unsigned char G_UChar() const { return static_cast<unsigned char>(MMin(255.0f, g * 255.0f)); }
    unsigned char B_UChar() const { return static_cast<unsigned char>(MMin(255.0f, b * 255.0f)); }
    unsigned char A_UChar() const { return static_cast<unsigned char>(MMin(255.0f, a * 255.0f)); }
};

class ShadingFrame {
public:
    Vec3 tangent;   // x
    Vec3 binormal;  // y
    Vec3 normal;    // z

public:
    ShadingFrame() : tangent(1, 0, 0), binormal(0, 1, 0), normal(0, 0, 1) {}

    explicit ShadingFrame(const Vec3& n) {
        normal = n.Normalize();

        Vec3 helper = (std::abs(normal.x) < 0.8f) ? Vec3(1, 0, 0) : Vec3(0, 1, 0);

        tangent = Vec3::Cross(helper, normal).Normalize();

        binormal = Vec3::Cross(normal, tangent).Normalize();
    }

    ShadingFrame(const Vec3& t, const Vec3& b, const Vec3& n)
        : tangent(t), binormal(b), normal(n) {
    }
    void fromVector(const Vec3& n)
    {
        // Gram-Schmit
        normal = n.Normalize();
        if (fabsf(normal.x) > fabsf(normal.y))
        {
            float l = 1.0f / sqrtf(normal.x * normal.x + normal.z * normal.z);
            tangent = Vec3(normal.z * l, 0.0f, -normal.x * l);
        }
        else
        {
            float l = 1.0f / sqrtf(normal.y * normal.y + normal.z * normal.z);
            tangent = Vec3(0, normal.z * l, -normal.y * l);
        }
        binormal = Cross(normal, tangent);
    }
    void fromVectorTangent(const Vec3& n, const Vec3& t)
    {
        normal = n.Normalize();
        tangent = t.Normalize();
        binormal = Cross(normal, tangent);
    }

    Vec3 GetTangent() const { return tangent; }
    Vec3 GetBinormal() const { return binormal; }
    Vec3 GetNormal() const { return normal; }

    Matrix ToMatrixGL() const {
        return Matrix(
            tangent.x, binormal.x, normal.x, 0,
            tangent.y, binormal.y, normal.y, 0,
            tangent.z, binormal.z, normal.z, 0,
            0, 0, 0, 1
        );
    }

    Vec3 WorldToLocal(const Vec3& worldVec) const {
        return Vec3(
            Dot(worldVec, tangent),
            Dot(worldVec, binormal),
            Dot(worldVec, normal)
        );
    }

    Vec3 LocalToWorld(const Vec3& localVec) const {
        return tangent * localVec.x + binormal * localVec.y + normal * localVec.z;
    }

    Matrix GetInverseMatrix() const {
        return ToMatrixGL().Transpose();
    }
};

class SphericalCoordinates {
public:
    float theta;
    float phi;
    float radius;

    SphericalCoordinates() : theta(0), phi(0), radius(1) {}
    SphericalCoordinates(float t, float p, float r = 1.0f) : theta(t), phi(p), radius(r) {}

    explicit SphericalCoordinates(const Vec3& cartesian) {
        radius = cartesian.Length();
        if (radius > 0) {
            float invRadius = 1.0f / radius;
            float x = cartesian.x * invRadius;
            float y = cartesian.y * invRadius;
            float z = cartesian.z * invRadius;

            theta = std::acos(MMax(-1.0f, MMin(1.0f, z)));
            phi = std::atan2(y, x);
        }
        else {
            theta = 0;
            phi = 0;
        }
    }

    Vec3 ToCartesian() const {
        float sinTheta = std::sin(theta);
        float cosTheta = std::cos(theta);
        float sinPhi = std::sin(phi);
        float cosPhi = std::cos(phi);

        return Vec3(
            radius * sinTheta * cosPhi,
            radius * sinTheta * sinPhi,
            radius * cosTheta
        );
    }

    void FromCartesianYUp(const Vec3& cartesian) {
        radius = cartesian.Length();
        if (radius > 0) {
            float invRadius = 1.0f / radius;
            float x = cartesian.x * invRadius;
            float y = cartesian.y * invRadius;
            float z = cartesian.z * invRadius;

            theta = std::acos(MMax(-1.0f, MMin(1.0f, y)));
            phi = std::atan2(z, x);
        }
        else {
            theta = 0;
            phi = 0;
        }
    }

    Vec3 ToCartesianYUp() const {
        float sinTheta = std::sin(theta);
        float cosTheta = std::cos(theta);
        float sinPhi = std::sin(phi);
        float cosPhi = std::cos(phi);

        return Vec3(
            radius * sinTheta * cosPhi,
            radius * cosTheta,
            radius * sinTheta * sinPhi
        );
    }
};


inline float distance(Vec2 v1, Vec2 v2) {
    return (v1 - v2).magnitude();
}
inline Vec2 direction(Vec2 position, Vec2 aim_position) {
    return (aim_position - position).Normalize();
}
inline float angle360X(Vec2 v) {
    float rad = std::atan2(v.y, v.x);
    if (rad < 0) {
        rad += 2 * PI;
    }
    return rad * 180.f / PI;
}
inline float angle360Y(Vec2 v) {
    float rad = std::atan2(v.y, v.x);
    if (rad - PI / 2 > 0) {
        rad = 2 * PI - (rad - PI / 2);
    }
    else
    {
        rad = PI / 2 - rad;
    }
    return rad * 180.f / PI - 90.f;
}
inline float randomRange(float min, float max) {
    static std::mt19937 gen{ std::random_device{}() };
    std::uniform_real_distribution<float> dist(min, max);
    return dist(gen);
}
inline int randomRangeint(int min, int max) {
    static std::mt19937 gen{ std::random_device{}() };
    std::uniform_int_distribution<int> dist(min, max - 1);
    return dist(gen);
}
inline Vec2 randomVec2d() {
    float angle = randomRange(0, 360);
    float radians = angle_radians(angle);
    float x = cosf(radians);
    float y = sinf(radians);
    return Vec2(x, y);
}
inline Vec2 rotateVec2d(Vec2 v, float angle) {
    Vec2 res;
    float radians = angle_radians(angle);
    float a = v.x;
    float b = v.y;
    res.x = a * cosf(radians) + b * sinf(radians);
    res.y = -a * sinf(radians) + b * cosf(radians);
    return res;
}
inline Vec2 randomVec2dInRange(Vec2 v, float angle) {
    float randomAngle = randomRange(-angle, angle);
    Vec2 res = rotateVec2d(v, randomAngle);
    return res;
}

inline Vec2 randomVec2dInRange(Vec2 v1, Vec2 v2) {
    float angle_1 = angle360X(v1);
    float angle_2 = angle360X(v2);
    if (angle_2 > angle_1) {
        return rotateVec2d(Vec2(right), randomRange(angle_1, angle_2));
    }
    else if (angle_2 < angle_1) {
        return rotateVec2d(Vec2(right), randomRange(angle_2, angle_1));
    }
    else {
        return v1.Normalize();
    }
}

inline bool randomRes(float probability) {
    if (randomRange(0, 1) <= probability) {
        return true;
    }
    else
    {
        return false;
    }
}
inline bool inArea(Vec2 point, Vec2 start, Vec2 end) {
    if (point.x >= start.x && point.x <= end.x && point.y <= start.y && point.y >= end.y) {
        return true;
    }
    if (point.x <= start.x && point.x >= end.x && point.y >= start.y && point.y <= end.y) {
        return true;
    }
    if (point.x >= start.x && point.x <= end.x && point.y >= start.y && point.y <= end.y) {
        return true;
    }
    if (point.x <= start.x && point.x >= end.x && point.y <= start.y && point.y >= end.y) {
        return true;
    }
    return false;
}
inline float Distance3(const Vec3& v1, const Vec3& v2) {
    return (v2 - v1).magnitude();
}
inline Vec3 Dir3(const Vec3& me, const Vec3& aim) {
    return (aim - me).Normalize();
}
inline Vec3 Vec2::Vec2toVec3(float z){
    return Vec3(x, y, z);
}

