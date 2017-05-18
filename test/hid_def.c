#include <stdint.h>
#include "hid_def.h"

#define HID_USAGE_PAGE_USB_UART3 2, 0xff5e
#define HID_USAGE_USB_UART3 1, 0x01

#define HID_REPORT_RS485_MODE 0x01
#define HID_USAGE_UART_ID(n) 1, (0xa0 + (n))

#define HID_REPORT_LEDS_MODE 0x02
#define HID_USAGE_LED_ID(n) 1, (0xb0 + (n))
#define HID_USAGE_LED_EVT 1, 0x20
#define HID_USAGE_LED_ACT 1, 0x21

enum {
  uart_name_a = 0,
  uart_name_b = 1,
  uart_name_c = 2,
};

enum {
  rs485_mode_min = 0,
  rs485_mode_max = 1,
  rs485_mode_len = 1,
};

enum {
  led_name_red = 0,
  led_name_green = 1,
  led_name_yellow = 2,
};

enum {
  led_evt_min = 0x0,
  led_evt_max = 0x6,
  led_evt_len = 4,
};

enum {
  led_act_min = 0,
  led_act_max = 6,
  led_act_len = 4,
};

static const uint8_t hid_report_descriptor[] = {
#ifdef HID_TEST_SIMPLE
  /**/HID_USAGE_PAGE(USB_UART3),
  /**/HID_USAGE(USB_UART3),
  /**/HID_REPORT_ID(HID_REPORT_RS485_MODE),
  /**/HID_COLLECTION(APPLICATION),
  /**/  HID_USAGE(USB_UART3),
  /**/  HID_COLLECTION(PHYSICAL),
  /**/    HID_USAGE(UART_ID(0)),
  /**/    HID_USAGE(UART_ID(1)),
  /**/    HID_USAGE(UART_ID(2)),
  /**/    HID_LOGICAL_MINIMUM(1, 0),
  /**/    HID_LOGICAL_MAXIMUM(1, 1),
  /**/    HID_REPORT_SIZE(1),
  /**/    HID_REPORT_COUNT(3),
  /**/    HID_FEATURE(DATA, VARIABLE, ABSOLUTE),
  /**/  HID_END_COLLECTION(PHYSICAL),
  /**/HID_END_COLLECTION(APPLICATION),
#endif /* HID_TEST_SIMPLE */

#ifdef HID_TEST_ADVANCED
/**/HID_USAGE_PAGE(USB_UART3),
  /**/HID_USAGE(USB_UART3),
  
  /**/HID_REPORT_ID(HID_REPORT_RS485_MODE),
  /**/HID_COLLECTION(APPLICATION),
  /**/  HID_USAGE(USB_UART3),
  /**/  HID_COLLECTION(PHYSICAL),
  /**/    HID_USAGE(UART_ID(uart_name_a)),
  /**/    HID_USAGE(UART_ID(uart_name_b)),
  /**/    HID_USAGE(UART_ID(uart_name_c)),
  /**/    HID_LOGICAL_MINIMUM(1, rs485_mode_min),
  /**/    HID_LOGICAL_MAXIMUM(1, rs485_mode_max),
  /**/    HID_REPORT_SIZE(rs485_mode_len),
  /**/    HID_REPORT_COUNT(3),
  /**/    HID_FEATURE(DATA, VARIABLE, ABSOLUTE), /* mode bits */
  /**/    HID_REPORT_SIZE(8 - rs485_mode_len * 3),
  /**/    HID_REPORT_COUNT(1),
  /**/    HID_FEATURE(CONSTANT), /* padding */
  /**/  HID_END_COLLECTION(PHYSICAL),
  /**/HID_END_COLLECTION(APPLICATION),

#define LED_MODE_REPORT(name)                        \
  /**/  HID_COLLECTION(PHYSICAL),                    \
  /**/    HID_USAGE(LED_ID(_CAT2(led_name_, name))), \
  /**/    HID_COLLECTION(LOGICAL),                   \
  /**/      HID_USAGE(LED_EVT),                      \
  /**/      HID_LOGICAL_MINIMUM(1, led_evt_min),     \
  /**/      HID_LOGICAL_MAXIMUM(1, led_evt_max),     \
  /**/      HID_REPORT_SIZE(led_evt_len),            \
  /**/      HID_REPORT_COUNT(1),                     \
  /**/      HID_FEATURE(DATA, VARIABLE, ABSOLUTE),   \
  /**/      HID_USAGE(LED_ACT),                      \
  /**/      HID_LOGICAL_MINIMUM(1, led_act_min),     \
  /**/      HID_LOGICAL_MAXIMUM(1, led_act_max),     \
  /**/      HID_REPORT_SIZE(led_act_len),            \
  /**/      HID_REPORT_COUNT(1),                     \
  /**/      HID_FEATURE(DATA, VARIABLE, ABSOLUTE),   \
  /**/    HID_END_COLLECTION(LOGICAL),               \
  /**/  HID_END_COLLECTION(PHYSICAL),
  
  /**/HID_REPORT_ID(HID_REPORT_LEDS_MODE),
  /**/HID_COLLECTION(APPLICATION),
  /**/  LED_MODE_REPORT(red)
  /**/  LED_MODE_REPORT(green)
  /**/  LED_MODE_REPORT(yellow)
  /**/  /*_MAP(LED_MODE_REPORT, leds_list)*/
  /**/HID_END_COLLECTION(APPLICATION),
#endif /* HID_TEST_ADVANCED */
  
#ifdef HID_TEST_MOUSE
  /**/HID_USAGE_PAGE (GENERIC_DESKTOP),
  /**/HID_USAGE (MOUSE),
  /**/HID_COLLECTION (APPLICATION),
  /**/  HID_USAGE (POINTER),
  /**/  HID_COLLECTION (PHYSICAL),
  /**/    HID_USAGE_PAGE (BUTTONS),
  /**/    HID_USAGE_MINIMUM (1, 1),
  /**/    HID_USAGE_MAXIMUM (1, 3),
  /**/    HID_LOGICAL_MINIMUM (1, 0),
  /**/    HID_LOGICAL_MAXIMUM (1, 1),
  /**/    HID_REPORT_COUNT (3),
  /**/    HID_REPORT_SIZE (1),
  /**/    HID_INPUT (DATA, VARIABLE, ABSOLUTE),
  /**/    HID_REPORT_COUNT (1),
  /**/    HID_REPORT_SIZE (5),
  /**/    HID_INPUT (CONSTANT),
  /**/    HID_USAGE_PAGE (GENERIC_DESKTOP),
  /**/    HID_USAGE (X),
  /**/    HID_USAGE (Y),
  /**/    HID_LOGICAL_MINIMUM (1, -127),
  /**/    HID_LOGICAL_MAXIMUM (1, 127),
  /**/    HID_REPORT_SIZE (8),
  /**/    HID_REPORT_COUNT (2),
  /**/    HID_INPUT (DATA, VARIABLE, RELATIVE),
  /**/  HID_END_COLLECTION (PHYSICAL),
  /**/HID_END_COLLECTION (APPLICATION),
#endif /* HID_TEST_MOUSE */

#ifdef HID_TEST_REMOTE_CONTROL
  /**/HID_USAGE_PAGE (CONSUMER),
  /**/HID_USAGE (CONSUMER_CONTROL),
  /**/HID_COLLECTION (APPLICATION),
  /**/  HID_USAGE (NUMERIC_KEY_PAD),
  /**/  HID_COLLECTION (LOGICAL),
  /**/    HID_USAGE_PAGE (BUTTON),
  /**/    HID_USAGE (BUTTON(1, 1)),
  /**/    HID_USAGE (BUTTON(1, 2)),
  /**/    HID_USAGE (BUTTON(1, 3)),
  /**/    HID_USAGE (BUTTON(1, 4)),
  /**/    HID_USAGE (BUTTON(1, 5)),
  /**/    HID_USAGE (BUTTON(1, 6)),
  /**/    HID_USAGE (BUTTON(1, 7)),
  /**/    HID_USAGE (BUTTON(1, 8)),
  /**/    HID_USAGE (BUTTON(1, 9)),
  /**/    HID_USAGE (BUTTON(1, 10)),
  /**/    HID_LOGICAL_MINIMUM (1, 1),
  /**/    HID_LOGICAL_MAXIMUM (1, 10),
  /**/    HID_REPORT_SIZE (4),
  /**/    HID_REPORT_COUNT (1),
  /**/    HID_INPUT (DATA, ARRAY, ABSOLUTE, NULL_STATE),
  /**/  HID_END_COLLECTION (),
  
  /**/  HID_USAGE_PAGE (CONSUMER),
  /**/  HID_USAGE (CHANNEL),
  /**/  HID_USAGE (VOLUME),
  /**/  HID_LOGICAL_MINIMUM (1, -1),
  /**/  HID_LOGICAL_MAXIMUM (1, 1),
  /**/  HID_REPORT_SIZE (2),
  /**/  HID_REPORT_COUNT (2),
  /**/  HID_INPUT (DATA, VARIABLE, RELATIVE, PREFERRED_STATE),
  
  /**/  HID_USAGE (MUTE),
  /**/  HID_USAGE (POWER),
  /**/  HID_USAGE (SLEEP_MODE),
  /**/  HID_USAGE (DATA_ON_SCREEN),
  /**/  HID_USAGE (BROADCAST_MODE),
  /**/  HID_USAGE (RECALL_LAST),
  /**/  HID_USAGE (ASSIGN_SELECTION),
  /**/  HID_LOGICAL_MINIMUM (1, 1),
  /**/  HID_LOGICAL_MAXIMUM (1, 7),
  /**/  HID_REPORT_SIZE (4),
  /**/  HID_REPORT_COUNT (1),
  /**/  HID_INPUT (DATA, ARRAY, ABSOLUTE, NULL_STATE),

  /**/  HID_USAGE (SELECTION),
  /**/  HID_COLLECTION (LOGICAL),
  /**/    HID_USAGE_PAGE (BUTTON),
  /**/    HID_USAGE (BUTTON(1, 1)),
  /**/    HID_USAGE (BUTTON(1, 2)),
  /**/    HID_USAGE (BUTTON(1, 3)),
  /**/    HID_LOGICAL_MINIMUM (1, 1),
  /**/    HID_LOGICAL_MAXIMUM (1, 3),
  /**/    HID_REPORT_SIZE (2),
  /**/    HID_REPORT_COUNT (1),
  /**/    HID_INPUT (DATA, ARRAY, ABSOLUTE, NULL_STATE),
  /**/  HID_END_COLLECTION (),

  /**/  HID_LOGICAL_MINIMUM (1, 1),
  /**/  HID_LOGICAL_MAXIMUM (1, 2),
  /**/  HID_REPORT_SIZE (2),
  /**/  HID_REPORT_COUNT (1),
  /**/  HID_INPUT (CONSTANT, VARIABLE, ABSOLUTE),
  /**/HID_END_COLLECTION (),
#endif /* HID_TEST_REMOTE_CONTROL */

#ifdef HID_TEST_UNITS
  /* Centimeter */
  HID_UNIT(SI(LIN), CM(1)), HID_UNIT_EXPONENT(0),
  /* Nanometer */
  HID_UNIT(SI(LIN), CM(1)), HID_UNIT_EXPONENT(-7),
  /* Micrometer */
  HID_UNIT(SI(LIN), CM(1)), HID_UNIT_EXPONENT(-4),
  /* Millimeter */
  HID_UNIT(SI(LIN), CM(1)), HID_UNIT_EXPONENT(-1),
  /* Decimeter */
  HID_UNIT(SI(LIN), CM(1)), HID_UNIT_EXPONENT(1),
  /* Meter */
  HID_UNIT(SI(LIN), CM(1)), HID_UNIT_EXPONENT(2),
  /* Kilometer */
  HID_UNIT(SI(LIN), CM(1)), HID_UNIT_EXPONENT(5),
  /* Megameter */
  HID_UNIT(SI(LIN), CM(1)), HID_UNIT_EXPONENT(7),
  
  /* Ampere */
  HID_UNIT(SI(LIN), A(1)), HID_UNIT_EXPONENT(0),
  /* Volt (cm^2 x g^1 x s^-3 x A^-1 x 10^7) */
  HID_UNIT(SI(LIN), CM(2), G(1), S(-3), A(-1)), HID_UNIT_EXPONENT(7),
  /* Watt (cm^2 x g^1 x s^-3 x 10^7) */
  HID_UNIT(SI(LIN), CM(2), G(1), S(-3)), HID_UNIT_EXPONENT(7),
  /* Joule (cm^2 x g^1 x s^-2 x 10^7) */
  HID_UNIT(SI(LIN), CM(2), G(1), S(-2)), HID_UNIT_EXPONENT(7),

  /* Linear acceleration (m x s^2) */
  HID_UNIT(SI(LIN), RAD(1), S(2)), HID_UNIT_EXPONENT(2),
  /* Angular acceleration (rad x s^2) */
  HID_UNIT(SI(ROT), RAD(1), S(2)), HID_UNIT_EXPONENT(0),
#endif /* HID_TEST_UNITS */
};
