/* *INDENT-OFF* */ /* ATTRIBUTE_PRINTF confuses indent, avoid running it
		      for now.  */
/* Basic, host-specific, and target-specific definitions for GDB.
   Copyright (C) 1986, 1988, 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996,
   1997, 1998, 1999, 2000, 2001, 2002, 2003, 2004, 2005, 2007, 2008, 2009,
   2010, 2011 Free Software Foundation, Inc.

   This file is part of GDB.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#ifndef DEFS_H
#define DEFS_H

#ifdef GDBSERVER
#  error gdbserver should not include gdb/defs.h
#endif

#include "config.h"		/* Generated by configure.  */

#include <sys/types.h>
#include <stdio.h>
#include <errno.h>		/* System call error return status.  */
#include <limits.h>
#include <stdint.h>

/* The libdecnumber library, on which GDB depends, includes a header file
   called gstdint.h instead of relying directly on stdint.h.  GDB, on the
   other hand, includes stdint.h directly, relying on the fact that gnulib
   generates a copy if the system doesn't provide one or if it is missing
   some features.  Unfortunately, gstdint.h and stdint.h cannot be included
   at the same time, which may happen when we include a file from
   libdecnumber.

   The following macro definition effectively prevents the inclusion of
   gstdint.h, as all the definitions it provides are guarded against
   the GCC_GENERATED_STDINT_H macro.  We already have gnulib/stdint.h
   included, so it's ok to blank out gstdint.h.  */
#define GCC_GENERATED_STDINT_H 1

#ifdef HAVE_STDDEF_H
#include <stddef.h>
#endif

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#include <fcntl.h>

/* First include ansidecl.h so we can use the various macro definitions
   here and in all subsequent file inclusions.  */

#include "ansidecl.h"

#include "gdb_locale.h"

#include "gdb_wchar.h"

/* For ``enum target_signal''.  */
#include "gdb/signals.h"

/* Just in case they're not defined in stdio.h.  */

#ifndef SEEK_SET
#define SEEK_SET 0
#endif
#ifndef SEEK_CUR
#define SEEK_CUR 1
#endif

/* The O_BINARY flag is defined in fcntl.h on some non-Posix platforms.
   It is used as an access modifier in calls to open(), where it acts
   similarly to the "b" character in fopen()'s MODE argument.  On Posix
   platforms it should be a no-op, so it is defined as 0 here.  This 
   ensures that the symbol may be used freely elsewhere in gdb.  */

#ifndef O_BINARY
#define O_BINARY 0
#endif

#include <stdarg.h>		/* For va_list.  */

#include "libiberty.h"

/* Rather than duplicate all the logic in BFD for figuring out what
   types to use (which can be pretty complicated), symply define them
   in terms of the corresponding type from BFD.  */

#include "bfd.h"

/* A byte from the program being debugged.  */
typedef bfd_byte gdb_byte;

/* An address in the program being debugged.  Host byte order.  */
typedef bfd_vma CORE_ADDR;

/* The largest CORE_ADDR value.  */
#define CORE_ADDR_MAX (~ (CORE_ADDR) 0)

/* This is to make sure that LONGEST is at least as big as CORE_ADDR.  */

#ifndef LONGEST

#ifdef BFD64

#define LONGEST BFD_HOST_64_BIT
#define ULONGEST BFD_HOST_U_64_BIT

#else /* No BFD64 */

#ifdef CC_HAS_LONG_LONG
#define LONGEST long long
#define ULONGEST unsigned long long
#else
#ifdef BFD_HOST_64_BIT
/* BFD_HOST_64_BIT is defined for some hosts that don't have long long
   (e.g. i386-windows) so try it.  */
#define LONGEST BFD_HOST_64_BIT
#define ULONGEST BFD_HOST_U_64_BIT
#else
#define LONGEST long
#define ULONGEST unsigned long
#endif
#endif

#endif /* No BFD64 */

#endif /* ! LONGEST */

#ifndef min
#define min(a, b) ((a) < (b) ? (a) : (b))
#endif
#ifndef max
#define max(a, b) ((a) > (b) ? (a) : (b))
#endif

#include "ptid.h"

/* Check if a character is one of the commonly used C++ marker characters.  */
extern int is_cplus_marker (int);

/* Enable xdb commands if set.  */
extern int xdb_commands;

/* Enable dbx commands if set.  */
extern int dbx_commands;

/* System root path, used to find libraries etc.  */
extern char *gdb_sysroot;

/* GDB datadir, used to store data files.  */
extern char *gdb_datadir;

/* If non-NULL, the possibly relocated path to python's "lib" directory
   specified with --with-python.  */
extern char *python_libdir;

/* Search path for separate debug files.  */
extern char *debug_file_directory;

extern int quit_flag;
extern int immediate_quit;
extern int sevenbit_strings;

extern void quit (void);

/* FIXME: cagney/2000-03-13: It has been suggested that the peformance
   benefits of having a ``QUIT'' macro rather than a function are
   marginal.  If the overhead of a QUIT function call is proving
   significant then its calling frequency should probably be reduced
   [kingdon].  A profile analyzing the current situtation is
   needed.  */

#define QUIT { \
  if (quit_flag) quit (); \
  if (deprecated_interactive_hook) deprecated_interactive_hook (); \
}

/* Languages represented in the symbol table and elsewhere.
   This should probably be in language.h, but since enum's can't
   be forward declared to satisfy opaque references before their
   actual definition, needs to be here.  */

enum language
  {
    language_unknown,		/* Language not known */
    language_auto,		/* Placeholder for automatic setting */
    language_c,			/* C */
    language_cplus,		/* C++ */
    language_d,			/* D */
    language_objc,		/* Objective-C */
    language_java,		/* Java */
    language_fortran,		/* Fortran */
    language_m2,		/* Modula-2 */
    language_asm,		/* Assembly language */
    language_pascal,		/* Pascal */
    language_ada,		/* Ada */
    language_opencl,		/* OpenCL */
    language_minimal,		/* All other languages, minimal support only */
    nr_languages
  };

enum precision_type
  {
    single_precision,
    double_precision,
    unspecified_precision
  };

/* A generic, not quite boolean, enumeration.  */
enum auto_boolean
{
  AUTO_BOOLEAN_TRUE,
  AUTO_BOOLEAN_FALSE,
  AUTO_BOOLEAN_AUTO
};

/* Potential ways that a function can return a value of a given type.  */
enum return_value_convention
{
  /* Where the return value has been squeezed into one or more
     registers.  */
  RETURN_VALUE_REGISTER_CONVENTION,
  /* Commonly known as the "struct return convention".  The caller
     passes an additional hidden first parameter to the caller.  That
     parameter contains the address at which the value being returned
     should be stored.  While typically, and historically, used for
     large structs, this is convention is applied to values of many
     different types.  */
  RETURN_VALUE_STRUCT_CONVENTION,
  /* Like the "struct return convention" above, but where the ABI
     guarantees that the called function stores the address at which
     the value being returned is stored in a well-defined location,
     such as a register or memory slot in the stack frame.  Don't use
     this if the ABI doesn't explicitly guarantees this.  */
  RETURN_VALUE_ABI_RETURNS_ADDRESS,
  /* Like the "struct return convention" above, but where the ABI
     guarantees that the address at which the value being returned is
     stored will be available in a well-defined location, such as a
     register or memory slot in the stack frame.  Don't use this if
     the ABI doesn't explicitly guarantees this.  */
  RETURN_VALUE_ABI_PRESERVES_ADDRESS,
};

/* the cleanup list records things that have to be undone
   if an error happens (descriptors to be closed, memory to be freed, etc.)
   Each link in the chain records a function to call and an
   argument to give it.

   Use make_cleanup to add an element to the cleanup chain.
   Use do_cleanups to do all cleanup actions back to a given
   point in the chain.  Use discard_cleanups to remove cleanups
   from the chain back to a given point, not doing them.

   If the argument is pointer to allocated memory, then you need
   to additionally set the 'free_arg' member to a function that will
   free that memory.  This function will be called both when the cleanup
   is executed and when it's discarded.  */

struct cleanup
  {
    struct cleanup *next;
    void (*function) (void *);
    void (*free_arg) (void *);
    void *arg;
  };

/* vec.h-style vectors of strings want a typedef for char * or const char *.  */

typedef char * char_ptr;
typedef const char * const_char_ptr;

/* Needed for various prototypes */

struct symtab;
struct breakpoint;
struct frame_info;
struct gdbarch;
struct value;

/* From main.c.  */

/* This really belong in utils.c (path-utils.c?), but it references some
   globals that are currently only available to main.c.  */
extern char *relocate_gdb_directory (const char *initial, int flag);

/* From utils.c */

extern void initialize_utils (void);

extern void notice_quit (void);

extern int strcmp_iw (const char *, const char *);

extern int strcmp_iw_ordered (const char *, const char *);

extern int streq (const char *, const char *);

extern int subset_compare (char *, char *);

extern char *safe_strerror (int);

extern void set_display_time (int);

extern void set_display_space (int);

#define	ALL_CLEANUPS	((struct cleanup *)0)

extern void do_cleanups (struct cleanup *);
extern void do_final_cleanups (struct cleanup *);

extern void discard_cleanups (struct cleanup *);
extern void discard_final_cleanups (struct cleanup *);
extern void discard_my_cleanups (struct cleanup **, struct cleanup *);

/* NOTE: cagney/2000-03-04: This typedef is strictly for the
   make_cleanup function declarations below.  Do not use this typedef
   as a cast when passing functions into the make_cleanup() code.
   Instead either use a bounce function or add a wrapper function.
   Calling a f(char*) function with f(void*) is non-portable.  */
typedef void (make_cleanup_ftype) (void *);

extern struct cleanup *make_cleanup (make_cleanup_ftype *, void *);

extern struct cleanup *make_cleanup_dtor (make_cleanup_ftype *, void *,
					  void (*dtor) (void *));

extern struct cleanup *make_cleanup_freeargv (char **);

struct ui_file;
extern struct cleanup *make_cleanup_ui_file_delete (struct ui_file *);

struct ui_out;
extern struct cleanup *
  make_cleanup_ui_out_redirect_pop (struct ui_out *uiout);

struct section_addr_info;
extern struct cleanup *(make_cleanup_free_section_addr_info 
                        (struct section_addr_info *));

extern struct cleanup *make_cleanup_close (int fd);

extern struct cleanup *make_cleanup_fclose (FILE *file);

extern struct cleanup *make_cleanup_bfd_close (bfd *abfd);

struct obstack;
extern struct cleanup *make_cleanup_obstack_free (struct obstack *obstack);

extern struct cleanup *make_cleanup_restore_integer (int *variable);
extern struct cleanup *make_cleanup_restore_uinteger (unsigned int *variable);

struct target_ops;
extern struct cleanup *make_cleanup_unpush_target (struct target_ops *ops);

extern struct cleanup *
  make_cleanup_restore_ui_file (struct ui_file **variable);

extern struct cleanup *make_cleanup_value_free_to_mark (struct value *);
extern struct cleanup *make_cleanup_value_free (struct value *);

extern struct cleanup *make_final_cleanup (make_cleanup_ftype *, void *);

extern struct cleanup *make_my_cleanup (struct cleanup **,
					make_cleanup_ftype *, void *);

extern struct cleanup *make_my_cleanup2 (struct cleanup **,
					 make_cleanup_ftype *, void *,
					 void (*free_arg) (void *));

extern struct cleanup *save_cleanups (void);
extern struct cleanup *save_final_cleanups (void);
extern struct cleanup *save_my_cleanups (struct cleanup **);

extern void restore_cleanups (struct cleanup *);
extern void restore_final_cleanups (struct cleanup *);
extern void restore_my_cleanups (struct cleanup **, struct cleanup *);

extern void free_current_contents (void *);

extern void null_cleanup (void *);

extern struct cleanup *make_command_stats_cleanup (int);

extern int myread (int, char *, int);

extern int query (const char *, ...) ATTRIBUTE_PRINTF (1, 2);
extern int nquery (const char *, ...) ATTRIBUTE_PRINTF (1, 2);
extern int yquery (const char *, ...) ATTRIBUTE_PRINTF (1, 2);

extern void init_page_info (void);

extern struct cleanup *make_cleanup_restore_page_info (void);
extern struct cleanup *
  set_batch_flag_and_make_cleanup_restore_page_info (void);

extern char *gdb_realpath (const char *);
extern char *xfullpath (const char *);

extern unsigned long gnu_debuglink_crc32 (unsigned long crc,
                                          unsigned char *buf, size_t len);

ULONGEST strtoulst (const char *num, const char **trailer, int base);

char *ldirname (const char *filename);

char **gdb_buildargv (const char *);

int compare_positive_ints (const void *ap, const void *bp);

/* A wrapper for bfd_errmsg to produce a more helpful error message
   in the case of bfd_error_file_ambiguously recognized.
   MATCHING, if non-NULL, is the corresponding argument to
   bfd_check_format_matches, and will be freed.  */

extern const char *gdb_bfd_errmsg (bfd_error_type error_tag, char **matching);

extern int parse_pid_to_attach (char *args);

extern struct cleanup *make_bpstat_clear_actions_cleanup (void);

/* From demangle.c */

extern void set_demangling_style (char *);


/* Annotation stuff.  */

extern int annotation_level;	/* in stack.c */

extern void begin_line (void);

extern void wrap_here (char *);

extern void reinitialize_more_filter (void);

/* Normal results */
extern struct ui_file *gdb_stdout;
/* Input stream */
extern struct ui_file *gdb_stdin;
/* Serious error notifications */
extern struct ui_file *gdb_stderr;
/* Log/debug/trace messages that should bypass normal stdout/stderr
   filtering.  For moment, always call this stream using
   *_unfiltered.  In the very near future that restriction shall be
   removed - either call shall be unfiltered.  (cagney 1999-06-13).  */
extern struct ui_file *gdb_stdlog;
/* Target output that should bypass normal stdout/stderr filtering.
   For moment, always call this stream using *_unfiltered.  In the
   very near future that restriction shall be removed - either call
   shall be unfiltered.  (cagney 1999-07-02).  */
extern struct ui_file *gdb_stdtarg;
extern struct ui_file *gdb_stdtargerr;
extern struct ui_file *gdb_stdtargin;

#include "ui-file.h"

/* More generic printf like operations.  Filtered versions may return
   non-locally on error.  */

extern void fputs_filtered (const char *, struct ui_file *);

extern void fputs_unfiltered (const char *, struct ui_file *);

extern int fputc_filtered (int c, struct ui_file *);

extern int fputc_unfiltered (int c, struct ui_file *);

extern int putchar_filtered (int c);

extern int putchar_unfiltered (int c);

extern void puts_filtered (const char *);

extern void puts_unfiltered (const char *);

extern void puts_filtered_tabular (char *string, int width, int right);

extern void puts_debug (char *prefix, char *string, char *suffix);

extern void vprintf_filtered (const char *, va_list) ATTRIBUTE_PRINTF (1, 0);

extern void vfprintf_filtered (struct ui_file *, const char *, va_list)
  ATTRIBUTE_PRINTF (2, 0);

extern void fprintf_filtered (struct ui_file *, const char *, ...)
  ATTRIBUTE_PRINTF (2, 3);

extern void fprintfi_filtered (int, struct ui_file *, const char *, ...)
  ATTRIBUTE_PRINTF (3, 4);

extern void printf_filtered (const char *, ...) ATTRIBUTE_PRINTF (1, 2);

extern void printfi_filtered (int, const char *, ...) ATTRIBUTE_PRINTF (2, 3);

extern void vprintf_unfiltered (const char *, va_list) ATTRIBUTE_PRINTF (1, 0);

extern void vfprintf_unfiltered (struct ui_file *, const char *, va_list)
  ATTRIBUTE_PRINTF (2, 0);

extern void fprintf_unfiltered (struct ui_file *, const char *, ...)
  ATTRIBUTE_PRINTF (2, 3);

extern void printf_unfiltered (const char *, ...) ATTRIBUTE_PRINTF (1, 2);

extern void print_spaces (int, struct ui_file *);

extern void print_spaces_filtered (int, struct ui_file *);

extern char *n_spaces (int);

extern void fputstr_filtered (const char *str, int quotr,
			      struct ui_file * stream);

extern void fputstr_unfiltered (const char *str, int quotr,
				struct ui_file * stream);

extern void fputstrn_filtered (const char *str, int n, int quotr,
			       struct ui_file * stream);

extern void fputstrn_unfiltered (const char *str, int n, int quotr,
				 struct ui_file * stream);

/* Display the host ADDR on STREAM formatted as ``0x%x''.  */
extern void gdb_print_host_address (const void *addr, struct ui_file *stream);

extern const char *host_address_to_string (const void *addr);

/* Convert CORE_ADDR to string in platform-specific manner.
   This is usually formatted similar to 0x%lx.  */
extern const char *paddress (struct gdbarch *gdbarch, CORE_ADDR addr);

/* Return a string representation in hexadecimal notation of ADDRESS,
   which is suitable for printing.  */

extern const char *print_core_address (struct gdbarch *gdbarch,
				       CORE_ADDR address);

/* %d for LONGEST */
extern char *plongest (LONGEST l);
/* %u for ULONGEST */
extern char *pulongest (ULONGEST l);

extern char *phex (ULONGEST l, int sizeof_l);
extern char *phex_nz (ULONGEST l, int sizeof_l);
extern char *int_string (LONGEST, int, int, int, int);

/* Convert a CORE_ADDR into a HEX string with leading zeros.
   The output from core_addr_to_string() can be passed direct to
   string_to_core_addr().  */
extern const char *core_addr_to_string (const CORE_ADDR addr);
extern const char *core_addr_to_string_nz (const CORE_ADDR addr);
extern CORE_ADDR string_to_core_addr (const char *my_string);

/* Return a string that contains a number formatted as a hex
   string.  */
extern char *hex_string (LONGEST);
extern char *hex_string_custom (LONGEST, int);

extern void fprintf_symbol_filtered (struct ui_file *, char *,
				     enum language, int);

extern void perror_with_name (const char *) ATTRIBUTE_NORETURN;

extern void print_sys_errmsg (const char *, int);

/* From regex.c or libc.  BSD 4.4 declares this with the argument type as
   "const char *" in unistd.h, so we can't declare the argument
   as "char *".  */

extern char *re_comp (const char *);

/* From symfile.c */

extern void symbol_file_command (char *, int);

/* Remote targets may wish to use this as their load function.  */
extern void generic_load (char *name, int from_tty);

/* Report on STREAM the performance of memory transfer operation,
   such as 'load'.
   DATA_COUNT is the number of bytes transferred.
   WRITE_COUNT is the number of separate write operations, or 0,
   if that information is not available.
   START_TIME is the time at which an operation was started.
   END_TIME is the time at which an operation ended.  */
struct timeval;
extern void print_transfer_performance (struct ui_file *stream,
					unsigned long data_count,
					unsigned long write_count,
					const struct timeval *start_time,
					const struct timeval *end_time);

/* From top.c */

typedef void initialize_file_ftype (void);

extern char *skip_quoted (char *);

extern char *gdb_readline (char *);

extern char *gdb_readline_wrapper (char *);

extern char *command_line_input (char *, int, char *);

extern void print_prompt (void);

extern int input_from_terminal_p (void);

extern int info_verbose;

/* From printcmd.c */

extern void set_next_address (struct gdbarch *, CORE_ADDR);

extern void print_address_symbolic (struct gdbarch *, CORE_ADDR,
				    struct ui_file *, int, char *);

extern int build_address_symbolic (struct gdbarch *,
				   CORE_ADDR addr,
				   int do_demangle, 
				   char **name, 
				   int *offset, 
				   char **filename, 
				   int *line, 	
				   int *unmapped);

extern void print_address (struct gdbarch *, CORE_ADDR, struct ui_file *);
extern const char *pc_prefix (CORE_ADDR);

/* From source.c */

#define OPF_TRY_CWD_FIRST     0x01
#define OPF_SEARCH_IN_PATH    0x02

extern int openp (const char *, int, const char *, int, char **);

extern int source_full_path_of (const char *, char **);

extern void mod_path (char *, char **);

extern void add_path (char *, char **, int);

extern void directory_command (char *, int);

extern void directory_switch (char *, int);

extern char *source_path;

extern void init_source_path (void);

/* From exec.c */

typedef int (*find_memory_region_ftype) (CORE_ADDR addr, unsigned long size,
					 int read, int write, int exec,
					 void *data);

/* Take over the 'find_mapped_memory' vector from exec.c.  */
extern void exec_set_find_memory_regions
  (int (*func) (find_memory_region_ftype func, void *data));

/* Possible lvalue types.  Like enum language, this should be in
   value.h, but needs to be here for the same reason.  */

enum lval_type
  {
    /* Not an lval.  */
    not_lval,
    /* In memory.  */
    lval_memory,
    /* In a register.  Registers are relative to a frame.  */
    lval_register,
    /* In a gdb internal variable.  */
    lval_internalvar,
    /* Part of a gdb internal variable (structure field).  */
    lval_internalvar_component,
    /* Value's bits are fetched and stored using functions provided by
       its creator.  */
    lval_computed
  };

/* Control types for commands */

enum misc_command_type
  {
    ok_command,
    end_command,
    else_command,
    nop_command
  };

enum command_control_type
  {
    simple_control,
    break_control,
    continue_control,
    while_control,
    if_control,
    commands_control,
    python_control,
    while_stepping_control,
    invalid_control
  };

/* Structure for saved commands lines
   (for breakpoints, defined commands, etc).  */

struct command_line
  {
    struct command_line *next;
    char *line;
    enum command_control_type control_type;
    /* The number of elements in body_list.  */
    int body_count;
    /* For composite commands, the nested lists of commands.  For
       example, for "if" command this will contain the then branch and
       the else branch, if that is available.  */
    struct command_line **body_list;
  };

extern struct command_line *read_command_lines (char *, int, int,
						void (*)(char *, void *),
						void *);
extern struct command_line *read_command_lines_1 (char * (*) (void), int,
						  void (*)(char *, void *),
						  void *);

extern void free_command_lines (struct command_line **);

/* String containing the current directory (what getwd would return).  */

extern char *current_directory;

/* Default radixes for input and output.  Only some values supported.  */
extern unsigned input_radix;
extern unsigned output_radix;

/* Possibilities for prettyprint parameters to routines which print
   things.  Like enum language, this should be in value.h, but needs
   to be here for the same reason.  FIXME:  If we can eliminate this
   as an arg to LA_VAL_PRINT, then we can probably move it back to
   value.h.  */

enum val_prettyprint
  {
    Val_no_prettyprint = 0,
    Val_prettyprint,
    /* Use the default setting which the user has specified.  */
    Val_pretty_default
  };

/* Optional native machine support.  Non-native (and possibly pure
   multi-arch) targets do not need a "nm.h" file.  This will be a
   symlink to one of the nm-*.h files, built by the `configure'
   script.  */

#ifdef GDB_NM_FILE
#include "nm.h"
#endif

/* Assume that fopen accepts the letter "b" in the mode string.
   It is demanded by ISO C9X, and should be supported on all
   platforms that claim to have a standard-conforming C library.  On
   true POSIX systems it will be ignored and have no effect.  There
   may still be systems without a standard-conforming C library where
   an ISO C9X compiler (GCC) is available.  Known examples are SunOS
   4.x and 4.3BSD.  This assumption means these systems are no longer
   supported.  */
#ifndef FOPEN_RB
# include "fopen-bin.h"
#endif

/* Defaults for system-wide constants (if not defined by xm.h, we fake it).
   FIXME: Assumes 2's complement arithmetic.  */

#if !defined (UINT_MAX)
#define	UINT_MAX ((unsigned int)(~0))	    /* 0xFFFFFFFF for 32-bits */
#endif

#if !defined (INT_MAX)
#define	INT_MAX ((int)(UINT_MAX >> 1))	    /* 0x7FFFFFFF for 32-bits */
#endif

#if !defined (INT_MIN)
#define INT_MIN ((int)((int) ~0 ^ INT_MAX)) /* 0x80000000 for 32-bits */
#endif

#if !defined (ULONG_MAX)
#define	ULONG_MAX ((unsigned long)(~0L))    /* 0xFFFFFFFF for 32-bits */
#endif

#if !defined (LONG_MAX)
#define	LONG_MAX ((long)(ULONG_MAX >> 1))   /* 0x7FFFFFFF for 32-bits */
#endif

#if !defined (ULONGEST_MAX)
#define	ULONGEST_MAX (~(ULONGEST)0)        /* 0xFFFFFFFFFFFFFFFF for 64-bits */
#endif

#if !defined (LONGEST_MAX)                 /* 0x7FFFFFFFFFFFFFFF for 64-bits */
#define	LONGEST_MAX ((LONGEST)(ULONGEST_MAX >> 1))
#endif

/* Convert a LONGEST to an int.  This is used in contexts (e.g. number of
   arguments to a function, number in a value history, register number, etc.)
   where the value must not be larger than can fit in an int.  */

extern int longest_to_int (LONGEST);

/* Assorted functions we can declare, now that const and volatile are 
   defined.  */

extern char *savestring (const char *, size_t);

/* Utility macros to allocate typed memory.  Avoids errors like:
   struct foo *foo = xmalloc (sizeof struct bar); and memset (foo,
   sizeof (struct foo), 0).  */
#define XZALLOC(TYPE) ((TYPE*) xzalloc (sizeof (TYPE)))
#define XMALLOC(TYPE) ((TYPE*) xmalloc (sizeof (TYPE)))
#define XCALLOC(NMEMB, TYPE) ((TYPE*) xcalloc ((NMEMB), sizeof (TYPE)))

#include "common-utils.h"

extern int parse_escape (struct gdbarch *, char **);

/* Message to be printed before the error message, when an error occurs.  */

extern char *error_pre_print;

/* Message to be printed before the error message, when an error occurs.  */

extern char *quit_pre_print;

/* Message to be printed before the warning message, when a warning occurs.  */

extern char *warning_pre_print;

extern void verror (const char *fmt, va_list ap)
     ATTRIBUTE_NORETURN ATTRIBUTE_PRINTF (1, 0);

extern void error (const char *fmt, ...)
     ATTRIBUTE_NORETURN ATTRIBUTE_PRINTF (1, 2);

extern void error_stream (struct ui_file *) ATTRIBUTE_NORETURN;

extern void vfatal (const char *fmt, va_list ap)
     ATTRIBUTE_NORETURN ATTRIBUTE_PRINTF (1, 0);

extern void fatal (const char *fmt, ...)
     ATTRIBUTE_NORETURN ATTRIBUTE_PRINTF (1, 2);

extern void internal_verror (const char *file, int line, const char *,
			     va_list ap)
     ATTRIBUTE_NORETURN ATTRIBUTE_PRINTF (3, 0);

extern void internal_vwarning (const char *file, int line,
			       const char *, va_list ap)
     ATTRIBUTE_PRINTF (3, 0);

extern void internal_warning (const char *file, int line,
			      const char *, ...) ATTRIBUTE_PRINTF (3, 4);

extern void warning (const char *, ...) ATTRIBUTE_PRINTF (1, 2);

extern void vwarning (const char *, va_list args) ATTRIBUTE_PRINTF (1, 0);

/* List of known OS ABIs.  If you change this, make sure to update the
   table in osabi.c.  */
enum gdb_osabi
{
  GDB_OSABI_UNINITIALIZED = -1, /* For struct gdbarch_info.  */

  GDB_OSABI_UNKNOWN = 0,	/* keep this zero */

  GDB_OSABI_SVR4,
  GDB_OSABI_HURD,
  GDB_OSABI_SOLARIS,
  GDB_OSABI_OSF1,
  GDB_OSABI_LINUX,
  GDB_OSABI_FREEBSD_AOUT,
  GDB_OSABI_FREEBSD_ELF,
  GDB_OSABI_NETBSD_AOUT,
  GDB_OSABI_NETBSD_ELF,
  GDB_OSABI_OPENBSD_ELF,
  GDB_OSABI_WINCE,
  GDB_OSABI_GO32,
  GDB_OSABI_IRIX,
  GDB_OSABI_INTERIX,
  GDB_OSABI_HPUX_ELF,
  GDB_OSABI_HPUX_SOM,
  GDB_OSABI_QNXNTO,
  GDB_OSABI_CYGWIN,
  GDB_OSABI_AIX,
  GDB_OSABI_DICOS,
  GDB_OSABI_DARWIN,
  GDB_OSABI_SYMBIAN,

  GDB_OSABI_INVALID		/* keep this last */
};

/* Global functions from other, non-gdb GNU thingies.
   Libiberty thingies are no longer declared here.  We include libiberty.h
   above, instead.  */

/* From other system libraries */

#ifdef HAVE_STDDEF_H
#include <stddef.h>
#endif

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif
#ifndef min
#define min(a, b) ((a) < (b) ? (a) : (b))
#endif
#ifndef max
#define max(a, b) ((a) > (b) ? (a) : (b))
#endif


#ifndef atof
extern double atof (const char *);	/* X3.159-1989  4.10.1.1 */
#endif

/* Various possibilities for alloca.  */
#ifndef alloca
#ifdef __GNUC__
#define alloca __builtin_alloca
#else /* Not GNU C */
#ifdef HAVE_ALLOCA_H
#include <alloca.h>
#else
#ifdef _AIX
#pragma alloca
#else

/* We need to be careful not to declare this in a way which conflicts with
   bison.  Bison never declares it as char *, but under various circumstances
   (like __hpux) we need to use void *.  */
extern void *alloca ();
#endif /* Not _AIX */
#endif /* Not HAVE_ALLOCA_H */
#endif /* Not GNU C */
#endif /* alloca not defined */

/* Dynamic target-system-dependent parameters for GDB.  */
#include "gdbarch.h"

/* Maximum size of a register.  Something small, but large enough for
   all known ISAs.  If it turns out to be too small, make it bigger.  */

enum { MAX_REGISTER_SIZE = 64 };

/* Static target-system-dependent parameters for GDB.  */

/* Number of bits in a char or unsigned char for the target machine.
   Just like CHAR_BIT in <limits.h> but describes the target machine.  */
#if !defined (TARGET_CHAR_BIT)
#define TARGET_CHAR_BIT 8
#endif

/* If we picked up a copy of CHAR_BIT from a configuration file
   (which may get it by including <limits.h>) then use it to set
   the number of bits in a host char.  If not, use the same size
   as the target.  */

#if defined (CHAR_BIT)
#define HOST_CHAR_BIT CHAR_BIT
#else
#define HOST_CHAR_BIT TARGET_CHAR_BIT
#endif

/* In findvar.c.  */

extern LONGEST extract_signed_integer (const gdb_byte *, int,
				       enum bfd_endian);

extern ULONGEST extract_unsigned_integer (const gdb_byte *, int,
					  enum bfd_endian);

extern int extract_long_unsigned_integer (const gdb_byte *, int,
					  enum bfd_endian, LONGEST *);

extern CORE_ADDR extract_typed_address (const gdb_byte *buf,
					struct type *type);

extern void store_signed_integer (gdb_byte *, int,
				  enum bfd_endian, LONGEST);

extern void store_unsigned_integer (gdb_byte *, int,
				    enum bfd_endian, ULONGEST);

extern void store_typed_address (gdb_byte *buf, struct type *type,
				 CORE_ADDR addr);


/* From valops.c */

extern int watchdog;

/* Hooks for alternate command interfaces.  */

/* The name of the interpreter if specified on the command line.  */
extern char *interpreter_p;

/* If a given interpreter matches INTERPRETER_P then it should update
   deprecated_command_loop_hook and deprecated_init_ui_hook with the
   per-interpreter implementation.  */
/* FIXME: deprecated_command_loop_hook and deprecated_init_ui_hook
   should be moved here.  */

struct target_waitstatus;
struct cmd_list_element;

extern void (*deprecated_pre_add_symbol_hook) (const char *);
extern void (*deprecated_post_add_symbol_hook) (void);
extern void (*selected_frame_level_changed_hook) (int);
extern int (*deprecated_ui_loop_hook) (int signo);
extern void (*deprecated_init_ui_hook) (char *argv0);
extern void (*deprecated_command_loop_hook) (void);
extern void (*deprecated_show_load_progress) (const char *section,
					      unsigned long section_sent, 
					      unsigned long section_size, 
					      unsigned long total_sent, 
					      unsigned long total_size);
extern void (*deprecated_print_frame_info_listing_hook) (struct symtab * s,
							 int line,
							 int stopline,
							 int noerror);
extern int (*deprecated_query_hook) (const char *, va_list)
     ATTRIBUTE_FPTR_PRINTF(1,0);
extern void (*deprecated_warning_hook) (const char *, va_list)
     ATTRIBUTE_FPTR_PRINTF(1,0);
extern void (*deprecated_flush_hook) (struct ui_file * stream);
extern void (*deprecated_interactive_hook) (void);
extern void (*deprecated_readline_begin_hook) (char *, ...)
     ATTRIBUTE_FPTR_PRINTF_1;
extern char *(*deprecated_readline_hook) (char *);
extern void (*deprecated_readline_end_hook) (void);
extern void (*deprecated_register_changed_hook) (int regno);
extern void (*deprecated_context_hook) (int);
extern ptid_t (*deprecated_target_wait_hook) (ptid_t ptid,
					      struct target_waitstatus *status,
					      int options);

extern void (*deprecated_attach_hook) (void);
extern void (*deprecated_detach_hook) (void);
extern void (*deprecated_call_command_hook) (struct cmd_list_element * c,
					     char *cmd, int from_tty);

extern void (*deprecated_set_hook) (struct cmd_list_element * c);

extern void (*deprecated_error_begin_hook) (void);

extern int (*deprecated_ui_load_progress_hook) (const char *section,
						unsigned long num);


/* Inhibit window interface if non-zero.  */

extern int use_windows;

/* Definitions of filename-related things.  */

/* Host specific things.  */

#ifdef __MSDOS__
# define CANT_FORK
# define GLOBAL_CURDIR
# define DIRNAME_SEPARATOR ';'
#endif

#if !defined (__CYGWIN__) && defined (_WIN32)
# define DIRNAME_SEPARATOR ';'
#endif

#ifndef DIRNAME_SEPARATOR
#define DIRNAME_SEPARATOR ':'
#endif

#ifndef SLASH_STRING
#define SLASH_STRING "/"
#endif

/* Provide default definitions of PIDGET, TIDGET, and MERGEPID.
   The name ``TIDGET'' is a historical accident.  Many uses of TIDGET
   in the code actually refer to a lightweight process id, i.e,
   something that can be considered a process id in its own right for
   certain purposes.  */

#ifndef PIDGET
#define PIDGET(PTID) (ptid_get_pid (PTID))
#define TIDGET(PTID) (ptid_get_lwp (PTID))
#define MERGEPID(PID, TID) ptid_build (PID, TID, 0)
#endif

/* Define well known filenos if the system does not define them.  */
#ifndef STDIN_FILENO
#define STDIN_FILENO   0
#endif
#ifndef STDOUT_FILENO
#define STDOUT_FILENO  1
#endif
#ifndef STDERR_FILENO
#define STDERR_FILENO  2
#endif

/* If this definition isn't overridden by the header files, assume
   that isatty and fileno exist on this system.  */
#ifndef ISATTY
#define ISATTY(FP)	(isatty (fileno (FP)))
#endif

/* Ensure that V is aligned to an N byte boundary (B's assumed to be a
   power of 2).  Round up/down when necessary.  Examples of correct
   use include:

   addr = align_up (addr, 8); -- VALUE needs 8 byte alignment
   write_memory (addr, value, len);
   addr += len;

   and:

   sp = align_down (sp - len, 16); -- Keep SP 16 byte aligned
   write_memory (sp, value, len);

   Note that uses such as:

   write_memory (addr, value, len);
   addr += align_up (len, 8);

   and:

   sp -= align_up (len, 8);
   write_memory (sp, value, len);

   are typically not correct as they don't ensure that the address (SP
   or ADDR) is correctly aligned (relying on previous alignment to
   keep things right).  This is also why the methods are called
   "align_..." instead of "round_..." as the latter reads better with
   this incorrect coding style.  */

extern ULONGEST align_up (ULONGEST v, int n);
extern ULONGEST align_down (ULONGEST v, int n);

/* Allocation and deallocation functions for the libiberty hash table
   which use obstacks.  */
void *hashtab_obstack_allocate (void *data, size_t size, size_t count);
void dummy_obstack_deallocate (void *object, void *data);

/* From progspace.c */

extern void initialize_progspace (void);
extern void initialize_inferiors (void);

/* Special block numbers */

enum block_enum
{
  GLOBAL_BLOCK = 0,
  STATIC_BLOCK = 1,
  FIRST_LOCAL_BLOCK = 2
};

#endif /* #ifndef DEFS_H */
