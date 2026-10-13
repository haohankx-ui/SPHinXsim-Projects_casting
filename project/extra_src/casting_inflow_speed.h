#ifndef CASTING_INFLOW_SPEED_H
#define CASTING_INFLOW_SPEED_H

#include "base_data_type.h"

namespace SPH
{

struct CastingInflowSpeed
{
    Real normal_speed_;
    Real triggered_speed_;
    Real *trigger_time_;

    CastingInflowSpeed(Real normal_speed, Real triggered_speed, Real *trigger_time)
        : normal_speed_(normal_speed),triggered_speed_(triggered_speed),trigger_time_(trigger_time){}

    Real getAxisVelocity(
        const Vecd &,
        const Real &,
        Real)
    {
        return *trigger_time_ < 0.0
                   ? normal_speed_
                   : triggered_speed_;
    }
};

} // namespace SPH

#endif // CASTING_INFLOW_SPEED_H