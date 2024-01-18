#ifndef GATEKEEPER_FLAGS_UTILS_H
#define GATEKEEPER_FLAGS_UTILS_H

///
/// @brief Determines whether a specific flag is set in the source.
/// @param src The source integer containing flags.
/// @param target The flag to check.
/// @return 1 if the flag is set; otherwise, 0.
///
char has_flag(int src, int target);

///
/// @brief Enables the specified flag.
/// @param src The pointer to the flags container.
/// @param target The flag to add.
///
void enable_flag(void* src, int target);

///
/// @brief Disables the specified flag.
/// @param src The pointer to the flags container.
/// @param target The flag to disable.
///
void disable_flag(void* src, int target);

#endif