/*
 *  Created by Martin on 07/11/2017.
 *
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef TWOBLUECUBES_CATCH_MATCHERS_FLOATING_H_INCLUDED
#define TWOBLUECUBES_CATCH_MATCHERS_FLOATING_H_INCLUDED

#include <catch2/matchers/catch_matchers.hpp>

namespace Catch {
namespace Matchers {

    namespace Detail {
        enum class FloatingPointKind : uint8_t;
    }

    struct WithinAbsMatcher final : MatcherBase<double> {
        WithinAbsMatcher(double target, double margin);
        bool match(double const& matchee) const override;
        std::string describe() const override;
    private:
        double m_target;
        double m_margin;
    };

    struct WithinUlpsMatcher final : MatcherBase<double> {
        WithinUlpsMatcher(double target, uint64_t ulps, Detail::FloatingPointKind baseType);
        bool match(double const& matchee) const override;
        std::string describe() const override;
    private:
        double m_target;
        uint64_t m_ulps;
        Detail::FloatingPointKind m_type;
    };

    // Given IEEE-754 format for floats and doubles, we can assume
    // that float -> double promotion is lossless. Given this, we can
    // assume that if we do the standard relative comparison of
    // |lhs - rhs| <= epsilon * max(fabs(lhs), fabs(rhs)), then we get
    // the same result if we do this for floats, as if we do this for
    // doubles that were promoted from floats.
    struct WithinRelMatcher final : MatcherBase<double> {
        WithinRelMatcher(double target, double epsilon);
        bool match(double const& matchee) const override;
        std::string describe() const override;
    private:
        double m_target;
        double m_epsilon;
    };

    //! Creates a matcher that accepts doubles within certain ULP range of target
    WithinUlpsMatcher WithinULP(double target, uint64_t maxUlpDiff);
    //! Creates a matcher that accepts floats within certain ULP range of target
    WithinUlpsMatcher WithinULP(float target, uint64_t maxUlpDiff);
    //! Creates a matcher that accepts numbers within certain range of target
    WithinAbsMatcher WithinAbs(double target, double margin);

    //! Creates a matcher that accepts doubles within certain relative range of target
    WithinRelMatcher WithinRel(double target, double eps);
    //! Creates a matcher that accepts doubles within 100*DBL_EPS relative range of target
    WithinRelMatcher WithinRel(double target);
    //! Creates a matcher that accepts doubles within certain relative range of target
    WithinRelMatcher WithinRel(float target, float eps);
    //! Creates a matcher that accepts floats within 100*FLT_EPS relative range of target
    WithinRelMatcher WithinRel(float target);

} // namespace Matchers
} // namespace Catch

#endif // TWOBLUECUBES_CATCH_MATCHERS_FLOATING_H_INCLUDED