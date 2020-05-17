#ifndef ERRORS_H
#define ERRORS_H

#define SUCCESS 1

#define ERROR_ALLOC_POINT 5
#define ERROR_ALLOC_MODEL_PROJ 7
#define ERROR_ALLOC_MODEL 8
#define ERROR_ALLOC_POINTS_ARRAY 14
#define ERROR_ALLOC_LINKS_MATRIX 15

#define ERROR_FILE_OPEN 16
#define ERROR_FILE_DATA 17
#define ERROR_SEARCH_NONEXISTENT_COORD 18

#define CHECK_CODE_EXIT(cur_code, check_code) ( if (cur_code == check_code) { return 1; } else { return 0; } )

#endif // ERRORS_H
