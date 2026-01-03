
#ifndef STORMBOT_CAMERA_
#define STORMBOT_CAMERA_

#include "../Automat/Subsystem.h"
#include "vex.h"

class BoundingBox {
    public:
        BoundingBox(int center_x, int center_y, int width, int height);
        ~BoundingBox();

        double getApproxDistance(int actual_width, int actual_height); // Returns in inches

        int m_center_x;
        int m_center_y;
        int m_width;
        int m_height;
};

class CameraReader : public atmt::Subsystem {
    public:
        CameraReader(); // No destructor because I don't want to override
        ~CameraReader() override;

        void periodic() override;

        vex::aivision::object* getLargestOfColors(vex::aivision camera, vex::aivision::colordesc color1, vex::aivision::colordesc color2);

        BoundingBox* getLargestTagFront();
        BoundingBox* getLargestScoringFront();
        BoundingBox* getLargestBatteryFront();

    private:
        vex::aivision::colordesc m_color_red;
        vex::aivision::colordesc m_color_blue;
        vex::aivision::colordesc m_color_white;

        vex::aivision m_camera_front;
        // vex::aivision m_camera_left;
        // vex::aivision m_camera_right;
};

#endif