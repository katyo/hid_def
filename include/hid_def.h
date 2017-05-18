#ifndef __HID_DEF_H__
#define __HID_DEF_H__

#include "macro.h"

#define HID_REQ_GET_REPORT   0x01
#define HID_REQ_GET_IDLE     0x02
#define HID_REQ_GET_PROTOCOL 0x03
#define HID_REQ_SET_REPORT   0x09
#define HID_REQ_SET_IDLE     0x0a
#define HID_REQ_SET_PROTOCOL 0x0b

#define HID_REPORT_INPUT   0x01
#define HID_REPORT_OUTPUT  0x02
#define HID_REPORT_FEATURE 0x03

/*
 * type: USB_DT_REPORT or USB_DT_HID
 */
#define HID_REQ_VALUE(dt, id) (((dt) << 8) | (id))

/*
 * Element prefix
 */
#define HID_TYPE_MAIN   (0<<2)
#define HID_TYPE_GLOBAL (1<<2)
#define HID_TYPE_LOCAL  (2<<2)
#define HID_HEAD(tag, type, size) (((tag)<<4) | _CAT2(HID_TYPE_, type) | (((size) < 4 ? (size) : 3) & 0x3))

#define HID_DATA0(x)
#define HID_DATA1(x) , (x)

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define HID_DATA2(x) , (((x) >> 0) & 0xff), (((x) >> 8) & 0xff)
#define HID_DATA4(x) , (((x) >> 0) & 0xff), (((x) >> 8) & 0xff), (((x) >> 16) & 0xff), (((x) >> 24) & 0xff)
#else /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ || __BYTE_ORDER__ == __ORDER_PDP_ENDIAN__ */
#define HID_DATA2(x) , (((x) >> 8) & 0xff), (((x) >> 0) & 0xff)
#if __BYTE_ORDER__ == __ORDER_PDP_ENDIAN__
#define HID_DATA4(x) , (((x) >> 16) & 0xff), (((x) >> 24) & 0xff), (((x) >> 0) & 0xff), (((x) >> 8) & 0xff)
#else /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ */
#define HID_DATA4(x) , (((x) >> 24) & 0xff), (((x) >> 16) & 0xff), (((x) >> 8) & 0xff), (((x) >> 0) & 0xff)
#endif
#endif

#define HID_DATA(size, data) _CAT2(HID_DATA, size)(data)

#define HID_ELEM(tag, type, size, ...) HID_HEAD(tag, type, size) HID_DATA(size, __VA_ARGS__)

/*
 * Main elements
 */

/* type */
#define HID_FLAG_DATA     (0<<0)
#define HID_FLAG_CONSTANT (1<<0)
/* kind */
#define HID_FLAG_ARRAY    (0<<1)
#define HID_FLAG_VARIABLE (1<<1)
/* rel */
#define HID_FLAG_ABSOLUTE (0<<2)
#define HID_FLAG_RELATIVE (1<<2)
/* wrap */
#define HID_FLAG_NO_WRAP  (0<<3)
#define HID_FLAG_WRAP     (1<<3)
/* lin */
#define HID_FLAG_LINEAR     (0<<4)
#define HID_FLAG_NON_LINEAR (1<<4)
/* pref */
#define HID_FLAG_PREFERRED_STATE  (0<<5)
#define HID_FLAG_NO_PREFERRED     (1<<5)
/* null */
#define HID_FLAG_NO_NULL_POSITION (0<<6)
#define HID_FLAG_NULL_STATE       (1<<6)
/* vol (only for feature and output) */
#define HID_FLAG_NON_VOLATILE     (0<<7)
#define HID_FLAG_VOLATILE         (1<<7)
/* data */
#define HID_FLAG_BIT_FIELD        (0<<7)
#define HID_FLAG_BUFFERED_BYTES   (1<<7)

#define HID_APPLY_FLAG(x) _CAT2(HID_FLAG_, x)
#define HID_UNION_FLAG(...) (0 _MAP(| HID_APPLY_FLAG, ##__VA_ARGS__))

#define HID_INPUT(...)   HID_ELEM(0x8, MAIN, 1, HID_UNION_FLAG(__VA_ARGS__))
#define HID_OUTPUT(...)  HID_ELEM(0x9, MAIN, 1, HID_UNION_FLAG(__VA_ARGS__))
#define HID_FEATURE(...) HID_ELEM(0xb, MAIN, 1, HID_UNION_FLAG(__VA_ARGS__))

#define HID_COLLECTION_PHYSICAL       0x00 /* group of axes */
#define HID_COLLECTION_APPLICATION    0x01 /* mouse, keyboard */
#define HID_COLLECTION_LOGICAL        0x02 /* interrelated data */
#define HID_COLLECTION_REPORT         0x03
#define HID_COLLECTION_NAMED_ARRAY    0x04
#define HID_COLLECTION_USAGE_SWITCH   0x05
#define HID_COLLECTION_USAGE_MODIFIER 0x06
#define HID_COLLECTION_VENDOR_DEFINED 0x80
#define HID_COLLECTION(x) HID_ELEM(0xa, MAIN, 1, _CAT2(HID_COLLECTION_, x))
#define HID_END_COLLECTION(...) HID_ELEM(0xc, MAIN, 0)

/*
 * Global elements
 */

/* Usage Pages (see Hut1_12v2.pdf) */
#define HID_USAGE_PAGE_UNDEFINED             1, 0x00
#define HID_USAGE_PAGE_GENERIC_DESKTOP       1, 0x01
#define HID_USAGE_PAGE_DESKTOP               1, 0x01
#define HID_USAGE_PAGE_SIMULATION            1, 0x02
#define HID_USAGE_PAGE_VIRTUAL_REALITY       1, 0x03
#define HID_USAGE_PAGE_SPORT                 1, 0x04
#define HID_USAGE_PAGE_GAME                  1, 0x05
#define HID_USAGE_PAGE_GENERIC_DEVICE        1, 0x06
#define HID_USAGE_PAGE_KEYBOARD              1, 0x07
#define HID_USAGE_PAGE_KEYPAD                1, 0x07
#define HID_USAGE_PAGE_LED                   1, 0x08
#define HID_USAGE_PAGE_LEDS                  1, 0x08
#define HID_USAGE_PAGE_BUTTON                1, 0x09
#define HID_USAGE_PAGE_BUTTONS               1, 0x09
#define HID_USAGE_PAGE_ORDINAL               1, 0x0a
#define HID_USAGE_PAGE_TELEPHONY             1, 0x0b
#define HID_USAGE_PAGE_CONSUMER              1, 0x0c
#define HID_USAGE_PAGE_DIGITIZER             1, 0x0d
#define HID_USAGE_PAGE_PHYSICAL_DEVICE       1, 0x0f
#define HID_USAGE_PAGE_UNICODE               1, 0x10
#define HID_USAGE_PAGE_ALPHA_NUMERIC_DISPLAY 1, 0x14
#define HID_USAGE_PAGE_MEDICAL_INSTRUMENTS   1, 0x40
#define HID_USAGE_PAGE_MONITOR_DEVICE        1, 0x80
#define HID_USAGE_PAGE_POWER_DEVICE          1, 0x84
#define HID_USAGE_PAGE_BATTERY_SYSTEM        1, 0x85
#define HID_USAGE_PAGE_BAR_CODE_SCANNER      1, 0x8c
#define HID_USAGE_PAGE_SCALE                 1, 0x8d
#define HID_USAGE_PAGE_CAMERA_CONTROL        1, 0x90
#define HID_USAGE_PAGE_ARCADE                1, 0x91
/* End of Usage Pages */

#define HID_USAGE_PAGE2(n, x) HID_ELEM(0x0, GLOBAL, n, x)
#define HID_USAGE_PAGE(x) _CALL(HID_USAGE_PAGE2, _CAT2(HID_USAGE_PAGE_, x))

#define HID_LOGICAL_MINIMUM(n, x) HID_ELEM(0x1, GLOBAL, n, x)
#define HID_LOGICAL_MAXIMUM(n, x) HID_ELEM(0x2, GLOBAL, n, x)

#define HID_PHYSICAL_MINIMUM(n, x) HID_ELEM(0x3, GLOBAL, n, x)
#define HID_PHYSICAL_MAXIMUM(n, x) HID_ELEM(0x4, GLOBAL, n, x)

#define HID_UNIT_EXPONENT(x) HID_ELEM(0x5, GLOBAL, 1, x)

#define HID_UNIT_NONE_SYSTEM    0x0
#define HID_UNIT_SI_LINEAR      0x1
#define HID_UNIT_SI_LIN         0x1
#define HID_UNIT_SI_ROTATION    0x2
#define HID_UNIT_SI_ROT         0x2
#define HID_UNIT_EN_LINEAR      0x3
#define HID_UNIT_EN_LIN         0x3
#define HID_UNIT_EN_ROTATION    0x4
#define HID_UNIT_EN_ROT         0x4
#define HID_UNIT_VENDOR_DEFINED 0xf

#define HID_UNIT_SI(k) HID_UNIT_SI_##k
#define HID_UNIT_EN(k) HID_UNIT_EN_##k

#define HID_UNIT_EXP(n) (!_ASSERT(-8 <= (n) && (n) <= 7) ? (0) : ((n) < 0) ? (0x10 + (n)) : (n))
#define HID_UNIT_NIB(n, x) ((x) << (4 * (n)))

#define HID_UNIT_LENGTH(n)      HID_UNIT_NIB(1, HID_UNIT_EXP(n))
#define HID_UNIT_MASS(n)        HID_UNIT_NIB(2, HID_UNIT_EXP(n))
#define HID_UNIT_TIME(n)        HID_UNIT_NIB(3, HID_UNIT_EXP(n))
#define HID_UNIT_TEMPERATURE(n) HID_UNIT_NIB(4, HID_UNIT_EXP(n))
#define HID_UNIT_CURRENT(n)     HID_UNIT_NIB(5, HID_UNIT_EXP(n))
#define HID_UNIT_LUMINOSITY(n)  HID_UNIT_NIB(6, HID_UNIT_EXP(n))

#define HID_UNIT_NONE           0x0
#define HID_UNIT_CENTIMETER(n)  HID_UNIT_LENGTH(n)
#define HID_UNIT_GRAM(n)        HID_UNIT_MASS(n)
#define HID_UNIT_SECOND(n)      HID_UNIT_TIME(n)
#define HID_UNIT_KELVIN(n)      HID_UNIT_TEMPERATURE(n)
#define HID_UNIT_AMPERE(n)      HID_UNIT_CURRENT(n)
#define HID_UNIT_CANDELLA(n)    HID_UNIT_LUMINOSITY(n)
#define HID_UNIT_RADIANS(n)     HID_UNIT_LENGTH(n)
#define HID_UNIT_INCH(n)        HID_UNIT_LENGTH(n)
#define HID_UNIT_SLUG(n)        HID_UNIT_MASS(n)
#define HID_UNIT_FAHRENHEIT(n)  HID_UNIT_TEMPERATURE(n)
#define HID_UNIT_DEGREES(n)     HID_UNIT_LENGTH(n)

#define HID_UNIT_CM(n)          HID_UNIT_CENTIMETER(n)
#define HID_UNIT_G(n)           HID_UNIT_GRAM(n)
#define HID_UNIT_SEC(n)         HID_UNIT_SECOND(n)
#define HID_UNIT_S(n)           HID_UNIT_SECOND(n)
#define HID_UNIT_K(n)           HID_UNIT_KELVIN(n)
#define HID_UNIT_AMP(n)         HID_UNIT_AMPERE(n)
#define HID_UNIT_A(n)           HID_UNIT_AMPERE(n)
#define HID_UNIT_CD(n)          HID_UNIT_CANDELLA(n)
#define HID_UNIT_RAD(n)         HID_UNIT_RADIANS(n)
#define HID_UNIT_IN(n)          HID_UNIT_INCH(n)
#define HID_UNIT_F(n)           HID_UNIT_FAHRENHEIT(n)
#define HID_UNIT_DEG(n)         HID_UNIT_DEGREES(n)

#define HID_APPLY_UNIT(x) _CAT2(HID_UNIT_, x)
#define HID_UNION_UNIT(...) (0 _MAP(| HID_APPLY_UNIT, ##__VA_ARGS__))
#define HID_UNIT(...) HID_ELEM(0x6, GLOBAL, 4, HID_UNION_UNIT(__VA_ARGS__))

#define HID_REPORT_SIZE(x) HID_ELEM(0x7, GLOBAL, 1, x)
#define HID_REPORT_ID(x) HID_ELEM(0x8, GLOBAL, 1, x)
#define HID_REPORT_COUNT(x) HID_ELEM(0x9, GLOBAL, 1, x)

#define HID_PUSH HID_ELEM(0xa, GLOBAL, 0)
#define HID_POP HID_ELEM(0xb, GLOBAL, 0)

/*
 * Local elements
 */

#define HID_USAGE_UNDEFINED      1, 0x00

/* Generic Desktop Usages */
#define HID_USAGE_POINTER        1, 0x01
#define HID_USAGE_MOUSE          1, 0x02
#define HID_USAGE_JOYSTICK       1, 0x04
#define HID_USAGE_GAME_PAD       1, 0x05
#define HID_USAGE_KEYBOARD       1, 0x06
#define HID_USAGE_KEYPAD         1, 0x07
#define HID_USAGE_MULTI_AXIS     1, 0x08
#define HID_USAGE_TABLET         1, 0x09

#define HID_USAGE_X              1, 0x30
#define HID_USAGE_Y              1, 0x31
#define HID_USAGE_Z              1, 0x32
#define HID_USAGE_RX             1, 0x33
#define HID_USAGE_RY             1, 0x34
#define HID_USAGE_RZ             1, 0x35
#define HID_USAGE_SLIDER         1, 0x36
#define HID_USAGE_DIAL           1, 0x37
#define HID_USAGE_WHEEL          1, 0x38
#define HID_USAGE_HAT_SWITCH     1, 0x39
#define HID_USAGE_COUNTED_BUFFER 1, 0x3a
#define HID_USAGE_BYTE_COUNT     1, 0x3b
#define HID_USAGE_MOTION_WAKEUP  1, 0x3c
#define HID_USAGE_START          1, 0x3d
#define HID_USAGE_SELECT         1, 0x3e

#define HID_USAGE_VX                    1, 0x40
#define HID_USAGE_VY                    1, 0x41
#define HID_USAGE_VZ                    1, 0x42
#define HID_USAGE_VBRX                  1, 0x43
#define HID_USAGE_VBRY                  1, 0x44
#define HID_USAGE_VBRZ                  1, 0x45
#define HID_USAGE_VNO                   1, 0x46
#define HID_USAGE_FEATURE_NOTIFICATION  1, 0x47
#define HID_USAGE_RESOLUTION_MULTIPLIER 1, 0x48

#define HID_USAGE_SYSTEM_CONTROL        1, 0x80
#define HID_USAGE_SYSTEM_POWER_DOWN     1, 0x81
#define HID_USAGE_SYSTEM_SLEEP          1, 0x82
#define HID_USAGE_SYSTEM_WAKE_UP        1, 0x83
#define HID_USAGE_SYSTEM_CONTEXT_MENU   1, 0x84
#define HID_USAGE_SYSTEM_MAIN_MENU      1, 0x85
#define HID_USAGE_SYSTEM_APP_MENU       1, 0x86
#define HID_USAGE_SYSTEM_MENU_HELP      1, 0x87
#define HID_USAGE_SYSTEM_MENU_EXIT      1, 0x88
#define HID_USAGE_SYSTEM_MENU_SELECT    1, 0x89
#define HID_USAGE_SYSTEM_MENU_RIGHT     1, 0x8a
#define HID_USAGE_SYSTEM_MENU_LEFT      1, 0x8b
#define HID_USAGE_SYSTEM_MENU_UP        1, 0x8c
#define HID_USAGE_SYSTEM_MENU_DOWN      1, 0x8d
#define HID_USAGE_SYSTEM_COLD_RESTART   1, 0x8e
#define HID_USAGE_SYSTEM_WARM_RESTART   1, 0x8f

#define HID_USAGE_D_PAD_UP    1, 0x90
#define HID_USAGE_D_PAD_DOWN  1, 0x91
#define HID_USAGE_D_PAD_RIGHT 1, 0x92
#define HID_USAGE_D_PAD_LEFT  1, 0x93

#define HID_USAGE_SYSTEM_DOCK                1, 0xa0
#define HID_USAGE_SYSTEM_UNDOCK              1, 0xa1
#define HID_USAGE_SYSTEM_SETUP               1, 0xa2
#define HID_USAGE_SYSTEM_BREAK               1, 0xa3
#define HID_USAGE_SYSTEM_DEBUGGER_BREAK      1, 0xa4
#define HID_USAGE_APPLICATION_BREAK          1, 0xa5
#define HID_USAGE_APPLICATION_DEBUGGER_BREAK 1, 0xa6
#define HID_USAGE_SYSTEM_SPEAKER_MUTE        1, 0xa7
#define HID_USAGE_SYSTEM_HIBERNATE           1, 0xa8

#define HID_USAGE_SYSTEM_DISPLAY_INVERT    1, 0xb0
#define HID_USAGE_SYSTEM_DISPLAY_INTERNAL  1, 0xb1
#define HID_USAGE_SYSTEM_DISPLAY_EXTERNAL  1, 0xb2
#define HID_USAGE_SYSTEM_DISPLAY_BOTH      1, 0xb3
#define HID_USAGE_SYSTEM_DISPLAY_DUAL      1, 0xb4
#define HID_USAGE_SYSTEM_DISPLAY_TOGGLE    1, 0xb5
#define HID_USAGE_SYSTEM_DISPLAY_SWAP      1, 0xb6
#define HID_USAGE_SYSTEM_DISPLAY_AUTOSCALE 1, 0xb7

/* Simulation Usages */
#define HID_USAGE_FLIGHT       1, 0x01
#define HID_USAGE_AUTOMOBILE   1, 0x02
#define HID_USAGE_TANK         1, 0x03
#define HID_USAGE_SPACESHIP    1, 0x04
#define HID_USAGE_SUBMARINE    1, 0x05
#define HID_USAGE_SAILING      1, 0x06
#define HID_USAGE_MOTOCYCLE    1, 0x07
#define HID_USAGE_SPORTS       1, 0x08
#define HID_USAGE_AIRPLANE     1, 0x09
#define HID_USAGE_HELICOPTER   1, 0x0a
#define HID_USAGE_MAGIC_CARPET 1, 0x0b
#define HID_USAGE_BICYCLE      1, 0x0c

#define HID_USAGE_FLIGHT_CONTROL_STICK 1, 0x20
#define HID_USAGE_FLIGHT_STICK         1, 0x21
#define HID_USAGE_CYCLE_CONTROL        1, 0x22
#define HID_USAGE_CYCLE_TRIM           1, 0x23
#define HID_USAGE_FLIGHT_YOKE          1, 0x24
#define HID_USAGE_TRACK_CONTROL        1, 0x25

#define HID_USAGE_AILERON                  1, 0xb0
#define HID_USAGE_AILERON_TRIM             1, 0xb1
#define HID_USAGE_ANTI_TORQUE_CONTROL      1, 0xb2
#define HID_USAGE_AUTOPILOT_ENABLE         1, 0xb3
#define HID_USAGE_CHAFF_RELEASE            1, 0xb4
#define HID_USAGE_COLLECTIVE_CONTROL       1, 0xb5
#define HID_USAGE_DRIVE_BRAKE              1, 0xb6
#define HID_USAGE_ELECRONIC_CONTERMEASURES 1, 0xb7
#define HID_USAGE_ELEVATOR                 1, 0xb8
#define HID_USAGE_ELEVATOR_TRIM            1, 0xb9
#define HID_USAGE_RUDDER                   1, 0xba
#define HID_USAGE_THROTTLE                 1, 0xbb
#define HID_USAGE_FLIGHT_COMMUNICATIONS    1, 0xbc
#define HID_USAGE_FLARE_RELEASE            1, 0xbd
#define HID_USAGE_LANDING_GEAR             1, 0xbe
#define HID_USAGE_TOE_BRAKE                1, 0xbf

#define HID_USAGE_TRIGGER          1, 0xc0
#define HID_USAGE_WEAPON_ARM       1, 0xc1
#define HID_USAGE_WEAPON_SELECT    1, 0xc2
#define HID_USAGE_WING_FLAPS       1, 0xc3
#define HID_USAGE_ACCELERATOR      1, 0xc4
#define HID_USAGE_BRAKE            1, 0xc5
#define HID_USAGE_CLUTCH           1, 0xc6
#define HID_USAGE_SHIFTER          1, 0xc7
#define HID_USAGE_STEERING         1, 0xc8
#define HID_USAGE_TURRET_DIRECTION 1, 0xc9
#define HID_USAGE_BARREL_ELEVATION 1, 0xca
#define HID_USAGE_DIVE_PLANE       1, 0xcb
#define HID_USAGE_BALLAST          1, 0xcc
#define HID_USAGE_BICYCLE_CRANK    1, 0xcd
#define HID_USAGE_HANDLE_BARS      1, 0xce
#define HID_USAGE_FRONT_BRAKE      1, 0xcf
#define HID_USAGE_REAR_BRAKE       1, 0xd0

/* Virtual Reality Usages */
#define HID_USAGE_BELT         1, 0x01
#define HID_USAGE_BODY_SUIT    1, 0x02
#define HID_USAGE_FLEXOR       1, 0x03
#define HID_USAGE_GLOVE        1, 0x04
#define HID_USAGE_HEAD_TRACKER 1, 0x05
#define HID_USAGE_HEAD_DISPLAY 1, 0x06
#define HID_USAGE_HAND_TRACKER 1, 0x07
#define HID_USAGE_OCULOMETER   1, 0x08
#define HID_USAGE_VEST         1, 0x09
#define HID_USAGE_ANIMATRONIC  1, 0x0a

#define HID_USAGE_STEREO_ENABLE  1, 0x20
#define HID_USAGE_DISPLAY_ENABLE 1, 0x21

/* Sport Controls Usages */
#define HID_USAGE_BASEBALL_BAT   1, 0x01
#define HID_USAGE_GOLF_CLUB      1, 0x02
#define HID_USAGE_ROWING_MACHINE 1, 0x03
#define HID_USAGE_TREADMILL      1, 0x04

#define HID_USAGE_OAR                1, 0x30
#define HID_USAGE_SLOPE              1, 0x31
#define HID_USAGE_RATE               1, 0x32
#define HID_USAGE_STICK_SPEED        1, 0x33
#define HID_USAGE_STICK_FACE_ANGLE   1, 0x34
#define HID_USAGE_STICK_HEEL_TOE     1, 0x35
#define HID_USAGE_STICK_FLOW_THROUGH 1, 0x36
#define HID_USAGE_STICK_TEMPO        1, 0x37
#define HID_USAGE_STICK_TYPE         1, 0x38
#define HID_USAGE_STICK_HEIGHT       1, 0x39

#define HID_USAGE_PUTTER      1, 0x50
#define HID_USAGE_IRON(n)     1, (0x50 + (_ASSERT(1 <= (n) && (n) <= 11) ? (n) : (0))) /* n: [1..11] */
#define HID_USAGE_SAND_WEDGE  1, 0x5c
#define HID_USAGE_LOFT_WEDGE  1, 0x5d
#define HID_USAGE_POWER_WEDGE 1, 0x5e
#define HID_USAGE_WOOD(n)     1, (0x5e + (_ASSERT(1 <= (n) && (n) <= 11) ? (n) : (0))) /* n: [1..9] */

/* Game Controls Usages */
#define HID_USAGE_GAME_3D 1, 0x01
#define HID_USAGE_PINBALL 1, 0x02
#define HID_USAGE_GUN     1, 0x03

#define HID_USAGE_POINT_OF_VIEW          1, 0x20
#define HID_USAGE_TURN_RIGHT_LEFT        1, 0x21
#define HID_USAGE_PITCH_FORWARD_BACKWARD 1, 0x22
#define HID_USAGE_ROLL_RIGHT_LEFT        1, 0x23
#define HID_USAGE_MOVE_RIGHT_LEFT        1, 0x24
#define HID_USAGE_MOVE_FORWARD_BACKWARD  1, 0x25
#define HID_USAGE_MOVE_UP_DOWN           1, 0x26
#define HID_USAGE_LEAN_RIGHT_LEFT        1, 0x27
#define HID_USAGE_LEAN_FORWARD_BACKWARD  1, 0x28
#define HID_USAGE_HEIGHT_OF_POV          1, 0x29
#define HID_USAGE_FLIPPER                1, 0x2a
#define HID_USAGE_SECONDARY_FLIPPER      1, 0x2b
#define HID_USAGE_BUMP                   1, 0x2c
#define HID_USAGE_NEW_GAME               1, 0x2d
#define HID_USAGE_SHOOT_BALL             1, 0x2e
#define HID_USAGE_PLAYER                 1, 0x2f

#define HID_USAGE_GUN_BOLT          1, 0x30
#define HID_USAGE_GUN_CLIP          1, 0x31
#define HID_USAGE_GUN_SELECTOR      1, 0x32
#define HID_USAGE_GUN_SINGLE_SHOOT  1, 0x33
#define HID_USAGE_GUN_BURST         1, 0x34
#define HID_USAGE_GUN_AUTOMATIC     1, 0x35
#define HID_USAGE_GUN_SAFETY        1, 0x36
#define HID_USAGE_GAMEPAD_FIRE_JUMP 1, 0x37
#define HID_USAGE_GAMEPAD_TRIGGER   1, 0x39

/* Generic Device Usages */
#define HID_USAGE_BATTERY_STRENGTH           1, 0x20
#define HID_USAGE_WIRELESS_CHANNEL           1, 0x21
#define HID_USAGE_WIRELESS_ID                1, 0x22
#define HID_USAGE_DISCOVER_WIRELESS_CONTROL  1, 0x23
#define HID_USAGE_SECURITY_CODE_CHAR_ENTERED 1, 0x24
#define HID_USAGE_SECURITY_CODE_CHAR_ERASED  1, 0x25
#define HID_USAGE_SECURITY_CODE_CLEARED      1, 0x26

/* Keyboard/Keypad Usages */
#define HID_USAGE_ERROR_ROLL_OVER 1, 0x01
#define HID_USAGE_POST_FAIL       1, 0x02
#define HID_USAGE_ERROR_UNDEFINED 1, 0x03
#define HID_USAGE_KEY_A 1, 0x04
#define HID_USAGE_KEY_B 1, 0x05
#define HID_USAGE_KEY_C 1, 0x06
#define HID_USAGE_KEY_D 1, 0x07
#define HID_USAGE_KEY_E 1, 0x08
#define HID_USAGE_KEY_F 1, 0x09
#define HID_USAGE_KEY_G 1, 0x0a
#define HID_USAGE_KEY_H 1, 0x0b
#define HID_USAGE_KEY_I 1, 0x0c
#define HID_USAGE_KEY_J 1, 0x0d
#define HID_USAGE_KEY_K 1, 0x0e
#define HID_USAGE_KEY_L 1, 0x0f
#define HID_USAGE_KEY_M 1, 0x10
#define HID_USAGE_KEY_N 1, 0x11
#define HID_USAGE_KEY_O 1, 0x12
#define HID_USAGE_KEY_P 1, 0x13
#define HID_USAGE_KEY_Q 1, 0x14
#define HID_USAGE_KEY_R 1, 0x15
#define HID_USAGE_KEY_S 1, 0x16
#define HID_USAGE_KEY_T 1, 0x17
#define HID_USAGE_KEY_U 1, 0x18
#define HID_USAGE_KEY_V 1, 0x19
#define HID_USAGE_KEY_W 1, 0x1a
#define HID_USAGE_KEY_X 1, 0x1b
#define HID_USAGE_KEY_Y 1, 0x1c
#define HID_USAGE_KEY_Z 1, 0x1d
#define HID_USAGE_KEY_1 1, 0x1e
#define HID_USAGE_KEY_2 1, 0x1f
#define HID_USAGE_KEY_3 1, 0x20
#define HID_USAGE_KEY_4 1, 0x21
#define HID_USAGE_KEY_5 1, 0x22
#define HID_USAGE_KEY_6 1, 0x23
#define HID_USAGE_KEY_7 1, 0x24
#define HID_USAGE_KEY_8 1, 0x25
#define HID_USAGE_KEY_9 1, 0x26
#define HID_USAGE_KEY_0 1, 0x27
#define HID_USAGE_KEY_ENTER        1, 0x28
#define HID_USAGE_KEY_ESCAPE       1, 0x29
#define HID_USAGE_KEY_DELETE       1, 0x2a
#define HID_USAGE_KEY_BACKSPACE    1, 0x2a
#define HID_USAGE_KEY_TAB          1, 0x2b
#define HID_USAGE_KEY_SPACEBAR     1, 0x2c
#define HID_USAGE_KEY_SPACE        1, 0x2c
#define HID_USAGE_KEY_MINUS        1, 0x2d
#define HID_USAGE_KEY_UNDERSCORE   1, 0x2d
#define HID_USAGE_KEY_EQUALS       1, 0x2e
#define HID_USAGE_KEY_PLUS         1, 0x2e
#define HID_USAGE_KEY_SQUARE_OPEN  1, 0x2f
#define HID_USAGE_KEY_SQUARE_CLOSE 1, 0x30
#define HID_USAGE_KEY_BACKSLASH    1, 0x31
#define HID_USAGE_KEY_NON_US_SHARP 1, 0x32
#define HID_USAGE_KEY_SEMICOLON    1, 0x33
#define HID_USAGE_KEY_COLON        1, 0x33
#define HID_USAGE_KEY_QUOTE        1, 0x34
#define HID_USAGE_KEY_GRAVE_ACCENT 1, 0x35
#define HID_USAGE_KEY_TILDE        1, 0x35
#define HID_USAGE_KEY_COMMA        1, 0x36
#define HID_USAGE_KEY_DOT          1, 0x37
#define HID_USAGE_KEY_SLASH        1, 0x38
#define HID_USAGE_KEY_CAPS_LOCK    1, 0x39

#define HID_USAGE_KEY_F1  1, 0x3a
#define HID_USAGE_KEY_F2  1, 0x3b
#define HID_USAGE_KEY_F3  1, 0x3c
#define HID_USAGE_KEY_F4  1, 0x3d
#define HID_USAGE_KEY_F5  1, 0x3e
#define HID_USAGE_KEY_F6  1, 0x3f
#define HID_USAGE_KEY_F7  1, 0x40
#define HID_USAGE_KEY_F8  1, 0x41
#define HID_USAGE_KEY_F9  1, 0x42
#define HID_USAGE_KEY_F10 1, 0x43
#define HID_USAGE_KEY_F11 1, 0x44
#define HID_USAGE_KEY_F12 1, 0x45

#define HID_USAGE_KEY_PRINT_SCREEN   1, 0x46
#define HID_USAGE_KEY_SCROLL_LOCK    1, 0x47
#define HID_USAGE_KEY_PAUSE          1, 0x48
#define HID_USAGE_KEY_INSERT         1, 0x49
#define HID_USAGE_KEY_HOME           1, 0x4a
#define HID_USAGE_KEY_PAGE_UP        1, 0x4b
#define HID_USAGE_KEY_DELETE_FORWARD 1, 0x4c
#define HID_USAGE_KEY_END            1, 0x4d
#define HID_USAGE_KEY_PAGE_DOWN      1, 0x4e
#define HID_USAGE_KEY_RIGHT_ARROW    1, 0x4f
#define HID_USAGE_KEY_LEFT_ARROW     1, 0x50
#define HID_USAGE_KEY_DOWN_ARROW     1, 0x51
#define HID_USAGE_KEY_UP_ARROW       1, 0x52

#define HID_USAGE_KEY_PAD_NUM_LOCK    1, 0x53
#define HID_USAGE_KEY_PAD_DIVIDE      1, 0x54
#define HID_USAGE_KEY_PAD_MULTIPLY    1, 0x55
#define HID_USAGE_KEY_PAD_MINUS       1, 0x56
#define HID_USAGE_KEY_PAD_PLUS        1, 0x57
#define HID_USAGE_KEY_PAD_ENTER       1, 0x58
#define HID_USAGE_KEY_PAD_1           1, 0x59
#define HID_USAGE_KEY_PAD_END         1, 0x59
#define HID_USAGE_KEY_PAD_2           1, 0x5a
#define HID_USAGE_KEY_PAD_DOWN_ARROW  1, 0x5a
#define HID_USAGE_KEY_PAD_3           1, 0x5b
#define HID_USAGE_KEY_PAD_PAGE_DOWN   1, 0x5b
#define HID_USAGE_KEY_PAD_4           1, 0x5c
#define HID_USAGE_KEY_PAD_LEFT_ARROW  1, 0x5c
#define HID_USAGE_KEY_PAD_5           1, 0x5d
#define HID_USAGE_KEY_PAD_6           1, 0x5e
#define HID_USAGE_KEY_PAD_RIGHT_ARROW 1, 0x5e
#define HID_USAGE_KEY_PAD_7           1, 0x5f
#define HID_USAGE_KEY_PAD_HOME        1, 0x5f
#define HID_USAGE_KEY_PAD_8           1, 0x60
#define HID_USAGE_KEY_PAD_UP_ARROW    1, 0x60
#define HID_USAGE_KEY_PAD_9           1, 0x61
#define HID_USAGE_KEY_PAD_PAGE_UP     1, 0x61
#define HID_USAGE_KEY_PAD_0           1, 0x62
#define HID_USAGE_KEY_PAD_INSERT      1, 0x62
#define HID_USAGE_KEY_PAD_DOT         1, 0x63
#define HID_USAGE_KEY_PAD_DELETE      1, 0x63

#define HID_USAGE_KEY_NON_US_BACKSLASH 1, 0x64
#define HID_USAGE_KEY_APPLICATION      1, 0x65
#define HID_USAGE_KEY_POWER            1, 0x66

#define HID_USAGE_KEY_PAD_EQUALS       1, 0x67

#define HID_USAGE_KEY_F13 1, 0x68
#define HID_USAGE_KEY_F14 1, 0x69
#define HID_USAGE_KEY_F15 1, 0x6a
#define HID_USAGE_KEY_F16 1, 0x6b
#define HID_USAGE_KEY_F17 1, 0x6c
#define HID_USAGE_KEY_F18 1, 0x6d
#define HID_USAGE_KEY_F19 1, 0x6e
#define HID_USAGE_KEY_F20 1, 0x6f
#define HID_USAGE_KEY_F21 1, 0x70
#define HID_USAGE_KEY_F22 1, 0x71
#define HID_USAGE_KEY_F23 1, 0x72
#define HID_USAGE_KEY_F24 1, 0x73

#define HID_USAGE_KEY_EXECUTE     1, 0x74
#define HID_USAGE_KEY_HELP        1, 0x75
#define HID_USAGE_KEY_MENU        1, 0x76
#define HID_USAGE_KEY_SELECT      1, 0x77
#define HID_USAGE_KEY_STOP        1, 0x78
#define HID_USAGE_KEY_AGAIN       1, 0x79
#define HID_USAGE_KEY_UNDO        1, 0x7a
#define HID_USAGE_KEY_CUT         1, 0x7b
#define HID_USAGE_KEY_COPY        1, 0x7c
#define HID_USAGE_KEY_PASTE       1, 0x7d
#define HID_USAGE_KEY_FIND        1, 0x7e
#define HID_USAGE_KEY_MUTE        1, 0x7f
#define HID_USAGE_KEY_VOLUME_UP   1, 0x80
#define HID_USAGE_KEY_VOLUME_DOWN 1, 0x81

#define HID_USAGE_KEY_LOCKING_CAPS_LOCK   1, 0x82
#define HID_USAGE_KEY_LOCKING_NUM_LOCK    1, 0x83
#define HID_USAGE_KEY_LOCKING_SCROLL_LOCK 1, 0x84

#define HID_USAGE_KEY_PAD_COMMA       1, 0x85
#define HID_USAGE_KEY_PAD_EQUAL_SIGN  1, 0x86

#define HID_USAGE_KEY_INTERNATIONAL_1 1, 0x87
#define HID_USAGE_KEY_INTERNATIONAL_2 1, 0x88
#define HID_USAGE_KEY_INTERNATIONAL_3 1, 0x89
#define HID_USAGE_KEY_INTERNATIONAL_4 1, 0x8a
#define HID_USAGE_KEY_INTERNATIONAL_5 1, 0x8b
#define HID_USAGE_KEY_INTERNATIONAL_6 1, 0x8c
#define HID_USAGE_KEY_INTERNATIONAL_7 1, 0x8d
#define HID_USAGE_KEY_INTERNATIONAL_8 1, 0x8e
#define HID_USAGE_KEY_INTERNATIONAL_9 1, 0x8f

#define HID_USAGE_KEY_LANG_1 1, 0x90
#define HID_USAGE_KEY_LANG_2 1, 0x91
#define HID_USAGE_KEY_LANG_3 1, 0x92
#define HID_USAGE_KEY_LANG_4 1, 0x93
#define HID_USAGE_KEY_LANG_5 1, 0x94
#define HID_USAGE_KEY_LANG_6 1, 0x95
#define HID_USAGE_KEY_LANG_7 1, 0x96
#define HID_USAGE_KEY_LANG_8 1, 0x97
#define HID_USAGE_KEY_LANG_9 1, 0x98

#define HID_USAGE_KEY_ALTERNATE_ERASE 1, 0x99
#define HID_USAGE_KEY_SYSTEM_REQUEST  1, 0x9a
#define HID_USAGE_KEY_ATTENTION       1, 0x9a
#define HID_USAGE_KEY_CANCEL          1, 0x9b
#define HID_USAGE_KEY_CLEAR           1, 0x9c
#define HID_USAGE_KEY_PRIOR           1, 0x9d
#define HID_USAGE_KEY_RETURN          1, 0x9e
#define HID_USAGE_KEY_SEPARATOR       1, 0x9f
#define HID_USAGE_KEY_OUT             1, 0xa0
#define HID_USAGE_KEY_OPER            1, 0xa1
#define HID_USAGE_KEY_CLEAR_AGAIN     1, 0xa2
#define HID_USAGE_KEY_CR_SEL_PROPS    1, 0xa3
#define HID_USAGE_KEY_EX_SEL          1, 0xa4

#define HID_USAGE_KEY_PAD_00               1, 0xb0
#define HID_USAGE_KEY_PAD_000              1, 0xb1
#define HID_USAGE_KEY_THOUSANDS_SEPARATOR  1, 0xb2
#define HID_USAGE_KEY_DECIMAL_SEPARATOR    1, 0xb3
#define HID_USAGE_KEY_CURRENCY_UNIT        1, 0xb4
#define HID_USAGE_KEY_CURRENCY_SUB_UNIT    1, 0xb5
#define HID_USAGE_KEY_PAD_PAREN_OPEN       1, 0xb6
#define HID_USAGE_KEY_PAD_ROUND_OPEN       1, 0xb6
#define HID_USAGE_KEY_PAD_PAREN_CLOSE      1, 0xb7
#define HID_USAGE_KEY_PAD_ROUND_CLOSE      1, 0xb7
#define HID_USAGE_KEY_PAD_BRACE_OPEN       1, 0xb8
#define HID_USAGE_KEY_PAD_BRACE_CLOSE      1, 0xb9
#define HID_USAGE_KEY_PAD_TAB              1, 0xba
#define HID_USAGE_KEY_PAD_BACKSPACE        1, 0xbb
#define HID_USAGE_KEY_PAD_A                1, 0xbc
#define HID_USAGE_KEY_PAD_B                1, 0xbd
#define HID_USAGE_KEY_PAD_C                1, 0xbe
#define HID_USAGE_KEY_PAD_D                1, 0xbf
#define HID_USAGE_KEY_PAD_E                1, 0xc0
#define HID_USAGE_KEY_PAD_F                1, 0xc1
#define HID_USAGE_KEY_PAD_XOR              1, 0xc2
#define HID_USAGE_KEY_PAD_CARET            1, 0xc3
#define HID_USAGE_KEY_PAD_BINARY_XOR       1, 0xc3
#define HID_USAGE_KEY_PAD_PERCENT          1, 0xc4
#define HID_USAGE_KEY_PAD_LESS_THAN        1, 0xc5
#define HID_USAGE_KEY_PAD_LEFT_ANGLE       1, 0xc5
#define HID_USAGE_KEY_PAD_GREAT_THAN       1, 0xc6
#define HID_USAGE_KEY_PAD_RIGHT_ANGLE      1, 0xc6
#define HID_USAGE_KEY_PAD_AMPERSAND        1, 0xc7
#define HID_USAGE_KEY_PAD_BINARY_AND       1, 0xc7
#define HID_USAGE_KEY_PAD_LOGIC_AND        1, 0xc8
#define HID_USAGE_KEY_PAD_BINARY_OR        1, 0xc9
#define HID_USAGE_KEY_PAD_LOGIC_OR         1, 0xca
#define HID_USAGE_KEY_PAD_COLON            1, 0xcb
#define HID_USAGE_KEY_PAD_SHARP            1, 0xcc
#define HID_USAGE_KEY_PAD_SPACE            1, 0xcd
#define HID_USAGE_KEY_PAD_AT               1, 0xce
#define HID_USAGE_KEY_PAD_LOGIC_NOT        1, 0xcf
#define HID_USAGE_KEY_PAD_EXCLAMATION      1, 0xcf
#define HID_USAGE_KEY_PAD_MEMORY_STORE     1, 0xd0
#define HID_USAGE_KEY_PAD_MEMORY_RECALL    1, 0xd1
#define HID_USAGE_KEY_PAD_MEMORY_CLEAR     1, 0xd2
#define HID_USAGE_KEY_PAD_MEMORY_ADD       1, 0xd3
#define HID_USAGE_KEY_PAD_MEMORY_SUBSTRACT 1, 0xd4
#define HID_USAGE_KEY_PAD_MEMORY_MULTIPLY  1, 0xd5
#define HID_USAGE_KEY_PAD_MEMORY_DIVIDE    1, 0xd6
#define HID_USAGE_KEY_PAD_PLUS_MINUS       1, 0xd7
#define HID_USAGE_KEY_PAD_CLEAR            1, 0xd8
#define HID_USAGE_KEY_PAD_CLEAR_ENTRY      1, 0xd9
#define HID_USAGE_KEY_PAD_BINARY           1, 0xda
#define HID_USAGE_KEY_PAD_OCTAL            1, 0xdb
#define HID_USAGE_KEY_PAD_DECIMAL          1, 0xdc
#define HID_USAGE_KEY_PAD_HEXADECIMAL      1, 0xdd

#define HID_USAGE_KEY_LEFT_CONTROL  1, 0xe0
#define HID_USAGE_KEY_LEFT_SHIFT    1, 0xe1
#define HID_USAGE_KEY_LEFT_ALT      1, 0xe2
#define HID_USAGE_KEY_LEFT_GUI      1, 0xe3
#define HID_USAGE_KEY_RIGHT_CONTROL 1, 0xe4
#define HID_USAGE_KEY_RIGHT_SHIFT   1, 0xe5
#define HID_USAGE_KEY_RIGHT_ALT     1, 0xe6
#define HID_USAGE_KEY_RIGHT_GUI     1, 0xe7

/* LED Usages */
#define HID_USAGE_NUM_LOCK                   1, 0x01
#define HID_USAGE_CAPS_LOCK                  1, 0x02
#define HID_USAGE_SCROLL_LOCK                1, 0x03
#define HID_USAGE_COMPOSE                    1, 0x04
#define HID_USAGE_KANA                       1, 0x05
#define HID_USAGE_POWER                      1, 0x06
#define HID_USAGE_SHIFT                      1, 0x07
#define HID_USAGE_DO_NOT_DISTURB             1, 0x08
#define HID_USAGE_MUTE                       1, 0x09
#define HID_USAGE_TONE_ENABLE                1, 0x0a
#define HID_USAGE_HIGH_CUT_FILTER            1, 0x0b
#define HID_USAGE_LOW_CUT_FILTER             1, 0x0c
#define HID_USAGE_EQUALIZER_ENABLE           1, 0x0d
#define HID_USAGE_SOUND_FIELD_ON             1, 0x0e
#define HID_USAGE_SURROUND_ON                1, 0x0f
#define HID_USAGE_REPEAT                     1, 0x10
#define HID_USAGE_STEREO                     1, 0x11
#define HID_USAGE_SAMPLING_RATE_DETECT       1, 0x12
#define HID_USAGE_SPINNING                   1, 0x13
#define HID_USAGE_CAV                        1, 0x14
#define HID_USAGE_CLV                        1, 0x15
#define HID_USAGE_RECORDING_FORMAT_DETECT    1, 0x16
#define HID_USAGE_OFF_HOOK                   1, 0x17
#define HID_USAGE_RING                       1, 0x18
#define HID_USAGE_MESSAGE_WAITING            1, 0x19
#define HID_USAGE_DATA_MODE                  1, 0x1a
#define HID_USAGE_BATTERY_OPERATION          1, 0x1b
#define HID_USAGE_BATTERY_OK                 1, 0x1c
#define HID_USAGE_BATTERY_LOW                1, 0x1d
#define HID_USAGE_SPEAKER                    1, 0x1e
#define HID_USAGE_HEAD_SET                   1, 0x1f
#define HID_USAGE_HOLD                       1, 0x20
#define HID_USAGE_MICROPHONE                 1, 0x21
#define HID_USAGE_COVERAGE                   1, 0x22
#define HID_USAGE_NIGHT_MODE                 1, 0x23
#define HID_USAGE_SEND_CALLS                 1, 0x24
#define HID_USAGE_CALL_PICKUP                1, 0x25
#define HID_USAGE_CONFERENCE                 1, 0x26
#define HID_USAGE_STAND_BY                   1, 0x27
#define HID_USAGE_CAMERA_ON                  1, 0x28
#define HID_USAGE_CAMERA_OFF                 1, 0x29
#define HID_USAGE_ON_LINE                    1, 0x2a
#define HID_USAGE_OFF_LINE                   1, 0x2b
#define HID_USAGE_BUSY                       1, 0x2c
#define HID_USAGE_READY                      1, 0x2d
#define HID_USAGE_PAPER_OUT                  1, 0x2e
#define HID_USAGE_PAPER_JAM                  1, 0x2f
#define HID_USAGE_REMOTE                     1, 0x30
#define HID_USAGE_FORWARD                    1, 0x31
#define HID_USAGE_REVERSE                    1, 0x32
#define HID_USAGE_STOP                       1, 0x33
#define HID_USAGE_REWIND                     1, 0x34
#define HID_USAGE_FAST_FORWARD               1, 0x35
#define HID_USAGE_PLAY                       1, 0x36
#define HID_USAGE_PAUSE                      1, 0x37
#define HID_USAGE_RECORD                     1, 0x38
#define HID_USAGE_ERROR                      1, 0x39
#define HID_USAGE_USAGE_SELECTED_INDICATOR   1, 0x3a
#define HID_USAGE_USAGE_IN_USE_INDICATOR     1, 0x3b
#define HID_USAGE_USAGE_MULTI_MODE_INDICATOR 1, 0x3c
#define HID_USAGE_INDICATOR_ON               1, 0x3d
#define HID_USAGE_INDICATOR_FLASH            1, 0x3e
#define HID_USAGE_INDICATOR_SLOW_BLINK       1, 0x3f
#define HID_USAGE_INDICATOR_FAST_BLINK       1, 0x40
#define HID_USAGE_INDICATOR_OFF              1, 0x41
#define HID_USAGE_FLASH_ON_TIME              1, 0x42
#define HID_USAGE_SLOW_BLINK_ON_TIME         1, 0x43
#define HID_USAGE_SLOW_BLINK_OFF_TIME        1, 0x44
#define HID_USAGE_FAST_BLINK_ON_TIME         1, 0x45
#define HID_USAGE_FAST_BLINK_OFF_TIME        1, 0x46
#define HID_USAGE_USAGE_INDICATOR_COLOR      1, 0x47
#define HID_USAGE_INDICATOR_RED              1, 0x48
#define HID_USAGE_INDICATOR_GREEN            1, 0x49
#define HID_USAGE_INDICATOR_AMBER            1, 0x4a
#define HID_USAGE_GENERIC_INDICATOR          1, 0x4b
#define HID_USAGE_SYSTEM_SUSPEND             1, 0x4c
#define HID_USAGE_EXTERNAL_POWER_CONNECTED   1, 0x4d

/* Button Usages */
#define HID_USAGE_BUTTON_PRIMARY   1, 0x01
#define HID_USAGE_BUTTON_TRIGGER   1, 0x01
#define HID_USAGE_BUTTON_SECONDARY 1, 0x02
#define HID_USAGE_BUTTON_TERTIARY  1, 0x03
#define HID_USAGE_BUTTON(n, x)     n, (0x00 + (_ASSERT(1 <= (n) && (n) <= 2 && 1 <= (x) && (x) <= ((n) == 1 ? 0xff : 0xffff)) ? (x) : (0))) /* x: [1..255] (n:1) or [1..65535] (n:2) */

/* Ordinal Usages */
#define HID_USAGE_INSTANCE(n, x)   n, (0x00 + (_ASSERT(1 <= (n) && (n) <= 2 && 1 <= (x) && (x) <= ((n) == 1 ? 0xff : 0xffff)) ? (x) : (0))) /* x: [1..255] (n:1) or [1..65535] (n:2) */

/* Telephony Usages */
#define HID_USAGE_PHONE                1, 0x01
#define HID_USAGE_ANSWERING_MACHINE    1, 0x02
#define HID_USAGE_MESSAGE_CONTROLS     1, 0x03
#define HID_USAGE_HANDSET              1, 0x04
#define HID_USAGE_HEADSET              1, 0x05
#define HID_USAGE_TELEPHONY_KEYPAD     1, 0x06
#define HID_USAGE_PROGRAMMABLE_BUTTON  1, 0x07

#define HID_USAGE_HOOK_SWITCH          1, 0x20
#define HID_USAGE_FLASH                1, 0x21
#define HID_USAGE_FEATURE              1, 0x22
#define HID_USAGE_TELEPHONY_HOLD       1, 0x23
#define HID_USAGE_REDIAL               1, 0x24
#define HID_USAGE_TRANSFER             1, 0x25
#define HID_USAGE_DROP                 1, 0x26
#define HID_USAGE_PARK                 1, 0x27
#define HID_USAGE_FORWARD_CALLS        1, 0x28
#define HID_USAGE_ALTERNATE_FUNCTION   1, 0x29
#define HID_USAGE_LINE                 1, 0x2a
#define HID_USAGE_SPEAKER_PHONE        1, 0x2b
#define HID_USAGE_TELEPHONY_CONFERENCE 1, 0x2c
#define HID_USAGE_RING_ENABLE          1, 0x2d
#define HID_USAGE_RING_SELECT          1, 0x2e
#define HID_USAGE_PHONE_MUTE           1, 0x2f

#define HID_USAGE_CALLER_ID 1, 0x30
#define HID_USAGE_SEND      1, 0x31

#define HID_USAGE_SPEED_DIAL      1, 0x50
#define HID_USAGE_STORE_NUMBER    1, 0x51
#define HID_USAGE_RECALL_NUMBER   1, 0x52
#define HID_USAGE_PHONE_DIRECTORY 1, 0x53

#define HID_USAGE_VOICE_MAIL     1, 0x70
#define HID_USAGE_SCREEN_CALLS   1, 0x71
#define HID_USAGE_TELEPHONY_DO_NOT_DISTURB 1, 0x72
#define HID_USAGE_MESSAGE        1, 0x73
#define HID_USAGE_ANSWER_ON_OFF  1, 0x74

#define HID_USAGE_INSIDE_DIAL_TONE    1, 0x90
#define HID_USAGE_OUTSIDE_DIAL_TONE   1, 0x91
#define HID_USAGE_INSIDE_RING_TONE    1, 0x92
#define HID_USAGE_OUTSIDE_RING_TONE   1, 0x93
#define HID_USAGE_PRIORITY_RING_TONE  1, 0x94
#define HID_USAGE_INSIDE_RINGBACK     1, 0x95
#define HID_USAGE_PRIORITY_RINGBACK   1, 0x96
#define HID_USAGE_LINE_BUSY_TONE      1, 0x97
#define HID_USAGE_REORDER_TONE        1, 0x98
#define HID_USAGE_CALL_WAITING_TONE   1, 0x99
#define HID_USAGE_CONFIRMATION_TONE_1 1, 0x9a
#define HID_USAGE_CONFIRMATION_TONE_2 1, 0x9b
#define HID_USAGE_TONES_OFF           1, 0x9c
#define HID_USAGE_OUTSIDE_RINGBACK    1, 0x9d
#define HID_USAGE_RINGER              1, 0x9e

#define HID_USAGE_PHONE_KEY_0     1, 0xb0
#define HID_USAGE_PHONE_KEY_1     1, 0xb1
#define HID_USAGE_PHONE_KEY_2     1, 0xb2
#define HID_USAGE_PHONE_KEY_3     1, 0xb3
#define HID_USAGE_PHONE_KEY_4     1, 0xb4
#define HID_USAGE_PHONE_KEY_5     1, 0xb5
#define HID_USAGE_PHONE_KEY_6     1, 0xb6
#define HID_USAGE_PHONE_KEY_7     1, 0xb7
#define HID_USAGE_PHONE_KEY_8     1, 0xb8
#define HID_USAGE_PHONE_KEY_9     1, 0xb9
#define HID_USAGE_PHONE_KEY_STAR  1, 0xba
#define HID_USAGE_PHONE_KEY_POUND 1, 0xbb
#define HID_USAGE_PHONE_KEY_A     1, 0xbc
#define HID_USAGE_PHONE_KEY_B     1, 0xbd
#define HID_USAGE_PHONE_KEY_C     1, 0xbe
#define HID_USAGE_PHONE_KEY_D     1, 0xbf

/* Consumer Usages */
#define HID_USAGE_CONSUMER_CONTROL     1, 0x01
#define HID_USAGE_NUMERIC_KEY_PAD      1, 0x02
#define HID_USAGE_PROGRAMMABLE_BUTTONS 1, 0x03
#define HID_USAGE_CUSTOMER_MICROPHONE  1, 0x04
#define HID_USAGE_CUSTOMER_HEADPHONE   1, 0x05
#define HID_USAGE_GRAPHIC_EQUALIZER    1, 0x06

#define HID_USAGE_PLUS_10  1, 0x20
#define HID_USAGE_PLUS_100 1, 0x21
#define HID_USAGE_AM_PM    1, 0x22

#define HID_USAGE_CUSTOMER_POWER   1, 0x30
#define HID_USAGE_CUSTOMER_RESET   1, 0x31
#define HID_USAGE_CUSTOMER_SLEEP   1, 0x32
#define HID_USAGE_SLEEP_AFTER      1, 0x33
#define HID_USAGE_SLEEP_MODE       1, 0x34
#define HID_USAGE_ILLUMINATION     1, 0x35
#define HID_USAGE_FUNCTION_BUTTONS 1, 0x36

#define HID_USAGE_MENU                1, 0x40
#define HID_USAGE_MENU_PICK           1, 0x41
#define HID_USAGE_MENU_UP             1, 0x42
#define HID_USAGE_MENU_DOWN           1, 0x43
#define HID_USAGE_MENU_LEFT           1, 0x44
#define HID_USAGE_MENU_RIGHT          1, 0x45
#define HID_USAGE_MENU_ESCAPE         1, 0x46
#define HID_USAGE_MENU_VALUE_INCREASE 1, 0x47
#define HID_USAGE_MENU_VALUE_DECREASE 1, 0x48

#define HID_USAGE_DATA_ON_SCREEN        1, 0x60
#define HID_USAGE_CLOSED_CAPTION        1, 0x61
#define HID_USAGE_CLOSED_CAPTION_SELECT 1, 0x62
#define HID_USAGE_VCR_TV                1, 0x63
#define HID_USAGE_BROADCAST_MODE        1, 0x64
#define HID_USAGE_SNAPSHOT              1, 0x65
#define HID_USAGE_STILL                 1, 0x66

#define HID_USAGE_SELECTION                  1, 0x80
#define HID_USAGE_ASSIGN_SELECTION           1, 0x81
#define HID_USAGE_MODE_STEP                  1, 0x82
#define HID_USAGE_RECALL_LAST                1, 0x83
#define HID_USAGE_ENTER_CHANNEL              1, 0x84
#define HID_USAGE_ORDER_MOVIE                1, 0x85
#define HID_USAGE_CHANNEL                    1, 0x86
#define HID_USAGE_MEDIA_SELECTION            1, 0x87
#define HID_USAGE_MEDIA_SELECT_COMPUTER      1, 0x88
#define HID_USAGE_MEDIA_SELECT_TV            1, 0x89
#define HID_USAGE_MEDIA_SELECT_WWW           1, 0x8a
#define HID_USAGE_MEDIA_SELECT_DVD           1, 0x8b
#define HID_USAGE_MEDIA_SELECT_TELEPHONE     1, 0x8c
#define HID_USAGE_MEDIA_SELECT_PROGRAM_GUIDE 1, 0x8d
#define HID_USAGE_MEDIA_SELECT_VIDEO_PHONE   1, 0x8e
#define HID_USAGE_MEDIA_SELECT_GAMES         1, 0x8f
#define HID_USAGE_MEDIA_SELECT_MESSAGES      1, 0x90
#define HID_USAGE_MEDIA_SELECT_CD            1, 0x91
#define HID_USAGE_MEDIA_SELECT_VCR           1, 0x92
#define HID_USAGE_MEDIA_SELECT_TUNER         1, 0x93
#define HID_USAGE_QUIT                       1, 0x94
#define HID_USAGE_HELP                       1, 0x95
#define HID_USAGE_MEDIA_SELECT_TAPE          1, 0x96
#define HID_USAGE_MEDIA_SELECT_CABLE         1, 0x97
#define HID_USAGE_MEDIA_SELECT_SATELLITE     1, 0x98
#define HID_USAGE_MEDIA_SELECT_SECURITY      1, 0x99
#define HID_USAGE_MEDIA_SELECT_HOME          1, 0x9a
#define HID_USAGE_MEDIA_SELECT_CALL          1, 0x9b
#define HID_USAGE_CHANNEL_INCREMENT          1, 0x9c
#define HID_USAGE_CHANNEL_DECREMENT          1, 0x9d
#define HID_USAGE_MEDIA_SELECT_SAP           1, 0x9e

#define HID_USAGE_VCR_PLUS 1, 0xa0
#define HID_USAGE_ONCE     1, 0xa1
#define HID_USAGE_DAILY    1, 0xa2
#define HID_USAGE_WEEKLY   1, 0xa3
#define HID_USAGE_MONTHLY  1, 0xa4

#define HID_USAGE_CUSTOMER_PLAY         1, 0xb0
#define HID_USAGE_CUSTOMER_PAUSE        1, 0xb1
#define HID_USAGE_CUSTOMER_RECORD       1, 0xb2
#define HID_USAGE_CUSTOMER_FAST_FORWARD 1, 0xb3
#define HID_USAGE_CUSTOMER_REWIND       1, 0xb4
#define HID_USAGE_SCAN_NEXT_TRACK       1, 0xb5
#define HID_USAGE_SCAN_PREVIOUS_TRACK   1, 0xb6
#define HID_USAGE_CUSTOMER_STOP         1, 0xb7
#define HID_USAGE_CUSTOMER_EJECT        1, 0xb8
#define HID_USAGE_RANDOM_PLAY           1, 0xb9
#define HID_USAGE_SELECT_DISC           1, 0xba
#define HID_USAGE_ENTER_DISC            1, 0xbb
#define HID_USAGE_CUSTOMER_REPEAT       1, 0xbc
#define HID_USAGE_TRACKING              1, 0xbd
#define HID_USAGE_TRACK_NORMAL          1, 0xbe
#define HID_USAGE_SLOW_TRACKING         1, 0xbf
#define HID_USAGE_FRAME_FORWARD         1, 0xc0
#define HID_USAGE_FRAME_BACK            1, 0xc1
#define HID_USAGE_MARK                  1, 0xc2
#define HID_USAGE_CLEAR_MARK            1, 0xc3
#define HID_USAGE_REPEAT_FROM_MARK      1, 0xc4
#define HID_USAGE_RETURN_TO_MARK        1, 0xc5
#define HID_USAGE_SEARCH_MARK_FORWARD   1, 0xc6
#define HID_USAGE_SEARCH_MARK_BACKWARDS 1, 0xc7
#define HID_USAGE_COUNTER_RESET         1, 0xc8
#define HID_USAGE_SHOW_COUNTER          1, 0xc9
#define HID_USAGE_TRACKING_INCREMENT    1, 0xca
#define HID_USAGE_TRACKING_DECREMENT    1, 0xcb
#define HID_USAGE_STOP_EJECT            1, 0xcc
#define HID_USAGE_PLAY_PAUSE            1, 0xcd
#define HID_USAGE_PLAY_SKIP             1, 0xce

#define HID_USAGE_VOLUME           1, 0xe0
#define HID_USAGE_BALANCE          1, 0xe1
#define HID_USAGE_CUSTOMER_MUTE    1, 0xe2
#define HID_USAGE_BASS             1, 0xe3
#define HID_USAGE_TREBLE           1, 0xe4
#define HID_USAGE_BASS_BOOST       1, 0xe5
#define HID_USAGE_SURROUND_MODE    1, 0xe6
#define HID_USAGE_LOUDNESS         1, 0xe7
#define HID_USAGE_MPX              1, 0xe8
#define HID_USAGE_VOLUME_INCREMENT 1, 0xe9
#define HID_USAGE_VOLUME_DECREMENT 1, 0xea

#define HID_USAGE_SPEED_SELECT   1, 0xf0
#define HID_USAGE_PLAYBACK_SPEED 1, 0xf1
#define HID_USAGE_STANDARD_PLAY  1, 0xf2
#define HID_USAGE_LONG_PLAY      1, 0xf3
#define HID_USAGE_EXTENDED_PLAY  1, 0xf4
#define HID_USAGE_SLOW           1, 0xf5

#define HID_USAGE_FAN_ENABLE               2, 0x100
#define HID_USAGE_FAN_SPEED                2, 0x101
#define HID_USAGE_LIGHT_ENABLE             2, 0x102
#define HID_USAGE_LIGHT_ILLUMINATION_LEVEL 2, 0x103
#define HID_USAGE_CLIMATE_CONTROL_ENABLE   2, 0x104
#define HID_USAGE_ROOM_TEMPERATURE         2, 0x105
#define HID_USAGE_SECURITY_ENABLE          2, 0x106
#define HID_USAGE_FIRE_ALARM               2, 0x107
#define HID_USAGE_POLICE_ALARM             2, 0x108
#define HID_USAGE_PROXIMITY                2, 0x109
#define HID_USAGE_MOTION                   2, 0x10a
#define HID_USAGE_DURESS_ALARM             2, 0x10b
#define HID_USAGE_HOLDUP_ALARM             2, 0x10c
#define HID_USAGE_MEDICAL_ALARM            2, 0x10d

#define HID_USAGE_BALANCE_RIGHT    2, 0x150
#define HID_USAGE_BALANCE_LEFT     2, 0x151
#define HID_USAGE_BASS_INCREMENT   2, 0x152
#define HID_USAGE_BASS_DECREMENT   2, 0x153
#define HID_USAGE_TREBLE_INCREMENT 2, 0x154
#define HID_USAGE_TREBLE_DECREMENT 2, 0x155

#define HID_USAGE_SPEAKER_SYSTEM                    2, 0x160
#define HID_USAGE_CHANNEL_LEFT                      2, 0x161
#define HID_USAGE_CHANNEL_RIGHT                     2, 0x162
#define HID_USAGE_CHANNEL_CENTER                    2, 0x163
#define HID_USAGE_CHANNEL_FRONT                     2, 0x164
#define HID_USAGE_CHANNEL_CENTER_FRONT              2, 0x165
#define HID_USAGE_CHANNEL_SIDE                      2, 0x166
#define HID_USAGE_CHANNEL_SURROUND                  2, 0x167
#define HID_USAGE_CHANNEL_LOW_FREQUENCY_ENHANCEMENT 2, 0x168
#define HID_USAGE_CHANNEL_TOP                       2, 0x169
#define HID_USAGE_CHANNEL_UNKNOWN                   2, 0x16a

#define HID_USAGE_SUB_CHANNEL               2, 0x170
#define HID_USAGE_SUB_CHANNEL_INCREMENT     2, 0x171
#define HID_USAGE_SUB_CHANNEL_DECREMENT     2, 0x172
#define HID_USAGE_ALTERNATE_AUDIO_INCREMENT 2, 0x173
#define HID_USAGE_ALTERNATE_AUDIO_DECREMENT 2, 0x174

#define HID_USAGE_APPLICATION_LAUNCH_BUTTONS            2, 0x180
#define HID_USAGE_AL_LAUNCH_BUTTON_CONFIGURATION_TOOL   2, 0x181
#define HID_USAGE_AL_PROGRAMMABLE_BUTTON_CONFIGURATION  2, 0x182
#define HID_USAGE_AL_CONSUMER_CONTROL_CONFIGURATION     2, 0x183
#define HID_USAGE_AL_WORD_PROCESSOR                     2, 0x184
#define HID_USAGE_AL_TEXT_EDITOR                        2, 0x185
#define HID_USAGE_AL_SPREADSHEET                        2, 0x186
#define HID_USAGE_AL_GRAPHICS_EDITOR                    2, 0x187
#define HID_USAGE_AL_PRESENTATION_APP                   2, 0x188
#define HID_USAGE_AL_DATABASE_APP                       2, 0x189
#define HID_USAGE_AL_EMAIL_READER                       2, 0x18a
#define HID_USAGE_AL_NEWS_READER                        2, 0x18b
#define HID_USAGE_AL_VOICE_MAIL                         2, 0x18c
#define HID_USAGE_AL_CONTACTS_ADDRESS_BOOK              2, 0x18d
#define HID_USAGE_AL_CALENDAR_SCHEDULE                  2, 0x18e
#define HID_USAGE_AL_TASK_PROJECT_MANAGER               2, 0x18f
#define HID_USAGE_AL_LOG_JOURNAL_TIMECARD               2, 0x190
#define HID_USAGE_AL_CHECKBOOK_FINANCE                  2, 0x191
#define HID_USAGE_AL_CALCULATOR                         2, 0x192
#define HID_USAGE_AL_AV_CAPTURE_PLAYBACK                2, 0x193
#define HID_USAGE_AL_LOCAL_MACHINE_BROWSER              2, 0x194
#define HID_USAGE_AL_LAN_WAN_BROWSER                    2, 0x195
#define HID_USAGE_AL_INTERNET_BROWSER                   2, 0x196
#define HID_USAGE_AL_REMOTE_NETWORKING_ISP_CONNECT      2, 0x197
#define HID_USAGE_AL_NETWORK_CONFERENCE                 2, 0x198
#define HID_USAGE_AL_NETWORK_CHAT                       2, 0x199
#define HID_USAGE_AL_TELEPHONE_DIALER                   2, 0x19a
#define HID_USAGE_AL_LOGON                              2, 0x19b
#define HID_USAGE_AL_LOGOFF                             2, 0x19c
#define HID_USAGE_AL_LOGON_LOGOFF                       2, 0x19d
#define HID_USAGE_AL_TERMINAL_LOCK_SCREENSAVER          2, 0x19e
#define HID_USAGE_AL_CONTROL_PANEL                      2, 0x19f
#define HID_USAGE_AL_COMMAND_LINE_PROCESSOR_RUN         2, 0x1a0
#define HID_USAGE_AL_PROCESS_TASK_MANAGER               2, 0x1a1
#define HID_USAGE_AL_SELECT_TASK_APPLICATION            2, 0x1a2
#define HID_USAGE_AL_NEXT_TASK_APPLICATION              2, 0x1a3
#define HID_USAGE_AL_PREVIOUS_TASK_APPLICATION          2, 0x1a4
#define HID_USAGE_AL_PREEMPTIVE_HALT_TASK_APPLICATION   2, 0x1a5
#define HID_USAGE_AL_INTEGRATED_HELP_CENTER             2, 0x1a6
#define HID_USAGE_AL_DOCUMENTS                          2, 0x1a7
#define HID_USAGE_AL_THESAURUS                          2, 0x1a8
#define HID_USAGE_AL_DICTIONARY                         2, 0x1a9
#define HID_USAGE_AL_DESKTOP                            2, 0x1aa
#define HID_USAGE_AL_SPELL_CHECK                        2, 0x1ab
#define HID_USAGE_AL_GRAMMAR_CHECK                      2, 0x1ac
#define HID_USAGE_AL_WIRELESS_STATUS                    2, 0x1ad
#define HID_USAGE_AL_KEYBOARD_LAYOUT                    2, 0x1ae
#define HID_USAGE_AL_VIRUS_PROTECTION                   2, 0x1af
#define HID_USAGE_AL_ENCRYPTION                         2, 0x1b0
#define HID_USAGE_AL_SCREEN_SAVER                       2, 0x1b1
#define HID_USAGE_AL_ALARMS                             2, 0x1b2
#define HID_USAGE_AL_CLOCK                              2, 0x1b3
#define HID_USAGE_AL_FILE_BROWSER                       2, 0x1b4
#define HID_USAGE_AL_POWER_STATUS                       2, 0x1b5
#define HID_USAGE_AL_IMAGE_BROWSER                      2, 0x1b6
#define HID_USAGE_AL_AUDIO_BROWSER                      2, 0x1b7
#define HID_USAGE_AL_MOVIE_BROWSER                      2, 0x1b8
#define HID_USAGE_AL_DIGITAL_RIGHTS_MANAGER             2, 0x1b9
#define HID_USAGE_AL_DIGITAL_WALLET                     2, 0x1ba

#define HID_USAGE_AL_INSTANT_MESSAGING                  2, 0x1bc
#define HID_USAGE_AL_OEM_FEATURES_TIPS_TUTORIAL_BROWSER 2, 0x1bd
#define HID_USAGE_AL_OEM_HELP                           2, 0x1be
#define HID_USAGE_AL_ONLINE_COMMUNITY                   2, 0x1bf
#define HID_USAGE_AL_ENTERTAINMENT_CONTENT_BROWSER      2, 0x1c0
#define HID_USAGE_AL_ONLINE_SHOPPING_BROWSER            2, 0x1c1
#define HID_USAGE_AL_SMARTCARD_INFORMATION_HELP         2, 0x1c2
#define HID_USAGE_AL_MARKET_MONITOR_FINANCE_BROWSER     2, 0x1c3
#define HID_USAGE_AL_CUSTOMIZED_CORPORATE_NEWS_BROWSER  2, 0x1c4
#define HID_USAGE_AL_ONLINE_ACTIVITY_BROWSER            2, 0x1c5
#define HID_USAGE_AL_RESEARCH_SEARCH_BROWSER            2, 0x1c6
#define HID_USAGE_AL_AUDIO_PLAYER                       2, 0x1c7

#define HID_USAGE_GENERIC_GUI_APPLICATION_CONTROLS 2, 0x200
#define HID_USAGE_AC_NEW        2, 0x201
#define HID_USAGE_AC_OPEN       2, 0x202
#define HID_USAGE_AC_CLOSE      2, 0x203
#define HID_USAGE_AC_EXIT       2, 0x204
#define HID_USAGE_AC_MAXIMIZE   2, 0x205
#define HID_USAGE_AC_MINIMIZE   2, 0x206
#define HID_USAGE_AC_SAVE       2, 0x207
#define HID_USAGE_AC_PRINT      2, 0x208
#define HID_USAGE_AC_PROPERTIES 2, 0x209

#define HID_USAGE_AC_UNDO       2, 0x21a
#define HID_USAGE_AC_COPY       2, 0x21b
#define HID_USAGE_AC_CUT        2, 0x21c
#define HID_USAGE_AC_PASTE      2, 0x21d
#define HID_USAGE_AC_SELECT_ALL 2, 0x21e
#define HID_USAGE_AC_FIND       2, 0x21f

#define HID_USAGE_AC_FIND_AND_REPLACE  2, 0x220
#define HID_USAGE_AC_SEARCH            2, 0x221
#define HID_USAGE_AC_GO_TO             2, 0x222
#define HID_USAGE_AC_HOME              2, 0x223
#define HID_USAGE_AC_BACK              2, 0x224
#define HID_USAGE_AC_FORWARD           2, 0x225
#define HID_USAGE_AC_STOP              2, 0x226
#define HID_USAGE_AC_REFRESH           2, 0x227
#define HID_USAGE_AC_PREVIOUS_LINK     2, 0x228
#define HID_USAGE_AC_NEXT_LINK         2, 0x229
#define HID_USAGE_AC_BOOKMARKS         2, 0x22a
#define HID_USAGE_AC_HISTORY           2, 0x22b
#define HID_USAGE_AC_SUBSCRIPTIONS     2, 0x22c
#define HID_USAGE_AC_ZOOM_IN           2, 0x22d
#define HID_USAGE_AC_ZOOM_OUT          2, 0x22e
#define HID_USAGE_AC_ZOOM              2, 0x22f
#define HID_USAGE_AC_FULL_SCREEN_VIEW  2, 0x230
#define HID_USAGE_AC_NORMAL_VIEW       2, 0x231
#define HID_USAGE_AC_VIEW_TOGGLE       2, 0x232
#define HID_USAGE_AC_SCROLL_UP         2, 0x233
#define HID_USAGE_AC_SCROLL_DOWN       2, 0x234
#define HID_USAGE_AC_SCROLL            2, 0x325
#define HID_USAGE_AC_PAN_LEFT          2, 0x236
#define HID_USAGE_AC_PAN_RIGHT         2, 0x237
#define HID_USAGE_AC_PAN               2, 0x238
#define HID_USAGE_AC_NEW_WINDOW        2, 0x239
#define HID_USAGE_AC_TILE_HORIZONTALLY 2, 0x23a
#define HID_USAGE_AC_TILE_VERTICALLY   2, 0x23b
#define HID_USAGE_AC_FORMAT            2, 0x23c
#define HID_USAGE_AC_EDIT              2, 0x23d
#define HID_USAGE_AC_BOLD              2, 0x23e
#define HID_USAGE_AC_ITALICS           2, 0x23f
#define HID_USAGE_AC_UNDERLINE         2, 0x240
#define HID_USAGE_AC_STRIKETHROUGH     2, 0x241
#define HID_USAGE_AC_SUBSCRIPT         2, 0x242
#define HID_USAGE_AC_SUPERSCRIPT       2, 0x243
#define HID_USAGE_AC_ALL_CAPS          2, 0x244
#define HID_USAGE_AC_ROATE             2, 0x245
#define HID_USAGE_AC_RESIZE            2, 0x246
#define HID_USAGE_AC_FLIP_HORIZONTAL   2, 0x247
#define HID_USAGE_AC_FLIP_VERTICAL     2, 0x248
#define HID_USAGE_AC_MIRROR_HORIZONTAL 2, 0x249
#define HID_USAGE_AC_MIRROR_VERTICAL   2, 0x24a
#define HID_USAGE_AC_FONT_SELECT       2, 0x24b
#define HID_USAGE_AC_FONT_COLOR        2, 0x24c
#define HID_USAGE_AC_FONT_SIZE         2, 0x24d
#define HID_USAGE_AC_JUSTIFY_LEFT      2, 0x24e
#define HID_USAGE_AC_JUSTIFY_CENTER_H  2, 0x24f
#define HID_USAGE_AC_JUSTIFY_RIGHT     2, 0x250
#define HID_USAGE_AC_JUSTIFY_BLOCK_H   2, 0x251
#define HID_USAGE_AC_JUSTIFY_TOP       2, 0x252
#define HID_USAGE_AC_JUSTIFY_CENTER_V  2, 0x253
#define HID_USAGE_AC_JUSTIFY_BOTTOM    2, 0x254
#define HID_USAGE_AC_JUSTIFY_BLOCK_V   2, 0x255
#define HID_USAGE_AC_INDENT_DECREASE   2, 0x256
#define HID_USAGE_AC_INDENT_INCREASE   2, 0x257
#define HID_USAGE_AC_NUMBERED_LIST     2, 0x258
#define HID_USAGE_AC_RESTART_NUMBERING 2, 0x259
#define HID_USAGE_AC_BULLETED_LIST     2, 0x25a
#define HID_USAGE_AC_PROMOTE           2, 0x25b
#define HID_USAGE_AC_DEMOTE            2, 0x25c
#define HID_USAGE_AC_YES               2, 0x25d
#define HID_USAGE_AC_NO                2, 0x25e
#define HID_USAGE_AC_CANCEL            2, 0x25f
#define HID_USAGE_AC_CATALOG           2, 0x260
#define HID_USAGE_AC_BUY_CHECKOUT      2, 0x261
#define HID_USAGE_AC_ADD_TO_CART       2, 0x262
#define HID_USAGE_AC_EXPAND            2, 0x263
#define HID_USAGE_AC_EXPAND_ALL        2, 0x264
#define HID_USAGE_AC_COLLAPSE          2, 0x265
#define HID_USAGE_AC_COLLAPSE_ALL      2, 0x266
#define HID_USAGE_AC_PRINT_PREVIEW     2, 0x267
#define HID_USAGE_AC_PASTE_SPECIAL     2, 0x268
#define HID_USAGE_AC_INSERT_MODE       2, 0x269
#define HID_USAGE_AC_DELETE            2, 0x26a
#define HID_USAGE_AC_LOCK              2, 0x26b
#define HID_USAGE_AC_UNLOCK            2, 0x26c
#define HID_USAGE_AC_PROTECT           2, 0x26d
#define HID_USAGE_AC_UNPROTECT         2, 0x26e
#define HID_USAGE_AC_ATTACH_COMMENT    2, 0x26f
#define HID_USAGE_AC_DELETE_COMMENT    2, 0x270
#define HID_USAGE_AC_VIEW_COMMENT      2, 0x271
#define HID_USAGE_AC_SELECT_WORD       2, 0x272
#define HID_USAGE_AC_SELECT_SENTENCE   2, 0x273
#define HID_USAGE_AC_SELECT_PARAGRAPH  2, 0x274
#define HID_USAGE_AC_SELECT_COLUMN     2, 0x275
#define HID_USAGE_AC_SELECT_ROW        2, 0x276
#define HID_USAGE_AC_SELECT_TABLE      2, 0x277
#define HID_USAGE_AC_SELECT_OBJECT     2, 0x278
#define HID_USAGE_AC_REDO_REPEAT       2, 0x279
#define HID_USAGE_AC_SORT              2, 0x27a
#define HID_USAGE_AC_SORT_ASCENDING    2, 0x27b
#define HID_USAGE_AC_SORT_DESCENDING   2, 0x27c
#define HID_USAGE_AC_FILTER            2, 0x27d
#define HID_USAGE_AC_SET_CLOCK         2, 0x27e
#define HID_USAGE_AC_VIEW_CLOCK        2, 0x27f
#define HID_USAGE_AC_SELECT_TIME_ZONE  2, 0x280
#define HID_USAGE_AC_EDIT_TIME_ZONES   2, 0x281
#define HID_USAGE_AC_SET_ALARM         2, 0x282
#define HID_USAGE_AC_CLEAR_ALARM       2, 0x283
#define HID_USAGE_AC_SNOOZE_ALARM      2, 0x284
#define HID_USAGE_AC_RESET_ALARM       2, 0x285
#define HID_USAGE_AC_SYNCHRONIZE       2, 0x286
#define HID_USAGE_AC_SEND_RECEIVE      2, 0x287
#define HID_USAGE_AC_SEND_TO           2, 0x288
#define HID_USAGE_AC_REPLY             2, 0x289
#define HID_USAGE_AC_REPLY_ALL         2, 0x28a
#define HID_USAGE_AC_FORWARD_MESSAGE   2, 0x28b
#define HID_USAGE_AC_SEND              2, 0x28c
#define HID_USAGE_AC_ATTACH_FILE       2, 0x28d
#define HID_USAGE_AC_UPLOAD            2, 0x28e
#define HID_USAGE_AC_DOWNLOAD          2, 0x28f
#define HID_USAGE_AC_SET_BORDERS       2, 0x290
#define HID_USAGE_AC_INSERT_ROW        2, 0x291
#define HID_USAGE_AC_INSERT_COLUMN     2, 0x292
#define HID_USAGE_AC_INSERT_FILE       2, 0x293
#define HID_USAGE_AC_INSERT_PICTURE    2, 0x294
#define HID_USAGE_AC_INSERT_OBJECT     2, 0x295
#define HID_USAGE_AC_INSERT_SYMBOL     2, 0x296
#define HID_USAGE_AC_SAVE_AND_CLOSE    2, 0x297
#define HID_USAGE_AC_RENAME            2, 0x298
#define HID_USAGE_AC_MERGE             2, 0x299
#define HID_USAGE_AC_SPLIT             2, 0x29a

#define HID_USAGE_AC_DISTRIBUTE_HORIZONTALLY 2, 0x29b
#define HID_USAGE_AC_DISTRIBUTE_VERTICALLY   2, 0x29c

/* Digitizer Usages */
#define HID_USAGE_DIGITIZER                    1, 0x01
#define HID_USAGE_PEN                          1, 0x02
#define HID_USAGE_LIGHT_PEN                    1, 0x03
#define HID_USAGE_TOUCH_SCREEN                 1, 0x04
#define HID_USAGE_TOUCH_PAD                    1, 0x05
#define HID_USAGE_WHITE_BOARD                  1, 0x06
#define HID_USAGE_COORDINATE_MEASURING_MACHINE 1, 0x07
#define HID_USAGE_DIGITIZER_3D                 1, 0x08
#define HID_USAGE_STEREO_PLOTTER               1, 0x09
#define HID_USAGE_ARTICULATED_ARM              1, 0x0a
#define HID_USAGE_ARMATURE                     1, 0x0b
#define HID_USAGE_MULTIPLE_POINT_DIGITIZER     1, 0x0c
#define HID_USAGE_FREE_SPACE_WAND              1, 0x0d

#define HID_USAGE_STYLUS 1, 0x20
#define HID_USAGE_PUCK   1, 0x21
#define HID_USAGE_FINGER 1, 0x22

#define HID_USAGE_TIP_PRESSURE         1, 0x30
#define HID_USAGE_BARREL_PRESSURE      1, 0x31
#define HID_USAGE_IN_RANGE             1, 0x32
#define HID_USAGE_TOUCH                1, 0x33
#define HID_USAGE_UNTOUCH              1, 0x34
#define HID_USAGE_TAP                  1, 0x35
#define HID_USAGE_QUALITY              1, 0x36
#define HID_USAGE_DATA_VALID           1, 0x37
#define HID_USAGE_TRANSDUCER_INDEX     1, 0x38
#define HID_USAGE_TABLET_FUNCTION_KEYS 1, 0x39
#define HID_USAGE_PROGRAM_CHANGE_KEYS  1, 0x3a
#define HID_USAGE_DIG_BATTERY_STRENGTH 1, 0x3b
#define HID_USAGE_INVERT               1, 0x3c
#define HID_USAGE_X_TILT               1, 0x3d
#define HID_USAGE_Y_TILT               1, 0x3e
#define HID_USAGE_AZIMUTH              1, 0x3f
#define HID_USAGE_ALTITUDE             1, 0x40
#define HID_USAGE_TWIST                1, 0x41
#define HID_USAGE_TIP_SWITCH           1, 0x42
#define HID_USAGE_SECONDARY_TIP_SWITCH 1, 0x43
#define HID_USAGE_BARREL_SWITCH        1, 0x44
#define HID_USAGE_ERASER               1, 0x45
#define HID_USAGE_TABLET_PICK          1, 0x46

/* Alphanumeric Display Usages */
#define HID_USAGE_ALPHANUMERIC_DISPLAY 1, 0x01
#define HID_USAGE_BITMAPPED_DISPLAY    1, 0x02

#define HID_USAGE_DISPLAY_ATTRIBUTES_REPORT   1, 0x20
#define HID_USAGE_ASCII_CHARACTER_SET         1, 0x21
#define HID_USAGE_DATA_READ_BACK              1, 0x22
#define HID_USAGE_FONT_READ_BACK              1, 0x23
#define HID_USAGE_DISPLAY_CONTROL_REPORT      1, 0x24
#define HID_USAGE_CLEAR_DISPLAY               1, 0x25
#define HID_USAGE_ALNUM_DISPLAY_ENABLE        1, 0x26
#define HID_USAGE_SCREEN_SAVER_DELAY          1, 0x27
#define HID_USAGE_SCREEN_SAVER_ENABLE         1, 0x28
#define HID_USAGE_VERTICAL_SCROLL             1, 0x29
#define HID_USAGE_HORIZONTAL_SCROLL           1, 0x2a
#define HID_USAGE_CHARACTER_REPORT            1, 0x2b
#define HID_USAGE_DISPLAY_DATA                1, 0x2c
#define HID_USAGE_DISPLAY_STATUS              1, 0x2d
#define HID_USAGE_STAT_NOT_READY              1, 0x2e
#define HID_USAGE_STAT_READY                  1, 0x2f
#define HID_USAGE_NOT_A_LOADABLE_CHARACTER    1, 0x30
#define HID_USAGE_FONT_DATA_CANNOT_BE_READ    1, 0x31
#define HID_USAGE_CURSOR_POSITION_REPORT      1, 0x32
#define HID_USAGE_ROW                         1, 0x33
#define HID_USAGE_COLUMN                      1, 0x34
#define HID_USAGE_ROWS                        1, 0x35
#define HID_USAGE_COLUMNS                     1, 0x36
#define HID_USAGE_CURSOR_PIXEL_POSITION       1, 0x37
#define HID_USAGE_CURSOR_MODE                 1, 0x38
#define HID_USAGE_CURSOR_ENABLE               1, 0x39
#define HID_USAGE_CURSOR_BLINK                1, 0x3a
#define HID_USAGE_FONT_REPORT                 1, 0x3b
#define HID_USAGE_FONT_DATA                   1, 0x3c
#define HID_USAGE_CHARACTER_WIDTH             1, 0x3d
#define HID_USAGE_CHARACTER_HEIGHT            1, 0x3e
#define HID_USAGE_SPACING_HORIZONTAL          1, 0x3f
#define HID_USAGE_SPACING_VERTICAL            1, 0x40
#define HID_USAGE_UNICODE_CHARACTER_SET       1, 0x41
#define HID_USAGE_FONT_SEVEN_SEGMENT          1, 0x42
#define HID_USAGE_SEVEN_SEGMENT_DIRECT_MAP    1, 0x43
#define HID_USAGE_FONT_FOURTEEN_SEGMENT       1, 0x44
#define HID_USAGE_FOURTEEN_SEGMENT_DIRECT_MAP 1, 0x45
#define HID_USAGE_DISPLAY_BRIGHTNESS          1, 0x46
#define HID_USAGE_DISPLAY_CONTRAST            1, 0x47
#define HID_USAGE_CHARACTER_ATTRIBUTE         1, 0x48
#define HID_USAGE_ATTRIBUTE_READBACK          1, 0x49
#define HID_USAGE_ATTRIBUTE_DATA              1, 0x4a
#define HID_USAGE_CHAR_ATTR_ENHANCE           1, 0x4b
#define HID_USAGE_CHAR_ATTR_UNDERLINE         1, 0x4c
#define HID_USAGE_CHAR_ATTR_BLINK             1, 0x4d

#define HID_USAGE_BITMAP_SIZE_X 1, 0x80
#define HID_USAGE_BITMAP_SIZE_Y 1, 0x81

#define HID_USAGE_BIT_DEPTH_FORMAT     1, 0x83
#define HID_USAGE_DISPLAY_ORIENTATION  1, 0x84
#define HID_USAGE_PALETTE_REPORT       1, 0x85
#define HID_USAGE_PALETTE_DATA_SIZE    1, 0x86
#define HID_USAGE_PALETTE_DATA_OFFSET  1, 0x87
#define HID_USAGE_PALETTE_DATA         1, 0x88
#define HID_USAGE_BLIT_REPORT          1, 0x8a
#define HID_USAGE_BLIT_RECTANGLE_X1    1, 0x8b
#define HID_USAGE_BLIT_RECTANGLE_Y1    1, 0x8c
#define HID_USAGE_BLIT_RECTANGLE_X2    1, 0x8d
#define HID_USAGE_BLIT_RECTANGLE_Y2    1, 0x8e
#define HID_USAGE_BLIT_DATA            1, 0x8f
#define HID_USAGE_SOFT_BUTTON          1, 0x90
#define HID_USAGE_SOFT_BUTTON_ID       1, 0x91
#define HID_USAGE_SOFT_BUTTON_SIDE     1, 0x92
#define HID_USAGE_SOFT_BUTTON_OFFSET_1 1, 0x93
#define HID_USAGE_SOFT_BUTTON_OFFSET_2 1, 0x94
#define HID_USAGE_SOFT_BUTTON_REPORT   1, 0x95

/* Medical Instrument Usages */
#define HID_USAGE_MEDICAL_ULTRASOUND 1, 0x01

#define HID_USAGE_VCR_ACQUISITION   1, 0x20
#define HID_USAGE_FREEZE_THAW       1, 0x21
#define HID_USAGE_CLIP_STORE        1, 0x22
#define HID_USAGE_UPDATE            1, 0x23
#define HID_USAGE_NEXT              1, 0x24
#define HID_USAGE_SAVE              1, 0x25
#define HID_USAGE_PRINT             1, 0x26
#define HID_USAGE_MICROPHONE_ENABLE 1, 0x27

#define HID_USAGE_CINE           1, 0x40
#define HID_USAGE_TRANSMIT_POWER 1, 0x41
#define HID_USAGE_SOUND_VOLUME   1, 0x42
#define HID_USAGE_FOCUS          1, 0x43
#define HID_USAGE_DEPTH          1, 0x44

#define HID_USAGE_SOFT_STEP_PRIMARY   1, 0x60
#define HID_USAGE_SOFT_STEP_SECONDARY 1, 0x61

#define HID_USAGE_DEPTH_GAIN_COMPENSATION 1, 0x70

#define HID_USAGE_ZOOM_SELECT                  1, 0x80
#define HID_USAGE_ZOOM_ADJUST                  1, 0x81
#define HID_USAGE_SPECTRAL_DOPPLER_MODE_SELECT 1, 0x82
#define HID_USAGE_SPECTRAL_DOPPLER_ADJUST      1, 0x83
#define HID_USAGE_COLOR_DOPPLER_MODE_SELECT    1, 0x84
#define HID_USAGE_COLOR_DOPPLER_ADJUST         1, 0x85
#define HID_USAGE_MOTION_MODE_SELECT           1, 0x86
#define HID_USAGE_MOTION_MODE_ADJUST           1, 0x87
#define HID_USAGE_MODE_2D_SELECT               1, 0x88
#define HID_USAGE_MODE_2D_ADJUST               1, 0x89

#define HID_USAGE_SOFT_CONTROL_SELECT 1, 0xa0
#define HID_USAGE_SOFT_CONTROL_ADJUST 1, 0xa1

/* Power Device Usages */
#define HID_USAGE_INAME          1, 0x01
#define HID_USAGE_PRESENT_STATUS 1, 0x02
#define HID_USAGE_CHANGED_STATUS 1, 0x03
#define HID_USAGE_UPS            1, 0x04
#define HID_USAGE_POWER_SUPPLY   1, 0x05

#define HID_USAGE_BATTERY_SYSTEM     1, 0x10
#define HID_USAGE_BATTERY_SYSTEM_ID  1, 0x11
#define HID_USAGE_BATTERY            1, 0x12
#define HID_USAGE_BATTERY_ID         1, 0x13
#define HID_USAGE_CHARGER            1, 0x14
#define HID_USAGE_CHARGER_ID         1, 0x15
#define HID_USAGE_POWER_CONVERTER    1, 0x16
#define HID_USAGE_POWER_CONVERTER_ID 1, 0x17
#define HID_USAGE_OUTLET_SYSTEM      1, 0x18
#define HID_USAGE_OUTLET_SYSTEM_ID   1, 0x19
#define HID_USAGE_INPUT              1, 0x1a
#define HID_USAGE_INPUT_ID           1, 0x1b
#define HID_USAGE_OUTPUT             1, 0x1c
#define HID_USAGE_OUTPUT_ID          1, 0x1d
#define HID_USAGE_FLOW               1, 0x1e
#define HID_USAGE_FLOW_ID            1, 0x1f
#define HID_USAGE_OUTLET             1, 0x20
#define HID_USAGE_OUTLET_ID          1, 0x21
#define HID_USAGE_GANG               1, 0x22
#define HID_USAGE_GANG_ID            1, 0x23
#define HID_USAGE_POWER_SUMMARY      1, 0x24
#define HID_USAGE_POWER_SUMMARY_ID   1, 0x25

#define HID_USAGE_VOLTAGE        1, 0x30
#define HID_USAGE_CURRENT        1, 0x31
#define HID_USAGE_FREQUENCY      1, 0x32
#define HID_USAGE_APPARENT_POWER 1, 0x33
#define HID_USAGE_ACTIVE_POWER   1, 0x34
#define HID_USAGE_PERCENT_LOAD   1, 0x35
#define HID_USAGE_TEMPERATURE    1, 0x36
#define HID_USAGE_HUMIDITY       1, 0x37
#define HID_USAGE_BAD_COUNT      1, 0x38

#define HID_USAGE_CONFIG_VOLTAGE        1, 0x40
#define HID_USAGE_CONFIG_CURRENT        1, 0x41
#define HID_USAGE_CONFIG_FREQUENCY      1, 0x42
#define HID_USAGE_CONFIG_APPARENT_POWER 1, 0x43
#define HID_USAGE_CONFIG_ACTIVE_POWER   1, 0x44
#define HID_USAGE_CONFIG_PERCENT_LOAD   1, 0x45
#define HID_USAGE_CONFIG_TEMPERATURE    1, 0x46
#define HID_USAGE_CONFIG_HUMIDITY       1, 0x47

#define HID_USAGE_SWITCH_ON_CONTROL     1, 0x50
#define HID_USAGE_SWITCH_OFF_CONTROL    1, 0x51
#define HID_USAGE_TOGGLE_CONTROL        1, 0x52
#define HID_USAGE_LOW_VOLTAGE_TRANSFER  1, 0x53
#define HID_USAGE_HIGH_VOLTAGE_TRANSFER 1, 0x54
#define HID_USAGE_DELAY_BEFORE_REBOOT   1, 0x55
#define HID_USAGE_DELAY_BEFORE_STARTUP  1, 0x56
#define HID_USAGE_DELAY_BEFORE_SHUTDOWN 1, 0x57
#define HID_USAGE_TEST                  1, 0x58
#define HID_USAGE_MODULE_RESET          1, 0x59
#define HID_USAGE_AUDIBLE_ALARM_CONTROL 1, 0x5a

#define HID_USAGE_PRESENT                1, 0x60
#define HID_USAGE_GOOD                   1, 0x61
#define HID_USAGE_INTERNAL_FAILURE       1, 0x62
#define HID_USAGE_VOLTAGE_OUT_OF_RANGE_  1, 0x63
#define HID_USAGE_FREQUENCY_OUT_OF_RANGE 1, 0x64
#define HID_USAGE_OVER_LOAD              1, 0x65
#define HID_USAGE_OVER_CHARGED           1, 0x66
#define HID_USAGE_OVER_TEMPERATURE       1, 0x67
#define HID_USAGE_SHUTDOWN_REQUESTED     1, 0x68
#define HID_USAGE_SHUTDOWN_IMMINENT      1, 0x69

#define HID_USAGE_SWITCH_ON_OFF 1, 0x6b
#define HID_USAGE_SWITCHABLE    1, 0x6c
#define HID_USAGE_USED          1, 0x6d
#define HID_USAGE_BOOST         1, 0x6e
#define HID_USAGE_BUCK          1, 0x6f

#define HID_USAGE_INITIALIZED        1, 0x70
#define HID_USAGE_TESTED             1, 0x71
#define HID_USAGE_AWAITING_POWER     1, 0x72
#define HID_USAGE_COMMUNICATION_LOST 1, 0x73

#define HID_USAGE_IMANUFACTURER  1, 0xfd
#define HID_USAGE_IPRODUCT       1, 0xfe
#define HID_USAGE_ISERIAL_NUMBER 1, 0xff

/* Battery System Usages */
#define HID_USAGE_SMB_BATTERY_MODE      1, 0x01
#define HID_USAGE_SMB_BATTERY_STATUS    1, 0x02
#define HID_USAGE_SMB_ALARM_WARNING     1, 0x03
#define HID_USAGE_SMB_CHARGER_MODE      1, 0x04
#define HID_USAGE_SMB_CHARGER_STATUS    1, 0x05
#define HID_USAGE_SMB_CHARGER_SPEC_INFO 1, 0x06
#define HID_USAGE_SMB_SELECTOR_STATE    1, 0x07
#define HID_USAGE_SMB_SELECTOR_PRESETS  1, 0x08
#define HID_USAGE_SMB_SELECTOR_INFO     1, 0x09

#define HID_USAGE_OPTIONAL_MFG_FUNCTION(n) 1, (0x09 + (_ASSERT(1 <= (n) && (n) <= 5) ? (n) : (0))) /* n: [1..5] */
#define HID_USAGE_CONNECTION_TO_SMBUS      1, 0x15
#define HID_USAGE_OUTPUT_CONNECTION        1, 0x16
#define HID_USAGE_CHARGER_CONNECTION       1, 0x17
#define HID_USAGE_BATTERY_INSERTION        1, 0x18
#define HID_USAGE_USE_NEXT                 1, 0x19
#define HID_USAGE_OK_TO_USE                1, 0x1a
#define HID_USAGE_BATTERY_SUPPORTED        1, 0x1b
#define HID_USAGE_SELECTOR_REVISION        1, 0x1c
#define HID_USAGE_CHARGING_INDICATOR       1, 0x1d

#define HID_USAGE_MANUFACTURER_ACCESS      1, 0x28
#define HID_USAGE_REMAINING_CAPACITY_LIMIT 1, 0x29
#define HID_USAGE_REMAINING_TIME_LIMIT     1, 0x2a
#define HID_USAGE_AT_RATE                  1, 0x2b
#define HID_USAGE_CAPACITY_MODE            1, 0x2c
#define HID_USAGE_BROADCAST_TO_CHARGER     1, 0x2d
#define HID_USAGE_PRIMARY_BATTERY          1, 0x2e
#define HID_USAGE_CHARGE_CONTROLLER        1, 0x2f

#define HID_USAGE_TERMINATE_CHARGE               1, 0x40
#define HID_USAGE_TERMINATE_DISCHARGE            1, 0x41
#define HID_USAGE_BELOW_REMAINING_CAPACITY_LIMIT 1, 0x42
#define HID_USAGE_REMAINING_TIME_LIMIT_EXPIRED   1, 0x43
#define HID_USAGE_CHARGING                       1, 0x44
#define HID_USAGE_DISCHARGING                    1, 0x45
#define HID_USAGE_FULLY_CHARGED                  1, 0x46
#define HID_USAGE_FULLY_DISCHARGED               1, 0x47
#define HID_USAGE_CONDITIONING_FLAG              1, 0x48
#define HID_USAGE_AT_RATE_OK                     1, 0x49
#define HID_USAGE_SMB_ERROR_CODE                 1, 0x4a
#define HID_USAGE_NEED_REPLACEMENT               1, 0x4b

#define HID_USAGE_AT_RATE_TIME_TO_FULL     1, 0x60
#define HID_USAGE_AT_RATE_TIME_TO_EMPTY    1, 0x61
#define HID_USAGE_AVERAGE_CURRENT          1, 0x62
#define HID_USAGE_MAX_ERROR                1, 0x63
#define HID_USAGE_RELATIVE_STATE_OF_CHARGE 1, 0x64
#define HID_USAGE_ABSOLUTE_STATE_OF_CHARGE 1, 0x65
#define HID_USAGE_REMAINING_CAPACITY       1, 0x66
#define HID_USAGE_FULL_CHARGE_CAPACITY     1, 0x67
#define HID_USAGE_RUN_TIME_TO_EMPTY        1, 0x68
#define HID_USAGE_AVERAGE_TIME_TO_EMPTY    1, 0x69
#define HID_USAGE_AVERAGE_TIME_TO_FULL     1, 0x6a
#define HID_USAGE_CYCLE_COUNT              1, 0x6b

#define HID_USAGE_BATTERY_PACK_MODEL_LEVEL   1, 0x80
#define HID_USAGE_INTERNAL_CHARGE_CONTROLLER 1, 0x81
#define HID_USAGE_PRIMARY_BATTERY_SUPPORT    1, 0x82
#define HID_USAGE_DESIGN_CAPACITY            1, 0x83
#define HID_USAGE_SPECIFICATION_INFO         1, 0x84
#define HID_USAGE_MANUFACTURER_DATE          1, 0x85
#define HID_USAGE_SERIAL_NUMBER              1, 0x86
#define HID_USAGE_IMANUFACTURER_NAME         1, 0x87
#define HID_USAGE_IDEVICE_NAME               1, 0x88
#define HID_USAGE_IDEVICE_CHEMISTERY         1, 0x89
#define HID_USAGE_MANUFACTURER_DATA          1, 0x8a
#define HID_USAGE_RECHARGABLE                1, 0x8b
#define HID_USAGE_WARNING_CAPACITY_LIMIT     1, 0x8c
#define HID_USAGE_CAPACITY_GRANULARITY(n)    1, (0x8c + (_ASSERT(1 <= (n) && (n) <= 2) ? (n) : (n))) /* n: [1..2] */
#define HID_USAGE_IOEM_INFORMATION           1, 0x8f

#define HID_USAGE_INHIBIT_CHARGE 1, 0xc0
#define HID_USAGE_ENABLE_POLLING 1, 0xc1
#define HID_USAGE_RESET_TO_ZERO  1, 0xc2

#define HID_USAGE_AC_PRESENT             1, 0xd0
#define HID_USAGE_BATTERY_PRESENT        1, 0xd1
#define HID_USAGE_POWER_FAIL             1, 0xd2
#define HID_USAGE_ALARM_INHIBITED        1, 0xd3
#define HID_USAGE_THERMISTOR_UNDER_RANGE 1, 0xd4
#define HID_USAGE_THERMISTOR_HOT         1, 0xd5
#define HID_USAGE_THERMISTOR_COLD        1, 0xd6
#define HID_USAGE_THERMISTOR_OVER_RANGE  1, 0xd7
#define HID_USAGE_VOLTAGE_OUT_OF_RANGE   1, 0xd8
#define HID_USAGE_CURRENT_OUT_OF_RANGE   1, 0xd9
#define HID_USAGE_CURRENT_NOT_REGULATED  1, 0xda
#define HID_USAGE_VOLTAGE_NOT_REGULATED  1, 0xdb
#define HID_USAGE_MASTER_MODE            1, 0xdc

#define HID_USAGE_CHARGER_SELECTOR_SUPPORT 1, 0xf0
#define HID_USAGE_CHARGER_SPEC             1, 0xf1
#define HID_USAGE_LEVEL(n)                 1, (0xf0 + (_ASSERT(2 <= (n) && (n) <= 3) ? (n) : (0))) /* n: [2..3] */

/* End of Usages */

#define HID_USAGE2(n, x) HID_ELEM(0x0, LOCAL, n, x)
#define HID_USAGE(x) _CALL(HID_USAGE2, _CAT2(HID_USAGE_, x))

#define HID_PAGED_USAGE(p, u) HID_ELEM(0x0, LOCAL, 4, (_NTH1(_CAT2(HID_USAGE_PAGE_, p)) << 16) | _NTH1(_CAT2(HID_USAGE_, u)))

#define HID_USAGE_MINIMUM(n, x) HID_ELEM(0x1, LOCAL, n, x)
#define HID_USAGE_MAXIMUM(n, x) HID_ELEM(0x2, LOCAL, n, x)
#define HID_DESIGNATOR_INDEX(n, x) HID_ELEM(0x3, LOCAL, n, x)
#define HID_DESIGNATOR_MINIMUM(n, x) HID_ELEM(0x4, LOCAL, n, x)
#define HID_DESIGNATOR_MAXIMUM(n, x) HID_ELEM(0x5, LOCAL, n, x)
#define HID_STRING_INDEX(n, x) HID_ELEM(0x7, LOCAL, n, x)
#define HID_STRING_MINIMUM(n, x) HID_ELEM(0x8, LOCAL, n, x)
#define HID_STRING_MAXIMUM(n, x) HID_ELEM(0x9, LOCAL, n, x)
#define HID_DELIMITER(x) HID_ELEM(0xa, LOCAL, 1, x)
#define HID_DELIMITER_OPEN HID_DELIMITER(1)
#define HID_DELIMITER_CLOSE HID_DELIMITER(0)

#endif /* __HID_DEF_H__ */
