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

#ifdef HID_TEST_UPS
  /* Unit abbrevations */
#define SI_TIME SI(LIN), S(1)
#define SI_HERTZ SI(LIN), S(-1)
#define SI_VOLTS SI(LIN), CM(2), G(1), S(-3), A(-1)
#define SI_POWER SI(LIN), CM(2), G(1), S(-3)
  /*
   * Collection UPS
   *   Collection PowerConverter (1)
   *     Collection Output (1)
   *   Collection Flow (4:AC Output)
   *   Collection PowerSummary (1)
   *   Collection OutletSystem (1)
   *     Collection Outlet (1:Non Switchable)
   *     Collection Outlet (2:Switchable)
   */
  /* 0x05, 0x84, */ HID_USAGE_PAGE (POWER_DEVICE),
  /* 0x09, 0x04, */ HID_USAGE (UPS),
  /* 0xa1, 0x00, */ HID_COLLECTION (PHYSICAL),
  /* 0x09, 0x16, */   HID_USAGE (POWER_CONVERTER),
  /* 0xa1, 0x00, */   HID_COLLECTION (PHYSICAL),
  /* 0x09, 0x17, */     HID_USAGE (POWER_CONVERTER_ID),
  /* 0x85, 0x0b, */     HID_REPORT_ID (11),
  /* 0x75, 0x08, */     HID_REPORT_SIZE (8),
  /* 0x95, 0x01, */     HID_REPORT_COUNT (1),
  /* 0x15, 0x00, */     HID_LOGICAL_MINIMUM (1, 0),
  /* 0x26, 0xff, 0x00, */ HID_LOGICAL_MAXIMUM (2, 255),
  /* 0x65, 0x00, */     HID_UNIT (NONE),
  /* 0xb1, 0x03, */     HID_FEATURE (CONSTANT, VARIABLE, ABSOLUTE),
  /* 0x09, 0x1c, */     HID_USAGE (OUTPUT),
  /* 0xa1, 0x00, */     HID_COLLECTION (PHYSICAL),
  /* 0x09, 0x1d, */       HID_USAGE (OUTPUT_ID),
  /* 0xb1, 0x03, */       HID_FEATURE (CONSTANT, VARIABLE, ABSOLUTE),
  /* 0x09, 0x30, */       HID_USAGE (VOLTAGE),
  /* 0x85, 0x0e, */       HID_REPORT_ID (14),
  /* 0x67, 0x21, 0xd1, 0xf0, 0x00, */ HID_UNIT (SI_VOLTS),
  /* 0x55, 0x07, */       HID_UNIT_EXPONENT (7),
  /* 0xb1, 0x83, */       HID_FEATURE (CONSTANT, VARIABLE, ABSOLUTE, VOLATILE),
  /* 0x09, 0x53, */       HID_USAGE (LOW_VOLTAGE_TRANSFER),
  /* 0x85, 0x13, */       HID_REPORT_ID (19),
  /* 0xb1, 0x82, */       HID_FEATURE (DATA, VARIABLE, ABSOLUTE, VOLATILE),
  /* 0x09, 0x54, */       HID_USAGE (HIGH_VOLTAGE_TRANSFER),
  /* 0x75, 0x10, */       HID_REPORT_SIZE (16),
  /* 0x26, 0xff, 0x7f, */ HID_LOGICAL_MAXIMUM (2, 32767),
  /* 0xb1, 0x82, */       HID_FEATURE (DATA, VARIABLE, ABSOLUTE, VOLATILE),
  /* 0xc0, */           HID_END_COLLECTION (),
  /* 0xc0, */         HID_END_COLLECTION (),
  /* 0x09, 0x1e, */   HID_USAGE (FLOW),
  /* 0xa1, 0x84, */   HID_COLLECTION (VENDOR_DEFINED),
  /* 0x09, 0x1f, */     HID_USAGE (FLOW_ID),
  /* 0x85, 0x0b, */     HID_REPORT_ID (11),
  /* 0x75, 0x08, */     HID_REPORT_SIZE (8),
  /* 0x95, 0x01, */     HID_REPORT_COUNT (1),
  /* 0x65, 0x00, */     HID_UNIT (NONE),
  /* 0x55, 0x00, */     HID_UNIT_EXPONENT (0),
  /* 0x26, 0xff, 0x00, */ HID_LOGICAL_MAXIMUM (2, 255),
  /* 0xb1, 0x03, */     HID_FEATURE (CONSTANT, VARIABLE, ABSOLUTE),
  /* 0x09, 0x40, */     HID_USAGE (CONFIG_VOLTAGE),
  /* 0x85, 0x12, */     HID_REPORT_ID (18),
  /* 0x67, 0x21, 0xd1, 0xf0, 0x00, */ HID_UNIT (SI_VOLTS),
  /* 0x55, 0x07, */     HID_UNIT_EXPONENT (7),
  /* 0xb1, 0x82, */     HID_FEATURE (DATA, VARIABLE, ABSOLUTE, VOLATILE),
  /* 0x09, 0x42, */     HID_USAGE (CONFIG_FREQUENCY),
  /* 0x85, 0x0d, */     HID_REPORT_ID (13),
  /* 0x66, 0x01, 0xf0, */ HID_UNIT (SI_HERTZ),
  /* 0x55, 0x00, */     HID_UNIT_EXPONENT (0),
  /* 0xb1, 0x83, */     HID_FEATURE (CONSTANT, VARIABLE, ABSOLUTE, VOLATILE),
  /* 0x09, 0x43, */     HID_USAGE (CONFIG_APPARENT_POWER),
  /* 0x75, 0x10, */     HID_REPORT_SIZE (16),
  /* 0x26, 0xff, 0x7f, */ HID_LOGICAL_MAXIMUM (2, 32767),
  /* 0x66, 0x21, 0xd1, */ HID_UNIT (SI_POWER),
  /* 0x55, 0x07, */     HID_UNIT_EXPONENT (7),
  /* 0xb1, 0x83, */     HID_FEATURE (CONSTANT, VARIABLE, ABSOLUTE, VOLATILE),
  /* 0xc0, */         HID_END_COLLECTION (),
  /* 0x09, 0x24, */   HID_USAGE (POWER_SUMMARY),
  /* 0xa1, 0x00, */   HID_COLLECTION (PHYSICAL),
  /* 0x09, 0x25, */     HID_USAGE (POWER_SUMMARY_ID),
  /* 0x09, 0x1f, */     HID_USAGE (FLOW_ID),
  /* 0x85, 0x0b, */     HID_REPORT_ID (11),
  /* 0x75, 0x08, */     HID_REPORT_SIZE (8),
  /* 0x95, 0x02, */     HID_REPORT_COUNT (2),
  /* 0x26, 0xff, 0x00, */ HID_LOGICAL_MAXIMUM (2, 255),
  /* 0x65, 0x00, */     HID_UNIT (NONE),
  /* 0x55, 0x00, */     HID_UNIT_EXPONENT (0),
  /* 0xb1, 0x03, */     HID_FEATURE (CONSTANT, VARIABLE, ABSOLUTE),
  /* 0x05, 0x85, */     HID_USAGE_PAGE (BATTERY_SYSTEM),
  /* 0x09, 0x2c, */     HID_USAGE (CAPACITY_MODE),
  /* 0x85, 0x0c, */     HID_REPORT_ID (12),
  /* 0x75, 0x08, */     HID_REPORT_SIZE (8),
  /* 0x95, 0x01, */     HID_REPORT_COUNT (1),
  /* 0xb1, 0x03, */     HID_FEATURE (CONSTANT, VARIABLE, ABSOLUTE),
  /* 0x09, 0x29, */     HID_USAGE (REMAINING_CAPACITY_LIMIT),
  /* 0x09, 0x8d, */     HID_USAGE (CAPACITY_GRANULARITY(1)),
  /* 0x95, 0x02, */     HID_REPORT_COUNT (2),
  /* 0x25, 0x64, */     HID_LOGICAL_MAXIMUM (1, 100),
  /* 0xb1, 0x03, */     HID_FEATURE (CONSTANT, VARIABLE, ABSOLUTE),
  /* 0x09, 0x89, */     HID_USAGE (IDEVICE_CHEMISTERY),
  /* 0x26, 0xff, 0x00, */ HID_LOGICAL_MAXIMUM (2, 255),
  /* 0x85, 0x10, */     HID_REPORT_ID (16),
  /* 0x95, 0x01, */     HID_REPORT_COUNT (1),
  /* 0xb1, 0x03, */     HID_FEATURE (CONSTANT, VARIABLE, ABSOLUTE),
  /* 0x05, 0x84, */     HID_USAGE_PAGE (POWER_DEVICE),
  /* 0x09, 0xfd, */     HID_USAGE (IMANUFACTURER),
  /* 0x09, 0xfe, */     HID_USAGE (IPRODUCT),
  /* 0x09, 0xff, */     HID_USAGE (ISERIAL_NUMBER),
  /* 0x95, 0x03, */     HID_REPORT_COUNT (3),
  /* 0xb1, 0x03, */     HID_FEATURE (CONSTANT, VARIABLE, ABSOLUTE),
  /* 0x09, 0x35, */     HID_USAGE (PERCENT_LOAD),
  /* 0x85, 0x0e, */     HID_REPORT_ID (14),
  /* 0x95, 0x01, */     HID_REPORT_COUNT (1),
  /* 0x65, 0x00, */     HID_UNIT (NONE),
  /* 0x55, 0x00, */     HID_UNIT_EXPONENT (0),
  /* 0xb1, 0x83, */     HID_FEATURE (CONSTANT, VARIABLE, ABSOLUTE, VOLATILE),
  /* 0x05, 0x85, */     HID_USAGE_PAGE (BATTERY_SYSTEM),
  /* 0x09, 0x83, */     HID_USAGE (DESIGN_CAPACITY),
  /* 0x09, 0x67, */     HID_USAGE (FULL_CHARGE_CAPACITY),
  /* 0x85, 0x0c, */     HID_REPORT_ID (12),
  /* 0x95, 0x02, */     HID_REPORT_COUNT (2),
  /* 0x75, 0x08, */     HID_REPORT_SIZE (8),
  /* 0x25, 0x64, */     HID_LOGICAL_MAXIMUM (1, 100),
  /* 0xb1, 0x03, */     HID_FEATURE (CONSTANT, VARIABLE, ABSOLUTE),
  /* 0x09, 0x66, */     HID_USAGE (REMAINING_CAPACITY),
  /* 0x85, 0x16, */     HID_REPORT_ID (22),
  /* 0x95, 0x01, */     HID_REPORT_COUNT (1),
  /* 0xb1, 0x83, */     HID_FEATURE (CONSTANT, VARIABLE, ABSOLUTE, VOLATILE),
  /* 0x09, 0x66, */     HID_USAGE (REMAINING_CAPACITY),
  /* 0x81, 0x83, */     HID_INPUT (CONSTANT, VARIABLE, ABSOLUTE, VOLATILE),
  /* 0x09, 0x68, */     HID_USAGE (RUN_TIME_TO_EMPTY),
  /* 0x66, 0x01, 0x10, */ HID_UNIT (SI_TIME),
  /* 0x75, 0x10, */     HID_REPORT_SIZE (16),
  /* 0x26, 0x08, 0x07, */ HID_LOGICAL_MAXIMUM (2, 1800),
  /* 0xb1, 0x83, */     HID_FEATURE (CONSTANT, VARIABLE, ABSOLUTE, VOLATILE),
  /* 0x09, 0x68, */     HID_USAGE (RUN_TIME_TO_EMPTY),
  /* 0x81, 0x83, */     HID_INPUT (CONSTANT, VARIABLE, ABSOLUTE, VOLATILE),
  /* 0x05, 0x84, */     HID_USAGE_PAGE (POWER_DEVICE),
  /* 0x09, 0x02, */     HID_USAGE (PRESENT_STATUS),
  /* 0xa1, 0x02, */     HID_COLLECTION (LOGICAL),
  /* 0x09, 0x73, */       HID_USAGE (COMMUNICATION_LOST),
  /* 0x85, 0x01, */       HID_REPORT_ID (1),
  /* 0x95, 0x01, */       HID_REPORT_COUNT (1),
  /* 0x75, 0x01, */       HID_REPORT_SIZE (1),
  /* 0x65, 0x00, */       HID_UNIT (NONE),
  /* 0x25, 0x01, */       HID_LOGICAL_MAXIMUM (1, 1),
  /* 0x45, 0x00, */       HID_PHYSICAL_MAXIMUM (1, 0),
  /* 0x81, 0x83, */       HID_INPUT (CONSTANT, VARIABLE, ABSOLUTE, VOLATILE),
  /* 0x09, 0x73, */       HID_USAGE (COMMUNICATION_LOST),
  /* 0xb1, 0x83, */       HID_FEATURE (CONSTANT, VARIABLE, ABSOLUTE, VOLATILE),
  /* 0x09, 0x00, */       HID_USAGE (UNDEFINED),
  /* 0x75, 0x07, */       HID_REPORT_SIZE (7),
  /* 0x81, 0x03, */       HID_INPUT (CONSTANT, VARIABLE, ABSOLUTE),
  /* 0x09, 0x00, */       HID_USAGE (UNDEFINED),
  /* 0xb1, 0x03, */       HID_FEATURE (CONSTANT,VARIABLE,ABSOLUTE),
  /* 0x05, 0x85, */       HID_USAGE_PAGE (BATTERY_SYSTEM),
  /* 0x09, 0xd0, */       HID_USAGE (AC_PRESENT),
  /* 0x09, 0x44, */       HID_USAGE (CHARGING),
  /* 0x09, 0x45, */       HID_USAGE (DISCHARGING),
  /* 0x09, 0x42, */       HID_USAGE (BELOW_REMAINING_CAPACITY_LIMIT),
  /* 0x09, 0x4b, */       HID_USAGE (NEED_REPLACEMENT),
  /* 0x0b, 0x61, 0x00, 0x84, 0x00, */ HID_PAGED_USAGE (POWER_DEVICE, GOOD),
  /* 0x0b, 0x69, 0x00, 0x84, 0x00, */ HID_PAGED_USAGE (POWER_DEVICE, SHUTDOWN_IMMINENT),
  /* 0x0b, 0x65, 0x00, 0x84, 0x00, */ HID_PAGED_USAGE (POWER_DEVICE, OVER_LOAD),
  /* 0x0b, 0x62, 0x00, 0x84, 0x00, */ HID_PAGED_USAGE (POWER_DEVICE, INTERNAL_FAILURE),
  /* 0x85, 0x02, */       HID_REPORT_ID (2),
  /* 0x75, 0x01, */       HID_REPORT_SIZE (1),
  /* 0x95, 0x09, */       HID_REPORT_COUNT (9),
  /* 0x25, 0x01, */       HID_LOGICAL_MAXIMUM (1, 1),
  /* 0x81, 0x83, */       HID_INPUT (CONSTANT, VARIABLE, ABSOLUTE, VOLATILE),
  /* 0x09, 0x00, */       HID_USAGE (UNDEFINED),
  /* 0x75, 0x07, */       HID_REPORT_SIZE (7),
  /* 0x95, 0x01, */       HID_REPORT_COUNT (1),
  /* 0x81, 0x03, */       HID_INPUT (CONSTANT,VARIABLE,ABSOLUTE),
  /* 0x09, 0xd0, */       HID_USAGE (AC_PRESENT),
  /* 0x09, 0x44, */       HID_USAGE (CHARGING),
  /* 0x09, 0x45, */       HID_USAGE (DISCHARGING),
  /* 0x09, 0x42, */       HID_USAGE (BELOW_REMAINING_CAPACITY_LIMIT),
  /* 0x09, 0x4b, */       HID_USAGE (NEED_REPLACEMENT),
  /* 0x0b, 0x61, 0x00, 0x84, 0x00, */ HID_PAGED_USAGE (POWER_DEVICE, GOOD),
  /* 0x0b, 0x69, 0x00, 0x84, 0x00, */ HID_PAGED_USAGE (POWER_DEVICE, SHUTDOWN_IMMINENT),
  /* 0x0b, 0x65, 0x00, 0x84, 0x00, */ HID_PAGED_USAGE (POWER_DEVICE, OVER_LOAD),
  /* 0x0b, 0x62, 0x00, 0x84, 0x00, */ HID_PAGED_USAGE (POWER_DEVICE, INTERNAL_FAILURE),
  /* 0x95, 0x09, */       HID_REPORT_COUNT (9),
  /* 0x75, 0x01, */       HID_REPORT_SIZE (1),
  /* 0xb1, 0x83, */       HID_FEATURE (CONSTANT, VARIABLE, ABSOLUTE, VOLATILE),
  /* 0x09, 0x00, */       HID_USAGE (UNDEFINED),
  /* 0x95, 0x01, */       HID_REPORT_COUNT (1),
  /* 0x75, 0x07, */       HID_REPORT_SIZE (7),
  /* 0xb1, 0x03, */       HID_FEATURE (CONSTANT, VARIABLE, ABSOLUTE),
  /* 0xc0, */           HID_END_COLLECTION (),
  /* 0x05, 0x84, */     HID_USAGE_PAGE (POWER_DEVICE),
  /* 0x09, 0x57, */     HID_USAGE (DELAY_BEFORE_SHUTDOWN),
  /* 0x85, 0x0f, */     HID_REPORT_ID (15),
  /* 0x75, 0x18, */     HID_REPORT_SIZE (24),
  /* 0x95, 0x01, */     HID_REPORT_COUNT (1),
  /* 0x66, 0x01, 0x10, */ HID_UNIT (SI_TIME),
  /* 0x15, 0xff, */     HID_LOGICAL_MINIMUM (1, -1),
  /* 0x27, 0xfe, 0xff, 0x00, 0x00, */ HID_LOGICAL_MAXIMUM (4, 65534),
  /* 0xb1, 0x82, */     HID_FEATURE (DATA, VARIABLE, ABSOLUTE, VOLATILE),
  /* 0x09, 0x56, */     HID_USAGE (DELAY_BEFORE_STARTUP),
  /* 0x85, 0x11, */     HID_REPORT_ID (17),
  /* 0x55, 0x01, */     HID_UNIT_EXPONENT (1),
  /* 0xb1, 0x82, */     HID_FEATURE (DATA, VARIABLE, ABSOLUTE, VOLATILE),
  /* 0xc0, */         HID_END_COLLECTION (),
  /* 0x09, 0x18, */   HID_USAGE (OUTLET_SYSTEM),
  /* 0xa1, 0x00, */   HID_COLLECTION (PHYSICAL),
  /* 0x09, 0x19, */     HID_USAGE (OUTLET_SYSTEM_ID),
  /* 0x85, 0x0b, */     HID_REPORT_ID (11),
  /* 0x75, 0x08, */     HID_REPORT_SIZE (8),
  /* 0x95, 0x01, */     HID_REPORT_COUNT (1),
  /* 0x65, 0x00, */     HID_UNIT (NONE),
  /* 0x55, 0x00, */     HID_UNIT_EXPONENT (0),
  /* 0x15, 0x00, */     HID_LOGICAL_MINIMUM (1, 0),
  /* 0x26, 0xff, 0x00, */ HID_LOGICAL_MAXIMUM (2, 255),
  /* 0xb1, 0x03, */     HID_FEATURE (CONSTANT, VARIABLE, ABSOLUTE),
  /* 0x09, 0x20, */     HID_USAGE (OUTLET),
  /* 0xa1, 0x81, */     HID_COLLECTION (VENDOR_DEFINED),
  /* 0x09, 0x21, */     HID_USAGE (OUTLET_ID),
  /* 0xb1, 0x03, */     HID_FEATURE (CONSTANT, VARIABLE, ABSOLUTE),
  /* 0x09, 0x1f, */     HID_USAGE (FLOW_ID),
  /* 0xb1, 0x03, */     HID_FEATURE (CONSTANT, VARIABLE, ABSOLUTE),
  /* 0x09, 0x02, */     HID_USAGE (PRESENT_STATUS),
  /* 0xa1, 0x02, */     HID_COLLECTION (LOGICAL),
  /* 0x09, 0x6c, */     HID_USAGE (SWITCHABLE),
  /* 0x85, 0x0c, */     HID_REPORT_ID (12),
  /* 0x25, 0x01, */     HID_LOGICAL_MAXIMUM (1, 1),
  /* 0xb1, 0x03, */     HID_FEATURE (CONSTANT, VARIABLE, ABSOLUTE),
  /* 0xc0, */         HID_END_COLLECTION (),
  /* 0xc0, */       HID_END_COLLECTION (),
  /* 0x09, 0x20, */ HID_USAGE (OUTLET),
  /* 0xa1, 0x82, */ HID_COLLECTION (VENDOR_DEFINED),
  /* 0x09, 0x21, */   HID_USAGE (OUTLET_ID),
  /* 0x85, 0x0b, */   HID_REPORT_ID (11),
  /* 0x26, 0xff, 0x00, */ HID_LOGICAL_MAXIMUM (2, 255),
  /* 0xb1, 0x03, */   HID_FEATURE (CONSTANT, VARIABLE, ABSOLUTE),
  /* 0x09, 0x1f, */   HID_USAGE (FLOW_ID),
  /* 0x85, 0x0d, */   HID_REPORT_ID (13),
  /* 0xb1, 0x83, */   HID_FEATURE (CONSTANT, VARIABLE, ABSOLUTE, VOLATILE),
  /* 0x09, 0x02, */   HID_USAGE (PRESENT_STATUS),
  /* 0xa1, 0x02, */   HID_COLLECTION (LOGICAL),
  /* 0x09, 0x6c, */     HID_USAGE (SWITCHABLE),
  /* 0x25, 0x01, */     HID_LOGICAL_MAXIMUM (1, 1),
  /* 0xb1, 0x83, */     HID_FEATURE (CONSTANT, VARIABLE, ABSOLUTE, VOLATILE),
  /* 0x09, 0x6b, */     HID_USAGE (SWITCH_ON_OFF),
  /* 0x85, 0x03, */     HID_REPORT_ID (3),
  /* 0x75, 0x01, */     HID_REPORT_SIZE (1),
  /* 0x81, 0x83, */     HID_INPUT (CONSTANT, VARIABLE, ABSOLUTE, VOLATILE),
  /* 0x09, 0x6b, */     HID_USAGE (SWITCH_ON_OFF),
  /* 0xb1, 0x83, */     HID_FEATURE (CONSTANT, VARIABLE, ABSOLUTE, VOLATILE),
  /* 0x09, 0x00, */     HID_USAGE (UNDEFINED),
  /* 0x75, 0x07, */     HID_REPORT_SIZE (7),
  /* 0x81, 0x03, */     HID_INPUT (CONSTANT, VARIABLE, ABSOLUTE),
  /* 0x09, 0x00, */     HID_USAGE (UNDEFINED),
  /* 0xb1, 0x03, */     HID_FEATURE (CONSTANT, VARIABLE, ABSOLUTE),
  /* 0xc0, */         HID_END_COLLECTION (),
  /* 0x0b, 0x29, 0x00, 0x85, 0x00, */ HID_PAGED_USAGE (BATTERY_SYSTEM, REMAINING_CAPACITY_LIMIT),
  /* 0x85, 0x14, */   HID_REPORT_ID (20),
  /* 0x75, 0x08, */   HID_REPORT_SIZE (8),
  /* 0x95, 0x01, */   HID_REPORT_COUNT (1),
  /* 0x65, 0x00, */   HID_UNIT (NONE),
  /* 0x25, 0x64, */   HID_LOGICAL_MAXIMUM (1, 100),
  /* 0xb1, 0x82, */   HID_FEATURE (DATA, VARIABLE, ABSOLUTE, VOLATILE),
  /* 0xc0, */       HID_END_COLLECTION (),
  /* 0xc0, */     HID_END_COLLECTION (),
  /* 0xc0, */   HID_END_COLLECTION (),
#endif /* HID_TEST_UPS */
};
