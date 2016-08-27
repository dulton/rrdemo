/* ************************************************************************//*!
 * \file
 * \author zhengrr
 * \date 2016-8-17
 * \copyright The MIT License
 ******************************************************************************/
#ifndef LANGC_ATOM_H
#define LANGC_ATOM_H

extern const char *langc_atom_new(const char *str, int len);
extern const char *langc_atom_string(const char *str);
extern const char *langc_atom_int(long n);
extern       int   langc_atom_length(const char *str);

#endif  /* LANGC_ATOM_H */
