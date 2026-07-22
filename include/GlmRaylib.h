#pragma once

#include <raylib.h>
#include <glm/glm.hpp>
#include <glm/detail/type_quat.hpp>

using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat4;
using glm::quat;

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