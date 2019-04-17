// Smayan Daruka
// sd9080
// Homework 6

#define _BSD_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <endian.h>
#include <string.h>
#include "exec.h"

// analyze_file function takes in the file pointer and the name of the file
int analyze_file(FILE* file, char* filename){
    // creates an exec_t struct specified in exec.h
    exec_t table;

    // creates 3 structs namely symbol table, reference table, and relocation table
    syment_t sym;
    refent_t ref;
    relent_t rel;

    // buffer variables to read in data from the file
    uint32_t buf32;
    uint16_t buf16;
    uint8_t buf8;

    // an array of char pointers that contain all of the section names
    char* section_name[] = {"text", "rdata", "data","sdata", "sbss", "bss", "reltab", "reftab", "symtab", "strings"};

    // counter variables
    int count;
    size_t i;

    // size of the header block in bytes
    int size_header_block = 52;

    // variable used for fseek to move specified number of bytes
    size_t offset_bytes;

    // reads in the first 2 bytes of the file
    fread(&buf16,2,1,file);
    // converts from big-endian to litte-endian
    table.magic = be16toh(buf16);
    // reads in the next 2 bytes of the file
    fread(&buf16,2,1,file);
    // converts from big-endian to litte-endian
    table.version = be16toh(buf16);

    // checks if the file has the correct magic number and if not, it stops processing that file
    // prints an error message for the same
    if(table.magic != HDR_MAGIC){
        fprintf(stderr, "error: %s is not an R2K object module (magic number %#6x)\n", filename, table.magic);
        return EXIT_FAILURE;
    }

    // prints 20 hyphens as mentioned in the write-up
    printf("--------------------\n");

    // reads in the next 4 bytes of the file
    fread(&buf32,4,1,file);
    // reads in the next 4 bytes of the file
    fread(&buf32,4,1,file);
    // converts from big-endian to litte-endian
    table.entry = be32toh(buf32);

    // checks if there is an entry point in the file
    if(table.entry == 0)
        printf("File %s is an R2K object module\n", filename);
    else
        printf("File %s is an R2K load module (entry point %#010x)\n", filename, table.entry);

    // Prints the date after decoding the version number
    printf("Module version: %4d/%02d/%02d\n", 2000 + ((table.version >> 9) & 0x7), table.version >> 5 & 0xf, table.version & 0x1f);

    // This loop prints all the sections information
    for(count = 0; count < N_EH; count++){
        // reads in the next 4 bytes of the file
        fread(&buf32,4,1,file);
        // converts from big-endian to litte-endian
        table.data[count] = be32toh(buf32);
        // checks if that particular section is not empty and then prints it
        if(table.data[count] != 0){
            if(count > 5 && count < 9)
                printf("Section %s is %d entries long\n", section_name[count], table.data[count]);
            else
                printf("Section %s is %d bytes long\n", section_name[count], table.data[count]);
        }
    }

    // temp variable
    uint32_t tempTable[(table.sz_strings) / 4];
    // creates a string table
    char string[table.sz_strings];

    // calculates the size of all data up to the string table
    for(i = 0; i < EH_IX_STR; i++){
        if(i < 6)
            size_header_block += table.data[i];
        else if(i == 6)
            size_header_block += (8 * table.data[i]);
        else // each entry is 12 bytes long: reltab and reftab
            size_header_block += (12 * table.data[i]);
    }

    // sets the read cursor to the specified position and reads in data into the tempTable
    fseek(file, size_header_block, SEEK_SET);
    for(i = 0; i < (table.sz_strings / 4); i++){
        // reads in the next 4 bytes of the file
        fread(&buf32,4,1,file);
        tempTable[i] = buf32;
    }
    // copies tempTable into string table which is used later for reference table and symbols table
    memcpy(string, tempTable, table.sz_strings);

    // Relocation table
    // checks if the relocation table is not null or empty
    if(table.data[EH_IX_REL] != 0){
        printf("Relocation information:\n");
        // sets the offset and later moves to that location
        offset_bytes = (size_header_block - ((8 * table.data[6]) + (12 * (table.data[7] + table.data[8]))));
        fseek(file, offset_bytes, SEEK_SET);
        for(i = 0; i < table.n_reloc; i++){
            // reads in the next 4 bytes of the file
            fread(&buf32, 4, 1, file);
            // converts from big-endian to litte-endian
            rel.addr = be32toh(buf32);
            // reads in the next 1 byte of the file
            fread(&buf8, 1, 1, file);
            rel.section = buf8;
            // reads in the next 1 byte of the file
            fread(&buf8, 1, 1, file);
            rel.type = buf8;
            // reads in the next 2 bytes of the file
            fread(&buf16, 2, 1, file);
            printf("   %#010x (%s) type %#06x\n", rel.addr, section_name[rel.section - 1], rel.type);
        }
    }

    // Reference table
    // checks if the reference table is not null or empty
    if(table.n_refs != 0){
        printf("Reference information:\n");
        // sets the offset and later moves to that location
        offset_bytes = (size_header_block - (12 * (table.n_syms + table.n_refs)));
        fseek(file, offset_bytes, SEEK_SET);
        for(i = 0; i < table.n_refs; i++){
            // reads in the next 4 bytes of the file
            fread(&buf32, 4, 1, file);
            // converts from big-endian to litte-endian
            ref.addr = be32toh(buf32);
            // reads in the next 4 bytes of the file
            fread(&buf32, 4, 1, file);
            // converts from big-endian to litte-endian
            ref.sym = be32toh(buf32);
            // reads in the next 1 byte of the file
            fread(&buf8, 1, 1, file);
            ref.section = buf8;
            // reads in the next 1 byte of the file
            fread(&buf8, 1, 1, file);
            ref.type = buf8;
            // reads in the next 2 bytes of the file
            fread(&buf16, 2, 1, file);
            printf("   %#010x type %#06x symbol %s\n", ref.addr, ref.type, (string + ref.sym));
        }
    }

    // Symbol Table
    // checks if the symbol table is not null or empty
    if(table.n_syms != 0){
        printf("Symbol table:\n");
        // sets the offset and later moves to that location
        offset_bytes = (size_header_block - (12 * table.n_syms));
        fseek(file, offset_bytes, SEEK_SET);
        for(i = 0; i < table.n_syms; i++){
            // reads in the next 4 bytes of the file
            fread(&buf32, 4, 1, file);
            // converts from big-endian to litte-endian
            sym.flags = be32toh(buf32);
            // reads in the next 4 bytes of the file
            fread(&buf32, 4, 1, file);
            // converts from big-endian to litte-endian
            sym.value = be32toh(buf32);
            // reads in the next 4 bytes of the file
            fread(&buf32, 4, 1, file);
            // converts from big-endian to litte-endian
            sym.sym = be32toh(buf32);
            printf("   value 0x%08x flags 0x%08x symbol %s\n", sym.value, sym.flags, (string + sym.sym));
        }
    }
    // prints 20 hyphens as mentioned in the write-up
    printf("--------------------\n");

    return 1;
}

int main(int argc, char* argv[]){
    // checks if there were no command line arguments and prints a usage message and exits the program
    if(argc == 1){
        fprintf(stderr, "usage: alm file1 [ file2 ... ]\n");
        return EXIT_FAILURE;
    }
    // for every command line argument, it opens the file and passes it into the analyze function
    for(int i = 1; i < argc; i++){
        FILE* fp = fopen(argv[i], "r");
        // if the file was opened successfully
        if(fp != NULL){
            analyze_file(fp, argv[i]);
            fclose(fp);
        }
        // prints the error message when the file could not be opened for reading
        else
            perror(argv[i]);
    }
    return 0;
}
