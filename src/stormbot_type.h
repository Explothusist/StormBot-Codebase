#ifndef STORMBOT_ROBOT_TYPE_
#define STORMBOT_ROBOT_TYPE_

#define STORMBOT_INDEPENDENT_
// #define STORMBOT_STATE_MATCHED_

#if defined(STORMBOT_INDEPENDENT_) + defined(STORMBOT_STATE_MATCHED_) != 1
    #error "Exactly one StormBot control system should be defined"
#endif

#endif