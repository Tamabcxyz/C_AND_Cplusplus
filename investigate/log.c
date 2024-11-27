#include <stdio.h>
#include <string.h>
#define LINE_COUNTER_BUF_LEN 20
static char line_buf[LINE_COUNTER_BUF_LEN] = {
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  ' ',
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', '0', '\t', '\0'};

void update_line_buf(int n){
    snprintf(line_buf, LINE_COUNTER_BUF_LEN, "\n%17d", n);
}

int main()
{
    for(int i=1000;i<=1005;i++){
        update_line_buf(i);
        printf("%s contain data is %d", line_buf, i);
    }

    return 0;
}