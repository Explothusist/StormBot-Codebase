
#include "ApproachAndAlign.h"

#include <cmath>

#include "../Automat/utils.h"
#include "../Constants.h"

ApproachAndAlign::ApproachAndAlign(Drivetrain* drivetrain, CameraReader* cameras, atmt::SerialReader* serial):
    atmt::Command(),
    m_drivetrain{ drivetrain },
    m_cameras{ cameras },
    m_serial{ serial },
    m_check_dist_counter{ 0 },
    m_last_dist{ -1 },
    m_invisibility_count{ 0 }
{
    usesSubsystem(m_drivetrain);
    usesSubsystem(m_cameras);
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
atmt::Command* ApproachAndAlign::clone() const {
    return new ApproachAndAlign(m_drivetrain, m_cameras, m_serial);
};

void ApproachAndAlign::initialize() {

};
void ApproachAndAlign::execute() {
    m_cameras->requestTagUpdate(TagCamera_Front, m_serial);
    TagDetection* object = m_cameras->getLastTagDetection(TagCamera_Front);
    // BoundingBox* object = m_cameras->getLargestScoringFront(); // TODO: Read multiple cameras 

    // if (
    //     object != nullptr && 
    //     object->m_width >= constants::camera::ColorRect_Insignificant && 
    //     object->m_height >= constants::camera::ColorRect_Insignificant
    // ) {
    if (
        object != nullptr && 
        object->bounding_width >= constants::camera::AprilTag_Insignificant && 
        object->bounding_height >= constants::camera::AprilTag_Insignificant
    ) {
        m_invisibility_count = 0;
        if (
            m_last_dist == -1 || 
            m_check_dist_counter > 10 || 
            (m_last_dist <= constants::drivetrain::align::Align_Slow_At_Distance && m_check_dist_counter > 5) || 
            (m_last_dist <= constants::drivetrain::align::Align_Slow_At_Distance/2 && m_check_dist_counter > 2)
        ) { // Check with more frequency as we get closer (because checking costs time)
            m_last_dist = getApproxDistance(object, constants::camera::ColorRect_Actual_Width, constants::camera::ColorRect_Actual_Height);
        }
        m_last_offset = object->x;

        // int min_speed = object->m_center_x >= 0 ? constants::drivetrain::align::Min_Speed_To_Move : -constants::drivetrain::align::Min_Speed_To_Move;
        // double obj_percent_pos = static_cast<double>(object->m_center_x) / static_cast<double>(constants::camera::Camera_Viewport_Width);
        // int bonus_speed = constants::drivetrain::align::Align_Max_Speed_LR - constants::drivetrain::align::Min_Speed_To_Move;

        // double drive_lr = min_speed + (obj_percent_pos * bonus_speed); // in percentage

        double drive_lr = atmt::getProportional(
            object->x, 
            0.0, 
            constants::camera::Camera_Viewport_Width, 
            constants::drivetrain::align::Min_Speed_To_Move, 
            constants::drivetrain::align::Align_Max_Speed_LR
        );

        // min_speed = constants::drivetrain::align::Align_Min_Speed_FB;
        // obj_percent_pos = std::min(m_last_dist / constants::drivetrain::align::Align_Slow_At_Distance, 1.0);
        // bonus_speed = constants::drivetrain::align::Align_Max_Speed_FB - constants::drivetrain::align::Align_Min_Speed_FB;

        // double drive_fb = min_speed + (obj_percent_pos * bonus_speed); // in percentage

        double drive_fb = atmt::getProportional(
            m_last_dist, 
            0.0, 
            constants::drivetrain::align::Align_Slow_At_Distance, 
            constants::drivetrain::align::Align_Min_Speed_FB, 
            constants::drivetrain::align::Align_Max_Speed_FB
        );

        m_drivetrain->setDrive(
            static_cast<int>(std::round(drive_lr * 100.0)), // In joystick -100 to 100
            static_cast<int>(std::round(drive_fb * 100.0)),
            0
        );
        // delete object; // free BoundingBox returned by CameraReader
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
        (std::abs(m_last_dist) < constants::drivetrain::align::Align_Epsilon_FB && std::abs(m_last_offset) < constants::drivetrain::align::Align_Epsilon_LR) ||
        (m_invisibility_count > 20);
};