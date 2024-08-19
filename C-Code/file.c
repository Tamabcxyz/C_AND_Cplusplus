//read and write file
#include <stdio.h>

int main()
{
    FILE *rfile, *wfile;
    rfile = fopen("test.txt", "r");
    wfile = fopen("test_cp.txt", "w");
    if(!rfile | !wfile) {
        printf("cannot open file\n");
    }
    char str[255];
    while(fgets(str, sizeof(str), rfile)){
        puts(str);
        fputs(str, wfile);
    }
    
    fclose(rfile);
    fclose(wfile);
    return 0;
}