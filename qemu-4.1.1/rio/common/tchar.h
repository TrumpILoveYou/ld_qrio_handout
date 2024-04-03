 #ifndef LOG4CPLUS_TCHAR_HEADER_
 #define LOG4CPLUS_TCHAR_HEADER_
 
 #include <log4cplus/config.hxx>
 
 #if defined (LOG4CPLUS_HAVE_PRAGMA_ONCE)
 #pragma once
 #endif
 
 #if defined (_WIN32)
 #include <cstddef>
 #endif
 
 
 #ifdef UNICODE
 #  define LOG4CPLUS_TEXT2(STRING) L##STRING
 #else
 #  define LOG4CPLUS_TEXT2(STRING) STRING
 #endif // UNICODE
 #define LOG4CPLUS_TEXT(STRING) LOG4CPLUS_TEXT2(STRING)
 
 
 namespace log4cplus
 {
 
 #if defined (UNICODE)
 typedef wchar_t tchar;
 
 #else
 typedef char tchar;
 
 #endif
 
 } // namespace log4cplus
 
 
 #endif // LOG4CPLUS_TCHAR_HEADER_
