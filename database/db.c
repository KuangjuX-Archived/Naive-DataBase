#include<stdbool.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

typedef struct {
    char* buffer;
    size_t buffer_length;
    ssize_t input_length;
}InputBuffer;

ssize_t getline(char **lineptr, size_t *n, FILE* stream);
/**
 * lineptr : a pointer to the variable we use to point to the buffer containing the read line. If it set to NULL it is mallocatted by getline and should thus be freed by the user, even if the command fails.
 * n : a pointer to the variable we use to save the size of allocated buffer.
 * stream : the input stream to read from. We’ll be reading from standard input.
 * return value : the number of bytes read, which may be less than the size of the buffer.
 * We tell getline to store the read line in input_buffer->buffer and the size of the allocated buffer in input_buffer->buffer_length. We store the return value in input_buffer->input_length.
 * buffer starts as null, so getline allocates enough memory to hold the line of input and makes buffer point to it.
**/
InputBuffer* new_input_buffer() {
    InputBuffer* input_buffer = (InputBuffer*)(malloc)(sizeof(InputBuffer));
    input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_length = 0;

    return input_buffer;
}

void read_input(InputBuffer* input_buffer){
    ssize_t bytes_read = getline(&(input_buffer),&(input_buffer->buffer_length),stdin);
    if(bytes_read <= 0){
        printf("Error reading input\n");
        exit(EXIT_FAILURE);
    }

    //Ignore trailing newline
    input_buffer->input_length = bytes_read-1;
    input_buffer->buffer[bytes_read-1] = 0;
}

void close_input_buffer(InputBuffer* input_buffer){
    free(input_buffer->buffer);
    free(input_buffer);
}

void print_prompt(){
    printf("db > ");
}
int main(int argc, char* argv[]){
    InputBuffer* input_buffer = new_input_buffer();
    //loop
    while(true){
        print_prompt();
        read_input(input_buffer);

        if(strcmp(input_buffer->buffer ,".exit") == 0){
        //     close_input_buffer(input_buffer);
        //     exit(EXIT_SUCCESS);
        // }else{
        //     printf("Unrecognized command '%s' .\n",input_buffer->buffer);
        // }

        if(input_buffer->buffer[0] == '.'){
            switch (do_meta_command(input_buffer)){
                case (META_COMMAND_SUCCESS):
                    continue;
                case (META_COMMAND_UNRECONGNIZED_COMMAND):
                    printf("Unrecognized command '%s'\n", input_buffer->buffer);
                    continue;    
            }
        }

        Statement statement;
        switch(prepare_statement(input_buffer,&statement)){
            case (PREPARE_SUCCESS):
                break;
            case (PREPARE_UNRECOGNIZED_STATEMENT):
                printf("Unrecognized keyword at start of '%s'.\n",input_buffer->buffer);
                continue;
        }

        execute_statement(&statement);
        printf("Executed.\n");
        
    }
}