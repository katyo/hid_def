# Описание отчётов HID на C

Этот заголовочный файл языка C (*hid_def.h*) определяет простой [DSL](https://ru.wikipedia.org/wiki/Предметно-ориентированный_язык), который помогает определять **дескрипторы отчётов [HID](https://ru.wikipedia.org/wiki/USB_HID)** непосредственно в **исходнике на C** в удобочитаемой форме без использования каких-либо дополнительных инструментов вроде [hidrd](https://github.com/DIGImend/hidrd).

Сам язык очень похож на примеры из спецификации ([HID1_11.pdf](https://www.usb.org/developers/hidpage/HID1_11.pdf)), поэтому он прост для восприятия и использования для описания отчётов HID любой сложности.

Конечно, вы **должны** понимать, как организованы дескрипторы отчётов HID и как их конструировать, используя элементы, но больше вам не требуется думать об их внутреннем двоичном представлении.

*ВАЖНОЕ ПРИМЕЧАНИЕ*: Поскольку этот DSL был разработан для и с применением GCC/CLang, он не был протестирован с другими типами компиляторов.
Поэтому приветствуются ПРы с поддержкой других компиляторов.

## Пример использования

Чтобы получить первое представление об этой библиотеке, рассмотрим пример ниже.

Это пример дескриптора отчёта HID из официальной спецификации **HID 1.11** для стандартной трёх кнопочной мыши:

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

Это тот же пример, но переписанный на Си используя наше определение HID отчётов:

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

Это очень похоже на оригинальный пример, но элементы имеют префикс *HID_* во избежание коллизий с другими идентификаторами в ваших исходниках. Также элементы со значениями (типа `HID_LOGICAL_MINIMUM`, `HID_LOGICAL_MAXIMUM` и др.) принимают два аргумента: первый означает размер значения в байтах, а второй - это само значение. Элементы, которые объявляют отчёты (типа `HID_INPUT`, `HID_OUTPUT` и `HID_FEATURE`), могут принимать любое число флагов. Аргумент у элементов `HID_END_COLLECTION` был добавлен в целях удобства, так что он опционален и может быть опущен.

Это двоичный вывод, который получен для нашего дескриптора как результат компиляции:

```
00000000  05 01 09 02 a1 01 09 01  a1 00 05 09 19 01 29 03  |..............).|
00000010  15 00 25 01 95 03 75 01  81 02 95 01 75 05 81 01  |..%...u.....u...|
00000020  05 01 09 30 09 31 15 81  25 7f 75 08 95 02 81 06  |...0.1..%.u.....|
00000030  c0 c0                                             |..|
```

А это результат преобразования двоичного представления обратно в текст, используя утилиту `hidrd-convert`:

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

Как видите, оба текстовых представления отчёта для мыши: из примера и результат декомпиляции - идентичны.

## Определение единиц измерения

В некоторых дескрипторах отчётов требуется использовать единицы измерения. Спецификация HID определяет некоторые базовые единицы, которые могут быть использованы для получения любых производных единиц. Смотрите пример ниже:

```C
/* Ампер это базовая единица */
HID_UNIT(SI(LIN), A(1)), HID_UNIT_EXPONENT(0),
/* Вольт может быть получен как cm^2 x g^1 x s^-3 x A^-1 x 10^7 */
HID_UNIT(SI(LIN), CM(2), G(1), S(-3), A(-1)), HID_UNIT_EXPONENT(7),
/* Ватт может быть получен как cm^2 x g^1 x s^-3 x 10^7 */
HID_UNIT(SI(LIN), CM(2), G(1), S(-3)), HID_UNIT_EXPONENT(7),
/* Джоуль может быть получен как cm^2 x g^1 x s^-2 x 10^7 */
HID_UNIT(SI(LIN), CM(2), G(1), S(-2)), HID_UNIT_EXPONENT(7),
```

В примере выше мы использовали линейную систему Си (SI(LIN)) и следующие базовые единицы: Сантиметр (CM), Грамм (G), Секунду (S), Ампер (A). С их помощью мы получили следующие производные единицы: Вольт (V), Ватт (W), Джоуль (J). Также, нам потребовалось указать экспоненту единиц, чтобы соблюсти порядок величин.

## Дополнительные примеры

Дополнительные примеры использования смотрите в *[тестах](test/hid_def.c)*.

## Как это работает

Реализация использует некоторые продвинутые техники препроцессора C, которые объявлены макросами из заголовочного файла *macro.h*.
