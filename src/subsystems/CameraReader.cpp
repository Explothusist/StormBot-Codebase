
#include "CameraReader.h"

#include "../Constants.h"

BoundingBox::BoundingBox(int center_x, int center_y, int width, int height, double angle = 0):
    m_center_x{ center_x },
    m_center_y{ center_y },
    m_width{ width },
    m_height{ height },
    m_angle{ angle }
{

};
BoundingBox::~BoundingBox() {

};

double BoundingBox::getApproxDistance(int actual_width, int actual_height) {
    double width_ratio = m_width / constants::Camera_Viewport_Width; // Pixels/Pixels = Percentage
    double height_ratio = m_height / constants::Camera_Viewport_Height; // Percent of Viewport

    width_ratio *= constants::Camera_FOV_Horizontal / 360; // Percentage * Percentage = Percentage
    height_ratio *= constants::Camera_FOV_Vertical / 360; // Percent of Circle

    width_ratio *= M_2_PI; // Percentage * Radians = Radians
    height_ratio *= M_2_PI; // Radians!

    double distance_w = actual_width / width_ratio; // Inches / Radians = Inches
    double distance_h = actual_height / height_ratio; // Inches of Distance

    return (distance_w + distance_h) / 2; // Average of two metrics
};

CameraReader::CameraReader():
    frclib::Subsystem(),
    m_camera_front{ vex::aivision(constants::CameraFront_Port) }//,
    // m_camera_left{ vex::aivision(constants::CameraLeft_Port) },
    // m_camera_right{ vex::aivision(constants::CameraRight_Port) }
{
    m_camera_front.colorDetection(false);
    m_camera_front.tagDetection(true);
    
    // m_camera_left.colorDetection(false);
    // m_camera_left.tagDetection(true);
    
    // m_camera_right.colorDetection(false);
    // m_camera_right.tagDetection(true);
};
CameraReader::~CameraReader() {
    
};

void CameraReader::periodic() {

};

BoundingBox* CameraReader::getLargestTagFront() {
    m_camera_front.takeSnapshot(vex::aivision::ALL_TAGS);

    if (m_camera_front.objectCount > 0) {
        vex::aivision::object obj = m_camera_front.largestObject;
        BoundingBox* ret = new BoundingBox( // (0, 0) is center of grid
            obj.centerX - (constants::Camera_Viewport_Width / 2),
            obj.centerY - (constants::Camera_Viewport_Height / 2),
            obj.width,
            obj.height,
            obj.angle
        );
        return ret;
    }
    return nullptr;
};