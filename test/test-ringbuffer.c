#include "ringbuffer.h"
#include "memcheck.h"
#include "mylog.h"

int main(int argc, char const *argv[])
{
    ringbuffer rb ;
    char *str1 = "abc";
    char *str2 = "1234567890";
    char buf[100] = {0};
    ringbuffer_init(&rb, 100);

    ringbuffer_push(&rb, str1, strlen(str1));
    int count = ringbuffer_count(&rb);
    mylogd("count:%d", count);
    ringbuffer_push(&rb, str2, strlen(str2));
    
    mylogd("before peek count:%d", ringbuffer_count(&rb));
    ringbuffer_peek(&rb, buf, 10);
    mylogd("afer peek count:%d", ringbuffer_count(&rb));
    mylogd("peek content:%s", buf);
    ringbuffer_destroy(&rb);
    check_memory_leak();
    return 0;
}

