/**
 * @file    sphinxsim_project.h
 * @brief   tbd.
 * @author  Xiangyu Hu & Han Yang
 */

#ifndef SPHINXSIM_PROJECT_H
#define SPHINXSIM_PROJECT_H

#include "base_simulation_builder.h"
#include "simulation_scaling.h"
#include "casting_inflow_speed.h"

//=================================================================================================//
namespace SPH
{
//=================================================================================================//
class EntityManager;

bool addExtraMaterial(
    EntityManager &config_manager, SPHBody &sph_body,
    const json &config, const std::string &type);

template <class InnerRelationType>
bool addExtraSolidRelaxation1stHalf(
    EntityManager &config_manager, ParticleDynamicsGroup &solid_relaxation_1st_half,
    MainMethods &main_methods, InnerRelationType &inner_relation);
//=================================================================================================//
class FluidBody;
struct FluidSolverConfig;

void addExtraEmitterFeatures(
    EntityManager &config_manager, MainMethods &main_methods,
    FluidBody &fluid_body, FluidSolverConfig &fluid_solver_config,
    StagePipeline<SimulationHookPoint> &simulation_pipeline,const json &config);
//=================================================================================================//
class OrientedBoxByParticle;
void addExtraInflowSpeed(
    EntityManager &config_manager, MainMethods &main_methods,
    FluidBody &fluid_body,OrientedBoxByParticle &emitter,
    ParticleDynamicsGroup &inflow_condition,
    const json &config);
//=================================================================================================//
} // namespace SPH
#endif // SPHINXSIM_PROJECT_H