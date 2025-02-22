[![unlicense](https://img.shields.io/badge/Unlicense-%23373737)](https://unlicense.org/)
![Stage: alpha](https://img.shields.io/badge/-alpha-red)

# lina

**lina** is a lightweight & header only linear algebra library built as an extension to [linalg](https://github.com/sgorsten/linalg/tree/v2.2) v2.2 from Sterling Orsten.
It's basically linalg with extra steps and a different namespace.

_(still wip)_

### Features

#### Custom Aliases
   - Defines 2D, 3D, and 4D vector types (`vec2`, `vec3`, `vec4`) and matrices (`mat3f`, `mat4f`) using both floating-point and integer types.
   - Includes common shorthand types like `vec2f`, `vec3i`, `vec4u`, etc., for convenience.

#### Mathematical Constants
   - Predefined constants: `kTwoPi`, `kPi`, `kHalfPi`, `kQuarterPi`, `kInvPi`, `kHalfLog`, `kEpsilon`.

#### Utility Functions
   - **Pointer accessor**: Function to access data memory address (`ptr()`).
   - **Vector / Matrix Conversion**: Functions for converting to lower dimensions structure (`to_vec2()`, `to_vec3()`, `to_mat3()`). 
   - **Angle Conversion**: Functions for converting between degrees and radians (`degrees()`, `radians()`).
   - **Min/Max**: Utility functions for finding minimum and maximum values among four inputs (`min4()`, `max4()`).
   - **Comparisons**: `almost_equal()` to check near-equality for floating-point values.

#### Signal Processing Functions
   - `saturate()` to clamp values between 0 and 1.
   - `step()` for threshold-based interpolation.
   - `trilerp()` for two-stage interpolation.
   - `stepcurve()` for a pyramid-based curve.
   - `bias()` and `gain()` for smoother transitions with customizable dynamics.

#### Matrix Utility Functions
   - `frustum_tan_fov_matrix()` and `perspective_fov_matrix()` for generating projection matrices with customized frustums.
   - `rigidbody_inverse()` for efficient inversion of rigid-body transformation matrices.

#### Streaming Support
   - Operators for outputting vectors and matrices to `std::ostream`.

## Unlicense

**lina** is released under The Unlicense.
