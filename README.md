# HID report descriptors on C

This C-header (*hid_def.h*) declares simple [DSL](https://en.wikipedia.org/wiki/Domain-specific_language), which helps to define **[HID](https://en.wikipedia.org/wiki/USB_HID) report descriptors** immediately in **C source code** in human readable form without using any additional tools like [hidrd](https://github.com/DIGImend/hidrd).

The language itself is quite similar to the examples from specification ([HID1_11.pdf](https://www.usb.org/developers/hidpage/HID1_11.pdf)), so it is easy to sense and use to declare the HID reports of any complexity.

Of course, you **must** understand how HID report descriptors arranged and how to construct it using elements, but more you don't need to think about its internal binary representation.

## The usage example

In order to get first notion about this library look the example below.

This is HID report descriptor from official specification **HID 1.11** for standard three button mouse:

```
Usage Page (Generic Desktop),
Usage (Mouse),
Collection (Application),
  Usage (Pointer),
  Collection (Physical),
    Usage Page (Buttons),
    Usage Minimum (01),
    Usage Maximun (03),
    Logical Minimum (0),
    Logical Maximum (1),
    Report Count (3),
    Report Size (1),
    Input (Data, Variable, Absolute),
    Report Count (1),
    Report Size (5),
    Input (Constant),
    Usage Page (Generic Desktop),
    Usage (X),
    Usage (Y),
    Logical Minimum (-127),
    Logical Maximum (127),
    Report Size (8),
    Report Count (2),
    Input (Data, Variable, Relative),
  End Collection,
End Collection
```

This is same example, but rewritten to C using our HID reports definition:

```C
static const uint8_t mouse_hid_report_descriptor[] = {
  HID_USAGE_PAGE (GENERIC_DESKTOP),
  HID_USAGE (MOUSE),
  HID_COLLECTION (APPLICATION),
    HID_USAGE (POINTER),
    HID_COLLECTION (PHYSICAL),
      HID_USAGE_PAGE (BUTTONS),
      HID_USAGE_MINIMUM (1, 1),
      HID_USAGE_MAXIMUM (1, 3),
      HID_LOGICAL_MINIMUM (1, 0),
      HID_LOGICAL_MAXIMUM (1, 1),
      HID_REPORT_COUNT (3),
      HID_REPORT_SIZE (1),
      HID_INPUT (DATA, VARIABLE, ABSOLUTE),
      HID_REPORT_COUNT (1),
      HID_REPORT_SIZE (5),
      HID_INPUT (CONSTANT),
      HID_USAGE_PAGE (GENERIC_DESKTOP),
      HID_USAGE (X),
      HID_USAGE (Y),
      HID_LOGICAL_MINIMUM (1, -127),
      HID_LOGICAL_MAXIMUM (1, 127),
      HID_REPORT_SIZE (8),
      HID_REPORT_COUNT (2),
      HID_INPUT (DATA, VARIABLE, RELATIVE),
    HID_END_COLLECTION (PHYSICAL),
  HID_END_COLLECTION (APPLICATION),
};
```

This is quite similar to original example, but elements have a prefix *HID_* to avoid collisions with other identifiers in your sources. Also the elements with values (like `HID_LOGICAL_MINIMUM`, `HID_LOGICAL_MAXIMUM` and etc.) get two arguments: the first means a size of value in bytes, the second is the value itself. The elements, which defines reports (like `HID_INPUT`, `HID_OUTPUT` and `HID_FEATURE`), can get any number of flags. The argument of `HID_END_COLLECTION` elements was added in usability purposes, so it is optional and can be away.

This is a binary output which get for that descriptor as result of compilation:

```
00000000  05 01 09 02 a1 01 09 01  a1 00 05 09 19 01 29 03  |..............).|
00000010  15 00 25 01 95 03 75 01  81 02 95 01 75 05 81 01  |..%...u.....u...|
00000020  05 01 09 30 09 31 15 81  25 7f 75 08 95 02 81 06  |...0.1..%.u.....|
00000030  c0 c0                                             |..|
```

This is result of converting binary representation back to text using `ridrd-convert` utility:

```
Usage Page (Desktop),               ; Generic desktop controls (01h)
Usage (Mouse),                      ; Mouse (02h, application collection)
Collection (Application),
    Usage (Pointer),                ; Pointer (01h, physical collection)
    Collection (Physical),
        Usage Page (Button),        ; Button (09h)
        Usage Minimum (01h),
        Usage Maximum (03h),
        Logical Minimum (0),
        Logical Maximum (1),
        Report Count (3),
        Report Size (1),
        Input (Variable),
        Report Count (1),
        Report Size (5),
        Input (Constant),
        Usage Page (Desktop),       ; Generic desktop controls (01h)
        Usage (X),                  ; X (30h, dynamic value)
        Usage (Y),                  ; Y (31h, dynamic value)
        Logical Minimum (-127),
        Logical Maximum (127),
        Report Size (8),
        Report Count (2),
        Input (Variable, Relative),
    End Collection,
End Collection
```

As you can see, both textual representation of report for mouse from example and result of decompilation is identical.

## Unit definition

In some report descriptors you need use measurement units. The HID specification define some basic units which can be used to derive any derivative units. See example below:

```C
/* Ampere is a basic unit */
HID_UNIT(A(1)), HID_UNIT_EXPONENT(0),
/* Volt can be derived as cm^2 x g^1 x s^-3 x A^-1 x 10^7 */
HID_UNIT(CM(2), G(1), S(-3), A(-1)), HID_UNIT_EXPONENT(7),
/* Watt can be derived as cm^2 x g^1 x s^-3 */
HID_UNIT(CM(2), G(1), S(-3)), HID_UNIT_EXPONENT(7),
/* Joule can be derived as cm^2 x g^1 x s^-2 */
HID_UNIT(CM(2), G(1), S(-2)), HID_UNIT_EXPONENT(7),
```

In example above we used the next basic units: Centimeter (CM), Gram (G), Second (S), Ampere (A). With it we derived the next derivative units: Volt (V), Watt (W), Joule (J). Moreover we required to use unit exponent to fit value order.

## Additional examples

To get more usage examples look in *[tests](test/hid_def.c)*.

## How it works

The implementation uses some advanced C pre-processor techniques, which defined by macros from *macro.h* header.
