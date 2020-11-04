#ifndef DB_H
#define DB_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <errno.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

//define data 
#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255
typedef struct{
    uint32_t id;
    char username[COLUMN_USERNAME_SIZE + 1];
    char email[COLUMN_EMAIL_SIZE + 1];
} Row;

//define the compact representation of a row
#define SIZE_OF_ATTRIBUTE(Struct, Attribute) (sizeof(((Struct*)0)->Attribute))
#define ID_SIZE SIZE_OF_ATTRIBUTE(Row,id)

#define USERNAME_SIZE SIZE_OF_ATTRIBUTE(Row,username)
#define EMAIL_SIZE SIZE_OF_ATTRIBUTE(Row,email)
#define ID_OFFSET 0
#define USERNAME_OFFSET (ID_OFFSET + ID_SIZE)
#define EMAIL_OFFSET (USERNAME_OFFSET + USERNAME_SIZE)
#define ROW_SIZE (ID_SIZE + USERNAME_SIZE + EMAIL_SIZE)

typedef struct {
    char* buffer;
    size_t buffer_length;
    ssize_t input_length;
}InputBuffer;




//define table structure
#define PAGE_SIZE 4096
#define TABLE_MAX_PAGES 100
#define ROWS_PER_PAGE (PAGE_SIZE / ROW_SIZE)
#define TABLE_MAX_ROWS (ROWS_PER_PAGE * TABLE_MAX_PAGES)

//define pager for disk
typedef struct{
    int file_descriptor;
    uint32_t file_length;
    void* pages[TABLE_MAX_PAGES];
}Pager;

typedef struct{
    uint32_t num_rows;
    Pager* pager;
}Table;


typedef enum{
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
}MetaCommandResult;

typedef enum{
    EXECUTE_SUCCESS,
    EXECUTE_TABLE_FULL
}ExecuteResult;


typedef enum{
    PREPARE_SUCCESS,
    PREPARE_NEGATIVE_ID,
    PREPARE_STRING_TOO_LONG,
    PREPARE_SYNTAX_ERROR,
    PREPARE_UNRECOGNIZED_STATEMENT
} PrepareResult;

typedef enum {
    STATEMENT_INSERT,
    STATEMENT_SELECT
} StatementType;

typedef struct {
    StatementType type;
    //add Row
    Row row_to_insert;
}Statement;

InputBuffer* new_input_buffer();

void read_input(InputBuffer* input_buffer);

void close_input_buffer(InputBuffer* input_buffer);

void print_prompt();

void print_row(Row* row);

MetaCommandResult do_meta_command(InputBuffer* input_buffer);

PrepareResult prepare_insert(InputBuffer* input_buffer, Statement* statement);

PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement);

Table* db_open(const char* filename);

Pager* pager_open(const char* filename);

void* get_page(Pager* pager, uint32_t page_num);

void* row_slot(Table* table, uint32_t row_num);

ExecuteResult execute_insert(Statement* statement, Table* table);

ExecuteResult execute_select(Statement* statement, Table* table);

ExecuteResult execute_statement(Statement* statement, Table* table);

void serialize_row(Row* source, void* destination);

void deserialize_row(void* source, Row* destination);

#endif