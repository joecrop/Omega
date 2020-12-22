#ifndef SAMPLE_CURVE_VIEW_RANGE_H
#define SAMPLE_CURVE_VIEW_RANGE_H

#include "../../shared/interactive_curve_view_range.h"

namespace Sample
{

  class CurveViewRange : public Shared::InteractiveCurveViewRange
  {
  public:
    CurveViewRange(Shared::InteractiveCurveViewRangeDelegate *delegate = nullptr);
    void roundAbscissa() override;
    void normalize() override;
    void setTrigonometric() override;
    void setDefault() override;

  private:
    constexpr static float k_displayLeftMarginRatio = 0.1f;
  };

} // namespace Sample

#endif
