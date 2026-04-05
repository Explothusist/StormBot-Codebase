
#include "UpdateApriltag.h"

#include <cmath>
#include "../Constants.h"

UpdateApriltag::UpdateApriltag(atmt::SerialReader* serial, CameraReader* camera_reader, TagCamera camera):
    atmt::Command(),
    m_serial{ serial },
    m_camera_reader{ camera_reader },
    m_tag_camera{ camera }
{
    // Does not use CameraReader* at the moment (somewhat risky)
    // usesSubsystem(serial);
};
UpdateApriltag::UpdateApriltag(UpdateApriltag& command):
    atmt::Command(command)
{
    m_serial = command.m_serial;
    m_camera_reader = command.m_camera_reader;
    m_tag_camera = command.m_tag_camera;
};
UpdateApriltag::~UpdateApriltag() {
    // Will run ~Command() after this is complete
};
atmt::Command* UpdateApriltag::clone() const {
    return new UpdateApriltag(m_serial, m_camera_reader, m_tag_camera);
};

void UpdateApriltag::initialize() {
    uint8_t prefix;
    uint8_t message[atmt::kMaxPacketSize];
    uint8_t length;
    bool success = m_serial->popMessagePrefixed(getSerialMessageId(), prefix, message, length);
    if (!success || length != sizeof(TagDetection)) {
        return;
    }
    TagDetection* tag = reinterpret_cast<TagDetection*>(message);
    m_camera_reader->updateTagDetection(m_tag_camera, tag);
};
void UpdateApriltag::execute() {
    
};
void UpdateApriltag::end(bool interrupted) {
    
};
bool UpdateApriltag::is_finished() {
    return true;
};