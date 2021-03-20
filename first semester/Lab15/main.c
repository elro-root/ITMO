#include <stdio.h>
#include <stdlib.h>
#include <string.h>

union archive_list {
    char tmp[8];

    struct {
        unsigned num_of_files;
        unsigned size_of_list;
    } list;
};

union archive_header {
    char tmp[4];

    struct {
        unsigned arc_size;
    } arc;
};

union file_header {
    char tmp[8];

    struct {
        unsigned header_size;
        unsigned file_size;
    } file;
};


void copy(FILE *file, FILE *archive) {
    int c;
    while ((c = getc(file)) != EOF) {
        putc(c, archive);
    }
}

unsigned find_size(char *file_name) {
    FILE *file = fopen(file_name, "rb");
    fseek(file, 0, SEEK_END);
    unsigned file_size = ftell(file);
    fclose(file);
    return file_size;
}

void create(char *arch_name, int argc, char *argv[]) {
    FILE *arch_file = fopen(arch_name, "wb");

    union archive_list archive_list;
    union archive_header arc_header;
    arc_header.arc.arc_size = 12;
    archive_list.list.num_of_files = 0;
    archive_list.list.size_of_list = 0;

    for (int i = 4; i < argc; i++) {
        unsigned file_name_size = strlen(argv[i]);
        archive_list.list.size_of_list += file_name_size;
        arc_header.arc.arc_size += find_size(argv[i]) + 8 + file_name_size * 2 + 1;
        archive_list.list.num_of_files += 1; //считаем кол-во файлов при создании архива
    }

    fwrite(arc_header.tmp, sizeof(char), 4, arch_file);
    fwrite(archive_list.tmp, sizeof(char), 8, arch_file);

    for (int i = 4; i < argc; i++) {

        fwrite(argv[i], sizeof(char), strlen(argv[i]), arch_file);
        fputc(63, arch_file); // "?"

    }

    for (int i = 4; i < argc; i++) {
        union file_header file_header;
        file_header.file.header_size = 8 + strlen(argv[i]);
        file_header.file.file_size = find_size(argv[i]);


        fwrite(file_header.tmp, sizeof(char), 8, arch_file);
        fwrite(argv[i], sizeof(char), strlen(argv[i]), arch_file);

        FILE *file = fopen(argv[i], "rb");

        copy(file, arch_file);

        fclose(file);
        remove(argv[i]);
    }

    fclose(arch_file);
}

void list(char *arch_name) {
    FILE *arch_file = fopen(arch_name, "rb");

    union archive_list archive_list;
    fseek(arch_file, 4, SEEK_CUR);
    fread(archive_list.tmp, sizeof(char), 8, arch_file);

    int files_counter = 0;

    while (files_counter < archive_list.list.num_of_files) {
        char ch = fgetc(arch_file);

        while (ch != '?') {
            printf("%c", ch);
            ch = fgetc(arch_file);
        }

        printf("\n");
        files_counter++;
    }

    fclose(arch_file);
}

void extract(char *arch_name) {
    FILE *arch_file = fopen(arch_name, "rb");

    union archive_header arc_header;
    fread(arc_header.tmp, sizeof(char), 4, arch_file);
    union archive_list archive_list;
    fread(archive_list.tmp, sizeof(char), 8, arch_file);
    fseek(arch_file, archive_list.list.num_of_files + archive_list.list.size_of_list,
          SEEK_CUR);

    while (ftell(arch_file) < arc_header.arc.arc_size) {
        union file_header file_header;
        fread(file_header.tmp, sizeof(char), 8, arch_file);

        char *file_name = malloc((file_header.file.header_size - 8) * sizeof(char));
        fread(file_name, sizeof(char), file_header.file.header_size - 8, arch_file);

        FILE *output_file = fopen(file_name, "wb");
          //
        for (unsigned i = 0; i < file_header.file.file_size; i++) {
            int c = getc(arch_file);
            putc(c, output_file);
        }

        fclose(output_file);
        free(file_name);
    }
    fclose(arch_file);
}

int main(int argc, char *argv[]) {
    char *arch_name = argv[2];

    switch (argv[3][2]) {
        case 'c':
            create(arch_name, argc, argv);
            break;
        case 'e':
            extract(arch_name);
            remove(arch_name);
            break;
        case 'l':
            printf("File in %s:\n", arch_name);
            list(arch_name);
            break;
        default:
            printf("Please enter the correct command:\ncreate\nextract\nlist\n");
            break;
    }
}
