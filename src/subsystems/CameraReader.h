
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

        BoundingBox* getLargestTagFront();
        BoundingBox* getLargestColorFront();

    private:
        vex::aivision::colordesc m_color_red;
        vex::aivision::colordesc m_color_blue;

        vex::aivision m_camera_front;
        // vex::aivision m_camera_left;
        // vex::aivision m_camera_right;
};

#endif