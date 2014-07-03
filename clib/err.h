/*
 * Copyright (c) International Business Machines Corp., 2014
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

/*!
 * @file err.h
 * @brief CLib error container
 * @details Error is a special container that contains a library error
 * @details For example,
 * @code
 * #include <clib/error.h>
 * #include <clib/vector.h>
 * #include <clib/vector_iter.h>
 *
 *  	FIX ME
 *
 * }
 * @endcode
 * @author Shaun Wetzstein <shaun@us.ibm.com>
 * @date 2013
 */

#ifndef __ERR_H__
#define __ERR_H__

#include <sys/cdefs.h>

#include <stdlib.h>
#include <string.h>

#include "nargs.h"
#include "list.h"

/* ======================================================================= */

#define ERR_NONE			0
#define ERR_ERRNO			1
#define ERR_UNEXPECTED			2
#define ERR_VERSION			3
#define ERR_LAST			4

#define ERR_MAGIC			0x45525220	// "ERR "
#define ERR_DATA_SIZE			1000

#define INIT_ERR			{ERR_MAGIC, 0, 0, NULL, 0, {0,}, 0}

#define ERROR(t,c,f, ...)		({				\
  err_t * _e = (err_t  *)malloc(sizeof(*_e) + ERR_DATA_SIZE);		\
  memset(_e, 0, sizeof(*_e) + ERR_DATA_SIZE);				\
  _e->size = snprintf(_e->data, ERR_DATA_SIZE, (f), ##__VA_ARGS__);	\
  _e->magic = ERR_MAGIC, _e->type = (t), _e->code = (c);		\
  _e->file = __FILE__, _e->line = __LINE__; 				\
  err_put(_e);								\
					})

#define ERRNO(e)							\
  ERROR(ERR_ERRNO, (e), "%s => %s (errno=%d)", __func__, strerror(e), e)

#define UNEXPECTED(f, ...)						\
  ERROR(ERR_UNEXPECTED, -1, (f),  ##__VA_ARGS__)

#define VERSION(v,f, ...)						\
  ERROR(ERR_VERSION, v, (f),  ##__VA_ARGS__)

/*!
 * @brief error container
 */
struct err {			//!< The error class
	unsigned long magic;	//!< Error magic number
	list_node_t node;	//!@ private

	int type, code;		//!< Error type & code
	const char *file;	//!< Error source file name
	int line;		//!< Error source line number

	int size;		//!< Extended error data size
	char data[];		//!< Extended error data
};
typedef struct err err_t;	//!< Alias for the @em error class

/* ======================================================================= */

extern void err_delete(err_t *)
/*! @cond */
__nonnull((1)) /*! @endcond */ ;

/*!
 * @brief Return the last library error
 * @details For example,
 * @code
 * ...
 * err_clear(err_get());
 * ...
 * @endcode
 * @memberof error
 * @param self [in] error object @em self pointer
 * @return None
 */
extern err_t *err_get(void);

/*!
 * @brief Set the last library error
 * @details For example,
 * @code
 * ...
 * err_out(&e);
 * ...
 * @endcode
 * @memberof error
 * @param self [in] error object @em self pointer
 * @return None
 */
extern void err_put(err_t *);

/*!
 * @fn int err_type(err_t *self, [ int type ])
 * @brief Set or get the type from an @em error
 * @details For example,
 * @code
 * ...
 * err_type(&e, MY_ERROR_TYPE);
 * if (err_type(&e) == MY_ERROR_TYPE)
 * ...
 * @endcode
 * @memberof error
 * @param self [in] error object @em self pointer
 * @param type [in] error type
 * @return current error type
 */
/*! @cond */
#define err_type(...) STRCAT(err_type, NARGS(__VA_ARGS__))(__VA_ARGS__)
extern int err_type1(err_t *)
/*! @cond */
__nonnull((1)) /*! @endcond */ ;
extern void err_type2(err_t *, int)
/*! @cond */
__nonnull((1)) /*! @endcond */ ;
/*! @endcond */

/*!
 * @fn int err_code(err_t *self, [ int code ])
 * @brief Set or get the code from an @em error
 * @details For example,
 * @code
 * ...
 * err_code(&e, errno);
 * if (err_code(&e) == EINVAL)
 * ...
 * @endcode
 * @memberof error
 * @param self [in] error object @em self pointer
 * @param code [in] error code
 * @return current error code
 */
/*! @cond */
#define err_code(...) STRCAT(err_code, NARGS(__VA_ARGS__))(__VA_ARGS__)
extern int err_code1(err_t *)
/*! @cond */
__nonnull((1)) /*! @endcond */ ;
extern void err_code2(err_t *, int)
/*! @cond */
__nonnull((1)) /*! @endcond */ ;
/*! @endcond */

/*!
 * @fn int err_file(err_t *self, [ const char * file ])
 * @brief Set or get the file name from an @em error
 * @details For example,
 * @code
 * ...
 * err_file(&e, "example.txt");
 * if (strcmp(err_file(&e), "example.txt") == 0)
 * ...
 * @endcode
 * @memberof error
 * @param self [in] error object @em self pointer
 * @param file [in] error file name
 * @return current file name
 */
/*! @cond */
#define err_file(...) STRCAT(err_file, NARGS(__VA_ARGS__))(__VA_ARGS__)
extern const char *err_file1(err_t *)
/*! @cond */
__nonnull((1)) /*! @endcond */ ;
extern void err_file2(err_t *, const char *)
/*! @cond */
__nonnull((1)) /*! @endcond */ ;
/*! @endcond */

/*!
 * @fn int err_line(err_t *self, [ int line ])
 * @brief Set or get the line number from an @em error
 * @details For example,
 * @code
 * ...
 * err_line(&e, errno);
 * if (err_line(&e) == EINVAL)
 * ...
 * @endcode
 * @memberof error
 * @param self [in] error object @em self pointer
 * @param line [in] error line
 * @return current error line
 */
/*! @cond */
#define err_line(...) STRCAT(err_line, NARGS(__VA_ARGS__))(__VA_ARGS__)
extern int err_line1(err_t *)
/*! @cond */
__nonnull((1)) /*! @endcond */ ;
extern void err_line2(err_t *, int)
/*! @cond */
__nonnull((1)) /*! @endcond */ ;
/*! @endcond */

/*!
 * @fn int err_data(err_t *self, [ const void *data ])
 * @brief Set or get the extended data from an @em error
 * @details For example,
 * @code
 * ...
 * err_data(&e, extended_data);
 * memcpy(err_log, err_data(&e), err_size(&e));
 * ...
 * @endcode
 * @memberof error
 * @param self [in] error object @em self pointer
 * @param data [in] error extended data
 * @return current error extended data
 */
/*! @cond */
#define err_data(...) STRCAT(err_data, NARGS(__VA_ARGS__))(__VA_ARGS__)
extern const void *err_data1(err_t *)
/*! @cond */
__nonnull((1)) /*! @endcond */ ;
extern void err_data2(err_t *, int, const void *)
/*! @cond */
__nonnull((1)) /*! @endcond */ ;
/*! @endcond */

/*!
 * @brief Get the data size from an @em error
 * @details For example,
 * @code
 * ...
 * err_size(&e, data_size);
 * if (err_size(&e) <= 0)
 * ...
 * @endcode
 * @memberof error
 * @param self [in] error object @em self pointer
 * @return current error data size
 */
extern int err_size(err_t *)
/*! @cond */
__nonnull((1)) /*! @endcond */ ;

/*!
 * @brief Get the type name from an @em error
 * @details For example,
 * @code
 * ...
 * if (strcmp(err_name(&e), "errno") == 0)
 * ...
 * @endcode
 * @memberof error
 * @param self [in] error object @em self pointer
 * @return current error data size
 */
/*! @cond */
extern const char *err_type_name(err_t *)
/*! @cond */
__nonnull((1)) /*! @endcond */ ;

/* ======================================================================= */

#endif				/* __ERR_H__ */
