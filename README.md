[![unlicense](https://img.shields.io/badge/Unlicense-%23373737)](https://unlicense.org/)
![Stage: alpha](https://img.shields.io/badge/-alpha-red)

# lina

**lina** is a lightweight, header-only linear algebra library built on top of [linalg](https://github.com/sgorsten/linalg/tree/v2.2) v2.2 by Sterling Orsten.
It's basically extending linalg with graphics / math helpers, aliases, and a configurable namespace.

### Features (non-exhaustive)

#### Type Aliases
- **Custom**: `vec2_t`–`vec4_t`, `vec2f`–`vec4f`, `vec2d`–`vec4d`, `vec2i`–`vec4i`, `vec2u`–`vec4u`, `mat2f`, `mat3f`, `mat3x4f`, `mat4x2f`, `mat4x3f`, `mat4f`, and `quat` (`vec4f`).
- **GLSL & Slang**: `vec2`–`vec4`, `ivec2`–`ivec4`, `uvec2`–`uvec4`, `dvec2`–`dvec4`, `mat3`/`mat4`/`mat3x3`/`mat3x4`/`mat4x4`, and Slang equivalents (`float2`–`float4`, `float2x2`–`float4x4`, `int2`–`int4`, `uint2`–`uint4`, `double2`–`double4`).

#### Constants
- `kTrueEpsilon`, `kEpsilon`, `kHalfLog`, `kQuarterPi`, `kHalfPi`, `kPi`, `kTwoPi`, `kInvPi`, `kSqrtTwo`, `kHalfSqrtTwo`.

#### Transforms, Quaternions & Matrices
- **Construction & decomposition**: `transform_matrix()`, `decompose_transform_from_matrix()`, `quat_from_basis()`, `remove_translation()`, `look_dir_matrix()`, `row_mul()`, `normalize_plane()`.
- **Axes & projections**: `rotation_matrix_axis()`, `rotation_matrix_x/y/z()`, `translation_matrix_x/y/z()`, `frustum_tan_fov_matrix()`, `perspective_fov_matrix()`, `rigidbody_inverse()`.
- **Quaternions & dual quaternions**: `qlerp()`, `any_perpendicular()`, `shortest_arc()`, `dual_quat` / `dualquat`, `dual_quat_from_rt()`, `dual_quat_from_matrix()`, `dual_quat_translation()`, `dual_quat_transform_point()`.

#### Interpolation, Curves & Color
- **Curves & shaping**: `saturate()`, `step()`, `smoothstep()`, `trilerp()`, `stepcurve()`, `bias()`, `gain()`, `quadratic_bezier()`, `cubic_bezier()`.
- **sRGB / linear**: `to_srgb_channel()`, `to_linear_channel()`, `to_srgb()`, `to_linear()`.

#### General Utilities & Streaming
- **Data access & casts**: `ptr()`, `as()`.
- **Conversions**: `to_vec2()`, `to_vec3()`, `to_vec4()`, `to_mat3()`, `to_mat3x4()`, `to_mat4()`.
- **Math & comparisons**: `degrees()`, `radians()`, `min4()`, `max4()`, `almost_equal()`, `sign()`.
- **Streaming**: `operator<<` for `vec` and `mat` when `LINA_OSTREAM` is defined.

### Configuration Macros

- `LINA_USE_DOUBLE_PRECISION` — sets `LINA_FP` to `double` instead of `float`.
- `LINA_NAMESPACE` — customizes the namespace (defaults to `lina`).
- `LINA_NO_NAMESPACE` — places types and helpers in an anonymous namespace instead.
- `LINA_DEFINE_ALIASES_GLSL` / `LINA_DEFINE_ALIASES_SLANG` — toggles GLSL and Slang type aliases.
- `LINA_OSTREAM` — includes `<iostream>` and enables `operator<<` for vectors and matrices.
  
## Unlicense

**lina** is released under The Unlicense.
