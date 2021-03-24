#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
static const char *optString = "iomd";

static const struct option longOpts[] = {
        {"input", required_argument, NULL, 'i'},
        {"output", required_argument, NULL, 'o'},
        {"max_iter", required_argument, NULL, 'm'},
        {"dump_freq", required_argument, NULL, 'd'}
};

int **arr_malloc(unsigned long height, unsigned long width){ // Функция динамческого выделения памяти под двумерный массив
    int **ARR = (int **) malloc(height * sizeof(int *));
    for (int i = 0; i < height; i++)
    {
        ARR[i] = (int *) malloc(width * sizeof(int));
    }
    return ARR;
}
void arr_free(int ** arr, unsigned long height){
    for (int i = 0; i < height; i++){
        free(arr[i]);
    }
    free(arr);
}
int neighborCounter(int **area, int x, int y){ // Фукция посчёта кол-ва соседий x y
    int sum = 0;
    for (int i = x - 1; i <= x + 1; i++){
        for (int j = y - 1; j <= y + 1; j++){
            sum += area[i][j];
        }
    }
    if (area[x][y] == 1){
        sum--;
    }
    return sum;
}
unsigned char *matrix_to_str(int **matrix, unsigned long height, unsigned long width){
    unsigned char *info_on_pix = (unsigned char *) malloc(height * width * 3);
    int m = 0;
    for (int i = height - 1; i >= 0; i--){
        for (int j = 0; j < width; j++){
            if (matrix[i][j] == 1)
            { //задача цвета для живых пикселей
                info_on_pix[m] = 0; // синий
                info_on_pix[m + 1] = 100; // зелёный
                info_on_pix[m + 2] = 255; // красный
            } else
            { // задача цвета для заднего фона (неживых пикселей)
                info_on_pix[m] = 0; // синий
                info_on_pix[m + 1] = 0; // зелёный
                info_on_pix[m + 2] = 0; // красный
            }
            m += 3;
        }
    }
    return info_on_pix;
}

int main(int argc, char *argv[]){
    FILE* image;
    long dump_freq = 1, max_iter = 1;
    char  *input_file_name, *dir_name;
    unsigned long height, width, size;
    unsigned char header[54];
    int **current_generation, **next_generation;
    int opt = getopt_long(argc, argv, optString, longOpts, NULL);
    while (opt != -1){
        switch (opt) {
            case 'i':
                input_file_name = optarg;
                image = fopen(input_file_name, "rb");
                if (!image){
                    printf("i cant open file, sorry");
                    exit(0);
                }
                break;
            case 'o':
                dir_name = optarg;
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
    fread(header, sizeof(unsigned char ), 54, image);
    // считываем из заголовка параметров изображения путем побитового прибавления значений байтов со смещением
    size = header[0x5] << 24 | header[0x4] << 16 | header[0x3] << 8 | header[0x2];
    width = header[0x15] << 24 | header[0x14] << 16 | header[0x13] << 8 | header[0x12];
    height = header[0x19] << 24 | header[0x18] << 16 | header[0x17] << 8 | header[0x16];
    printf("size = %lu\nheight = %lu\nwidth = %lu\n\n", size, height, width); // выводим основные параметры bmp изображения
    current_generation = arr_malloc(height, width * 3);
    next_generation = arr_malloc(height,  width * 3);
    fseek(image, 54, SEEK_SET);
    char buffer[3]; // записываем значения пикселей в двумерный массив
    for (int i = height - 1; i >= 0; i--)
    {
        for (int j = 0; j < width; j++){
            buffer[0] = fgetc(image);
            buffer[1] = fgetc(image);
            buffer[2] = fgetc(image);

            if (buffer[0] != 0 || buffer[1] != 0 || buffer[2] != 0)
                current_generation[i][j] = 1;
            else
                current_generation[i][j] = 0;
        }
    }
    char fileName[10]; // выделение памяти для массивов выходных данных
    char directory[256];
    unsigned char *pixelInfo; 
    for (unsigned long i = 0; i < height; i++){ // копирование информации о начально поколении для последующего редактирования
        for (unsigned long j = 0; j < width; j++)
            next_generation[i][j] = current_generation[i][j];
    }
    int countOfNeighbors;
    for (int gameIteration = 0; gameIteration < max_iter; gameIteration++) // создаание новых поколений и вывод их в файл
    {
        for (unsigned long i = 1; i < height - 1; i++) // изменение след. покаления в соответсвиями с правилами игры
        {
            for (unsigned long j = 1; j < width - 1; j++)
            {
                countOfNeighbors = neighborCounter(current_generation, i, j);
                if (current_generation[i][j] == 0 && countOfNeighbors == 3)
                {
                    next_generation[i][j] = 1;
                }
                else if (current_generation[i][j] == 1)
                {
                    if (countOfNeighbors < 2 || countOfNeighbors > 3)
                    {
                        next_generation[i][j] = 0;
                    }
                }
            }
        }
        for (unsigned long i = 0; i < height; i++) // обновление новосгенерированного покаления
        {
            for (unsigned long j = 0; j < width; j++)
            {
                current_generation[i][j] = next_generation[i][j];
            }
        }
        pixelInfo = matrix_to_str(current_generation, height, width); // перевод информации о пикселях из двумерного массива в строку
        if (gameIteration % dump_freq == 0) // создание output файла если номер итерации соответствует частоте
        {
            // адрес сохраняемого файла
            sprintf(fileName, "%d", gameIteration); // приведение номера итерации к строковому типу для задания имени файла
            strcpy(directory, dir_name); // название директории считанное с коммандной строки
            strcat(directory, "/");
            strcat(directory, fileName);
            strcat(directory, ".bmp");
            FILE *new_bmp = fopen(directory, "wb"); // Создание output файла
            if (new_bmp != NULL)
            {
                printf("File number %d was created\n", gameIteration);
            }
            else
            {
                printf("File number %d wasn't created\n", gameIteration);
            }
            fseek(new_bmp, 0, SEEK_SET);
            fwrite(header, 1, 54, new_bmp); // записываем в output файл значений заголовка (не изменяется) и значений пикселей
            fwrite(pixelInfo, 1, 3 * width * height, new_bmp);
        }
    }
    arr_free(current_generation, height);
    arr_free(next_generation, height);
    free(pixelInfo);
    return 0;
}
