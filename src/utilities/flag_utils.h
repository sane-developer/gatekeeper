#ifndef GATEKEEPER_FLAGS_H
#define GATEKEEPER_FLAGS_H

///
/// @brief Determines whether a specific flag is set in the source.
/// @param source The source integer containing flags.
/// @param target The flag to check.
/// @return 1 if the flag is set; otherwise, 0.
///
char has_flag(int source, int target);

///
/// @brief Enables the specified flag.
/// @param source The pointer to the flags container.
/// @param target The flag to add.
///
void enable_flag(void* source, int target);

///
/// @brief Disables the specified flag.
/// @param source The pointer to the flags container.
/// @param target The flag to disable.
///
void disable_flag(void* source, int target);

#endif