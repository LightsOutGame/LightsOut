#pragma once

// String Macro Helpers
#define STRINGIZE(x) _STRINGIZE(x)
#define _STRINGIZE(x) #x

// Typed Expression Helpers
#define REM(...) __VA_ARGS__
#define EAT(...)

#define TYPEOF(x) TYPEOF_DETAIL(TYPEOF_SEP x)
#define TYPEOF_DETAIL(...) TYPEOF_HEAD(__VA_ARGS__)
#define TYPEOF_HEAD(x, ...) x
#define TYPEOF_SEP(...) __VA_ARGS__,

#define NAMEOF(x) EAT x

#define DECL(x) REM x
