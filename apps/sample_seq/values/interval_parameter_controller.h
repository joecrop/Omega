#ifndef SAMPLE_INTERVAL_PARAM_CONTROLLER_H
#define SAMPLE_INTERVAL_PARAM_CONTROLLER_H

#include "../../shared/interval_parameter_controller.h"

namespace Sample
{

  class IntervalParameterController : public Shared::IntervalParameterController
  {
  public:
    using Shared::IntervalParameterController::IntervalParameterController;
    bool setParameterAtIndex(int parameterIndex, double f) override;
  };

} // namespace Sample

#endif
