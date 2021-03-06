/*
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#include "RangeFinder.h"
#include "RangeFinder_Backend.h"

class AP_RangeFinder_PWM : public AP_RangeFinder_Backend
{
public:
    // constructor
    AP_RangeFinder_PWM(RangeFinder::RangeFinder_State &_state);

    // destructor
    ~AP_RangeFinder_PWM(void) {};

    // static detection function
    static bool detect();

    // update state
    void update(void);

protected:

    bool get_reading(uint16_t &reading_cm);

    MAV_DISTANCE_SENSOR _get_mav_distance_sensor_type() const override {
        return MAV_DISTANCE_SENSOR_UNKNOWN;
    }

private:

    int8_t last_pin; // last pin used for reading pwm (used to recognise change in pin assignment)
    uint32_t last_reading_ms;      // system time of last read (used for health reporting)

    // the following two members are updated by the interrupt handler
    uint32_t irq_value_us;         // last calculated pwm value (irq copy)
    uint32_t irq_pulse_start_us;   // system time of start of pulse

    void irq_handler(uint8_t pin, bool pin_high, uint32_t timestamp_us);

    void check_pin();

};
