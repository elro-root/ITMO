#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h> //для считывания аругментов комндой строки
#include <sys/stat.h> //для создания папки mkdir()
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
    int max_iter = -1, dump_freq = 1;
    uint32_t size;
    int32_t height, width;
    char* dir_name = NULL;
    FILE* in = NULL;
    int opt = getopt_long(argc, argv, optString, longOpts, NULL);
    while (opt != -1){
        switch (opt) {
            case 'i':
                in = fopen(optarg, "rb");
                if (!in){
                    printf("i cant open input file, sorry");
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
    unsigned char* data = (unsigned char*) malloc((size - sizeof(header)) * sizeof(unsigned char));
    fread(data, size - sizeof(header), 1, in);
    fclose(in);
    int** current_generation = gen_malloc(height, width);
    int m = 0;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (data[m] != 255 || data[m + 1] != 255 || data[m + 2] != 255)
                current_generation[i][j] = 1;
            else
                current_generation[i][j] = 0;
            m += 3;
        }
        m += width % 4;
    }
    char gen_num[10];
    char directory[256];
    char name[30] = "Generation ";
    int g = 1;
    while (g <= max_iter) {
        int** next_generation = GOFL(current_generation,  height, width);
        if (!check(current_generation, next_generation, height, width)){
            gen_free(next_generation, height);
            break;
        }
        if (g % dump_freq != 0)
            continue;
        // адрес сохраняемого файла
        sprintf(gen_num, "%d", g);
        strcpy(directory, dir_name);
        strcat(directory, "/");
        strcat(directory, name);
        strcat(directory, gen_num);
        strcat(directory, ".bmp");
        FILE *out = fopen(directory, "wb");
        if (out == NULL){
            printf("i can open output file, sorry\n");
            gen_free(next_generation, height);
            break;
        }
        m = 0;

        for (int i = 0; i < height; ++i) { //преобразовываем массив из нулей и единиц в байтовый массив пикселей
            for (int j = 0; j < width; ++j) {
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
                data[m] = 0; //выравнивание строки для кратности ее 4
                ++m;
            }
        }
        fwrite(&header, sizeof(header), 1, out);
        fwrite(data, size - sizeof(header), 1, out);
        fclose(out);
        current_generation = next_generation;
        ++g;
    }
    printf("End of game, created %d generation.\n", g - 1);
    gen_free(current_generation, height);
    free(data);
    return 0;
}