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

int count_nbr (int** grid, int x, int y, int height, int width) {
    int n_count = 0;
    if (y-1 >= 0 && x-1 >= 0 && grid[y-1][x-1] == 1)
        n_count += 1;

    if (y-1 >= 0 && grid[y-1][x] == 1)
        n_count += 1;

    if (y-1 >= 0 && x+1 < width && grid[y-1][x+1] == 1)
        n_count += 1;

    if (x-1 >= 0 && grid[y][x-1] == 1)
        n_count += 1;

    if (x+1 < width && grid[y][x+1] == 1)
        n_count += 1;

    if (y+1 < height && x-1 >=0 && grid[y+1][x-1] == 1)
        n_count += 1;

    if (y+1 < height && grid[y+1][x] == 1)
        n_count += 1;

    if (y+1 < height && x+1 < width && grid[y+1][x+1] == 1)
        n_count += 1;

    return n_count;
}

int** GOFL(int** cur_gen, int height, int width) {
    int** next_gen = gen_malloc(height, width);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            next_gen[i][j] = cur_gen[i][j];
            int count = count_nbr(cur_gen, j, i, height, width);
            if (next_gen[i][j] == 0 && count == 3)
                next_gen[i][j] = 1;
            if (next_gen[i][j] == 1 && (count < 2 || count > 3))
                next_gen[i][j] = 0;
        }
    }
    return next_gen;
}
int check(int** prev_gen, int** cur_gen, int height, int width){
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (prev_gen[i][j] != cur_gen[i][j])
                return 1;
        }
    }
    return 0;
}
#endif //LAB14_BMP_H
