#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <sys/stat.h>
#include "bmp.h"
static const char *optString = "iomd";

static const struct option longOpts[] = {
        {"input", required_argument, NULL, 'i'},
        {"output", required_argument, NULL, 'o'},
        {"max_iter", required_argument, NULL, 'm'},
        {"dump_freq", required_argument, NULL, 'd'}
};

int main(int argc, char *argv[]){
    BMPHeader header;
    int height, width, size, max_iter, dump_freq = 1;
    max_iter = 2147483647; // максимальное кол-во для поколений
    char* dir_name = NULL;
    FILE* in = NULL;
    int opt = getopt_long(argc, argv, optString, longOpts, NULL);
    while (opt != -1){
        switch (opt) {
            case 'i':
                in = fopen(optarg, "rb");
                if (!in){
                    printf("i cant open file, sorry");
                    exit(0);
                }
                break;
            case 'o':
                dir_name = optarg;
                mkdir(dir_name, 0777);
                break;
            case 'm':
                max_iter = strtol(optarg, NULL, 10);
                break;
            case 'd':
                dump_freq = strtol(optarg, NULL, 10);
                break;
            default:
                break;
        }
        opt = getopt_long(argc, argv, optString, longOpts, NULL);
    }
    fread(&header, sizeof(header), 1, in);
    width = header.width_px;
    height = header.height_px;
    size = header.size;
    unsigned char* data = (unsigned char*) malloc((size - 54) * sizeof(unsigned char));
    fread(data, size - 54, 1, in);
    int** current_generation = gen_malloc(height, width);
    int m = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (data[m] != 255 || data[m + 1] != 255 || data[m + 2] != 255)
                current_generation[i][j] = 1;
            else
                current_generation[i][j] = 0;
            m += 3;
        }
        m += width % 4;
    }
    char num[10]; // выделение памяти для массивов выходных данных
    char directory[256];
    char* name = "Generation ";
    for (int g = 1; g <= max_iter; g++) { // создаание новых поколений и вывод их в файл
        int** next_generation = GOFL(current_generation,  height, width);
        if (!check(current_generation, next_generation, height, width)){
            printf("End of game, created %d generation\n", g - 1);
            gen_free(next_generation, height);
            break;
        }
        if (g % dump_freq != 0) // создание output файла если номер итерации соответствует частоте
            continue;
        // адрес сохраняемого файла
        sprintf(num, "%d", g); // приведение номера итерации к строковому типу для задания имени файла
        strcpy(directory, dir_name); // название директории считанное с коммандной строки
        strcat(directory, "/");
        strcat(directory, name);
        strcat(directory, num);
        strcat(directory, ".bmp");
        FILE *out = fopen(directory, "wb"); // Создание output файла
        if (out == NULL){
            printf("Generation %d wasn't created\n", g);
            return EXIT_FAILURE;
        }
         // записываем в output файл значений заголовка (не изменяется) и значений пикселей
        m = 0;
        for (int i = 0; i < height; i++) { //преобразовываем массив из нулей и единиц в байтовый массив пикселей
            for (int j = 0; j < width; j++) {
                if (next_generation[i][j] == 1) {
                    data[m] = 0;
                    data[m + 1] = 0;
                    data[m + 2] = 0;
                } //цвет живых клеток
                else {
                    data[m] = 255;
                    data[m + 1] = 255;
                    data[m + 2] = 255;
                }//цвет фона
                m += 3;
            }
            while (m % 4 != 0) {
                data[m] = 0; //дозаписываем конец строки теми самыми пустыми байтами для того, чтобы строка была кратна 4 байтам
                m++;
            }
        }
        fwrite(&header, header.offset, 1, out);
        fseek(out, 54, SEEK_SET);
        fwrite(data, sizeof(unsigned char), size, out);
        fclose(out);
        current_generation = next_generation;
    }
    gen_free(current_generation, height);
    //gen_free(next_generation, height);
    free(data);
    return 0;
}
