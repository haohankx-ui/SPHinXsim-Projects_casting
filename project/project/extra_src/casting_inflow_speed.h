#ifndef CASTING_INFLOW_SPEED_H
#define CASTING_INFLOW_SPEED_H

#include "base_data_type.h"

namespace SPH
{

struct CastingInflowSpeed
{
    Real normal_speed_;
    Real triggered_speed_;
    Real deceleration_time_;
    Real *trigger_time_;

    CastingInflowSpeed(Real normal_speed, Real triggered_speed, Real deceleration_time, Real *trigger_time)
        : normal_speed_(normal_speed), triggered_speed_(triggered_speed),
          deceleration_time_(deceleration_time), trigger_time_(trigger_time) {}

    Real getAxisVelocity(
        const Vecd &,
        const Real &,
        Real physical_time)
    {
        if (*trigger_time_ < 0.0)
        {
            return normal_speed_;
        }
        Real elapsed_time = physical_time - *trigger_time_;

        if (elapsed_time >= deceleration_time_)
        {
            return triggered_speed_;
        }

        Real ratio =elapsed_time / deceleration_time_;
        Real smooth_ratio = ratio * ratio * (3.0 - 2.0 * ratio);
        return normal_speed_ +smooth_ratio * (triggered_speed_ - normal_speed_);
    }
};

} // namespace SPH

#endif // CASTING_INFLOW_SPEED_H