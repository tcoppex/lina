#ifndef LINA_LINA_H_
#define LINA_LINA_H_

/* -------------------------------------------------------------------------- */

#ifndef _MSC_VER
#define _MSC_VER 1901
#define UNDEF_MSC_VER
#endif

#include "linalg/linalg.h" // v2.2
using namespace linalg::aliases;

#ifdef UNDEF_MSC_VER
#undef _MSC_VER
#undef UNDEF_MSC_VER
#endif

#include <limits>

/* -------------------------------------------------------------------------- */

#ifdef LINA_NO_NAMESPACE
#define BEGIN_LINA_NAMESPACE  namespace {
#define END_LINA_NAMESPACE    }
#else
#ifndef LINA_NAMESPACE
#define LINA_NAMESPACE lina
#endif
#define BEGIN_LINA_NAMESPACE  namespace LINA_NAMESPACE {
#define END_LINA_NAMESPACE    }
#endif

/* -------------------------------------------------------------------------- */

#ifdef LINA_USE_DOUBLE_PRECISION
#define LINA_FP double
#else
#define LINA_FP float
#endif

/* -------------------------------------------------------------------------- */

BEGIN_LINA_NAMESPACE

//
// Aliases.
//
namespace aliases {

template<class T> using vec2 = linalg::vec<T,2>;
template<class T> using vec3 = linalg::vec<T,3>;
template<class T> using vec4 = linalg::vec<T,4>;

using vec2f = vec2<LINA_FP>;
using vec3f = vec3<LINA_FP>;
using vec4f = vec4<LINA_FP>;
using mat3f = linalg::mat<LINA_FP, 3, 3>;
using mat4f = linalg::mat<LINA_FP, 4, 4>;
// using mat3x3f = mat3f;
// using mat4x4f = mat4f;

using vec2i = vec2<int32_t>;
using vec3i = vec3<int32_t>;
using vec4i = vec4<int32_t>;

using vec2u = vec2<uint32_t>;
using vec3u = vec3<uint32_t>;
using vec4u = vec4<uint32_t>;

}

//
// Constants.
//
constexpr LINA_FP kEpsilon      = std::numeric_limits<LINA_FP>::epsilon();
constexpr LINA_FP kHalfLog      = -0.693147180599;  // log(0.5);
constexpr LINA_FP kQuarterPi    = 0.785398163397;   // atanf(1.0f);
constexpr LINA_FP kHalfPi       = 2.0 * kQuarterPi;
constexpr LINA_FP kPi           = 4.0 * kQuarterPi;
constexpr LINA_FP kTwoPi        = 8.0 * kQuarterPi;
constexpr LINA_FP kInvPi        = 1.0 / kPi;

//
// Functions.
//
template<typename T>
inline constexpr T degrees(T const& _radians) { return _radians * (180.0 / kPi); }

template<typename T>
inline constexpr T radians(T const& _degrees) { return _degrees * (kPi / 180.0); }

template<typename T>
inline constexpr T min4(T const& a, T const& b, T const& c, T const& d) {
  return min( a, min( b, min( c, d)));
}

template<typename T>
inline constexpr T max4(T const& a, T const& b, T const& c, T const& d) {
  return max( a, max( b, max( c, d)));
}

template<typename T>
constexpr bool almost_equal(T const& a, T const& b) {
  static_assert( std::is_floating_point<T>::value );
  T const distance = linalg::abs(b - a);
  return (distance < std::numeric_limits<T>::epsilon())
      || (distance < (std::numeric_limits<T>::min() * linalg::abs(b + a)));
}

template<typename T>
constexpr T saturate(T const& a) {
  static_assert( std::is_floating_point<T>::value );
  return clamp(a, 0, 1);
}

// ----------------------------------------------------------------------------

template<typename T>
constexpr T step(T const& a, T const& x) {
  static_assert( std::is_floating_point<T>::value );
  return static_cast<T>(select(a > x, 0, 1));
}

// Interpolate in two steps. ([0, 0.5, 1.0]->[a, b, c])
template<typename T>
constexpr T trilerp(T const& a, T const& b, T const& c, T const& x) {
  static_assert( std::is_floating_point<T>::value );
  T l1 = a + 2 * x * (b - a);
  T l2 = b + 2 * (x - 1) * (c - b);
  return lerp(l1, l2, step(0.5, x));
}

// Interpolate following a pyramid curve. ([0, 0.5, 1.0]->[a, b, a])
template<typename T>
constexpr T stepcurve(T const& a, T const& b, T const& x) {
  static_assert( std::is_floating_point<T>::value );
  return lerp(a, b, 1-abs(2*x-1));
}

// Adjust interpolation dynamics for a and b, clamping near boundaries for smooth transitions.
template<typename T>
constexpr T bias(T const& a, T const& b) {
  static_assert( std::is_floating_point<T>::value );
  if (a < kEpsilon || b < kEpsilon) {
    return 0.0;
  }
  if (a > (1.0-kEpsilon) || b > (1.0-kEpsilon)) {
    return 1.0;
  }
  return pow(a, log(b) / kHalfLog);
}

template<typename T>
constexpr T gain(T const& a, T const& b) {
  static_assert( std::is_floating_point<T>::value );
  if (a < kEpsilon) {
    return 0.0;
  }
  if (a > (1.0-kEpsilon)) {
    return 1.0;
  }
  const T bb = clamp(b, kEpsilon, 1.0 - kEpsilon);
  const T e = log(1.0-bb) / kHalfLog;
  auto f = [e](auto x) { return pow(2.0 * x, e) / 2.0; };
  return (a < 0.5) ? f(a) : 1.0 - f(1.0 - a);

  // equivalent to :
  //return lerp(f(a), 1.0-f(1.0-a), step(0.5, a));
  // (note : when using a smoothstep instead we obtain an elastic effect).
}

// ----------------------------------------------------------------------------

// The far plane is placed at infinity if farZ <= nearZ, better for far off objects.
// https://github.com/KhronosGroup/OpenXR-SDK-Source/blob/b15ef6ce120dad1c7d3ff57039e73ba1a9f17102/src/common/xr_linear.h#L564
template<class T>
linalg::mat<T,4,4> frustum_tan_fov_matrix(T l, T r, T d, T u, T n, T f, linalg::fwd_axis a, linalg::z_range z)
{
  const T s = a == linalg::pos_z ? T(1) : T(-1),
          o = z == linalg::neg_one_to_one ? n : 0,
          zz = (f<=n) ? T(-1) : (f+o)/(n-f),
          zw = (f<=n) ? -(n+o) : (f*(n+o))/(n-f);
  const T w = T(1)/(r-l);
  const T h = T(1)/(u-d);
  return {{2*w,0,0,0},{0,2*h,0,0},{(r+l)*w,(u+d)*h,zz,s},{0,0,zw,0}};
}

template<class T>
linalg::mat<T,4,4> perspective_fov_matrix(T angleLeft, T angleRight, T angleDown, T angleUp, T n, T f, linalg::fwd_axis a = linalg::neg_z, linalg::z_range z = linalg::neg_one_to_one) {
  return lina::frustum_tan_fov_matrix(std::tan(angleLeft), std::tan(angleRight), std::tan(angleDown), std::tan(angleUp), n, f, a, z);
}

template <class T>
constexpr linalg::mat<T, 4, 4> rigidbody_inverse(const linalg::mat<T, 4, 4>& a) {
  auto rt = linalg::transpose(linalg::mat<T, 3, 3>{
    {a[0][0], a[0][1], a[0][2]},
    {a[1][0], a[1][1], a[1][2]},
    {a[2][0], a[2][1], a[2][2]}
  });
  auto inv_t = - linalg::mul(rt, linalg::vec<T, 3>{ a[0][3], a[1][3], a[2][3] });
  return linalg::mat<T, 4, 4>{
    {rt[0][0], rt[0][1], rt[0][2], inv_t[0]},
    {rt[1][0], rt[1][1], rt[1][2], inv_t[1]},
    {rt[2][0], rt[2][1], rt[2][2], inv_t[2]},
    {0.0, 0.0, 0.0, 1.0}
  };
}

// ----------------------------------------------------------------------------

#if 0
template<typename T>
bool solve_basic_ik(T const lenA, T const lenB, const linalg::vec<T, 3>& target, const linalg::vec<T, 3>& targetUp, linalg::vec<T, 3>& _outIK) {
    T const lenA2 = lenA * lenA;
    T const lenB2 = lenB * lenB;

    linalg::vec<T, 3> normalizedTarget = normalize(target);
    T const lenTarget = length(normalizedTarget);

    if (lenTarget < kEpsilon) {
      return false;
    }

    linalg::mat<T, 3, 3> Minv;
    Minv[0] = normalizedTarget;
    linalg::vec<T, 3> y_axis = normalize(targetUp - dot(targetUp, Minv[0]) * Minv[0]);
    Minv[1] = y_axis;
    Minv[2] = cross(Minv[0], y_axis);

    linalg::vec<T, 3> R = mul(Minv, target);
    T const lenR = length(R);

    if (lenR < kEpsilon) {
      return false;
    }

    linalg::vec<T, 3> S;
    S.x = clamp(0.5 * (lenR + (lenA2 - lenB2) / lenR), 0.0, (1.0 - kEpsilon) * lenA);

    T const ySquared = lenA2 - S.x * S.x;
    if (ySquared < 0.0) {
      return false;
    }
    S.y = sqrt(ySquared);
    S.z = 0;

    _outIK = mul(Minv, S);

    return S.x > 0.0;
}
#endif

// ----------------------------------------------------------------------------

END_LINA_NAMESPACE

/* -------------------------------------------------------------------------- */

//
// Types interoperability.
//

#if defined(__cpp_lib_ios)

template<typename T> std::ostream &operator<<(std::ostream& o, linalg::vec<T,2> const& v) {
  return o << "(" << v.x << ", " << v.y << ")";
}

template<typename T> std::ostream &operator<<(std::ostream& o, linalg::vec<T,3> const& v) {
  return o << '(' << v.x << ", " << v.y << ", " << v.z << ')';
}

template<typename T> std::ostream &operator<<(std::ostream& o, linalg::vec<T,4> const& v) {
  return o << '(' << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ')';
}

template<typename T, int N> std::ostream &operator<<(std::ostream& o, linalg::mat<T,2,N> const& m) {
  return o << m.row(0) << std::endl
           << m.row(1);
}

template<typename T, int N> std::ostream &operator<<(std::ostream& o, linalg::mat<T,3,N> const& m) {
  return o << m.row(0) << std::endl
           << m.row(1) << std::endl
           << m.row(2);
}

template<typename T, int N> std::ostream &operator<<(std::ostream& o, linalg::mat<T,4,N> const& m) {
  return o << m.row(0) << std::endl
           << m.row(1) << std::endl
           << m.row(2) << std::endl
           << m.row(3);
}

#endif

/* -------------------------------------------------------------------------- */

#endif  // LINA_LINA_H_ 