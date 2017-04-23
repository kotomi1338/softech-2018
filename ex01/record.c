#include <stdio.h>

int main(void)
{
        FILE *file;
        char name;
        int number;

        file = fopen("log.csv", "a");

        printf("商品名を入力(小文字アルファベット1文字)\n--> ");
        scanf("%c", &name);

        printf("個数を入力(整数)\n--> ");
        scanf("%d", &number);

        fprintf(file, "%c, %d\n", name, number);

        fclose(file);
        return 0;
}
