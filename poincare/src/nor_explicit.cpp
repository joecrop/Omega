#include <poincare/nor_explicit.h>
#include <poincare/layout_helper.h>
#include <poincare/serialization_helper.h>
#include <poincare/undefined.h>
#include <poincare/rational.h>
#include <poincare/based_integer.h>
#include <cmath>

namespace Poincare
{

  constexpr Expression::FunctionHelper NorExplicit::s_functionHelper;

  int NorExplicitNode::numberOfChildren() const { return NorExplicit::s_functionHelper.numberOfChildren(); }

  Layout NorExplicitNode::createLayout(Preferences::PrintFloatMode floatDisplayMode, int numberOfSignificantDigits) const
  {
    return LayoutHelper::Prefix(NorExplicit(this), floatDisplayMode, numberOfSignificantDigits, NorExplicit::s_functionHelper.name());
  }

  int NorExplicitNode::serialize(char *buffer, int bufferSize, Preferences::PrintFloatMode floatDisplayMode, int numberOfSignificantDigits) const
  {
    return SerializationHelper::Prefix(this, buffer, bufferSize, floatDisplayMode, numberOfSignificantDigits, NorExplicit::s_functionHelper.name());
  }

  Expression NorExplicitNode::shallowReduce(ReductionContext reductionContext)
  {
    return NorExplicit(this).shallowReduce(reductionContext);
  }

  template <typename T>
  Complex<T> NorExplicitNode::computeOnComplex(const std::complex<T> c, Preferences::ComplexFormat, Preferences::AngleUnit angleUnit)
  {
    if (c.imag() != 0)
    {
      return Complex<T>::RealUndefined();
    }
    return Complex<T>::Builder(c.real() - std::floor(c.real()));
  }

  Expression NorExplicit::shallowReduce(ExpressionNode::ReductionContext reductionContext)
  {
    {
      Expression e = Expression::defaultShallowReduce();
      e = e.defaultHandleUnitsInChildren();
      if (e.isUndefined())
      {
        return e;
      }
    }
    Expression a = childAtIndex(0);
    Expression b = childAtIndex(1);
    Expression c = childAtIndex(2);

    if (a.type() == ExpressionNode::Type::Matrix)
    {
      return mapOnMatrixFirstChild(reductionContext);
    }

    if (a.type() != ExpressionNode::Type::Rational)
    {
      return Undefined::Builder();
    }
    if (b.type() != ExpressionNode::Type::Rational)
    {
      return Undefined::Builder();
    }
    if (c.type() != ExpressionNode::Type::Rational)
    {
      return Undefined::Builder();
    }
    Rational ar = static_cast<Rational &>(a);
    Rational br = static_cast<Rational &>(b);
    Rational cr = static_cast<Rational &>(c);
    if (!ar.integerDenominator().isOne())
    {
      return Undefined::Builder();
    }
    if (!br.integerDenominator().isOne())
    {
      return Undefined::Builder();
    }
    if (!cr.integerDenominator().isOne())
    {
      return Undefined::Builder();
    }

    if (ar.signedIntegerNumerator().isNegative())
    {
      return Undefined::Builder();
    }
    if (br.signedIntegerNumerator().isNegative())
    {
      return Undefined::Builder();
    }
    if (cr.signedIntegerNumerator().isNegative())
    {
      return Undefined::Builder();
    }

    Integer aq = ar.signedIntegerNumerator();
    Integer bq = br.signedIntegerNumerator();
    Integer cq = cr.signedIntegerNumerator();
    Integer x = Integer::Nor(aq, bq, cq);
    Expression result = Rational::Builder(x);
    replaceWithInPlace(result);
    return result.shallowReduce(reductionContext);
  }

} // namespace Poincare
