#ifndef UTIL_H
#define UTIL_H

typedef enum os_type
{
    WINDOWS,
    LINUX,
    MAC

} OS_Type;

OS_Type get_os(void);
void clear_terminal(void);

#endif // UTIL_H