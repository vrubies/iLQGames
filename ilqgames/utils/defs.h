
#include <Eigen/Dense>

namespace ilqgames
{

  namespace constants
  {
    // Small number for use in approximate equality checking.
    static constexpr float kSmallNumber = 1e-4;

  } // namespace constants

  namespace types
  {

    using Point2d = Eigen::Vector2f;

  } // namespace types

  namespace utils
  {
    template <typename T>
    inline constexpr T sgn(T x, std::false_type is_signed)
    {
      return T(0) < x;
    }

    template <typename T>
    inline constexpr T sgn(T x, std::true_type is_signed)
    {
      return (T(0) < x) - (x < T(0));
    }

    template <typename T>
    inline constexpr T sgn(T x)
    {
      return sgn(x, std::is_signed<T>());
    }

    template <typename T>
    inline constexpr T signed_sqrt(T x)
    {
      return sgn(x) * std::sqrt(std::abs(x));
    }
  } // namespace utils

} // namespace ilqgames