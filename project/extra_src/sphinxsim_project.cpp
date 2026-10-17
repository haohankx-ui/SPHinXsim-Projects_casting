#include "sphinxsys.h"
#include "sphinxsim_project.h"
#include "riser_check.h"

#include <iostream>
namespace SPH
{
//=================================================================================================//
bool addExtraMaterial(EntityManager &config_manager, SPHBody &sph_body,
                      const json &config, const std::string &type)
{
    return false;
}
//=================================================================================================//
void addExtraEmitterFeatures(
    EntityManager &config_manager, MainMethods &main_methods,
    FluidBody &fluid_body, FluidSolverConfig &fluid_solver_config,
    StagePipeline<SimulationHookPoint> &simulation_pipeline,
    const json &config)
{
    if (config.contains("riser_check"))
    {
        const json &riser_config = config.at("riser_check");
        auto &riser_fluid_height = addRiserCheck(config_manager, main_methods,fluid_body,config);
        auto &scaling_config = config_manager.getEntity<ScalingConfig>("ScalingConfig");
        auto *sv_physical_time = &fluid_body.getSPHSystem().svPhysicalTime();
        auto *sv_riser_lower_triggertime =fluid_body.getSPHSystem().registerSystemVariable<Real>(
                "RiserLowerTriggertime", -1.0);
        Real riser_top_height =scaling_config.jsonToReal(
                riser_config.at("riser_top_height"),
                "Length");
        Real riser_bottom_height = scaling_config.jsonToReal(
                riser_config.at("riser_bottom_height"),
                "Length");

        simulation_pipeline.insert_hook(
            SimulationHookPoint::AfterUpdateConfiguration,
            [&riser_fluid_height,
             &fluid_solver_config,
             sv_riser_lower_triggertime,
             sv_physical_time,
             riser_bottom_height,
             riser_top_height]()
            {
                Real current_height = riser_fluid_height.exec();
               
                if (sv_riser_lower_triggertime->getValue() < 0.0 &&
                    current_height >= riser_bottom_height)
                {
                    sv_riser_lower_triggertime->setValue(
                        sv_physical_time->getValue());
                }
                if (fluid_solver_config.emitter_on_ &&
                    current_height >= riser_top_height)
                {
                    fluid_solver_config.emitter_on_ = false;

                    std::cerr << "Emitter stopped." << std::endl;
                }
            });
    }
}
//=================================================================================================//
void addExtraInflowSpeed(
    EntityManager &config_manager, MainMethods &main_methods, FluidBody &fluid_body,
    OrientedBoxByParticle &emitter, ParticleDynamicsGroup &inflow_condition,const json &config)
{
    const json &speed_config = config.at("casting_speed");
    auto &scaling_config = config_manager.getEntity<ScalingConfig>("ScalingConfig");
    Real normal_speed = scaling_config.jsonToReal(speed_config.at("normal_speed"), "Speed");
    Real triggered_speed = scaling_config.jsonToReal(speed_config.at("triggered_speed"), "Speed");
    Real deceleration_time = 0.5;
    if (speed_config.contains("deceleration_time"))
    {
        deceleration_time =scaling_config.jsonToReal(speed_config.at("deceleration_time"), "Time");
    }
    auto *sv_riser_lower_triggertime = fluid_body.getSPHSystem()
                                           .registerSystemVariable<Real>("RiserLowerTriggertime", -1.0);
    inflow_condition.add(&main_methods.template addStateDynamics<
                          fluid_dynamics::EmitterInflowConditionCK, CastingInflowSpeed>(
        emitter, normal_speed, triggered_speed, deceleration_time, sv_riser_lower_triggertime->Data()));
}
//=================================================================================================//
} // namespace SPH