
#ifndef STORMBOT_ALIGN_AND_POUNCE_
#define STORMBOT_ALIGN_AND_POUNCE_

#include "../Automat/command_based/Command.h"
#include "../subsystems/Drivetrain.h"
#include "../subsystems/CameraReader.h"

class ColorRectGamePieceTargetting : public atmt::Command {
    public:
        ColorRectGamePieceTargetting(Drivetrain* drivetrain, CameraReader* cameras, atmt::SerialReader* serial); // Put subsystems as parameters
        ColorRectGamePieceTargetting(ColorRectGamePieceTargetting& command); // Copy constructor
        ~ColorRectGamePieceTargetting();
        atmt::Command* cloneSelf() const override;

        void initialize() override; // User-made
        void execute() override; // User-made
        void end(bool interrupted) override; // User-made
        bool is_finished() override; // User-made
        
    private:
        Drivetrain* m_drivetrain;
        CameraReader* m_cameras;
        atmt::SerialReader* m_serial;

        int m_check_dist_counter;
        double m_last_dist;
        int m_last_offset; // x
        int m_invisibility_count;
};

#endif