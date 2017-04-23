#include <stdio.h>
#include <stdlib.h>

int main(void)
{
        FILE *file;
        int id, number;
        char name;
        int count[10];
        int sum = 0;
        char input;

        if ((file = fopen("log.csv", "r")) == NULL) {
                printf("ファイルを開けません。\n");
                return -1;
        }

        printf("商品名を入力(小文字アルファベット1文字)\n--> ");
        scanf("%c", &input);

        while(fscanf(file, "%c, %d", &name, &number) != EOF) {
                if (name == input) {
                        sum += number;
                }
        }

        printf("商品%cの売上個数は、%d個です。\n", input, sum);

        fclose(file);

        return 0;
}
