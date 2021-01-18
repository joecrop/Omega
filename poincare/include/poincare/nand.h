#ifndef POINCARE_NAND_H
#define POINCARE_NAND_H

#include <poincare/approximation_helper.h>
#include <poincare/expression.h>

namespace Poincare
{

  class NandNode final : public ExpressionNode
  {
  public:
    // TreeNode
    size_t size() const override { return sizeof(NandNode); }
    int numberOfChildren() const override;
#if POINCARE_TREE_LOG
    void logNodeName(std::ostream &stream) const override
    {
      stream << "Nand";
    }
#endif

    // Properties
    Type type() const override { return Type::Nand; }

  private:
    // Layout
    Layout createLayout(Preferences::PrintFloatMode floatDisplayMode, int numberOfSignificantDigits) const override;
    int serialize(char *buffer, int bufferSize, Preferences::PrintFloatMode floatDisplayMode, int numberOfSignificantDigits) const override;
    // Simplification
    Expression shallowReduce(ReductionContext reductionContext) override;
    LayoutShape leftLayoutShape() const override { return LayoutShape::MoreLetters; };
    LayoutShape rightLayoutShape() const override { return LayoutShape::BoundaryPunctuation; }

    // Evaluation
    template <typename T>
    static Complex<T> computeOnComplex(const std::complex<T> c, Preferences::ComplexFormat complexFormat, Preferences::AngleUnit angleUnit);
    Evaluation<float> approximate(SinglePrecision p, Context *context, Preferences::ComplexFormat complexFormat, Preferences::AngleUnit angleUnit) const override
    {
      return ApproximationHelper::Map<float>(this, context, complexFormat, angleUnit, computeOnComplex<float>);
    }
    Evaluation<double> approximate(DoublePrecision p, Context *context, Preferences::ComplexFormat complexFormat, Preferences::AngleUnit angleUnit) const override
    {
      return ApproximationHelper::Map<double>(this, context, complexFormat, angleUnit, computeOnComplex<double>);
    }
  };

  class Nand final : public Expression
  {
  public:
    Nand(const NandNode *n) : Expression(n) {}
    static Nand Builder(Expression child1, Expression child2) { return TreeHandle::FixedArityBuilder<Nand, NandNode>({child1, child2}); }

    static constexpr Expression::FunctionHelper s_functionHelper = Expression::FunctionHelper("nand", 2, &UntypedBuilderTwoChildren<Nand>);

    Expression shallowReduce(ExpressionNode::ReductionContext reductionContext);
  };

} // namespace Poincare

#endif
