
#include "ApproachAndAlign.h"

#include "cmath"

#include "Constants.h"

ApproachAndAlign::ApproachAndAlign(Drivetrain* drivetrain, CameraReader* cameras):
    Command(),
    m_drivetrain{ drivetrain },
    m_cameras{ cameras },
    m_check_dist_counter{ 0 },
    m_last_dist{ -1 }
{
    usesSubsystem(m_drivetrain);
};
ApproachAndAlign::ApproachAndAlign(ApproachAndAlign& command):
    Command(command)
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
    BoundingBox* object = m_cameras->getLargestTagFront(); // TODO: Read multiple cameras

    if (object != nullptr) {
        if (
            m_last_dist == -1 || 
            m_check_dist_counter > 10 || 
            (m_last_dist <= constants::Align_Slow_At_Distance && m_check_dist_counter > 5) || 
            (m_last_dist <= constants::Align_Slow_At_Distance/2 && m_check_dist_counter > 2)
        ) { // Check with more frequency as we get closer (because checking costs time)
            m_last_dist = object->getApproxDistance(constants::Apriltag_Actual_Width, constants::Apriltag_Actual_Height);
        }

        int min_speed = object->m_center_x >= 0 ? constants::Min_Speed_To_Move : -constants::Min_Speed_To_Move;
        double obj_percent_pos = object->m_center_x / constants::Camera_Viewport_Width;
        int bonus_speed = constants::Align_Max_Speed_LR - constants::Min_Speed_To_Move;

        double drive_lr = min_speed + (obj_percent_pos * bonus_speed); // in percentage

        min_speed = constants::Align_Min_Speed_FB;
        obj_percent_pos = std::min(m_last_dist / constants::Align_Slow_At_Distance, 1.0);
        bonus_speed = constants::Align_Max_Speed_FB - constants::Align_Min_Speed_FB;

        double drive_fb = min_speed + (obj_percent_pos * bonus_speed); // in percentage

        m_drivetrain->setDrive(
            drive_lr * 100, // In joystick -100 to 100
            drive_fb * 100,
            0
        );
    }else {
        m_drivetrain->stopDrive();
    }
};
void ApproachAndAlign::end(bool interrupted) {
    m_drivetrain->stopDrive();
};
bool ApproachAndAlign::is_finished() {
    return false;
};