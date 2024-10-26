# lina

**lina** is a lightweight & header only linear algebra library built as an extension to [linalg](https://github.com/sgorsten/linalg/tree/v2.1) v2.2 from Sterling Orsten.
It's basically linalg with extra steps and a different namespace.

_(still wip)_

## Features

### 1. Custom Aliases
   - Defines 2D, 3D, and 4D vector types (`vec2`, `vec3`, `vec4`) and matrices (`mat3f`, `mat4f`) using both floating-point and integer types.
   - Includes common shorthand types like `vec2f`, `vec3i`, `vec4u`, etc., for convenience.

### 2. Mathematical Constants
   - Predefined constants: `kTwoPi`, `kPi`, `kHalfPi`, `kQuarterPi`, `kInvPi`, `kHalfLog`, `kEpsilon`.

### 3. Utility Functions
   - **Angle Conversion**: Functions for converting between degrees and radians (`degrees()`, `radians()`).
   - **Min/Max**: Utility functions for finding minimum and maximum values among four inputs (`min4()`, `max4()`).
   - **Comparisons**: `almost_equal()` to check near-equality for floating-point values.

### 4. Signal Processing Functions
   - `saturate()` to clamp values between 0 and 1.
   - `step()` for threshold-based interpolation.
   - `trilerp()` for two-stage interpolation.
   - `stepcurve()` for a pyramid-based curve.
   - `bias()` and `gain()` for smoother transitions with customizable dynamics.

### 5. Matrix Utility Functions
   - `frustum_tan_fov_matrix()` and `perspective_fov_matrix()` for generating projection matrices with customized frustums.
   - `rigidbody_inverse()` for efficient inversion of rigid-body transformation matrices.

### 6. Streaming Support
   - Operators for outputting vectors and matrices to `std::ostream`.

## License

**lina** is released under The Unlicense.