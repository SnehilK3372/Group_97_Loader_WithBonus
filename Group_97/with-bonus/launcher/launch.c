#include "../loader/loader.h"

Elf32_Ehdr *ehdr_check;

int main(int argc, char** argv){
    if(argc != 2) {
        printf("Usage: %s <ELF Executable> \n",argv[0]);
        exit(1);
    }

    int fd=open(argv[1],O_RDONLY);

    ehdr_check=malloc(sizeof(Elf32_Ehdr));
    read(fd,ehdr_check,sizeof(Elf32_Ehdr));

    if(!(ehdr_check->e_ident[0]==0x7f && ehdr_check->e_ident[1]=='E' && ehdr_check->e_ident[2]=='L' && ehdr_check->e_ident[3]=='F')){
        printf("Provided file is not in ELF format");
        exit(1);
    }
    close(fd);

    load_and_run_elf(argv);
    loader_cleanup(); 
    return 0;
}