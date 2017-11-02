/*
 * includeControllers.h
 *
 *  Created on: Aug 29, 2017
 *      Author: mario
 */

#ifndef SRC_CONTROLLER_INCLUDECONTROLLERS_H_
#define SRC_CONTROLLER_INCLUDECONTROLLERS_H_

#include "common/controller.h"
#include "common/DisabledController.h"
#include "common/ProgramChange.h"

#include "pot/ControlChangePotentioMeter8Bit.h"
#include "pot/ControlChangePotentioMeter16Bit.h"

#include "pressure/NoteVelocityPressure.h"
#include "pressure/NoteControlChangePressure8Bit.h"
#include "pressure/NoteControlChangePressure16Bit.h"
#include "pressure/ControlChangePressure8Bit.h"
#include "pressure/ControlChangePressure16Bit.h"

#include "ribbon/PitchBendRibbon.h"
#include "ribbon/PitchBendNoteRibbon.h"
#include "ribbon/ControlChangeRibbon8Bit.h"
#include "ribbon/ControlChangeRibbon16Bit.h"

#include "switch/ProgramChangeSwitch.h"
#include "switch/NoteVelocitySwitch.h"
#include "switch/ControlChangeSwitch8Bit.h"
#include "switch/ControlChangeSwitch16Bit.h"
#include "switch/ControlChangeFadeSwitch8Bit.h"
#include "switch/ControlChangeFadeSwitch16Bit.h"

#include "toggle/ProgramChangeToggle.h"
#include "toggle/NoteVelocityToggle.h"
#include "toggle/NoteControlChangeToggle8Bit.h"
#include "toggle/NoteControlChangeToggle16Bit.h"
#include "toggle/ControlChangeToggle8Bit.h"
#include "toggle/ControlChangeToggle16Bit.h"
#include "toggle/ControlChangeFadeToggle8Bit.h"
#include "toggle/ControlChangeFadeToggle16Bit.h"

#endif /* SRC_CONTROLLER_INCLUDECONTROLLERS_H_ */
