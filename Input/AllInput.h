#ifndef ALL_INPUT_H_
#define ALL_INPUT_H_

#include "ConstantsAndStructs.h"

//---------------------------------------------------------------------------
//! @brief Reads the contents of a file into a buffer.
//!
//! This function allocates memory for a buffer, reads the contents of the 
//! file into it, and ensures that the buffer
//! is null-terminated and ends with a newline character.
//!
//! @param[in] filename The name of the file to read (must not be NULL).
//! @param[in] file     An open file pointer for reading (must not be NULL).
//! @param[in] filesize The size of the file in bytes.
//!
//! @return A pointer to the allocated buffer containing the file contents.
//!        The caller is responsible for freeing this buffer.
//--------------------------------------------------------------------------
char *read_to_buf(const char *filename, FILE *file, size_t filesize);

//---------------------------------------------------------------------------
//! @brief Parses the buffer of a FileInfo structure into individual lines.
//!
//! This function scans through the buffer, splits it into 
//! lines, skips blank lines and lines without alphabetic characters, and 
//! fills the array with information about each valid line 
//! (start, end, alpha pointers, size).
//!
//! @param[out] file_info Pointer to a FileInfo structure.
//!
//! @note The number of valid lines written may be less than
//!       the initially allocated size based on filtering criteries.
//---------------------------------------------------------------------------
void parse_buf(struct FileInfo *file_info);

//---------------------------------------------------------------------------
//! @brief Reads the contents of a file into a FileInfo structure.
//!
//! This function opens the given file, reads its contents into a buffer,
//! counts the number of lines, allocates memory for line information, and 
//! calls parse_buf() to populate it.
//!
//! @param[in]  filename  The name of the file to open.
//! @param[out] file_info Pointer to a FileInfo structure that will be 
//!                       filled with buffer and line information.
//!
//! @return PossibleErrors::kErrorOpening if the file cannot be opened,
//!         or the result of close_file() otherwise.
//---------------------------------------------------------------------------
PossibleErrors handle_buf_read(const char *filename, FileInfo *file_info);


#endif //ALL_INPUT_H_