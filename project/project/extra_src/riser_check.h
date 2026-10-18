#ifndef RISER_CHECK_H
#define RISER_CHECK_H

#include "base_simulation_builder.h"
#include "fluid_dynamics_builder.h"

namespace SPH
{

    BaseDynamics<Real>& addRiserCheck(
        EntityManager& config_manager, MainMethods& main_methods,
        FluidBody& fluid_body, const json& config);

} // namespace SPH

#endif // RISER_CHECK_H