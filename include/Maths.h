#pragma once

#include <raylib.h>
#include <box3d/types.h>
#include <glm/glm.hpp>
#include <glm/detail/type_quat.hpp>

using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat3;
using glm::mat4;
using glm::quat;

// ---------------------------------------------------------------------------
// Raylib <-> glm
// ---------------------------------------------------------------------------

inline Vector2 ToRaylib(const vec2 vec)
{
    return { vec.x, vec.y };
}

inline vec2 ToGlm(Vector2 vec)
{
    return { vec.x, vec.y };
}

inline Vector3 ToRaylib(const vec3 vec)
{
    return { vec.x, vec.y, vec.z };
}

inline vec3 ToGlm(Vector3 vec)
{
    return { vec.x, vec.y, vec.z };
}

inline Vector4 ToRaylib(const vec4 vec)
{
    return { vec.x, vec.y, vec.z, vec.w };
}

inline vec4 ToGlm(Vector4 vec)
{
    return { vec.x, vec.y, vec.z, vec.w };
}

inline Matrix ToRaylib(mat4 mat)
{
    return
    {
       mat[0].x, mat[0].y, mat[0].z, mat[0].w,
       mat[1].x, mat[1].y, mat[1].z, mat[1].w,
       mat[2].x, mat[2].y, mat[2].z, mat[2].w,
       mat[3].x, mat[3].y, mat[3].z, mat[3].w,
    };
}

inline mat4 ToGlm(Matrix mat)
{
    return
    {
       { mat.m0, mat.m1, mat.m2, mat.m3 },
       { mat.m4, mat.m5, mat.m6, mat.m7 },
       { mat.m8, mat.m9, mat.m10, mat.m11 },
       { mat.m12, mat.m13, mat.m14, mat.m15 }
    };
}

inline Quaternion ToRaylib(const quat quat)
{
    return { quat.x, quat.y, quat.z, quat.w };
}

// ---------------------------------------------------------------------------
// glm <-> box3d
// ---------------------------------------------------------------------------

inline b3Vec3 ToBox3d(const vec3 vec)
{
    return { vec.x, vec.y, vec.z };
}

inline vec3 ToGlm(b3Vec3 vec)
{
    return { vec.x, vec.y, vec.z };
}

inline b3Quat ToBox3d(const quat quat)
{
    return { { quat.x, quat.y, quat.z }, quat.w };
}

inline glm::quat ToGlm(b3Quat quat)
{
    return { quat.s, quat.v.x, quat.v.y, quat.v.z };
}

inline b3Matrix3 ToBox3d(const mat3& mat)
{
    return
    {
        { mat[0].x, mat[0].y, mat[0].z },
        { mat[1].x, mat[1].y, mat[1].z },
        { mat[2].x, mat[2].y, mat[2].z },
    };
}

inline mat3 ToGlm(b3Matrix3 mat)
{
    return
    {
        { mat.cx.x, mat.cx.y, mat.cx.z },
        { mat.cy.x, mat.cy.y, mat.cy.z },
        { mat.cz.x, mat.cz.y, mat.cz.z },
    };
}

// ---------------------------------------------------------------------------
// Raylib <-> box3d (direct, no glm round-trip)
// ---------------------------------------------------------------------------

inline Vector3 ToRaylib(const b3Vec3 vec)
{
    return { vec.x, vec.y, vec.z };
}

inline b3Vec3 ToBox3d(const Vector3 vec)
{
    return { vec.x, vec.y, vec.z };
}

inline Quaternion ToRaylib(const b3Quat quat)
{
    return { quat.v.x, quat.v.y, quat.v.z, quat.s };
}

inline b3Quat ToBox3d(const Quaternion quat)
{
    return { { quat.x, quat.y, quat.z }, quat.w };
}

// b3Matrix3 is a 3x3 (used for inertia tensors / rotation matrices), so it
// doesn't map onto raylib's 4x4 Matrix without deciding what to do with the
// extra row/column. This embeds it as a rotation with zero translation.
inline Matrix ToRaylib(const b3Matrix3& mat)
{
    return
    {
        mat.cx.x, mat.cy.x, mat.cz.x, 0.0f,
        mat.cx.y, mat.cy.y, mat.cz.y, 0.0f,
        mat.cx.z, mat.cy.z, mat.cz.z, 0.0f,
        0.0f,     0.0f,     0.0f,     1.0f,
    };
}

inline b3Matrix3 ToBox3d(const Matrix& mat)
{
    return
    {
        { mat.m0, mat.m1, mat.m2 },
        { mat.m4, mat.m5, mat.m6 },
        { mat.m8, mat.m9, mat.m10 },
    };
}