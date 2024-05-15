#ifndef GATEKEEPER_REPORTER_H_
#define GATEKEEPER_REPORTER_H_

///
/// @brief Reports the details about the bind request evaluation.
/// @param request The pointer to the populated bind request.
/// @param response The pointer to the populated bind response.
/// TODO: Switch void* to dedicated types for request and response when implemented.
///
void report_bind_evaluation(void* request, void* response);

#endif  // GATEKEEPER_REPORTER_H_
