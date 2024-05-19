// printk and scank lib

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

// 自定义的可变参数输入函数，用于读取不同类型的输入
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


// 自定义的可变参数输出函数，用于打印不同类型的输出
void print(const char* format, ...) {
    va_list args;
    va_start(args, format);

    for (const char* fmt_ptr = format; *fmt_ptr != '\0'; ++fmt_ptr) {
        if (*fmt_ptr == '%') {
            char format_buffer[11]; // 用于构建格式字符串
            format_buffer[0] = '%';
            int index = 1;

            for (; *(fmt_ptr + index) != '\0' && *(fmt_ptr + index) != '%'; ++index) {
                format_buffer[index] = *(fmt_ptr + index);
            }
            format_buffer[index + 1] = '\0'; // 确保字符串以null结尾

            switch (*(fmt_ptr + index)) {
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
                    int value = va_arg(args, int);
                    printf(format_buffer, value);
                    break;
                }
                case 'f': {
                    double value = va_arg(args, double);
                    printf(format_buffer, value);
                    break;
                }
                default:
                    // 打印未识别的格式字符
                    printf("%%%c", *(fmt_ptr + index));
                    break;
            }
        } else {
            putchar(*fmt_ptr);
        }
    }

    va_end(args);
}


