
#include "CameraReader.h"

#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include "../Constants.h"

BoundingBox::BoundingBox(int center_x, int center_y, int width, int height):
    m_center_x{ center_x },
    m_center_y{ center_y },
    m_width{ width },
    m_height{ height }
{

};
BoundingBox::~BoundingBox() {

};

double BoundingBox::getApproxDistance(int actual_width, int actual_height) {
    double width_ratio = static_cast<double>(m_width) / static_cast<double>(constants::Camera_Viewport_Width); // Pixels/Pixels = Percentage
    double height_ratio = static_cast<double>(m_height) / static_cast<double>(constants::Camera_Viewport_Height); // Percent of Viewport

    width_ratio *= constants::Camera_FOV_Horizontal / 360; // Percentage * Percentage = Percentage
    height_ratio *= constants::Camera_FOV_Vertical / 360; // Percent of Circle

    width_ratio *= M_PI * 2; // Percentage * Radians = Radians
    height_ratio *= M_PI * 2; // Radians!

    double distance_w = static_cast<double>(actual_width) / width_ratio; // Inches / Radians = Inches
    double distance_h = static_cast<double>(actual_height) / height_ratio; // Inches of Distance

    return (distance_w + distance_h) / 2.0; // Average of two metrics
};

CameraReader::CameraReader():
    atmt::Subsystem(),
    m_color_red{ vex::aivision::colordesc(1, 255, 0, 0, 20, 0.2) },
    m_color_blue{ vex::aivision::colordesc(1, 0, 0, 255, 20, 0.2) },
    m_color_white{ vex::aivision::colordesc(1, 255, 255, 255, 180, 0.2) },
    m_camera_front{ vex::aivision(constants::CameraFront_Port, m_color_red, m_color_blue, m_color_white) }//,
    // m_camera_left{ vex::aivision(constants::CameraLeft_Port, m_color_red, m_color_blue) },
    // m_camera_right{ vex::aivision(constants::CameraRight_Port, m_color_red, m_color_blue) }
{
    // m_camera_front.colorDetection(false);
    // m_camera_front.tagDetection(true);
    
    // m_camera_left.colorDetection(false);
    // m_camera_left.tagDetection(true);
    
    // m_camera_right.colorDetection(false);
    // m_camera_right.tagDetection(true);
};
CameraReader::~CameraReader() {
    
};

void CameraReader::periodic() {

};

vex::aivision::object* CameraReader::getLargestOfColors(vex::aivision camera, vex::aivision::colordesc color1, vex::aivision::colordesc color2) {
    vex::aivision::object* obj1{ nullptr };
    vex::aivision::object* obj2{ nullptr };

    camera.takeSnapshot(color1);
    if (camera.objectCount > 0) {
        obj1 = &camera.largestObject;
    }

    camera.takeSnapshot(color2);
    if (camera.objectCount > 0) {
        obj2 = &camera.largestObject;
    }

    if (obj1 == nullptr && obj2 == nullptr) {
        return nullptr;
    }else if (obj1 == nullptr) {
        return obj2;
    }else if (obj2 == nullptr) {
        return obj1;
    }else {
        int obj1_size = obj1->width * obj1->height;
        int obj2_size = obj2->width * obj2->height;
        if (obj1_size > obj2_size) {
            return obj1;
        }else {
            return obj2;
        }
    }
};

BoundingBox* CameraReader::getLargestTagFront() {
    m_camera_front.takeSnapshot(vex::aivision::ALL_TAGS);

    if (m_camera_front.objectCount > 0) {
        vex::aivision::object obj = m_camera_front.largestObject;
        BoundingBox* ret = new BoundingBox( // (0, 0) is center of grid
            obj.centerX - (constants::Camera_Viewport_Width / 2),
            obj.centerY - (constants::Camera_Viewport_Height / 2),
            obj.width,
            obj.height
        );
        return ret;
    }
    return nullptr;
};
BoundingBox* CameraReader::getLargestScoringFront() {
    vex::aivision::object* obj = getLargestOfColors(m_camera_front, m_color_blue, m_color_red);

    if (obj != nullptr) {
        BoundingBox* ret = new BoundingBox( // (0, 0) is center of grid
            obj->centerX - (constants::Camera_Viewport_Width / 2),
            obj->centerY - (constants::Camera_Viewport_Height / 2),
            obj->width,
            obj->height
        );
        delete obj;
        obj = nullptr;
        return ret;
    }
    return nullptr;
};
BoundingBox* CameraReader::getLargestBatteryFront() {
    m_camera_front.takeSnapshot(m_color_white);

    if (m_camera_front.objectCount > 0) {
        vex::aivision::object obj = m_camera_front.largestObject;
        BoundingBox* ret = new BoundingBox( // (0, 0) is center of grid
            obj.centerX - (constants::Camera_Viewport_Width / 2),
            obj.centerY - (constants::Camera_Viewport_Height / 2),
            obj.width,
            obj.height
        );
        return ret;
    }
    return nullptr;
};