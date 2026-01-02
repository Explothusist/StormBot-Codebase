
#include "ApproachAndAlign.h"

#include <cmath>

#include "../Constants.h"

ApproachAndAlign::ApproachAndAlign(Drivetrain* drivetrain, CameraReader* cameras):
    atmt::Command(),
    m_drivetrain{ drivetrain },
    m_cameras{ cameras },
    m_check_dist_counter{ 0 },
    m_last_dist{ -1 },
    m_invisibility_count{ 0 }
{
    usesSubsystem(m_drivetrain);
};
ApproachAndAlign::ApproachAndAlign(ApproachAndAlign& command):
    atmt::Command(command)
{
    m_drivetrain = command.m_drivetrain;
    m_cameras = command.m_cameras;
};
ApproachAndAlign::~ApproachAndAlign() {
    // Will run ~Command() after this is complete
};

void ApproachAndAlign::initialize() {

};
void ApproachAndAlign::execute() {
    BoundingBox* object = m_cameras->getLargestColorFront(); // TODO: Read multiple cameras

    if (
        object != nullptr && 
        object->m_width >= constants::ColorRect_Insignificant && 
        object->m_height >= constants::ColorRect_Insignificant
    ) {
        m_invisibility_count = 0;
        if (
            m_last_dist == -1 || 
            m_check_dist_counter > 10 || 
            (m_last_dist <= constants::Align_Slow_At_Distance && m_check_dist_counter > 5) || 
            (m_last_dist <= constants::Align_Slow_At_Distance/2 && m_check_dist_counter > 2)
        ) { // Check with more frequency as we get closer (because checking costs time)
            m_last_dist = object->getApproxDistance(constants::ColorRect_Actual_Width, constants::ColorRect_Actual_Height);
        }
        m_last_offset = object->m_center_x;

        int min_speed = object->m_center_x >= 0 ? constants::Min_Speed_To_Move : -constants::Min_Speed_To_Move;
        double obj_percent_pos = static_cast<double>(object->m_center_x) / static_cast<double>(constants::Camera_Viewport_Width);
        int bonus_speed = constants::Align_Max_Speed_LR - constants::Min_Speed_To_Move;

        double drive_lr = min_speed + (obj_percent_pos * bonus_speed); // in percentage

        min_speed = constants::Align_Min_Speed_FB;
        obj_percent_pos = std::min(m_last_dist / constants::Align_Slow_At_Distance, 1.0);
        bonus_speed = constants::Align_Max_Speed_FB - constants::Align_Min_Speed_FB;

        double drive_fb = min_speed + (obj_percent_pos * bonus_speed); // in percentage

        m_drivetrain->setDrive(
            static_cast<int>(std::round(drive_lr * 100.0)), // In joystick -100 to 100
            static_cast<int>(std::round(drive_fb * 100.0)),
            0
        );
        delete object; // free BoundingBox returned by CameraReader
    }else {
        m_invisibility_count += 1;
        m_drivetrain->stopDrive();
    }
};
void ApproachAndAlign::end(bool interrupted) {
    m_drivetrain->stopDrive();
};
bool ApproachAndAlign::is_finished() {
    return 
        (std::abs(m_last_dist) < constants::Align_Epsilon_FB && std::abs(m_last_offset) < constants::Align_Epsilon_LR) ||
        (m_invisibility_count > 20);
};