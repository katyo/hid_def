#ifndef __MACRO_H__
#define __MACRO_H__

#define _NONE(...)

#define _UNWR_(...) __VA_ARGS__
#define _UNWR(a) _UNWR_ a

#define _CAT2_(a, b) a##b
#define _CAT2(a, b) _CAT2_(a, b)

#define _CAT3_(a, b, c) a##b##c
#define _CAT3(a, b, c) _CAT3_(a, b, c)

#define _CAT4_(a, b, c, d) a##b##c##d
#define _CAT4(a, b, c, d) _CAT4_(a, b, c, d)

#define _CAT5_(a, b, c, d, e) a##b##c##d##e
#define _CAT5(a, b, c, d, e) _CAT5_(a, b, c, d, e)

#define _NTH0_(a, ...) a
#define _NTH0(...) _NTH0_(__VA_ARGS__)

#define _NTH1_(a, b, ...) b
#define _NTH1(...) _NTH1_(__VA_ARGS__)

#define _NTH2_(a, b, c, ...) c
#define _NTH2(...) _NTH2_(__VA_ARGS__)

#define _NTH3_(a, b, c, d, ...) d
#define _NTH3(...) _NTH3_(__VA_ARGS__)

#define _NTH4_(a, b, c, d, e, ...) e
#define _NTH4(...) _NTH4_(__VA_ARGS__)

#define _MAX2(a, b) ((a) > (b) ? (a) : (b))
#define _MIN2(a, b) ((a) < (b) ? (a) : (b))

#define _CALL_(f, ...) f(__VA_ARGS__)
#define _CALL(f, ...) _CALL_(f, ##__VA_ARGS__)

#define _EVAL0(...) __VA_ARGS__
#define _EVAL1(...) _EVAL0(_EVAL0(_EVAL0(__VA_ARGS__)))
#define _EVAL2(...) _EVAL1(_EVAL1(_EVAL1(__VA_ARGS__)))
#define _EVAL3(...) _EVAL2(_EVAL2(_EVAL2(__VA_ARGS__)))
#define _EVAL4(...) _EVAL3(_EVAL3(_EVAL3(__VA_ARGS__)))
#define _EVAL(...)  _EVAL4(_EVAL4(_EVAL4(__VA_ARGS__)))

#define _MAP_END(...)
#define _MAP_OUT
#define _MAP_COMMA ,

#define _MAP_GET_END2() 0, _MAP_END
#define _MAP_GET_END1(...) _MAP_GET_END2
#define _MAP_GET_END(...) _MAP_GET_END1
#define _MAP_NEXT0(test, next, ...) next _MAP_OUT
#define _MAP_NEXT1(test, next) _MAP_NEXT0(test, next, 0)
#define _MAP_NEXT(test, next)  _MAP_NEXT1(_MAP_GET_END test, next)

#define _MAP0(f, x, peek, ...) f(x) _MAP_NEXT(peek, _MAP1)(f, peek, __VA_ARGS__)
#define _MAP1(f, x, peek, ...) f(x) _MAP_NEXT(peek, _MAP0)(f, peek, __VA_ARGS__)

/**
 * Applies the function macro `f` to each of the remaining parameters.
 */
#define _MAP(f, ...) _EVAL(_MAP1(f, __VA_ARGS__, ()()(), ()()(), ()()(), 0))

#define _ASSERT(x) (1/(!!(x)) ? (x) : (x))

#endif /* __MACRO_H__ */
