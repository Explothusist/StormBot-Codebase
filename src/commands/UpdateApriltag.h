
#ifndef STORMBOT_UPDATEAPRILTAGCOMMAND_
#define STORMBOT_UPDATEAPRILTAGCOMMAND_

#include "../Automat/automat.h"
#include "../subsystems/CameraReader.h"

class UpdateApriltag : public atmt::Command {
    public:
        UpdateApriltag(atmt::SerialReader* serial, CameraReader* camera_reader, TagCamera camera); // Put subsystems as parameters
        UpdateApriltag(UpdateApriltag& command); // Copy constructor
        ~UpdateApriltag();
        atmt::Command* clone() const override;

        void initialize() override; // User-made
        void execute() override; // User-made
        void end(bool interrupted) override; // User-made
        bool is_finished() override; // User-made
        
    private:
        atmt::SerialReader* m_serial;
        CameraReader* m_camera_reader;
        TagCamera m_tag_camera;
};

#endif