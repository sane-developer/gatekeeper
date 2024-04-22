#ifndef BIND_REQUEST_STATUS_H_
#define BIND_REQUEST_STATUS_H_

///
/// @brief Represents the status of processed bind request.
///
typedef enum
{
    ///
    /// @brief Value indicating that bind request has been granted.
    ///
    REQUEST_GRANTED = 0,

    ///
    /// @brief Value indicating that bind request has been denied.
    ///
    REQUEST_DENIED = 1
}
bind_request_evaluation_t;

///
/// @brief Represents the status of the bind request evaluation.
///
typedef struct
{
    ///
    /// @brief Flag indicating whether bind request has been granted or denied.
    ///
    bind_request_evaluation_t evaluation;

    ///
    /// @brief Pointer to a string containing the reason behind performed evaluation. 
    ///
    char* reason;
}
bind_request_status_t;

#endif  // BIND_REQUEST_STATUS_H_
