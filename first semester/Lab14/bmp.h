//
// Created by Patrik Duksin on 2021-04-07.
//

#ifndef LAB14_BMP_H
#define LAB14_BMP_H

#pragma pack(push, 1)
typedef struct {             // Total: 54 data
    uint16_t  type;             // Magic identifier: 0x4d42
    uint32_t  size;             // File size in data
    uint16_t  reserved1;        // Not used
    uint16_t  reserved2;        // Not used
    uint32_t  offset;           // Offset to image data in data from beginning of file (54 data)
    uint32_t  dib_header_size;  // DIB Header size in data (40 data)
    int32_t   width_px;         // Width of the image
    int32_t   height_px;        // Height of image
    uint16_t  num_planes;       // Number of color planes
    uint16_t  bits_per_pixel;   // Bits per pixel
    uint32_t  compression;      // Compression type
    uint32_t  image_size_bytes; // Image size in data
    int32_t   x_resolution_ppm; // Pixels per meter
    int32_t   y_resolution_ppm; // Pixels per meter
    uint32_t  num_colors;       // Number of colors
    uint32_t  important_colors; // Important colors
} BMPHeader;
#pragma pack(pop)

int** gen_malloc(int height, int width){
    int** arr = (int** )malloc(sizeof(int*) * height);
    for (int i = 0; i < height; ++i) {
        arr[i] = (int*) malloc(sizeof(int*) * width);
    }
    return arr;
}

void gen_free(int** gen, int height){
    for (int i = 0; i < height; ++i) {
        free(gen[i]);
    }
    free(gen);
}

unsigned count_nbr (int** grid, int i, int j, int height, int width) {
    int n_count = 0;
    if (i-1 >= 0 && j-1 >= 0) {
        if (grid[i-1][j-1] >= 1)
            n_count++;
    }

    if (i-1 >= 0) {
        if(grid[i-1][j] >= 1)
            n_count++;
    }

    if (i-1 >= 0 && j+1 < height) {
        if(grid[i-1][j+1] >= 1)
            n_count++;
    }

    if (j-1 >= 0) {
        if(grid[i][j-1] >= 1)
            n_count++;
    }

    if (j+1 < height) {
        if(grid[i][j+1] >= 1)
            n_count++;
    }

    if (i+1 < width && j-1 >=0) {
        if(grid[i+1][j-1] >= 1)
            n_count++;
    }

    if (i+1 < width) {
        if(grid[i+1][j] >= 1)
            n_count++;
    }

    if (i+1 < width && j+1 < height) {
        if(grid[i+1][j+1] >= 1)
            n_count++;
    }

    return n_count;
}

int** GOFL(int** cur_gen, int height, int width) { //в аргументы функции приходят массив настоящего поколения, высота и ширина
    int** next_gen = gen_malloc(height, width);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            next_gen[i][j] = 0;
            int count = count_nbr(cur_gen, i, j, height, width);
            if (count < 2 || count > 3) //точка умирает, если соседей меньше двух или больше трех
                next_gen[i][j] = 0;
            if (count == 2)//остается неизменной, если соседей 2
                next_gen[i][j] = cur_gen[i][j];
            if (count == 3)
                next_gen[i][j] = 1;//рождается, если соседей 3
        }
    }
    return next_gen;//возвращаем матрицу пикселей
}
#endif //LAB14_BMP_H
