#ifndef GATEKEEPER_FLAGS_H
#define GATEKEEPER_FLAGS_H

///
/// @brief Determines whether the source has the specified flag.
/// @param src The source of flags.
/// @param flag The flag in question.
/// @return 1, when the flag is enabled; otherwise, 0.
///
#define has_flag(src, flag) (src) & (flag) == (flag)

///
/// @brief Enables the specified flag.
/// @param src The source of flags.
/// @param flag The flag to enable.
///
#define enable_flag(src, flag) (src) |= (flag)

///
/// @brief Disables the specified flag.
/// @param src The source of flags.
/// @param flag The flag to disable.
///
#define disable_flag(src, flag) (src) &= ~(flag)

#endif // GATEKEEPER_FLAGS_H