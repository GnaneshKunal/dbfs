#ifndef DB_H
#define DB_H

#include "utils.h"
#include <fcntl.h>              /* open */
#include <unistd.h>             /* lseek */
#include <errno.h>

typedef struct {
  char *buffer;
  size_t buffer_length;
  ssize_t input_length;
} InputBuffer;

InputBuffer *new_input_buffer();
void read_input(InputBuffer *input_buffer);
void close_input_buffer(InputBuffer *input_buffer);

typedef enum {
  EXECUTE_SUCCESS,
  EXECUTE_DUPLICATE_KEY,
  EXECUTE_TABLE_FULL,
} ExecuteResult;

typedef enum {
  META_COMMAND_SUCCESS,
  META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;

typedef enum {
  PREPARE_SUCCESS,
  PREPARE_NEGATIVE_ID,
  PREPARE_STRING_TOO_LONG,
  PREPARE_SYNTAX_ERROR,
  PREPARE_UNRECOGNIZED_STATEMENT,
} PrepareResult;

typedef enum {
  STATEMENT_INSERT,
  STATEMENT_SELECT
} StatementType;

#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255

typedef struct {
  uint32_t id;
  char username[COLUMN_USERNAME_SIZE + 1];
  char email[COLUMN_EMAIL_SIZE + 1];
} Row;

typedef struct {
  StatementType type;
  Row row_to_insert;            /* only used by insert statement */
} Statement;

#define size_of_attribute(Struct, Attribute) sizeof(((Struct*)0)->Attribute)

#define TABLE_MAX_PAGES 100

typedef struct {
  int file_descriptor;
  uint32_t file_length;
  uint32_t num_pages;
  void *pages[TABLE_MAX_PAGES];
} Pager;

typedef struct {
  uint32_t root_page_num;
  Pager *pager;
} Table;

MetaCommandResult do_meta_command(InputBuffer *input_buffer, Table *table);
PrepareResult prepare_insert_old(InputBuffer *input_buffer, Statement *statement);
PrepareResult prepare_insert(InputBuffer *input_buffer, Statement *statement);
PrepareResult prepare_statement(InputBuffer *input_buffer, Statement *statement);
ExecuteResult execute_statement(Statement *statement, Table *table);
ExecuteResult execute_select(Statement *statement, Table *table);
ExecuteResult execute_insert(Statement *statement, Table *table);

void print_row(Row *row);
void serialize_row(Row *source, void *destination);
void deserialize_row(void *source, Row *destination);
void *get_page(Pager *pager, uint32_t page_num);

Pager *pager_open(const char *filename);
void pager_flush(Pager *pager, uint32_t page_num);
Table *db_open(const char *filename);
void db_close(Table *table);

typedef struct {
  Table *table;
  uint32_t page_num;
  uint32_t cell_num;
  bool end_of_table;            /* Indicates a position one past the last element */
} Cursor;

Cursor *table_start(Table *table);
Cursor *table_find(Table *table, uint32_t key);
void* cursor_value(Cursor *cursor);
void cursor_advance(Cursor *cursor);

typedef enum { NODE_INTERNAL, NODE_LEAF } NodeType;

void leaf_node_insert(Cursor *cursor, uint32_t key, Row *value);
Cursor *leaf_node_find(Table *table, uint32_t page_num, uint32_t key);
NodeType get_node_type(void *node);
void set_node_type(void *node, NodeType type);
void print_constants(void);
void print_leaf_node(void *node);

#endif

