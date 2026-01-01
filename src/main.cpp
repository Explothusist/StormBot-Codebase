/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Cedric Serio                                              */
/*    Created:      12/20/2025, 2:52:29 PM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

#include "StormBot.h"

StormBot* m_robot{ new StormBot() };

int main() {

    m_robot->startLoop();

};
