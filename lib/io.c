// printk and scank lib

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

//自定义的可变参数输入函数，用于读取不同类型的输入
void scan(const char* format, ...) {
    va_list args;
    va_start(args, format);

    const char* fmt_ptr = format; // 用于遍历 format 字符串
    while (*fmt_ptr != '\0') {
        if (*fmt_ptr == '%') {
            fmt_ptr++; // 跳过 '%'

            switch (*fmt_ptr) {
                case 'd': {
                    int* value = va_arg(args, int*);
                    scanf("%d", value);
                    break;
                }
                case 's': {
                    char* value = va_arg(args, char*);
                    scanf("%99s", value); // 防止缓冲区溢出
                    break;
                }
                case 'c': {
                    char* value = va_arg(args, char*);
                    scanf("%c", value);
                    break; 
                }
                case 'l': {
                    fmt_ptr++; 
                    double* value = va_arg(args, double*);
                    scanf("%lf", value);
                    break; 
                }
                default:
                    break;
            }
        }
        fmt_ptr++;
    }

    va_end(args);
}

void print(const char* format, ...) {
    va_list args;
    va_start(args, format);

    while (*format != '\0') {
        if (*format == '%') {
            const char* start_format = format;  // 记录格式字符串的起始位置
            format++; // 移动指针以跳过 '%'

            // 检查是否有格式说明符
            while (*format >= '0' && *format <= '9' || *format == '.') {
                format++;
            }
            if (*format=='l' && *(format+1)=='f')
                format++;

            // 处理格式字符
            char format_specifier = *format;
            char format_buffer[32];  // 用于存储完整的格式字符串
            size_t format_length = format - start_format + 1;
            snprintf(format_buffer, format_length + 1, "%s", start_format);

            switch (format_specifier) {
                case 'd': {
                    int value = va_arg(args, int);
                    printf(format_buffer, value);
                    break;
                }
                case 's': {
                    const char* value = va_arg(args, const char*);
                    printf(format_buffer, value);
                    break;
                }
                case 'c': {
                    int value = va_arg(args, int); // `char` 在 va_arg 中提升为 `int`
                    printf(format_buffer, value);
                    break;
                }
                case 'f': {
                    double value = va_arg(args, double);
                    printf(format_buffer, value);
                    break;
                }
                default:
                    // 如果不是以上任何一个类型，则打印格式符号
                    putchar('%');
                    putchar(format_specifier);
                    break;
            }
        } else {
            putchar(*format);
        }
        format++; // 移动指针到下一个字符
    }

    va_end(args);
}

// int main() {
//     print("Hello %s! Your score is %d and your grade is %c.\n", "Alice", 95, 'A');
//     print("Pi is approximately %.2lf.\n", 3.14159);
//     print("Pi is approximately %lf.\n", 3.14159);
//     return 0;
// }

