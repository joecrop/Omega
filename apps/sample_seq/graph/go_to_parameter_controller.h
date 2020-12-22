#ifndef SAMPLE_GO_TO_PARAMETER_CONTROLLER_H
#define SAMPLE_GO_TO_PARAMETER_CONTROLLER_H

#include "../../shared/function_go_to_parameter_controller.h"

namespace Sample
{

  class GoToParameterController : public Shared::FunctionGoToParameterController
  {
  public:
    using Shared::FunctionGoToParameterController::FunctionGoToParameterController;

  private:
    bool setParameterAtIndex(int parameterIndex, double f) override;
  };

} // namespace Sample

#endif
