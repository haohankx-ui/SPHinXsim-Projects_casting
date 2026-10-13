#include "sphinxsys.h"
#include "riser_check.h"

namespace SPH
{

    BaseDynamics<Real>& addRiserCheck(
        EntityManager& config_manager, MainMethods& main_methods,
        FluidBody& fluid_body, const json& config)
    {
        const json& riser_config = config.at("riser_check");
        const std::string oriented_box_name =
            riser_config.at("oriented_box").get<std::string>();

        OrientedBox& oriented_box = config_manager.getEntity<OrientedBox>(oriented_box_name);

        auto& riser_check = fluid_body.addBodyPart<OrientedBoxByCell>(oriented_box);
        auto& riser_fluid_height = main_methods.addReduceDynamics<UpperFrontInAxisDirectionCK>(
                riser_check, "RiserFluidHeight");

        return riser_fluid_height;
    }

    } // namespace SPH