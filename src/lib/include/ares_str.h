/* MIT License
 *
 * Copyright (c) 1998 Massachusetts Institute of Technology
 * Copyright (c) The c-ares project and its contributors
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * SPDX-License-Identifier: MIT
 */
#ifndef __ARES_STR_H
#define __ARES_STR_H

CARES_EXTERN char  *ares_strdup(const char *s1);

CARES_EXTERN size_t ares_strlen(const char *str);

/*! Copy string from source to destination with destination buffer size
 *  provided.  The destination is guaranteed to be null terminated, if the
 *  provided buffer isn't large enough, only those bytes from the source that
 *  will fit will be copied.
 *
 *  \param[out] dest       Destination buffer
 *  \param[in]  src        Source to copy
 *  \param[in]  dest_size  Size of destination buffer
 *  \return String length.  Will be at most dest_size-1
 */
CARES_EXTERN size_t ares_strcpy(char *dest, const char *src, size_t dest_size);

CARES_EXTERN ares_bool_t   ares_str_isnum(const char *str);

CARES_EXTERN void          ares__str_ltrim(char *str);
CARES_EXTERN void          ares__str_rtrim(char *str);
CARES_EXTERN void          ares__str_trim(char *str);

CARES_EXTERN unsigned char ares__tolower(unsigned char c);
CARES_EXTERN ares_bool_t   ares__memeq_ci(const unsigned char *ptr,
                                          const unsigned char *val, size_t len);
CARES_EXTERN ares_bool_t   ares__is_hostname(const char *str);

/*! Validate the string provided is printable.  The length specified must be
 *  at least the size of the buffer provided.  If a NULL-terminator is hit
 *  before the length provided is hit, this will not be considered a valid
 *  printable string.  This does not validate that the string is actually
 *  NULL terminated.
 *
 *  \param[in] str  Buffer containing string to evaluate.
 *  \param[in] len  Number of characters to evaluate within provided buffer.
 *                  If 0, will return TRUE since it did not hit an exception.
 *  \return ARES_TRUE if the entire string is printable, ARES_FALSE if not.
 */
CARES_EXTERN ares_bool_t   ares__str_isprint(const char *str, size_t len);

/* We only care about ASCII rules */
#define ares__isascii(x) (((unsigned char)x) <= 127)

#define ares__isdigit(x) \
  (((unsigned char)x) >= '0' && ((unsigned char)x) <= '9')

#define ares__isxdigit(x)                                      \
  (ares__isdigit(x) ||                                         \
   (((unsigned char)x) >= 'a' && ((unsigned char)x) <= 'f') || \
   (((unsigned char)x) >= 'A' && ((unsigned char)x) <= 'F'))

#define ares__isupper(x) \
  (((unsigned char)x) >= 'A' && ((unsigned char)x) <= 'Z')

#define ares__islower(x) \
  (((unsigned char)x) >= 'a' && ((unsigned char)x) <= 'z')

#define ares__isalpha(x) (ares__islower(x) || ares__isupper(x))

#define ares__isspace(x) (((unsigned char)(x)) == '\r' || \
                          ((unsigned char)(x)) == '\t' || \
                          ((unsigned char)(x)) == ' '  || \
                          ((unsigned char)(x)) == '\v' || \
                          ((unsigned char)(x)) == '\f' || \
                          ((unsigned char)(x)) == '\n')

#define ares__isprint(x) (((unsigned char)(x)) >= 0x20 && \
                          ((unsigned char)(x)) <= 0x7E)

/* Character set allowed by hostnames.  This is to include the normal
 * domain name character set plus:
 *  - underscores which are used in SRV records.
 *  - Forward slashes such as are used for classless in-addr.arpa
 *    delegation (CNAMEs)
 *  - Asterisks may be used for wildcard domains in CNAMEs as seen in the
 *    real world.
 * While RFC 2181 section 11 does state not to do validation,
 * that applies to servers, not clients.  Vulnerabilities have been
 * reported when this validation is not performed.  Security is more
 * important than edge-case compatibility (which is probably invalid
 * anyhow).
 * [A-Za-z0-9-*._/]
 */
#define ares__is_hostnamech(x) (ares__isalpha(x) || ares__isdigit(x) || \
                                ((unsigned char)(x)) == '-' || \
                                ((unsigned char)(x)) == '.' || \
                                ((unsigned char)(x)) == '_' || \
                                ((unsigned char)(x)) == '/' || \
                                ((unsigned char)(x)) == '*')


/*! Compare two strings (for sorting)
 *
 *  Treats NULL and "" strings as equivalent
 *
 *  \param[in] a First String
 *  \param[in] b Second String
 *  \return < 0 if First String less than Second String,
 *            0 if First String equal to Second String,
 *          > 0 if First String greater than Second String
 */
CARES_EXTERN int ares_strcmp(const char *a, const char *b);

/*! Compare two strings up to specified length (for sorting)
 *
 *  Treats NULL and "" strings as equivalent
 *
 *  \param[in] a First String
 *  \param[in] b Second String
 *  \param[in] n Length
 *  \return < 0 if First String less than Second String,
 *            0 if First String equal to Second String,
 *          > 0 if First String greater than Second String
 */
CARES_EXTERN int ares_strncmp(const char *a, const char *b, size_t n);


/*! Compare two strings in a case-insensitive manner (for sorting)
 *
 *  Treats NULL and "" strings as equivalent
 *
 *  \param[in] a First String
 *  \param[in] b Second String
 *  \return < 0 if First String less than Second String,
 *            0 if First String equal to Second String,
 *          > 0 if First String greater than Second String
 */
CARES_EXTERN int ares_strcasecmp(const char *a, const char *b);

/*! Compare two strings in a case-insensitive manner up to specified length
 *  (for sorting)
 *
 *  Treats NULL and "" strings as equivalent
 *
 *  \param[in] a First String
 *  \param[in] b Second String
 *  \param[in] n Length
 *  \return < 0 if First String less than Second String,
 *            0 if First String equal to Second String,
 *          > 0 if First String greater than Second String
 */
CARES_EXTERN int ares_strncasecmp(const char *a, const char *b, size_t n);

/*! Compare two strings for equality
 *
 *  Treats NULL and "" strings as equivalent
 *
 *  \param[in] a First String
 *  \param[in] b Second String
 *  \return ARES_TRUE on match, or ARES_FALSE if no match
 */
CARES_EXTERN ares_bool_t ares_streq(const char *a, const char *b);

/*! Compare two strings for equality up to specified length
 *
 *  Treats NULL and "" strings as equivalent
 *
 *  \param[in] a First String
 *  \param[in] b Second String
 *  \param[in] n Length
 *  \return ARES_TRUE on match, or ARES_FALSE if no match
 */
CARES_EXTERN ares_bool_t ares_streq_max(const char *a, const char *b, size_t n);

/*! Compare two strings for equality in a case insensitive manner
 *
 *  Treats NULL and "" strings as equivalent
 *
 *  \param[in] a First String
 *  \param[in] b Second String
 *  \return ARES_TRUE on match, or ARES_FALSE if no match
 */
CARES_EXTERN ares_bool_t ares_strcaseeq(const char *a, const char *b);

/*! Compare two strings for equality up to specified length in a case
 *  insensitive manner
 *
 *  Treats NULL and "" strings as equivalent
 *
 *  \param[in] a First String
 *  \param[in] b Second String
 *  \param[in] n Length
 *  \return ARES_TRUE on match, or ARES_FALSE if no match
 */
CARES_EXTERN ares_bool_t ares_strcaseeq_max(const char *a, const char *b,
                                            size_t n);

#endif /* __ARES_STR_H */