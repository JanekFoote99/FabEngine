#pragma once
#include <glm/glm.hpp>
#include <stdint.h>

namespace fabTypes
{
  typedef int8_t i8;
  typedef int16_t i16;
  typedef int32_t i32;
  typedef int64_t i64;

  typedef uint8_t ui8;
  typedef uint16_t ui16;
  typedef uint32_t ui32;
  typedef uint64_t ui64;

  typedef glm::f32 f32;
  typedef glm::f64 f64;

  typedef glm::vec1 f32v1;
  typedef glm::vec2 f32v2;
  typedef glm::vec3 f32v3;
  typedef glm::vec4 f32v4;

  typedef glm::mat2 f32m2;
  typedef glm::mat3 f32m3;
  typedef glm::mat4 f32m4;

  typedef glm::mediump_mat2 f64m2;
  typedef glm::mediump_dmat3 f64m3;
  typedef glm::mediump_dmat4 f64m4;
}