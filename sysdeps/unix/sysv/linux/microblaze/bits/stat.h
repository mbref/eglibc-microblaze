/* The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */

#if !defined _SYS_STAT_H && !defined _FCNTL_H
# error "Never include <bits/stat.h> directly; use <sys/stat.h> instead."
#endif

#ifndef _BITS_STAT_H
#define _BITS_STAT_H	1

/* Versions of the `struct stat' data structure.  */
#define _STAT_VER_LINUX_OLD	1
#define _STAT_VER_KERNEL	1
#define _STAT_VER_SVR4		2
#define _STAT_VER_LINUX		3
#define _STAT_VER		_STAT_VER_LINUX	/* The one defined below.  */

/* Versions of the `xmknod' interface.  */
#define _MKNOD_VER_LINUX	1
#define _MKNOD_VER_SVR4		2
#define _MKNOD_VER		_MKNOD_VER_LINUX /* The bits defined below.  */

#ifndef __USE_FILE_OFFSET64
struct stat
{
        __dev_t         st_dev; /* Device. */
        __ino_t         st_ino; /* File serial number. */
        __mode_t        st_mode; /* File mode. */
        __nlink_t       st_nlink; /* Link count. */
        __uid_t         st_uid; /* User ID of the file's owner. */
        __gid_t         st_gid; /* Group ID of the file's group. */
        __dev_t         st_rdev; /* Device number, if device. */
        unsigned long   __pad2;
        __off_t         st_size; /* Size of file, in bytes. */
        __blksize_t     st_blksize; /* Optimal block size for I/O. */
        int             __pad3;
        __blkcnt_t      st_blocks; /* Number 512-byte blocks allocated. */
#ifdef __USE_MISC
        /* Nanosecond resolution timestamps are stored in a format
         * equivalent to 'struct timespec'. This is the type used
         * whenever possible but the Unix namespace rules do not allow the
         * identifier 'timespec' to appear in the <sys/stat.h> header.
         * Therefore we have to handle the use of this header in strictly
         * standard-compliant sources special. */
        struct timespec         st_atim; /* Time of last access. */
        struct timespec         st_mtim; /* Time of last modification. */
        struct timespec         st_ctim; /* Time of last status change. */
# define st_atime st_atim.tv_sec        /* Backward compatibility. */
# define st_mtime st_mtim.tv_sec
# define st_ctime st_ctim.tv_sec
#else
        __time_t                st_atime; /* Time of last access. */
        unsigned long int       st_atimensec; /* Nscecs of last access. */
        __time_t                st_mtime; /* Time of last modification. */
        unsigned long int       st_mtimensec; /* Nsecs of last modification. */
        __time_t                st_ctime; /* Time of last status change. */
        unsigned long int       st_ctimensec; /* Nsecs of last status change. */
#endif
        unsigned int    __unused4;
        unsigned int    __unused5;
};
#else /* __USE_FILE_OFFSET64 */
/* MS: If __USE_FILE_OFFSET64 is setup then struct stat should match stat64
 * structure. Glibc has no type __dev64_t that's why I had to use standard
 * type for st_dev and st_rdev. Several architectures uses pads after st_dev
 * but this approach covers BIG and LITTLE endian. I think it is better to
 * create one ifdef to separate stats structures. */
struct stat
{
        unsigned long long      st_dev; /* Device. */
        __ino64_t               st_ino; /* 32bit file serial number. */
        __mode_t                st_mode; /* File mode. */
        __nlink_t               st_nlink; /* Link count. */
        __uid_t                 st_uid; /* User ID of the file's owner. */
        __gid_t                 st_gid; /* Group ID of the file's group. */
        unsigned long long      st_rdev; /* Device number, if device. */
        unsigned long long      __pad2;
        __off64_t               st_size; /* Size of file, in bytes. */
        __blksize_t             st_blksize; /* Optimal block size for I/O. */
        int                     __pad3;
        __blkcnt64_t            st_blocks; /* Number 512-byte blocks allocated. */
#ifdef __USE_MISC
        /* Nanosecond resolution timestamps are stored in a format
         * equivalent to 'struct timespec'. This is the type used
         * whenever possible but the Unix namespace rules do not allow the
         * identifier 'timespec' to appear in the <sys/stat.h> header.
         * Therefore we have to handle the use of this header in strictly
         * standard-compliant sources special. */
        struct timespec         st_atim; /* Time of last access. */
        struct timespec         st_mtim; /* Time of last modification. */
        struct timespec         st_ctim; /* Time of last status change. */
# define st_atime st_atim.tv_sec        /* Backward compatibility. */
# define st_mtime st_mtim.tv_sec
# define st_ctime st_ctim.tv_sec
#else
        __time_t                st_atime; /* Time of last access. */
        unsigned long int       st_atimensec; /* Nscecs of last access. */
        __time_t                st_mtime; /* Time of last modification. */
        unsigned long int       st_mtimensec; /* Nsecs of last modification. */
        __time_t                st_ctime; /* Time of last status change. */
        unsigned long int       st_ctimensec; /* Nsecs of last status change. */
#endif
        unsigned int    __unused4;
        unsigned int    __unused5;
};
#endif /* __USE_FILE_OFFSET64 */

#ifdef __USE_LARGEFILE64
struct stat64
{
        unsigned long long      st_dev; /* Device. */
        __ino64_t               st_ino; /* 32bit file serial number. */
        __mode_t                st_mode; /* File mode. */
        __nlink_t               st_nlink; /* Link count. */
        __uid_t                 st_uid; /* User ID of the file's owner. */
        __gid_t                 st_gid; /* Group ID of the file's group. */
        unsigned long long      st_rdev; /* Device number, if device. */
        unsigned long long      __pad2;
        __off64_t               st_size; /* Size of file, in bytes. */
        __blksize_t             st_blksize; /* Optimal block size for I/O. */
        int                     __pad3;
        __blkcnt64_t            st_blocks; /* Number 512-byte blocks allocated. */
#ifdef __USE_MISC
        /* Nanosecond resolution timestamps are stored in a format
         * equivalent to 'struct timespec'. This is the type used
         * whenever possible but the Unix namespace rules do not allow the
         * identifier 'timespec' to appear in the <sys/stat.h> header.
         * Therefore we have to handle the use of this header in strictly
         * standard-compliant sources special. */
        struct timespec         st_atim; /* Time of last access. */
        struct timespec         st_mtim; /* Time of last modification. */
        struct timespec         st_ctim; /* Time of last status change. */
# define st_atime st_atim.tv_sec        /* Backward compatibility. */
# define st_mtime st_mtim.tv_sec
# define st_ctime st_ctim.tv_sec
#else
        __time_t                st_atime; /* Time of last access. */
        unsigned long int       st_atimensec; /* Nscecs of last access. */
        __time_t                st_mtime; /* Time of last modification. */
        unsigned long int       st_mtimensec; /* Nsecs of last modification. */
        __time_t                st_ctime; /* Time of last status change. */
        unsigned long int       st_ctimensec; /* Nsecs of last status change. */
#endif
        unsigned int    __unused4;
        unsigned int    __unused5;
};
#endif

/* Tell code we have these members.  */
#define _STATBUF_ST_BLKSIZE
#define _STATBUF_ST_RDEV
/* Nanosecond resolution time values are supported.  */
#define _STATBUF_ST_NSEC

/* Encoding of the file mode.  */

#define __S_IFMT        0170000 /* These bits determine file type.  */

/* File types.  */
#define __S_IFDIR       0040000 /* Directory.  */
#define __S_IFCHR       0020000 /* Character device.  */
#define __S_IFBLK       0060000 /* Block device.  */
#define __S_IFREG       0100000 /* Regular file.  */
#define __S_IFIFO       0010000 /* FIFO.  */
#define __S_IFLNK       0120000 /* Symbolic link.  */
#define __S_IFSOCK      0140000 /* Socket.  */

/* POSIX.1b objects.  Note that these macros always evaluate to zero.  But
   they do it by enforcing the correct use of the macros.  */
#define __S_TYPEISMQ(buf)  ((buf)->st_mode - (buf)->st_mode)
#define __S_TYPEISSEM(buf) ((buf)->st_mode - (buf)->st_mode)
#define __S_TYPEISSHM(buf) ((buf)->st_mode - (buf)->st_mode)

/* Protection bits.  */

#define __S_ISUID       04000   /* Set user ID on execution.  */
#define __S_ISGID       02000   /* Set group ID on execution.  */
#define __S_ISVTX       01000   /* Save swapped text after use (sticky).  */
#define __S_IREAD       0400    /* Read by owner.  */
#define __S_IWRITE      0200    /* Write by owner.  */
#define __S_IEXEC       0100    /* Execute by owner.  */

#ifdef __USE_ATFILE
# define UTIME_NOW	((1l << 30) - 1l)
# define UTIME_OMIT	((1l << 30) - 2l)
#endif

#endif	/* bits/stat.h */
