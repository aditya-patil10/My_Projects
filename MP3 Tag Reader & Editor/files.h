#ifndef FILES_H
#define FILES_H

//For view:
unsigned int BtoL_endian(unsigned char *size_of_tag);
int validate_view(char *file);
int view_data(char *file);

//For edit
void LtoB_endian(unsigned int size, unsigned char *data);
int validate_edit(char *file);
int edit_data(char *option, char *new_data, char *file);

#endif