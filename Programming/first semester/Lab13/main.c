#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

static const char *optString = "fgv";
static const struct option longOpts[] ={
       {"filepath", required_argument, NULL, 'f'},
       {"get", required_argument, NULL, 'g'},
       {"value", required_argument, NULL, 'v'},
       {"show", no_argument, NULL, 0},
       {"set", required_argument, NULL, 0}
};
typedef union Tag{
    char buffer[12];
    struct{
        unsigned char flags;
        unsigned int size;
    } data;
} TAG;

typedef union Frame{;
    char buffer[10];
    struct{
        unsigned char name[4];
        unsigned int size;
        unsigned char flags;
    } data;
} FRAME;

unsigned int reverse(unsigned int n){
    return ((n >> 24) & 0x000000ff) | ((n >> 8) & 0x0000ff00) | ((n << 8) & 0x00ff0000) |((n << 24) & 0xff000000);
}

void show(char* file_name){
    FILE* file;
    file = fopen(file_name, "rb");
    fseek(file, 0, SEEK_SET);
    if (file == NULL){
        printf("error when open file %s\n", file_name);
        exit(1);`pre
    }
    TAG tag;
    fread(tag.buffer + 2, sizeof(char), 10, file);
    unsigned int size_tag = reverse(tag.data.size);
    while (ftell(file) < size_tag + 10){
        FRAME frame;
        fread(frame.buffer, sizeof(char), 10, file);
        if (frame.data.name[0] == 0){
            break;
        }
        printf("%s: ", frame.data.name);
        unsigned int size_frame = reverse(frame.data.size);
        char* frame_data = malloc(sizeof(char) * size_frame);
        fread(frame_data, sizeof(char), size_frame, file);
        for (unsigned int i = 3; i < size_frame; ++i){
            printf("%c", frame_data[i]);
        }
        printf("\n");
        free(frame_data);
    }
    fclose(file);
}

void get(char* file_name, char* prop_name){
    FILE *file;
    file = fopen(file_name, "rb");
    fseek(file, 0, SEEK_SET);
    if (file == NULL){
        printf("error when open file %s\n", file_name);
        exit(1);
    }
    TAG tag;
    fread(tag.buffer + 2, sizeof(char), 10, file);
    unsigned int size_tag = reverse(tag.data.size);\
    while (ftell(file) < size_tag + 10){
        FRAME frame;
        fread(frame.buffer, sizeof(char), 10, file);
        unsigned int size_frame = reverse(frame.data.size);
        if (strcmp((char *)frame.data.name, prop_name) == 0){
            printf("%s: ", frame.data.name);
            char* frame_data = malloc(sizeof(char) * size_frame);
            fread(frame_data, sizeof(char), size_frame, file);
            for (unsigned int i = 3; i < size_frame; ++i){
                printf("%c", frame_data[i]);
            }
            printf("\n");
            free(frame_data);
        }
        if (frame.data.name[0] == 0){
            break;
        }
        fseek(file, size_frame, SEEK_CUR);
    }
    fclose(file);
}

void copy(FILE* input, FILE* output){
    int c;
    while ((c = getc(input)) != EOF)
        putc(c, output);
}

void set(char* file_name, char frame_name[4], char* frame_value){
    FILE* file;
    file = fopen(file_name, "rb");
    TAG tag;
    fread(tag.buffer + 2, sizeof(char), 10, file);
    unsigned int size_tag = reverse(tag.data.size);
    unsigned int old_frame_pos = 0;
    unsigned int old_frame_size = 0;
    while (ftell(file) < size_tag + 10){
        FRAME frame;
        fread(frame.buffer, sizeof(char), 10, file);
        unsigned int frameSize = reverse(frame.data.size);
        if (strcmp(frame.data.name, frame_name) == 0){
            old_frame_pos = ftell(file) - 10;
            old_frame_size = frameSize;
            break;
        }
        fseek(file, frameSize, SEEK_CUR);
    }
    unsigned int value_size = strlen(frame_value);
    unsigned int new_tag_size = size_tag - old_frame_size + value_size + 10 * (old_frame_pos != 0);
    if (old_frame_pos == 0){
        old_frame_pos = ftell(file);
    }
    if (value_size == 0){
        new_tag_size -= 10;
    }
    FILE* file_copy;
    file_copy = fopen("temp.mp3", "wb");
    fseek(file, 0, SEEK_SET);
    fseek(file_copy, 0, SEEK_SET);
    copy(file, file_copy);
    fclose(file);
    fclose(file_copy);
    file_copy = fopen("temp.mp3", "rb");
    file = fopen(file_name, "wb");
    tag.data.size = reverse(new_tag_size);
    fwrite(tag.buffer + 2, sizeof(char), 10, file);
    fseek(file_copy, 10, SEEK_SET);
    for (unsigned int i = 0; i < old_frame_pos - 10; ++i){
        int c;
        c = getc(file_copy);
        putc(c, file);
    }
    if (value_size > 0){
        FRAME frame_c;
        for (unsigned int j = 0; j < 4; ++j){
            frame_c.data.name[j] = frame_name[j];
        }
        frame_c.data.size = reverse(value_size);
        frame_c.data.flags = 0;
        fwrite(frame_c.buffer, sizeof(char), 10, file);
    }
    fwrite(frame_value, sizeof(char), value_size, file);
    fseek(file_copy, old_frame_pos + 10 + old_frame_size, SEEK_SET);
    for (unsigned int i = ftell(file); i < new_tag_size; ++i){
        unsigned short int c;
        c = getc(file_copy);
        putc(c, file);
    }
    copy(file_copy, file);
    fclose(file);
    fclose(file_copy);
    remove("temp.mp3");
}


int main (int argc, char *argv[]){
    char* file_name, *prop_name, *prop_value;
    int longIndex;
    int opt = getopt_long( argc, argv, optString, longOpts, &longIndex);
    while (opt != -1){
        switch (opt){
            case 'f':
                file_name = optarg;
                break;
            case 'g':
                prop_name = optarg;
                get(file_name, prop_name);
                break;
            case 'v':
                prop_value = optarg;
                set(file_name, prop_name, prop_value);
                break;
            case 0:
                if (strcmp("show", longOpts[longIndex].name) == 0){
                    show(file_name);
                }
                if (strcmp("set", longOpts[longIndex].name) == 0){
                    prop_name = optarg;
                }
                break;
            default:
                break;
        }
        opt = getopt_long(argc, argv, optString, longOpts, &longIndex);
    }
    return 0;
}