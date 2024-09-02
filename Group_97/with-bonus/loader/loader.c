#include "loader.h"


Elf32_Ehdr *ehdr;
Elf32_Phdr *phdr;
int fd;


void loader_cleanup() {
    if(ehdr!=NULL){
        free(ehdr);
    }
    if(phdr!=NULL){
        free(phdr);
    }
    
    close(fd);
}


void load_and_run_elf(char** exe) {

    fd = open(exe[1], O_RDONLY);

    if(fd==-1){
    printf("File not found!\n");
    exit(1);
    }

    ehdr=malloc(sizeof(Elf32_Ehdr));
    if((read(fd, ehdr, sizeof(Elf32_Ehdr))!=sizeof(Elf32_Ehdr))){
        printf("Elf header not found!\n");
        exit(1);
    }

    if(lseek(fd,ehdr->e_phoff,SEEK_SET)<0){
        printf("Failed to move pointer");
        exit(1);
    }

    int phsize=ehdr->e_phnum*ehdr->e_phentsize;

    phdr=malloc(phsize);
    if(read(fd, phdr, phsize)!=phsize){
        printf("Program header table not found!\n");
        exit(1);
    }

    for(int i=0;i<ehdr->e_phnum;i++){
        if(phdr[i].p_type == PT_LOAD){
            void* virtual_mem=mmap((void*)phdr[i].p_vaddr, phdr[i].p_memsz, PROT_READ | PROT_WRITE | PROT_EXEC,MAP_ANONYMOUS | MAP_PRIVATE | MAP_FIXED,-1,0);
            
            if(virtual_mem==MAP_FAILED){
                printf("mmap Failed");
                close(fd);
                exit(1);
            }

            lseek(fd,phdr[i].p_offset,SEEK_SET);
            read(fd,virtual_mem,phdr[i].p_filesz);
        }
        
    }
   
    int (*_start)() = (void*)(ehdr->e_entry);//typecasting
    int result = _start();
    printf("User _start return value = %d\n",result);
}
