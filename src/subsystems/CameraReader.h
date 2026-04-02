
#ifndef STORMBOT_CAMERA_
#define STORMBOT_CAMERA_

#include "../Automat/automat.h"
#include "vex.h"
#include "../storm_serial_utils.h"

typedef enum {
    TagCamera_Front = 0,
    TagCamera_Right = 1,
    TagCamera_Back = 2,
    TagCamera_Left = 3,
    TagCamera_Scoring = 4
} TagCamera;

class BoundingBox {
    public:
        BoundingBox(int center_x, int center_y, int width, int height);
        ~BoundingBox();

        int m_center_x;
        int m_center_y;
        int m_width;
        int m_height;
};

double getApproxDistance(int apparent_width, int apparent_height, int actual_width, int actual_height); // Returns in inches
double getApproxDistance(BoundingBox* bounding, int actual_width, int actual_height); // Returns in inches
double getApproxDistance(TagDetection* tag, int actual_width, int actual_height); // Returns in inches



class CameraReader : public atmt::Subsystem {
    public:
        CameraReader(); // No destructor because I don't want to override
        ~CameraReader() override;

        void init() override;
        void systemPeriodic() override;
        void disabledPeriodic() override;
        void autonomousPeriodic() override;
        void teleopPeriodic() override;

        vex::aivision::object* getLargestOfColors(vex::aivision* camera, vex::aivision::colordesc color1, vex::aivision::colordesc color2);

        BoundingBox* getLargestTagFront();
        BoundingBox* getLargestScoringFront();
        BoundingBox* getLargestBatteryFront();

        void updateTagDetection(TagCamera camera, TagDetection* detection);
        void requestTagUpdate(TagCamera camera, atmt::SerialReader* serial_reader);
        TagDetection* getLastTagDetection(TagCamera camera, int max_age_ms = 200);

        uint8_t getCameraAddress(TagCamera camera);

    private:
        vex::aivision::colordesc m_color_red;
        vex::aivision::colordesc m_color_blue;
        vex::aivision::colordesc m_color_white;

        vex::aivision* m_vex_camera_scoring;
        
        // vex::aivision m_camera_left;
        // vex::aivision m_camera_right;

        atmt::ThreadsafeBuffer<TagDetection*> m_last_tags[5];
        atmt::ThreadsafeBuffer<atmt::Timestamp> m_last_tag_timestamp[5];
};

#endif