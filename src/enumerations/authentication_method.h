#ifndef AUTHENTICATION_METHOD_H_
#define AUTHENTICATION_METHOD_H_

///
/// @brief Represents the supported methods of authentication. 
///
typedef enum
{
    ///
    /// @brief Value indicating that connection used the SSL authentication method.
    ///
    SSL,
    
    ///
    /// @brief Value indicating that connection used the login-password pair authentication method.
    ///
    SIMPLE,
    
    ///
    /// @brief Value indicating that connection did not use any authentication method.
    ///
    ANONYMOUS,
    
    ///
    /// @brief Value indicating that connection used the GSSAPI authentication method.
    ///
    SASL_GSSAPI,
    
    ///
    /// @brief Value indicating that connection used the EXTERNAL authentication method.
    ///
    SASL_EXTERNAL,
    
    ///
    /// @brief Value indicating that connection used the DIGEST-MD5 authentication method.
    ///
    SASL_DIGEST_MD5
}
authentication_method_t;

#endif  // AUTHENTICATION_METHOD_H_
