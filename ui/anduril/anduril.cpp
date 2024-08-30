// Anduril: Narsil-inspired UI for SpaghettiMonster.
// (Anduril is Aragorn's sword, the blade Narsil reforged)
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
/*
 * Usually a program would be structured like this...
 * - Library headers
 * - App headers
 * - App code
 *
 * ... in each source file.
 * ... and each library and part of the program would be linked together.
 *
 * But this doesn't follow that pattern, because it's using the
 *   -fwhole-program
 * flag to reduce the compiled size.  It lets us fit more features
 * in a tiny MCU chip's ROM.
 *
 * So the structure is like this instead...
 * - App-level configuration headers
 *   - Default config
 *   - Per build target config
 * - Library-level configuration headers
 * - Library code (FSM itself)
 * - App headers
 * - App code (all of it, inline)
 *
 * Don't do this in regular programs.  It's weird and kind of gross.
 * But in this case it gives us a bunch of much-needed space, so... woot.
 *
 * Also, there are a ton of compile-time options because it needs to build
 * a bunch of different versions and each one needs to be trimmed as small
 * as possible.  These are mostly "USE" flags.
 */
/********* load up MCU info, like ROM size and such *********/
// arch/mcu.h: Attiny portability header.
// Copyright (C) 2014-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
// This helps abstract away the differences between various attiny MCUs.
/* Copyright (c) 2002, 2003, 2004, 2007 Marek Michalkiewicz
   Copyright (c) 2005, 2006 Bjoern Haase
   Copyright (c) 2008 Atmel Corporation
   Copyright (c) 2008 Wouter van Gulik
   Copyright (c) 2009 Dmitry Xmelkov
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
/* Copyright (c) 2002,2003,2005,2006,2007 Marek Michalkiewicz, Joerg Wunsch
   Copyright (c) 2007 Eric B. Weddington
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
/** \file */
/** \defgroup avr_io <avr/io.h>: AVR device-specific IO definitions
    \code #include <avr/io.h> \endcode
    This header file includes the apropriate IO definitions for the
    device that has been specified by the <tt>-mmcu=</tt> compiler
    command-line switch.  This is done by diverting to the appropriate
    file <tt>&lt;avr/io</tt><em>XXXX</em><tt>.h&gt;</tt> which should
    never be included directly.  Some register names common to all
    AVR devices are defined directly within <tt>&lt;avr/common.h&gt;</tt>,
    which is included in <tt>&lt;avr/io.h&gt;</tt>,
    but most of the details come from the respective include file.
    Note that this file always includes the following files:
    \code 
    #include <avr/sfr_defs.h>
    #include <avr/portpins.h>
    #include <avr/common.h>
    #include <avr/version.h>
    \endcode
    See \ref avr_sfr for more details about that header file.
    Included are definitions of the IO register set and their
    respective bit values as specified in the Atmel documentation.
    Note that inconsistencies in naming conventions,
    so even identical functions sometimes get different names on
    different devices.
    Also included are the specific names useable for interrupt
    function definitions as documented
    \ref avr_signames "here".
    Finally, the following macros are defined:
    - \b RAMEND
    <br>
    The last on-chip RAM address.
    <br>
    - \b XRAMEND
    <br>
    The last possible RAM location that is addressable. This is equal to 
    RAMEND for devices that do not allow for external RAM. For devices 
    that allow external RAM, this will be larger than RAMEND.
    <br>
    - \b E2END
    <br>
    The last EEPROM address.
    <br>
    - \b FLASHEND
    <br>
    The last byte address in the Flash program space.
    <br>
    - \b SPM_PAGESIZE
    <br>
    For devices with bootloader support, the flash pagesize
    (in bytes) to be used for the \c SPM instruction. 
    - \b E2PAGESIZE
    <br>
    The size of the EEPROM page.
    
*/
/* Copyright (c) 2002, Marek Michalkiewicz <marekm@amelek.gda.pl>
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.  */
/* avr/sfr_defs.h - macros for accessing AVR special function registers */
/* $Id$ */
/** \defgroup avr_sfr_notes Additional notes from <avr/sfr_defs.h>
    \ingroup avr_sfr
   The \c <avr/sfr_defs.h> file is included by all of the \c <avr/ioXXXX.h>
   files, which use macros defined here to make the special function register
   definitions look like C variables or simple constants, depending on the
   <tt>_SFR_ASM_COMPAT</tt> define.  Some examples from \c <avr/iocanxx.h> to
   show how to define such macros:
\code
\endcode
   If \c _SFR_ASM_COMPAT is not defined, C programs can use names like
   <tt>PORTA</tt> directly in C expressions (also on the left side of
   assignment operators) and GCC will do the right thing (use short I/O
   instructions if possible).  The \c __SFR_OFFSET definition is not used in
   any way in this case.
   Define \c _SFR_ASM_COMPAT as 1 to make these names work as simple constants
   (addresses of the I/O registers).  This is necessary when included in
   preprocessed assembler (*.S) source files, so it is done automatically if
   \c __ASSEMBLER__ is defined.  By default, all addresses are defined as if
   they were memory addresses (used in \c lds/sts instructions).  To use these
   addresses in \c in/out instructions, you must subtract 0x20 from them.
   For more backwards compatibility, insert the following at the start of your
   old assembler source file:
\code
\endcode
   This automatically subtracts 0x20 from I/O space addresses, but it's a
   hack, so it is recommended to change your source: wrap such addresses in
   macros defined here, as shown below.  After this is done, the
   <tt>__SFR_OFFSET</tt> definition is no longer necessary and can be removed.
   Real example - this code could be used in a boot loader that is portable
   between devices with \c SPMCR at different addresses.
\verbatim
<avr/iom163.h>: #define SPMCR _SFR_IO8(0x37)
<avr/iom128.h>: #define SPMCR _SFR_MEM8(0x68)
\endverbatim
\code
	out	_SFR_IO_ADDR(SPMCR), r24
	sts	_SFR_MEM_ADDR(SPMCR), r24
\endcode
   You can use the \c in/out/cbi/sbi/sbic/sbis instructions, without the
   <tt>_SFR_IO_REG_P</tt> test, if you know that the register is in the I/O
   space (as with \c SREG, for example).  If it isn't, the assembler will
   complain (I/O address out of range 0...0x3f), so this should be fairly
   safe.
   If you do not define \c __SFR_OFFSET (so it will be 0x20 by default), all
   special register addresses are defined as memory addresses (so \c SREG is
   0x5f), and (if code size and speed are not important, and you don't like
   the ugly \#if above) you can always use lds/sts to access them.  But, this
   will not work if <tt>__SFR_OFFSET</tt> != 0x20, so use a different macro
   (defined only if <tt>__SFR_OFFSET</tt> == 0x20) for safety:
\code
	sts	_SFR_ADDR(SPMCR), r24
\endcode
   In C programs, all 3 combinations of \c _SFR_ASM_COMPAT and
   <tt>__SFR_OFFSET</tt> are supported - the \c _SFR_ADDR(SPMCR) macro can be
   used to get the address of the \c SPMCR register (0x57 or 0x68 depending on
   device). */
/* These only work in C programs.  */
/* Copyright (c) 2004,2005,2007,2012 Joerg Wunsch
   Copyright (c) 2005, Carlos Lamas
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
/* Copyright (c) 2002,2004,2005 Marek Michalkiewicz
   Copyright (c) 2005, Carlos Lamas
   Copyright (c) 2005,2007 Joerg Wunsch
   Copyright (c) 2013 Embecosm
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
/*
 * ISO/IEC 9899:1999  7.18 Integer types <stdint.h>
 */
/** \file */
/** \defgroup avr_stdint <stdint.h>: Standard Integer Types
    \code #include <stdint.h> \endcode
    Use [u]intN_t if you need exactly N bits.
    Since these typedefs are mandated by the C99 standard, they are preferred
    over rolling your own typedefs.  */
/*
 * __USING_MINT8 is defined to 1 if the -mint8 option is in effect.
 */
/* Integer types */
/* actual implementation goes here */
typedef signed int int8_t __attribute__((__mode__(__QI__)));
typedef unsigned int uint8_t __attribute__((__mode__(__QI__)));
typedef signed int int16_t __attribute__ ((__mode__ (__HI__)));
typedef unsigned int uint16_t __attribute__ ((__mode__ (__HI__)));
typedef signed int int32_t __attribute__ ((__mode__ (__SI__)));
typedef unsigned int uint32_t __attribute__ ((__mode__ (__SI__)));
typedef signed int int64_t __attribute__((__mode__(__DI__)));
typedef unsigned int uint64_t __attribute__((__mode__(__DI__)));
/** \name Integer types capable of holding object pointers
    These allow you to declare variables of the same size as a pointer. */
/*@{*/
/** \ingroup avr_stdint
    Signed pointer compatible type. */
typedef int16_t intptr_t;
/** \ingroup avr_stdint
    Unsigned pointer compatible type. */
typedef uint16_t uintptr_t;
/*@}*/
/** \name Minimum-width integer types
   Integer types having at least the specified width */
/*@{*/
/** \ingroup avr_stdint
    signed int with at least 8 bits. */
typedef int8_t int_least8_t;
/** \ingroup avr_stdint
    unsigned int with at least 8 bits. */
typedef uint8_t uint_least8_t;
/** \ingroup avr_stdint
    signed int with at least 16 bits. */
typedef int16_t int_least16_t;
/** \ingroup avr_stdint
    unsigned int with at least 16 bits. */
typedef uint16_t uint_least16_t;
/** \ingroup avr_stdint
    signed int with at least 32 bits. */
typedef int32_t int_least32_t;
/** \ingroup avr_stdint
    unsigned int with at least 32 bits. */
typedef uint32_t uint_least32_t;
/** \ingroup avr_stdint
    signed int with at least 64 bits.
    \note This type is not available when the compiler
    option -mint8 is in effect. */
typedef int64_t int_least64_t;
/** \ingroup avr_stdint
    unsigned int with at least 64 bits.
    \note This type is not available when the compiler
    option -mint8 is in effect. */
typedef uint64_t uint_least64_t;
/*@}*/
/** \name Fastest minimum-width integer types
   Integer types being usually fastest having at least the specified width */
/*@{*/
/** \ingroup avr_stdint
    fastest signed int with at least 8 bits. */
typedef int8_t int_fast8_t;
/** \ingroup avr_stdint
    fastest unsigned int with at least 8 bits. */
typedef uint8_t uint_fast8_t;
/** \ingroup avr_stdint
    fastest signed int with at least 16 bits. */
typedef int16_t int_fast16_t;
/** \ingroup avr_stdint
    fastest unsigned int with at least 16 bits. */
typedef uint16_t uint_fast16_t;
/** \ingroup avr_stdint
    fastest signed int with at least 32 bits. */
typedef int32_t int_fast32_t;
/** \ingroup avr_stdint
    fastest unsigned int with at least 32 bits. */
typedef uint32_t uint_fast32_t;
/** \ingroup avr_stdint
    fastest signed int with at least 64 bits.
    \note This type is not available when the compiler
    option -mint8 is in effect. */
typedef int64_t int_fast64_t;
/** \ingroup avr_stdint
    fastest unsigned int with at least 64 bits.
    \note This type is not available when the compiler
    option -mint8 is in effect. */
typedef uint64_t uint_fast64_t;
/*@}*/
/** \name Greatest-width integer types
   Types designating integer data capable of representing any value of
   any integer type in the corresponding signed or unsigned category */
/*@{*/
/** \ingroup avr_stdint
    largest signed int available. */
typedef int64_t intmax_t;
/** \ingroup avr_stdint
    largest unsigned int available. */
typedef uint64_t uintmax_t;
/*@}*/
/* Helping macro */
/** \name Limits of specified-width integer types
   C++ implementations should define these macros only when
   __STDC_LIMIT_MACROS is defined before <stdint.h> is included */
/*@{*/
/** \ingroup avr_stdint
    largest positive value an int8_t can hold. */
/** \ingroup avr_stdint
    smallest negative value an int8_t can hold. */
/** \ingroup avr_stdint
    largest value an uint8_t can hold. */
/** \ingroup avr_stdint
    largest positive value an int16_t can hold. */
/** \ingroup avr_stdint
    smallest negative value an int16_t can hold. */
/** \ingroup avr_stdint
    largest value an uint16_t can hold. */
/** \ingroup avr_stdint
    largest positive value an int32_t can hold. */
/** \ingroup avr_stdint
    smallest negative value an int32_t can hold. */
/** \ingroup avr_stdint
    largest value an uint32_t can hold. */
/** \ingroup avr_stdint
    largest positive value an int64_t can hold. */
/** \ingroup avr_stdint
    smallest negative value an int64_t can hold. */
/** \ingroup avr_stdint
    largest value an uint64_t can hold. */
/*@}*/
/** \name Limits of minimum-width integer types */
/*@{*/
/** \ingroup avr_stdint
    largest positive value an int_least8_t can hold. */
/** \ingroup avr_stdint
    smallest negative value an int_least8_t can hold. */
/** \ingroup avr_stdint
    largest value an uint_least8_t can hold. */
/** \ingroup avr_stdint
    largest positive value an int_least16_t can hold. */
/** \ingroup avr_stdint
    smallest negative value an int_least16_t can hold. */
/** \ingroup avr_stdint
    largest value an uint_least16_t can hold. */
/** \ingroup avr_stdint
    largest positive value an int_least32_t can hold. */
/** \ingroup avr_stdint
    smallest negative value an int_least32_t can hold. */
/** \ingroup avr_stdint
    largest value an uint_least32_t can hold. */
/** \ingroup avr_stdint
    largest positive value an int_least64_t can hold. */
/** \ingroup avr_stdint
    smallest negative value an int_least64_t can hold. */
/** \ingroup avr_stdint
    largest value an uint_least64_t can hold. */
/*@}*/
/** \name Limits of fastest minimum-width integer types */
/*@{*/
/** \ingroup avr_stdint
    largest positive value an int_fast8_t can hold. */
/** \ingroup avr_stdint
    smallest negative value an int_fast8_t can hold. */
/** \ingroup avr_stdint
    largest value an uint_fast8_t can hold. */
/** \ingroup avr_stdint
    largest positive value an int_fast16_t can hold. */
/** \ingroup avr_stdint
    smallest negative value an int_fast16_t can hold. */
/** \ingroup avr_stdint
    largest value an uint_fast16_t can hold. */
/** \ingroup avr_stdint
    largest positive value an int_fast32_t can hold. */
/** \ingroup avr_stdint
    smallest negative value an int_fast32_t can hold. */
/** \ingroup avr_stdint
    largest value an uint_fast32_t can hold. */
/** \ingroup avr_stdint
    largest positive value an int_fast64_t can hold. */
/** \ingroup avr_stdint
    smallest negative value an int_fast64_t can hold. */
/** \ingroup avr_stdint
    largest value an uint_fast64_t can hold. */
/*@}*/
/** \name Limits of integer types capable of holding object pointers */
/*@{*/
/** \ingroup avr_stdint
    largest positive value an intptr_t can hold. */
/** \ingroup avr_stdint
    smallest negative value an intptr_t can hold. */
/** \ingroup avr_stdint
    largest value an uintptr_t can hold. */
/*@}*/
/** \name Limits of greatest-width integer types */
/*@{*/
/** \ingroup avr_stdint
    largest positive value an intmax_t can hold. */
/** \ingroup avr_stdint
    smallest negative value an intmax_t can hold. */
/** \ingroup avr_stdint
    largest value an uintmax_t can hold. */
/*@}*/
/** \name Limits of other integer types
    C++ implementations should define these macros only when
    __STDC_LIMIT_MACROS is defined before <stdint.h> is included */
/*@{*/
/** \ingroup avr_stdint
    largest positive value a ptrdiff_t can hold. */
/** \ingroup avr_stdint
    smallest negative value a ptrdiff_t can hold. */
/* Limits of sig_atomic_t */
/* signal.h is currently not implemented (not avr/signal.h) */
/** \ingroup avr_stdint
    largest positive value a sig_atomic_t can hold. */
/** \ingroup avr_stdint
    smallest negative value a sig_atomic_t can hold. */
/** \ingroup avr_stdint
    largest value a size_t can hold. */
/* Limits of wchar_t */
/* wchar.h is currently not implemented */
/* #define WCHAR_MAX */
/* #define WCHAR_MIN */
/* Limits of wint_t */
/* wchar.h is currently not implemented */
/** \name Macros for integer constants
    C++ implementations should define these macros only when
    __STDC_CONSTANT_MACROS is defined before <stdint.h> is included.
    These definitions are valid for integer constants without suffix and
    for macros defined as integer constant without suffix */
/* The GNU C preprocessor defines special macros in the implementation
   namespace to allow a definition that works in #if expressions.  */
/*@}*/
/** \file */
/** \defgroup avr_inttypes <inttypes.h>: Integer Type conversions
    \code #include <inttypes.h> \endcode
    This header file includes the exact-width integer definitions from
    <tt><stdint.h></tt>, and extends them with additional facilities
    provided by the implementation.
    Currently, the extensions include two additional integer types
    that could hold a "far" pointer (i.e. a code pointer that can
    address more than 64 KB), as well as standard names for all printf
    and scanf formatting options that are supported by the \ref avr_stdio.
    As the library does not support the full range of conversion
    specifiers from ISO 9899:1999, only those conversions that are
    actually implemented will be listed here.
    The idea behind these conversion macros is that, for each of the
    types defined by <stdint.h>, a macro will be supplied that portably
    allows formatting an object of that type in printf() or scanf()
    operations.  Example:
    \code
    #include <inttypes.h>
    uint8_t smallval;
    int32_t longval;
    ...
    printf("The hexadecimal value of smallval is %" PRIx8
           ", the decimal value of longval is %" PRId32 ".\n",
	   smallval, longval);
    \endcode
*/
/** \name Far pointers for memory access >64K */
/*@{*/
/** \ingroup avr_inttypes
    signed integer type that can hold a pointer > 64 KB */
typedef int32_t int_farptr_t;
/** \ingroup avr_inttypes
    unsigned integer type that can hold a pointer > 64 KB */
typedef uint32_t uint_farptr_t;
/*@}*/
/** \name macros for printf and scanf format specifiers
    For C++, these are only included if __STDC_LIMIT_MACROS
    is defined before including <inttypes.h>.
 */
/*@{*/
/** \ingroup avr_inttypes
    decimal printf format for int8_t */
/** \ingroup avr_inttypes
    decimal printf format for int_least8_t */
/** \ingroup avr_inttypes
    decimal printf format for int_fast8_t */
/** \ingroup avr_inttypes
    integer printf format for int8_t */
/** \ingroup avr_inttypes
    integer printf format for int_least8_t */
/** \ingroup avr_inttypes
    integer printf format for int_fast8_t */
/** \ingroup avr_inttypes
    decimal printf format for int16_t */
/** \ingroup avr_inttypes
    decimal printf format for int_least16_t */
/** \ingroup avr_inttypes
    decimal printf format for int_fast16_t */
/** \ingroup avr_inttypes
    integer printf format for int16_t */
/** \ingroup avr_inttypes
    integer printf format for int_least16_t */
/** \ingroup avr_inttypes
    integer printf format for int_fast16_t */
/** \ingroup avr_inttypes
    decimal printf format for int32_t */
/** \ingroup avr_inttypes
    decimal printf format for int_least32_t */
/** \ingroup avr_inttypes
    decimal printf format for int_fast32_t */
/** \ingroup avr_inttypes
    integer printf format for int32_t */
/** \ingroup avr_inttypes
    integer printf format for int_least32_t */
/** \ingroup avr_inttypes
    integer printf format for int_fast32_t */
/** \ingroup avr_inttypes
    decimal printf format for intptr_t */
/** \ingroup avr_inttypes
    integer printf format for intptr_t */
/** \ingroup avr_inttypes
    octal printf format for uint8_t */
/** \ingroup avr_inttypes
    octal printf format for uint_least8_t */
/** \ingroup avr_inttypes
    octal printf format for uint_fast8_t */
/** \ingroup avr_inttypes
    decimal printf format for uint8_t */
/** \ingroup avr_inttypes
    decimal printf format for uint_least8_t */
/** \ingroup avr_inttypes
    decimal printf format for uint_fast8_t */
/** \ingroup avr_inttypes
    hexadecimal printf format for uint8_t */
/** \ingroup avr_inttypes
    hexadecimal printf format for uint_least8_t */
/** \ingroup avr_inttypes
    hexadecimal printf format for uint_fast8_t */
/** \ingroup avr_inttypes
    uppercase hexadecimal printf format for uint8_t */
/** \ingroup avr_inttypes
    uppercase hexadecimal printf format for uint_least8_t */
/** \ingroup avr_inttypes
    uppercase hexadecimal printf format for uint_fast8_t */
/** \ingroup avr_inttypes
    octal printf format for uint16_t */
/** \ingroup avr_inttypes
    octal printf format for uint_least16_t */
/** \ingroup avr_inttypes
    octal printf format for uint_fast16_t */
/** \ingroup avr_inttypes
    decimal printf format for uint16_t */
/** \ingroup avr_inttypes
    decimal printf format for uint_least16_t */
/** \ingroup avr_inttypes
    decimal printf format for uint_fast16_t */
/** \ingroup avr_inttypes
    hexadecimal printf format for uint16_t */
/** \ingroup avr_inttypes
    hexadecimal printf format for uint_least16_t */
/** \ingroup avr_inttypes
    hexadecimal printf format for uint_fast16_t */
/** \ingroup avr_inttypes
    uppercase hexadecimal printf format for uint16_t */
/** \ingroup avr_inttypes
    uppercase hexadecimal printf format for uint_least16_t */
/** \ingroup avr_inttypes
    uppercase hexadecimal printf format for uint_fast16_t */
/** \ingroup avr_inttypes
    octal printf format for uint32_t */
/** \ingroup avr_inttypes
    octal printf format for uint_least32_t */
/** \ingroup avr_inttypes
    octal printf format for uint_fast32_t */
/** \ingroup avr_inttypes
    decimal printf format for uint32_t */
/** \ingroup avr_inttypes
    decimal printf format for uint_least32_t */
/** \ingroup avr_inttypes
    decimal printf format for uint_fast32_t */
/** \ingroup avr_inttypes
    hexadecimal printf format for uint32_t */
/** \ingroup avr_inttypes
    hexadecimal printf format for uint_least32_t */
/** \ingroup avr_inttypes
    hexadecimal printf format for uint_fast32_t */
/** \ingroup avr_inttypes
    uppercase hexadecimal printf format for uint32_t */
/** \ingroup avr_inttypes
    uppercase hexadecimal printf format for uint_least32_t */
/** \ingroup avr_inttypes
    uppercase hexadecimal printf format for uint_fast32_t */
/** \ingroup avr_inttypes
    octal printf format for uintptr_t */
/** \ingroup avr_inttypes
    decimal printf format for uintptr_t */
/** \ingroup avr_inttypes
    hexadecimal printf format for uintptr_t */
/** \ingroup avr_inttypes
    uppercase hexadecimal printf format for uintptr_t */
/** \ingroup avr_inttypes
    decimal scanf format for int8_t */
/** \ingroup avr_inttypes
    decimal scanf format for int_least8_t */
/** \ingroup avr_inttypes
    decimal scanf format for int_fast8_t */
/** \ingroup avr_inttypes
    generic-integer scanf format for int8_t */
/** \ingroup avr_inttypes
    generic-integer scanf format for int_least8_t */
/** \ingroup avr_inttypes
    generic-integer scanf format for int_fast8_t */
/** \ingroup avr_inttypes
    decimal scanf format for int16_t */
/** \ingroup avr_inttypes
    decimal scanf format for int_least16_t */
/** \ingroup avr_inttypes
    decimal scanf format for int_fast16_t */
/** \ingroup avr_inttypes
    generic-integer scanf format for int16_t */
/** \ingroup avr_inttypes
    generic-integer scanf format for int_least16_t */
/** \ingroup avr_inttypes
    generic-integer scanf format for int_fast16_t */
/** \ingroup avr_inttypes
    decimal scanf format for int32_t */
/** \ingroup avr_inttypes
    decimal scanf format for int_least32_t */
/** \ingroup avr_inttypes
    decimal scanf format for int_fast32_t */
/** \ingroup avr_inttypes
    generic-integer scanf format for int32_t */
/** \ingroup avr_inttypes
    generic-integer scanf format for int_least32_t */
/** \ingroup avr_inttypes
    generic-integer scanf format for int_fast32_t */
/** \ingroup avr_inttypes
    decimal scanf format for intptr_t */
/** \ingroup avr_inttypes
    generic-integer scanf format for intptr_t */
/** \ingroup avr_inttypes
    octal scanf format for uint8_t */
/** \ingroup avr_inttypes
    octal scanf format for uint_least8_t */
/** \ingroup avr_inttypes
    octal scanf format for uint_fast8_t */
/** \ingroup avr_inttypes
    decimal scanf format for uint8_t */
/** \ingroup avr_inttypes
    decimal scanf format for uint_least8_t */
/** \ingroup avr_inttypes
    decimal scanf format for uint_fast8_t */
/** \ingroup avr_inttypes
    hexadecimal scanf format for uint8_t */
/** \ingroup avr_inttypes
    hexadecimal scanf format for uint_least8_t */
/** \ingroup avr_inttypes
    hexadecimal scanf format for uint_fast8_t */
/** \ingroup avr_inttypes
    octal scanf format for uint16_t */
/** \ingroup avr_inttypes
    octal scanf format for uint_least16_t */
/** \ingroup avr_inttypes
    octal scanf format for uint_fast16_t */
/** \ingroup avr_inttypes
    decimal scanf format for uint16_t */
/** \ingroup avr_inttypes
    decimal scanf format for uint_least16_t */
/** \ingroup avr_inttypes
    decimal scanf format for uint_fast16_t */
/** \ingroup avr_inttypes
    hexadecimal scanf format for uint16_t */
/** \ingroup avr_inttypes
    hexadecimal scanf format for uint_least16_t */
/** \ingroup avr_inttypes
    hexadecimal scanf format for uint_fast16_t */
/** \ingroup avr_inttypes
    octal scanf format for uint32_t */
/** \ingroup avr_inttypes
    octal scanf format for uint_least32_t */
/** \ingroup avr_inttypes
    octal scanf format for uint_fast32_t */
/** \ingroup avr_inttypes
    decimal scanf format for uint32_t */
/** \ingroup avr_inttypes
    decimal scanf format for uint_least32_t */
/** \ingroup avr_inttypes
    decimal scanf format for uint_fast32_t */
/** \ingroup avr_inttypes
    hexadecimal scanf format for uint32_t */
/** \ingroup avr_inttypes
    hexadecimal scanf format for uint_least32_t */
/** \ingroup avr_inttypes
    hexadecimal scanf format for uint_fast32_t */
/** \ingroup avr_inttypes
    octal scanf format for uintptr_t */
/** \ingroup avr_inttypes
    decimal scanf format for uintptr_t */
/** \ingroup avr_inttypes
    hexadecimal scanf format for uintptr_t */
/*@}*/
/** \name Bit manipulation */
/*@{*/
/** \def _BV
    \ingroup avr_sfr
    \code #include <avr/io.h>\endcode
    Converts a bit number into a byte value.
    \note The bit shift is performed by the compiler which then inserts the
    result into the code. Thus, there is no run-time overhead when using
    _BV(). */
/*@}*/
/** \name IO register bit manipulation */
/*@{*/
/** \def bit_is_set
    \ingroup avr_sfr
    \code #include <avr/io.h>\endcode
    Test whether bit \c bit in IO register \c sfr is set. 
    This will return a 0 if the bit is clear, and non-zero
    if the bit is set. */
/** \def bit_is_clear
    \ingroup avr_sfr
    \code #include <avr/io.h>\endcode
    Test whether bit \c bit in IO register \c sfr is clear. 
    This will return non-zero if the bit is clear, and a 0
    if the bit is set. */
/** \def loop_until_bit_is_set
    \ingroup avr_sfr
    \code #include <avr/io.h>\endcode
    Wait until bit \c bit in IO register \c sfr is set. */
/** \def loop_until_bit_is_clear
    \ingroup avr_sfr
    \code #include <avr/io.h>\endcode
    Wait until bit \c bit in IO register \c sfr is clear. */
/*@}*/
/*
 * Copyright (C) 2022, Microchip Technology Inc. and its subsidiaries ("Microchip")
 * All rights reserved.
 *
 * This software is developed by Microchip Technology Inc. and its subsidiaries ("Microchip").
 *
 * Redistribution and use in source and binary forms, with or without modification, are
 * permitted provided that the following conditions are met:
 *
 *     1. Redistributions of source code must retain the above copyright notice, this list of
 *        conditions and the following disclaimer.
 *
 *     2. Redistributions in binary form must reproduce the above copyright notice, this list
 *        of conditions and the following disclaimer in the documentation and/or other
 *        materials provided with the distribution. Publication is not required when
 *        this file is used in an embedded application.
 *
 *     3. Microchip's name may not be used to endorse or promote products derived from this
 *        software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY MICROCHIP "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL MICROCHIP BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING BUT NOT LIMITED TO
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWSOEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/* Registers and associated bit numbers */
/* Combine ADCL and ADCH */
// Inserted "DDC5" from "DDRC5" due to compatibility
// Inserted "DDC4" from "DDRC4" due to compatibility
// Inserted "DDC3" from "DDRC3" due to compatibility
// Inserted "DDC2" from "DDRC2" due to compatibility
// Inserted "DDC1" from "DDRC1" due to compatibility
// Inserted "DDC0" from "DDRC0" due to compatibility
// Inserted "DDB3" from "DDRB3" due to compatibility
// Inserted "DDB2" from "DDRB2" due to compatibility
// Inserted "DDB1" from "DDRB1" due to compatibility
// Inserted "DDB0" from "DDRB0" due to compatibility
// Inserted "DDA7" from "DDRA7" due to compatibility
// Inserted "DDA6" from "DDRA6" due to compatibility
// Inserted "DDA5" from "DDRA5" due to compatibility
// Inserted "DDA4" from "DDRA4" due to compatibility
// Inserted "DDA3" from "DDRA3" due to compatibility
// Inserted "DDA2" from "DDRA2" due to compatibility
// Inserted "DDA1" from "DDRA1" due to compatibility
// Inserted "DDA0" from "DDRA0" due to compatibility
/* Combine EEARL and EEARH */
/* Combine UBRR0L and UBRR0H */
/* Reserved [0x2E] */
/* Reserved [0x31] */
/* Reserved [0x38] */
/* SP [0x3D..0x3E] */
/* SREG [0x3F] */
/* Combine ICR1L and ICR1H */
/* Combine OCR1BL and OCR1BH */
/* Combine OCR1AL and OCR1AH */
/* Combine TCNT1L and TCNT1H */
/* Combine UBRR1L and UBRR1H */
/* Values and associated defines */
/* Interrupt vectors */
/* Vector 0 is the reset vector */
/* External Interrupt Request 0 */
/* Pin Change Interrupt Request 0 */
/* Pin Change Interrupt Request 1 */
/* Pin Change Interrupt Request 2 */
/* Watchdog Time-out Interrupt */
/* Timer/Counter1 Capture Event */
/* Timer/Counter1 Capture Event */
/* Timer/Counter1 Compare Match A */
/* Timer/Counter1 Compare Match A */
/* Timer/Counter1 Compare Match B */
/* Timer/Counter1 Compare Match B */
/* Timer/Counter1 Overflow */
/* Timer/Counter1 Overflow */
/* TimerCounter0 Compare Match A */
/* TimerCounter0 Compare Match A */
/* TimerCounter0 Compare Match B */
/* TimerCounter0 Compare Match B */
/* Timer/Couner0 Overflow */
/* Timer/Couner0 Overflow */
/* Analog Comparator */
/* ADC Conversion Complete */
/* ADC Conversion Complete */
/* USART0, Start */
/* USART0, Start */
/* USART0, Rx Complete */
/* USART0, Rx Complete */
/* USART0 Data Register Empty */
/* USART0 Data Register Empty */
/* USART0, Tx Complete */
/* USART0, Tx Complete */
/* USART1, Start */
/* USART1, Start */
/* USART1, Rx Complete */
/* USART1, Rx Complete */
/* USART1 Data Register Empty */
/* USART1 Data Register Empty */
/* USART1, Tx Complete */
/* USART1, Tx Complete */
/* USI Start Condition */
/* USI Start Condition */
/* USI Overflow */
/* USI Overflow */
/* Two-wire Serial Interface */
/* Two-wire Serial Interface */
/* EEPROM Ready */
/* Touch Sensing */
/* Constants */
/* Fuses */
/* Low Fuse Byte */
/* High Fuse Byte */
/* Extended Fuse Byte */
/* Lock Bits */
/* Signature */
/* Copyright (c) 2003  Theodore A. Roth
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
/* This file should only be included from <avr/io.h>, never directly. */
/* Define Generic PORTn, DDn, and PINn values. */
/* Port Data Register (generic) */
/* Port Data Direction Register (generic) */
/* Port Input Pins (generic) */
/* Define PORTxn an Pxn values for all possible port pins if not defined already by io.h. */
/* PORT A */
/* PORT B */
/* PORT C */
/* PORT D */
/* PORT E */
/* PORT F */
/* PORT G */
/* PORT H */
/* PORT J */
/* PORT K */
/* PORT L */
/* Copyright (c) 2007 Eric B. Weddington
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
/* Copyright (c) 2002, Marek Michalkiewicz <marekm@amelek.gda.pl>
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.  */
/* avr/sfr_defs.h - macros for accessing AVR special function registers */
/* $Id$ */
/* 
This purpose of this header is to define registers that have not been 
previously defined in the individual device IO header files, and to define 
other symbols that are common across AVR device families.
This file is designed to be included in <avr/io.h> after the individual
device IO header files, and after <avr/sfr_defs.h>
*/
/*------------ Registers Not Previously Defined ------------*/
/* 
These are registers that are not previously defined in the individual
IO header files, OR they are defined here because they are used in parts of
avr-libc even if a device is not selected but a general architecture has
been selected.
*/
/*
Stack pointer register.
AVR architecture 1 has no RAM, thus no stack pointer. 
All other architectures do have a stack pointer.  Some devices have only
less than 256 bytes of possible RAM locations (128 Bytes of SRAM
and no option for external RAM), thus SPH is officially "reserved"
for them.
*/
/* Status Register */
/* SREG bit definitions */
/*------------ Common Symbols ------------*/
/* 
Generic definitions for registers that are common across multiple AVR devices
and families.
*/
/* Pointer registers definitions */
/* Status Register */
/* Stack Pointer (combined) Register */
/* Stack Pointer High Register */
/* Stack Pointer Low Register */
/* RAMPD Register */
/* RAMPX Register */
/* RAMPY Register */
/* RAMPZ Register */
/* Extended Indirect Register */
/*------------ Workaround to old compilers (4.1.2 and earlier)  ------------*/
/* Copyright (c) 2005, Joerg Wunsch                               -*- c -*-
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
/** \defgroup avr_version <avr/version.h>: avr-libc version macros
    \code #include <avr/version.h> \endcode
    This header file defines macros that contain version numbers and
    strings describing the current version of avr-libc.
    The version number itself basically consists of three pieces that
    are separated by a dot: the major number, the minor number, and
    the revision number.  For development versions (which use an odd
    minor number), the string representation additionally gets the
    date code (YYYYMMDD) appended.
    This file will also be included by \c <avr/io.h>.  That way,
    portable tests can be implemented using \c <avr/io.h> that can be
    used in code that wants to remain backwards-compatible to library
    versions prior to the date when the library version API had been
    added, as referenced but undefined C preprocessor macros
    automatically evaluate to 0.
*/
/** \ingroup avr_version
    String literal representation of the current library version. */
/** \ingroup avr_version
    Numerical representation of the current library version.
    In the numerical representation, the major number is multiplied by
    10000, the minor number by 100, and all three parts are then
    added.  It is intented to provide a monotonically increasing
    numerical value that can easily be used in numerical checks.
 */
/** \ingroup avr_version
    String literal representation of the release date. */
/** \ingroup avr_version
    Numerical representation of the release date. */
/** \ingroup avr_version
    Library major version number. */
/** \ingroup avr_version
    Library minor version number. */
/** \ingroup avr_version
    Library revision number. */
/* Include fuse.h after individual IO header files. */
/* Copyright (c) 2007, Atmel Corporation
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
/* avr/fuse.h - Fuse API */
/* This file must be explicitly included by <avr/io.h>. */
/** \file */
/** \defgroup avr_fuse <avr/fuse.h>: Fuse Support
    \par Introduction
    The Fuse API allows a user to specify the fuse settings for the specific
    AVR device they are compiling for. These fuse settings will be placed
    in a special section in the ELF output file, after linking.
    Programming tools can take advantage of the fuse information embedded in
    the ELF file, by extracting this information and determining if the fuses
    need to be programmed before programming the Flash and EEPROM memories.
    This also allows a single ELF file to contain all the
    information needed to program an AVR. 
    To use the Fuse API, include the <avr/io.h> header file, which in turn
    automatically includes the individual I/O header file and the <avr/fuse.h>
    file. These other two files provides everything necessary to set the AVR
    fuses.
    
    \par Fuse API
    
    Each I/O header file must define the FUSE_MEMORY_SIZE macro which is
    defined to the number of fuse bytes that exist in the AVR device.
    
    A new type, __fuse_t, is defined as a structure. The number of fields in 
    this structure are determined by the number of fuse bytes in the 
    FUSE_MEMORY_SIZE macro.
    
    If FUSE_MEMORY_SIZE == 1, there is only a single field: byte, of type
    unsigned char.
    
    If FUSE_MEMORY_SIZE == 2, there are two fields: low, and high, of type
    unsigned char.
    
    If FUSE_MEMORY_SIZE == 3, there are three fields: low, high, and extended,
    of type unsigned char.
    
    If FUSE_MEMORY_SIZE > 3, there is a single field: byte, which is an array
    of unsigned char with the size of the array being FUSE_MEMORY_SIZE.
    
    A convenience macro, FUSEMEM, is defined as a GCC attribute for a 
    custom-named section of ".fuse".
    
    A convenience macro, FUSES, is defined that declares a variable, __fuse, of
    type __fuse_t with the attribute defined by FUSEMEM. This variable
    allows the end user to easily set the fuse data.
    \note If a device-specific I/O header file has previously defined FUSEMEM,
    then FUSEMEM is not redefined. If a device-specific I/O header file has
    previously defined FUSES, then FUSES is not redefined.
    Each AVR device I/O header file has a set of defined macros which specify the
    actual fuse bits available on that device. The AVR fuses have inverted
    values, logical 1 for an unprogrammed (disabled) bit and logical 0 for a
    programmed (enabled) bit. The defined macros for each individual fuse
    bit represent this in their definition by a bit-wise inversion of a mask.
    For example, the FUSE_EESAVE fuse in the ATmega128 is defined as:
    \code
    #define FUSE_EESAVE      ~_BV(3)
    \endcode
    \note The _BV macro creates a bit mask from a bit number. It is then 
    inverted to represent logical values for a fuse memory byte.
    
    To combine the fuse bits macros together to represent a whole fuse byte,
    use the bitwise AND operator, like so:
    \code
    (FUSE_BOOTSZ0 & FUSE_BOOTSZ1 & FUSE_EESAVE & FUSE_SPIEN & FUSE_JTAGEN)
    \endcode
    
    Each device I/O header file also defines macros that provide default values
    for each fuse byte that is available. LFUSE_DEFAULT is defined for a Low
    Fuse byte. HFUSE_DEFAULT is defined for a High Fuse byte. EFUSE_DEFAULT
    is defined for an Extended Fuse byte.
    
    If FUSE_MEMORY_SIZE > 3, then the I/O header file defines macros that
    provide default values for each fuse byte like so:
    FUSE0_DEFAULT
    FUSE1_DEFAULT
    FUSE2_DEFAULT
    FUSE3_DEFAULT
    FUSE4_DEFAULT
    ....
    
    \par API Usage Example
    
    Putting all of this together is easy. Using C99's designated initializers:
    
    \code
    #include <avr/io.h>
    FUSES = 
    {
        .low = LFUSE_DEFAULT,
        .high = (FUSE_BOOTSZ0 & FUSE_BOOTSZ1 & FUSE_EESAVE & FUSE_SPIEN & FUSE_JTAGEN),
        .extended = EFUSE_DEFAULT,
    };
    int main(void)
    {
        return 0;
    }
    \endcode
    
    Or, using the variable directly instead of the FUSES macro,
    
    \code
    #include <avr/io.h>
    __fuse_t __fuse __attribute__((section (".fuse"))) = 
    {
        .low = LFUSE_DEFAULT,
        .high = (FUSE_BOOTSZ0 & FUSE_BOOTSZ1 & FUSE_EESAVE & FUSE_SPIEN & FUSE_JTAGEN),
        .extended = EFUSE_DEFAULT,
    };
    int main(void)
    {
        return 0;
    }
    \endcode
    
    If you are compiling in C++, you cannot use the designated intializers so
    you must do:
    \code
    #include <avr/io.h>
    FUSES = 
    {
        LFUSE_DEFAULT, // .low
        (FUSE_BOOTSZ0 & FUSE_BOOTSZ1 & FUSE_EESAVE & FUSE_SPIEN & FUSE_JTAGEN), // .high
        EFUSE_DEFAULT, // .extended
    };
    int main(void)
    {
        return 0;
    }
    \endcode
    
    
    However there are a number of caveats that you need to be aware of to
    use this API properly.
    
    Be sure to include <avr/io.h> to get all of the definitions for the API.
    The FUSES macro defines a global variable to store the fuse data. This 
    variable is assigned to its own linker section. Assign the desired fuse 
    values immediately in the variable initialization.
    
    The .fuse section in the ELF file will get its values from the initial 
    variable assignment ONLY. This means that you can NOT assign values to 
    this variable in functions and the new values will not be put into the
    ELF .fuse section.
    
    The global variable is declared in the FUSES macro has two leading 
    underscores, which means that it is reserved for the "implementation",
    meaning the library, so it will not conflict with a user-named variable.
    
    You must initialize ALL fields in the __fuse_t structure. This is because
    the fuse bits in all bytes default to a logical 1, meaning unprogrammed. 
    Normal uninitialized data defaults to all locgial zeros. So it is vital that
    all fuse bytes are initialized, even with default data. If they are not,
    then the fuse bits may not programmed to the desired settings.
    
    Be sure to have the -mmcu=<em>device</em> flag in your compile command line and
    your linker command line to have the correct device selected and to have 
    the correct I/O header file included when you include <avr/io.h>.
    You can print out the contents of the .fuse section in the ELF file by
    using this command line:
    \code
    avr-objdump -s -j .fuse <ELF file>
    \endcode
    The section contents shows the address on the left, then the data going from
    lower address to a higher address, left to right.
*/
typedef struct
{
    unsigned char low;
    unsigned char high;
    unsigned char extended;
} __fuse_t;
/* Include lock.h after individual IO header files. */
/* Copyright (c) 2007, Atmel Corporation
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
/* avr/lock.h - Lock Bits API */
/** \file */
/** \defgroup avr_lock <avr/lock.h>: Lockbit Support
    \par Introduction
    The Lockbit API allows a user to specify the lockbit settings for the 
    specific AVR device they are compiling for. These lockbit settings will be 
    placed in a special section in the ELF output file, after linking.
    Programming tools can take advantage of the lockbit information embedded in
    the ELF file, by extracting this information and determining if the lockbits
    need to be programmed after programming the Flash and EEPROM memories.
    This also allows a single ELF file to contain all the
    information needed to program an AVR. 
    To use the Lockbit API, include the <avr/io.h> header file, which in turn
    automatically includes the individual I/O header file and the <avr/lock.h>
    file. These other two files provides everything necessary to set the AVR
    lockbits.
    
    \par Lockbit API
    
    Each I/O header file may define up to 3 macros that controls what kinds
    of lockbits are available to the user.
    
    If __LOCK_BITS_EXIST is defined, then two lock bits are available to the
    user and 3 mode settings are defined for these two bits.
    
    If __BOOT_LOCK_BITS_0_EXIST is defined, then the two BLB0 lock bits are
    available to the user and 4 mode settings are defined for these two bits.
    
    If __BOOT_LOCK_BITS_1_EXIST is defined, then the two BLB1 lock bits are
    available to the user and 4 mode settings are defined for these two bits.
    If __BOOT_LOCK_APPLICATION_TABLE_BITS_EXIST is defined then two lock bits
    are available to set the locking mode for the Application Table Section 
    (which is used in the XMEGA family).
    
    If __BOOT_LOCK_APPLICATION_BITS_EXIST is defined then two lock bits are
    available to set the locking mode for the Application Section (which is used
    in the XMEGA family).
    
    If __BOOT_LOCK_BOOT_BITS_EXIST is defined then two lock bits are available
    to set the locking mode for the Boot Loader Section (which is used in the
    XMEGA family).
    The AVR lockbit modes have inverted values, logical 1 for an unprogrammed 
    (disabled) bit and logical 0 for a programmed (enabled) bit. The defined 
    macros for each individual lock bit represent this in their definition by a 
    bit-wise inversion of a mask. For example, the LB_MODE_3 macro is defined 
    as:
    \code
    #define LB_MODE_3  (0xFC)
`   \endcode
    
    To combine the lockbit mode macros together to represent a whole byte,
    use the bitwise AND operator, like so:
    \code
    (LB_MODE_3 & BLB0_MODE_2)
    \endcode
    
    <avr/lock.h> also defines a macro that provides a default lockbit value:
    LOCKBITS_DEFAULT which is defined to be 0xFF.
    See the AVR device specific datasheet for more details about these
    lock bits and the available mode settings.
    
    A convenience macro, LOCKMEM, is defined as a GCC attribute for a 
    custom-named section of ".lock".
    
    A convenience macro, LOCKBITS, is defined that declares a variable, __lock, 
    of type unsigned char with the attribute defined by LOCKMEM. This variable
    allows the end user to easily set the lockbit data.
    \note If a device-specific I/O header file has previously defined LOCKMEM,
    then LOCKMEM is not redefined. If a device-specific I/O header file has
    previously defined LOCKBITS, then LOCKBITS is not redefined. LOCKBITS is
    currently known to be defined in the I/O header files for the XMEGA devices.
    \par API Usage Example
    
    Putting all of this together is easy:
    
    \code
    #include <avr/io.h>
    LOCKBITS = (LB_MODE_1 & BLB0_MODE_3 & BLB1_MODE_4);
    int main(void)
    {
        return 0;
    }
    \endcode
    
    Or:
    
    \code
    #include <avr/io.h>
    unsigned char __lock __attribute__((section (".lock"))) = 
        (LB_MODE_1 & BLB0_MODE_3 & BLB1_MODE_4);
    int main(void)
    {
        return 0;
    }
    \endcode
    
    
    
    However there are a number of caveats that you need to be aware of to
    use this API properly.
    
    Be sure to include <avr/io.h> to get all of the definitions for the API.
    The LOCKBITS macro defines a global variable to store the lockbit data. This 
    variable is assigned to its own linker section. Assign the desired lockbit 
    values immediately in the variable initialization.
    
    The .lock section in the ELF file will get its values from the initial 
    variable assignment ONLY. This means that you can NOT assign values to 
    this variable in functions and the new values will not be put into the
    ELF .lock section.
    
    The global variable is declared in the LOCKBITS macro has two leading 
    underscores, which means that it is reserved for the "implementation",
    meaning the library, so it will not conflict with a user-named variable.
    
    You must initialize the lockbit variable to some meaningful value, even
    if it is the default value. This is because the lockbits default to a 
    logical 1, meaning unprogrammed. Normal uninitialized data defaults to all 
    locgial zeros. So it is vital that all lockbits are initialized, even with 
    default data. If they are not, then the lockbits may not programmed to the 
    desired settings and can possibly put your device into an unrecoverable 
    state.
    
    Be sure to have the -mmcu=<em>device</em> flag in your compile command line and
    your linker command line to have the correct device selected and to have 
    the correct I/O header file included when you include <avr/io.h>.
    You can print out the contents of the .lock section in the ELF file by
    using this command line:
    \code
    avr-objdump -s -j .lock <ELF file>
    \endcode
*/
/* Lock Bit Modes */
/* Copyright (C) 1989-2015 Free Software Foundation, Inc.
This file is part of GCC.
GCC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3, or (at your option)
any later version.
GCC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
Under Section 7 of GPL version 3, you are granted additional
permissions described in the GCC Runtime Library Exception, version
3.1, as published by the Free Software Foundation.
You should have received a copy of the GNU General Public License and
a copy of the GCC Runtime Library Exception along with this program;
see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
<http://www.gnu.org/licenses/>.  */
/*
 * ISO C Standard:  7.17  Common definitions  <stddef.h>
 */
/* Any one of these symbols __need_* means that GNU libc
   wants us just to define one data type.  So don't define
   the symbols that indicate this file's entire job has been done.  */
/* snaroff@next.com says the NeXT needs this.  */
/* This avoids lossage on SunOS but only if stdtypes.h comes first.
   There's no way to win with the other order!  Sun lossage.  */
/* On 4.3bsd-net2, make sure ansi.h is included, so we have
   one less case to deal with in the following.  */
/* On FreeBSD 5, machine/ansi.h does not exist anymore... */
/* In 4.3bsd-net2, machine/ansi.h defines these symbols, which are
   defined if the corresponding type is *not* defined.
   FreeBSD-2.1 defines _MACHINE_ANSI_H_ instead of _ANSI_H_.
   NetBSD defines _I386_ANSI_H_ and _X86_64_ANSI_H_ instead of _ANSI_H_ */
/* Sequent's header files use _PTRDIFF_T_ in some conflicting way.
   Just ignore it.  */
/* On VxWorks, <type/vxTypesBase.h> may have defined macros like
   _TYPE_size_t which will typedef size_t.  fixincludes patched the
   vxTypesBase.h so that this macro is only defined if _GCC_SIZE_T is
   not defined, and so that defining this macro defines _GCC_SIZE_T.
   If we find that the macros are still defined at this point, we must
   invoke them so that the type is defined as expected.  */
/* In case nobody has defined these types, but we aren't running under
   GCC 2.00, make sure that __PTRDIFF_TYPE__, __SIZE_TYPE__, and
   __WCHAR_TYPE__ have reasonable values.  This can happen if the
   parts of GCC is compiled by an older compiler, that actually
   include gstddef.h, such as collect2.  */
/* Signed type of difference of two pointers.  */
/* Define this type if we are doing the whole job,
   or if we want this type in particular.  */
typedef int ptrdiff_t;
/* If this symbol has done its job, get rid of it.  */
/* Unsigned type of `sizeof' something.  */
/* Define this type if we are doing the whole job,
   or if we want this type in particular.  */
typedef unsigned int size_t;
/* Wide character type.
   Locale-writers should change this as necessary to
   be big enough to hold unique values not between 0 and 127,
   and not (wchar_t) -1, for each defined multibyte character.  */
/* Define this type if we are doing the whole job,
   or if we want this type in particular.  */
/* On BSD/386 1.1, at least, machine/ansi.h defines _BSD_WCHAR_T_
   instead of _WCHAR_T_, and _BSD_RUNE_T_ (which, unlike the other
   symbols in the _FOO_T_ family, stays defined even after its
   corresponding type is defined).  If we define wchar_t, then we
   must undef _WCHAR_T_; for BSD/386 1.1 (and perhaps others), if
   we undef _WCHAR_T_, then we must also define rune_t, since 
   headers like runetype.h assume that if machine/ansi.h is included,
   and _BSD_WCHAR_T_ is not defined, then rune_t is available.
   machine/ansi.h says, "Note that _WCHAR_T_ and _RUNE_T_ must be of
   the same type." */
/* FreeBSD 5 can't be handled well using "traditional" logic above
   since it no longer defines _BSD_RUNE_T_ yet still desires to export
   rune_t in some cases... */
typedef int wchar_t;
/*  In 4.3bsd-net2, leave these undefined to indicate that size_t, etc.
    are already defined.  */
/*  BSD/OS 3.1 and FreeBSD [23].x require the MACHINE_ANSI_H check here.  */
/*  NetBSD 5 requires the I386_ANSI_H and X86_64_ANSI_H checks here.  */
/* A null pointer constant.  */
/* Offset of member MEMBER in a struct of type TYPE. */
/** \defgroup avr_eeprom <avr/eeprom.h>: EEPROM handling
    \code #include <avr/eeprom.h> \endcode
    This header file declares the interface to some simple library
    routines suitable for handling the data EEPROM contained in the
    AVR microcontrollers.  The implementation uses a simple polled
    mode interface.  Applications that require interrupt-controlled
    EEPROM access to ensure that no time will be wasted in spinloops
    will have to deploy their own implementation.
    \par Notes:
    - In addition to the write functions there is a set of update ones.
    This functions read each byte first and skip the burning if the
    old value is the same with new.  The scaning direction is from
    high address to low, to obtain quick return in common cases.
    - All of the read/write functions first make sure the EEPROM is
    ready to be accessed.  Since this may cause long delays if a
    write operation is still pending, time-critical applications
    should first poll the EEPROM e. g. using eeprom_is_ready() before
    attempting any actual I/O.  But this functions are not wait until
    SELFPRGEN in SPMCSR becomes zero.  Do this manually, if your
    softwate contains the Flash burning.
    - As these functions modify IO registers, they are known to be
    non-reentrant.  If any of these functions are used from both,
    standard and interrupt context, the applications must ensure
    proper protection (e.g. by disabling interrupts before accessing
    them).
    - All write functions force erase_and_write programming mode.
    
    - For Xmega the EEPROM start address is 0, like other architectures.
    The reading functions add the 0x2000 value to use EEPROM mapping into
    data space.
 */
/** \def EEMEM
    \ingroup avr_eeprom
    Attribute expression causing a variable to be allocated within the
    .eeprom section.	*/
/** \def eeprom_is_ready
    \ingroup avr_eeprom
    \returns 1 if EEPROM is ready for a new read/write operation, 0 if not.
 */
/** \def eeprom_busy_wait
    \ingroup avr_eeprom
    Loops until the eeprom is no longer busy.
    \returns Nothing.
 */
/** \ingroup avr_eeprom
    Read one byte from EEPROM address \a __p.
 */
uint8_t eeprom_read_byte (const uint8_t *__p) __attribute__((__pure__));
/** \ingroup avr_eeprom
    Read one 16-bit word (little endian) from EEPROM address \a __p.
 */
uint16_t eeprom_read_word (const uint16_t *__p) __attribute__((__pure__));
/** \ingroup avr_eeprom
    Read one 32-bit double word (little endian) from EEPROM address \a __p.
 */
uint32_t eeprom_read_dword (const uint32_t *__p) __attribute__((__pure__));
/** \ingroup avr_eeprom
    Read one float value (little endian) from EEPROM address \a __p.
 */
float eeprom_read_float (const float *__p) __attribute__((__pure__));
/** \ingroup avr_eeprom
    Read a block of \a __n bytes from EEPROM address \a __src to SRAM
    \a __dst.
 */
void eeprom_read_block (void *__dst, const void *__src, size_t __n);
/** \ingroup avr_eeprom
    Write a byte \a __value to EEPROM address \a __p.
 */
void eeprom_write_byte (uint8_t *__p, uint8_t __value);
/** \ingroup avr_eeprom
    Write a word \a __value to EEPROM address \a __p.
 */
void eeprom_write_word (uint16_t *__p, uint16_t __value);
/** \ingroup avr_eeprom
    Write a 32-bit double word \a __value to EEPROM address \a __p.
 */
void eeprom_write_dword (uint32_t *__p, uint32_t __value);
/** \ingroup avr_eeprom
    Write a float \a __value to EEPROM address \a __p.
 */
void eeprom_write_float (float *__p, float __value);
/** \ingroup avr_eeprom
    Write a block of \a __n bytes to EEPROM address \a __dst from \a __src.
    \note The argument order is mismatch with common functions like strcpy().
 */
void eeprom_write_block (const void *__src, void *__dst, size_t __n);
/** \ingroup avr_eeprom
    Update a byte \a __value to EEPROM address \a __p.
 */
void eeprom_update_byte (uint8_t *__p, uint8_t __value);
/** \ingroup avr_eeprom
    Update a word \a __value to EEPROM address \a __p.
 */
void eeprom_update_word (uint16_t *__p, uint16_t __value);
/** \ingroup avr_eeprom
    Update a 32-bit double word \a __value to EEPROM address \a __p.
 */
void eeprom_update_dword (uint32_t *__p, uint32_t __value);
/** \ingroup avr_eeprom
    Update a float \a __value to EEPROM address \a __p.
 */
void eeprom_update_float (float *__p, float __value);
/** \ingroup avr_eeprom
    Update a block of \a __n bytes to EEPROM address \a __dst from \a __src.
    \note The argument order is mismatch with common functions like strcpy().
 */
void eeprom_update_block (const void *__src, void *__dst, size_t __n);
/** \name IAR C compatibility defines	*/
/*@{*/
/** \def _EEPUT
    \ingroup avr_eeprom
    Write a byte to EEPROM. Compatibility define for IAR C.	*/
/** \def __EEPUT
    \ingroup avr_eeprom
    Write a byte to EEPROM. Compatibility define for IAR C.	*/
/** \def _EEGET
    \ingroup avr_eeprom
    Read a byte from EEPROM. Compatibility define for IAR C.	*/
/** \def __EEGET
    \ingroup avr_eeprom
    Read a byte from EEPROM. Compatibility define for IAR C.	*/
/*@}*/
/* Copyright (c) 2002,2005,2007 Marek Michalkiewicz
   Copyright (c) 2007, Dean Camera
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
/* Copyright (c) 2002,2003,2005,2006,2007 Marek Michalkiewicz, Joerg Wunsch
   Copyright (c) 2007 Eric B. Weddington
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
/** \file */
/** \defgroup avr_io <avr/io.h>: AVR device-specific IO definitions
    \code #include <avr/io.h> \endcode
    This header file includes the apropriate IO definitions for the
    device that has been specified by the <tt>-mmcu=</tt> compiler
    command-line switch.  This is done by diverting to the appropriate
    file <tt>&lt;avr/io</tt><em>XXXX</em><tt>.h&gt;</tt> which should
    never be included directly.  Some register names common to all
    AVR devices are defined directly within <tt>&lt;avr/common.h&gt;</tt>,
    which is included in <tt>&lt;avr/io.h&gt;</tt>,
    but most of the details come from the respective include file.
    Note that this file always includes the following files:
    \code 
    #include <avr/sfr_defs.h>
    #include <avr/portpins.h>
    #include <avr/common.h>
    #include <avr/version.h>
    \endcode
    See \ref avr_sfr for more details about that header file.
    Included are definitions of the IO register set and their
    respective bit values as specified in the Atmel documentation.
    Note that inconsistencies in naming conventions,
    so even identical functions sometimes get different names on
    different devices.
    Also included are the specific names useable for interrupt
    function definitions as documented
    \ref avr_signames "here".
    Finally, the following macros are defined:
    - \b RAMEND
    <br>
    The last on-chip RAM address.
    <br>
    - \b XRAMEND
    <br>
    The last possible RAM location that is addressable. This is equal to 
    RAMEND for devices that do not allow for external RAM. For devices 
    that allow external RAM, this will be larger than RAMEND.
    <br>
    - \b E2END
    <br>
    The last EEPROM address.
    <br>
    - \b FLASHEND
    <br>
    The last byte address in the Flash program space.
    <br>
    - \b SPM_PAGESIZE
    <br>
    For devices with bootloader support, the flash pagesize
    (in bytes) to be used for the \c SPM instruction. 
    - \b E2PAGESIZE
    <br>
    The size of the EEPROM page.
    
*/
/* Auxiliary macro for ISR_ALIAS(). */
/** 
\file 
\@{ 
*/
/** \name Global manipulation of the interrupt flag
    The global interrupt flag is maintained in the I bit of the status
    register (SREG).
    Handling interrupts frequently requires attention regarding atomic
    access to objects that could be altered by code running within an
    interrupt context, see <util/atomic.h>.
    Frequently, interrupts are being disabled for periods of time in
    order to perform certain operations without being disturbed; see
    \ref optim_code_reorder for things to be taken into account with
    respect to compiler optimizations.
*/
/** \name Macros for writing interrupt handler functions */
/** \name ISR attributes */
/* \@} */
/* Copyright (c) 2002,2003,2005,2006,2007 Marek Michalkiewicz, Joerg Wunsch
   Copyright (c) 2007 Eric B. Weddington
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
/** \file */
/** \defgroup avr_io <avr/io.h>: AVR device-specific IO definitions
    \code #include <avr/io.h> \endcode
    This header file includes the apropriate IO definitions for the
    device that has been specified by the <tt>-mmcu=</tt> compiler
    command-line switch.  This is done by diverting to the appropriate
    file <tt>&lt;avr/io</tt><em>XXXX</em><tt>.h&gt;</tt> which should
    never be included directly.  Some register names common to all
    AVR devices are defined directly within <tt>&lt;avr/common.h&gt;</tt>,
    which is included in <tt>&lt;avr/io.h&gt;</tt>,
    but most of the details come from the respective include file.
    Note that this file always includes the following files:
    \code 
    #include <avr/sfr_defs.h>
    #include <avr/portpins.h>
    #include <avr/common.h>
    #include <avr/version.h>
    \endcode
    See \ref avr_sfr for more details about that header file.
    Included are definitions of the IO register set and their
    respective bit values as specified in the Atmel documentation.
    Note that inconsistencies in naming conventions,
    so even identical functions sometimes get different names on
    different devices.
    Also included are the specific names useable for interrupt
    function definitions as documented
    \ref avr_signames "here".
    Finally, the following macros are defined:
    - \b RAMEND
    <br>
    The last on-chip RAM address.
    <br>
    - \b XRAMEND
    <br>
    The last possible RAM location that is addressable. This is equal to 
    RAMEND for devices that do not allow for external RAM. For devices 
    that allow external RAM, this will be larger than RAMEND.
    <br>
    - \b E2END
    <br>
    The last EEPROM address.
    <br>
    - \b FLASHEND
    <br>
    The last byte address in the Flash program space.
    <br>
    - \b SPM_PAGESIZE
    <br>
    For devices with bootloader support, the flash pagesize
    (in bytes) to be used for the \c SPM instruction. 
    - \b E2PAGESIZE
    <br>
    The size of the EEPROM page.
    
*/
/* Copyright (c) 2006, 2007, 2008  Eric B. Weddington
   Copyright (c) 2011 Frédéric Nadeau
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
/* Copyright (c) 2002,2003,2005,2006,2007 Marek Michalkiewicz, Joerg Wunsch
   Copyright (c) 2007 Eric B. Weddington
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
/** \file */
/** \defgroup avr_io <avr/io.h>: AVR device-specific IO definitions
    \code #include <avr/io.h> \endcode
    This header file includes the apropriate IO definitions for the
    device that has been specified by the <tt>-mmcu=</tt> compiler
    command-line switch.  This is done by diverting to the appropriate
    file <tt>&lt;avr/io</tt><em>XXXX</em><tt>.h&gt;</tt> which should
    never be included directly.  Some register names common to all
    AVR devices are defined directly within <tt>&lt;avr/common.h&gt;</tt>,
    which is included in <tt>&lt;avr/io.h&gt;</tt>,
    but most of the details come from the respective include file.
    Note that this file always includes the following files:
    \code 
    #include <avr/sfr_defs.h>
    #include <avr/portpins.h>
    #include <avr/common.h>
    #include <avr/version.h>
    \endcode
    See \ref avr_sfr for more details about that header file.
    Included are definitions of the IO register set and their
    respective bit values as specified in the Atmel documentation.
    Note that inconsistencies in naming conventions,
    so even identical functions sometimes get different names on
    different devices.
    Also included are the specific names useable for interrupt
    function definitions as documented
    \ref avr_signames "here".
    Finally, the following macros are defined:
    - \b RAMEND
    <br>
    The last on-chip RAM address.
    <br>
    - \b XRAMEND
    <br>
    The last possible RAM location that is addressable. This is equal to 
    RAMEND for devices that do not allow for external RAM. For devices 
    that allow external RAM, this will be larger than RAMEND.
    <br>
    - \b E2END
    <br>
    The last EEPROM address.
    <br>
    - \b FLASHEND
    <br>
    The last byte address in the Flash program space.
    <br>
    - \b SPM_PAGESIZE
    <br>
    For devices with bootloader support, the flash pagesize
    (in bytes) to be used for the \c SPM instruction. 
    - \b E2PAGESIZE
    <br>
    The size of the EEPROM page.
    
*/
/** \file */
/** \defgroup avr_power <avr/power.h>: Power Reduction Management
\code #include <avr/power.h>\endcode
Many AVRs contain a Power Reduction Register (PRR) or Registers (PRRx) that 
allow you to reduce power consumption by disabling or enabling various on-board 
peripherals as needed. Some devices have the XTAL Divide Control Register
(XDIV) which offer similar functionality as System Clock Prescale
Register (CLKPR).
There are many macros in this header file that provide an easy interface
to enable or disable on-board peripherals to reduce power. See the table below.
\note Not all AVR devices have a Power Reduction Register (for example
the ATmega8). On those devices without a Power Reduction Register, the
power reduction macros are not available..
\note Not all AVR devices contain the same peripherals (for example, the LCD
interface), or they will be named differently (for example, USART and 
USART0). Please consult your device's datasheet, or the header file, to 
find out which macros are applicable to your device.
\note For device using the XTAL Divide Control Register (XDIV), when prescaler
is used, Timer/Counter0 can only be used in asynchronous mode. Keep in mind
that Timer/Counter0 source shall be less than ¼th of peripheral clock.
Therefore, when using a typical 32.768 kHz crystal, one shall not scale
the clock below 131.072 kHz.
*/
/** \addtogroup avr_power
\anchor avr_powermacros
<small>
<center>
<table border="3">
  <tr>
    <td width="10%"><strong>Power Macro</strong></td>
    <td width="15%"><strong>Description</strong></td>
  </tr>
  <tr>
    <td>power_aca_disable()</td>
    <td>Disable the Analog Comparator on PortA.</td>
  </tr>
  <tr>
    <td>power_aca_enable()</td>
    <td>Enable the Analog Comparator on PortA.</td>
  </tr>
  <tr>
    <td>power_adc_enable()</td>
    <td>Enable the Analog to Digital Converter module.</td>
  </tr>
  <tr>
    <td>power_adc_disable()</td>
    <td>Disable the Analog to Digital Converter module.</td>
  </tr>
  <tr>
    <td>power_adca_disable()</td>
    <td>Disable the Analog to Digital Converter module on PortA</td>
  </tr>
  <tr>
    <td>power_adca_enable()</td>
    <td>Enable the Analog to Digital Converter module on PortA</td>
  </tr>
  <tr>
    <td>power_evsys_disable()</td>
    <td>Disable the EVSYS module</td>
  </tr>
  <tr>
    <td>power_evsys_enable()</td>
    <td>Enable the EVSYS module</td>
  </tr>
  <tr>
    <td>power_hiresc_disable()</td>
    <td>Disable the HIRES module on PortC</td>
  </tr>
  <tr>
    <td>power_hiresc_enable()</td>
    <td>Enable the HIRES module on PortC</td>
  </tr>
   <tr>
    <td>power_lcd_enable()</td>
    <td>Enable the LCD module.</td>
  </tr>
  <tr>
    <td>power_lcd_disable().</td>
    <td>Disable the LCD module.</td>
  </tr>
  <tr>
    <td>power_pga_enable()</td>
    <td>Enable the Programmable Gain Amplifier module.</td>
  </tr>
  <tr>
    <td>power_pga_disable()</td>
    <td>Disable the Programmable Gain Amplifier module.</td>
  </tr>
  
  <tr>
    <td>power_pscr_enable()</td>
    <td>Enable the Reduced Power Stage Controller module.</td>
  </tr>
  <tr>
    <td>power_pscr_disable()</td>
    <td>Disable the Reduced Power Stage Controller module.</td>
  </tr>
  <tr>
    <td>power_psc0_enable()</td>
    <td>Enable the Power Stage Controller 0 module.</td>
  </tr>
  <tr>
    <td>power_psc0_disable()</td>
    <td>Disable the Power Stage Controller 0 module.</td>
  </tr>
  <tr>
    <td>power_psc1_enable()</td>
    <td>Enable the Power Stage Controller 1 module.</td>
  </tr>
  <tr>
    <td>power_psc1_disable()</td>
    <td>Disable the Power Stage Controller 1 module.</td>
  </tr>
  <tr>
    <td>power_psc2_enable()</td>
    <td>Enable the Power Stage Controller 2 module.</td>
  </tr>
  <tr>
    <td>power_psc2_disable()</td>
    <td>Disable the Power Stage Controller 2 module.</td>
  </tr>
  <tr>
    <td>power_ram0_enable()</td>
    <td>Enable the SRAM block 0 .</td>
  </tr>
  <tr>
    <td>power_ram0_disable()</td>
    <td>Disable the SRAM block 0. </td>
  </tr>
  <tr>
    <td>power_ram1_enable()</td>
    <td>Enable the SRAM block 1 .</td>
  </tr>
  <tr>
    <td>power_ram1_disable()</td>
    <td>Disable the SRAM block 1. </td>
  </tr>
  <tr>
    <td>power_ram2_enable()</td>
    <td>Enable the SRAM block 2 .</td>
  </tr>
  <tr>
    <td>power_ram2_disable()</td>
    <td>Disable the SRAM block 2. </td>
  </tr>
  <tr>
    <td>power_ram3_enable()</td>
    <td>Enable the SRAM block 3 .</td>
  </tr>
  <tr>
    <td>power_ram3_disable()</td>
    <td>Disable the SRAM block 3. </td>
  </tr>
  <tr>
    <td>power_rtc_disable()</td>
    <td>Disable the RTC module</td>
  </tr>
  <tr>
    <td>power_rtc_enable()</td>
    <td>Enable the RTC module</td>
  </tr>
  <tr>
    <td>power_spi_enable()</td>
    <td>Enable the Serial Peripheral Interface module.</td>
  </tr>
  <tr>
    <td>power_spi_disable()</td>
    <td>Disable the Serial Peripheral Interface module.</td>
  </tr>
  <tr>
    <td>power_spic_disable()</td>
    <td>Disable the SPI module on PortC</td>
  </tr>
  <tr>
    <td>power_spic_enable()</td>
    <td>Enable the SPI module on PortC</td>
  </tr>
  <tr>
    <td>power_spid_disable()</td>
    <td>Disable the SPI module on PortD</td>
  </tr>
  <tr>
    <td>power_spid_enable()</td>
    <td>Enable the SPI module on PortD</td>
  </tr>
  <tr>
    <td>power_tc0c_disable()</td>
    <td>Disable the TC0 module on PortC</td>
  </tr>
  <tr>
    <td>power_tc0c_enable()</td>
    <td>Enable the TC0 module on PortC</td>
  </tr>
  <tr>
    <td>power_tc0d_disable()</td>
    <td>Disable the TC0 module on PortD</td>
  </tr>
  <tr>
    <td>power_tc0d_enable()</td>
    <td>Enable the TC0 module on PortD</td>
  </tr>
  <tr>
    <td>power_tc0e_disable()</td>
    <td>Disable the TC0 module on PortE</td>
  </tr>
  <tr>
    <td>power_tc0e_enable()</td>
    <td>Enable the TC0 module on PortE</td>
  </tr>
  <tr>
    <td>power_tc0f_disable()</td>
    <td>Disable the TC0 module on PortF</td>
  </tr>
  <tr>
    <td>power_tc0f_enable()</td>
    <td>Enable the TC0 module on PortF</td>
  </tr>
  <tr>
    <td>power_tc1c_disable()</td>
    <td>Disable the TC1 module on PortC</td>
  </tr>
  <tr>
    <td>power_tc1c_enable()</td>
    <td>Enable the TC1 module on PortC</td>
  </tr>
  <tr>
    <td>power_twic_disable()</td>
    <td>Disable the Two Wire Interface module on PortC</td>
  </tr>
  <tr>
    <td>power_twic_enable()</td>
    <td>Enable the Two Wire Interface module on PortC</td>
  </tr>
  <tr>
    <td>power_twie_disable()</td>
    <td>Disable the Two Wire Interface module on PortE</td>
  </tr>
  <tr>
    <td>power_twie_enable()</td>
    <td>Enable the Two Wire Interface module on PortE</td>
  </tr>
  <tr>
    <td>power_timer0_enable()</td>
    <td>Enable the Timer 0 module.</td>
  </tr>
  <tr>
    <td>power_timer0_disable()</td>
    <td>Disable the Timer 0 module.</td>
  </tr>
  <tr>
    <td>power_timer1_enable()</td>
    <td>Enable the Timer 1 module.</td>
  </tr>
  <tr>
    <td>power_timer1_disable()</td>
    <td>Disable the Timer 1 module.</td>
  </tr>
  <tr>
    <td>power_timer2_enable()</td>
    <td>Enable the Timer 2 module.</td>
  </tr>
  <tr>
    <td>power_timer2_disable()</td>
    <td>Disable the Timer 2 module.</td>
  </tr>
  <tr>
    <td>power_timer3_enable()</td>
    <td>Enable the Timer 3 module.</td>
  </tr>
  <tr>
    <td>power_timer3_disable()</td>
    <td>Disable the Timer 3 module.</td>
  </tr>
  <tr>
    <td>power_timer4_enable()</td>
    <td>Enable the Timer 4 module.</td>
  </tr>
  <tr>
    <td>power_timer4_disable()</td>
    <td>Disable the Timer 4 module.</td>
  </tr>
  <tr>
    <td>power_timer5_enable()</td>
    <td>Enable the Timer 5 module.</td>
  </tr>
  <tr>
    <td>power_timer5_disable()</td>
    <td>Disable the Timer 5 module.</td>
  </tr>
  <tr>
    <td>power_twi_enable()</td>
    <td>Enable the Two Wire Interface module.</td>
  </tr>
  <tr>
    <td>power_twi_disable()</td>
    <td>Disable the Two Wire Interface module.</td>
  </tr>
  <tr>
    <td>power_usart_enable()</td>
    <td>Enable the USART module.</td>
  </tr>
  <tr>
    <td>power_usart_disable()</td>
    <td>Disable the USART module.</td>
  </tr>
  <tr>
    <td>power_usart0_enable()</td>
    <td>Enable the USART 0 module.</td>
  </tr>
  <tr>
    <td>power_usart0_disable()</td>
    <td>Disable the USART 0 module.</td>
  </tr>
  <tr>
    <td>power_usart1_enable()</td>
    <td>Enable the USART 1 module.</td>
  </tr>
  <tr>
    <td>power_usart1_disable()</td>
    <td>Disable the USART 1 module.</td>
  </tr>
  <tr>
    <td>power_usart2_enable()</td>
    <td>Enable the USART 2 module.</td>
  </tr>
  <tr>
    <td>power_usart2_disable()</td>
    <td>Disable the USART 2 module.</td>
  </tr>
  <tr>
    <td>power_usart3_enable()</td>
    <td>Enable the USART 3 module.</td>
  </tr>
  <tr>
    <td>power_usart3_disable()</td>
    <td>Disable the USART 3 module.</td>
  </tr>
  <tr>
    <td>power_usartc0_disable()</td>
    <td> Disable the USART0 module on PortC</td>
  </tr>
  <tr>
    <td>power_usartc0_enable()</td>
    <td> Enable the USART0 module on PortC</td>
  </tr>
  <tr>
    <td>power_usartd0_disable()</td>
    <td> Disable the USART0 module on PortD</td>
  </tr>
  <tr>
    <td>power_usartd0_enable()</td>
    <td> Enable the USART0 module on PortD</td>
  </tr>
  <tr>
    <td>power_usarte0_disable()</td>
    <td> Disable the USART0 module on PortE</td>
  </tr>
  <tr>
    <td>power_usarte0_enable()</td>
    <td> Enable the USART0 module on PortE</td>
  </tr>
  <tr>
    <td>power_usartf0_disable()</td>
    <td> Disable the USART0 module on PortF</td>
  </tr>
  <tr>
    <td>power_usartf0_enable()</td>
    <td> Enable the USART0 module on PortF</td>
  </tr>
  <tr>
    <td>power_usb_enable()</td>
    <td>Enable the USB module.</td>
  </tr>
  <tr>
    <td>power_usb_disable()</td>
    <td>Disable the USB module.</td>
  </tr>
  <tr>
    <td>power_usi_enable()</td>
    <td>Enable the Universal Serial Interface module.</td>
  </tr>
  <tr>
    <td>power_usi_disable()</td>
    <td>Disable the Universal Serial Interface module.</td>
  </tr>
  <tr>
    <td>power_vadc_enable()</td>
    <td>Enable the Voltage ADC module.</td>
  </tr>
  <tr>
    <td>power_vadc_disable()</td>
    <td>Disable the Voltage ADC module.</td>
  </tr>
  <tr>
    <td>power_all_enable()</td>
    <td>Enable all modules.</td>
  </tr>
  <tr>
    <td>power_all_disable()</td>
    <td>Disable all modules.</td>
  </tr>
</table>
</center>
</small>
@} */
static __inline void
__attribute__ ((__always_inline__))
__power_all_enable()
{
    (*(volatile uint8_t *)((0x34) + 0x20)) &= (uint8_t)~(((1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5)|(1<<6)));
}
static __inline void
__attribute__ ((__always_inline__))
__power_all_disable()
{
    (*(volatile uint8_t *)((0x34) + 0x20)) |= (uint8_t)(((1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5)|(1<<6)));
}
/* Copyright (c) 2002, 2004 Theodore A. Roth
   Copyright (c) 2004, 2007, 2008 Eric B. Weddington
   Copyright (c) 2005, 2006, 2007 Joerg Wunsch
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
/* Copyright (c) 2002,2003,2005,2006,2007 Marek Michalkiewicz, Joerg Wunsch
   Copyright (c) 2007 Eric B. Weddington
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
/** \file */
/** \defgroup avr_io <avr/io.h>: AVR device-specific IO definitions
    \code #include <avr/io.h> \endcode
    This header file includes the apropriate IO definitions for the
    device that has been specified by the <tt>-mmcu=</tt> compiler
    command-line switch.  This is done by diverting to the appropriate
    file <tt>&lt;avr/io</tt><em>XXXX</em><tt>.h&gt;</tt> which should
    never be included directly.  Some register names common to all
    AVR devices are defined directly within <tt>&lt;avr/common.h&gt;</tt>,
    which is included in <tt>&lt;avr/io.h&gt;</tt>,
    but most of the details come from the respective include file.
    Note that this file always includes the following files:
    \code 
    #include <avr/sfr_defs.h>
    #include <avr/portpins.h>
    #include <avr/common.h>
    #include <avr/version.h>
    \endcode
    See \ref avr_sfr for more details about that header file.
    Included are definitions of the IO register set and their
    respective bit values as specified in the Atmel documentation.
    Note that inconsistencies in naming conventions,
    so even identical functions sometimes get different names on
    different devices.
    Also included are the specific names useable for interrupt
    function definitions as documented
    \ref avr_signames "here".
    Finally, the following macros are defined:
    - \b RAMEND
    <br>
    The last on-chip RAM address.
    <br>
    - \b XRAMEND
    <br>
    The last possible RAM location that is addressable. This is equal to 
    RAMEND for devices that do not allow for external RAM. For devices 
    that allow external RAM, this will be larger than RAMEND.
    <br>
    - \b E2END
    <br>
    The last EEPROM address.
    <br>
    - \b FLASHEND
    <br>
    The last byte address in the Flash program space.
    <br>
    - \b SPM_PAGESIZE
    <br>
    For devices with bootloader support, the flash pagesize
    (in bytes) to be used for the \c SPM instruction. 
    - \b E2PAGESIZE
    <br>
    The size of the EEPROM page.
    
*/
/** \file */
/** \defgroup avr_sleep <avr/sleep.h>: Power Management and Sleep Modes
    \code #include <avr/sleep.h>\endcode
    Use of the \c SLEEP instruction can allow an application to reduce its
    power comsumption considerably. AVR devices can be put into different
    sleep modes. Refer to the datasheet for the details relating to the device
    you are using.
    There are several macros provided in this header file to actually
    put the device into sleep mode.  The simplest way is to optionally
    set the desired sleep mode using \c set_sleep_mode() (it usually
    defaults to idle mode where the CPU is put on sleep but all
    peripheral clocks are still running), and then call
    \c sleep_mode(). This macro automatically sets the sleep enable bit, goes 
    to sleep, and clears the sleep enable bit.
    
    Example:
    \code
    #include <avr/sleep.h>
    ...
      set_sleep_mode(<mode>);
      sleep_mode();
    \endcode
    
    Note that unless your purpose is to completely lock the CPU (until a 
    hardware reset), interrupts need to be enabled before going to sleep.
    As the \c sleep_mode() macro might cause race conditions in some
    situations, the individual steps of manipulating the sleep enable
    (SE) bit, and actually issuing the \c SLEEP instruction, are provided
    in the macros \c sleep_enable(), \c sleep_disable(), and
    \c sleep_cpu().  This also allows for test-and-sleep scenarios that
    take care of not missing the interrupt that will awake the device
    from sleep.
    Example:
    \code
    #include <avr/interrupt.h>
    #include <avr/sleep.h>
    ...
      set_sleep_mode(<mode>);
      cli();
      if (some_condition)
      {
        sleep_enable();
        sei();
        sleep_cpu();
        sleep_disable();
      }
      sei();
    \endcode
    This sequence ensures an atomic test of \c some_condition with
    interrupts being disabled.  If the condition is met, sleep mode
    will be prepared, and the \c SLEEP instruction will be scheduled
    immediately after an \c SEI instruction.  As the intruction right
    after the \c SEI is guaranteed to be executed before an interrupt
    could trigger, it is sure the device will really be put to sleep.
    Some devices have the ability to disable the Brown Out Detector (BOD) before 
    going to sleep. This will also reduce power while sleeping. If the
    specific AVR device has this ability then an additional macro is defined:
    \c sleep_bod_disable(). This macro generates inlined assembly code
    that will correctly implement the timed sequence for disabling the BOD
    before sleeping. However, there is a limited number of cycles after the
    BOD has been disabled that the device can be put into sleep mode, otherwise
    the BOD will not truly be disabled. Recommended practice is to disable
    the BOD (\c sleep_bod_disable()), set the interrupts (\c sei()), and then
    put the device to sleep (\c sleep_cpu()), like so:
    \code
    #include <avr/interrupt.h>
    #include <avr/sleep.h>
    ...
      set_sleep_mode(<mode>);
      cli();
      if (some_condition)
      {
        sleep_enable();
        sleep_bod_disable();
        sei();
        sleep_cpu();
        sleep_disable();
      }
      sei();
    \endcode
*/
/* Define an internal sleep control register and an internal sleep enable bit mask. */
/* Special casing these three devices - they are the
   only ones that need to write to more than one register. */
/** \ingroup avr_sleep
    Put the device in sleep mode. How the device is brought out of sleep mode
    depends on the specific mode selected with the set_sleep_mode() function.
    See the data sheet for your device for more details. */
/** \ingroup avr_sleep
    Put the device into sleep mode.  The SE bit must be set
    beforehand, and it is recommended to clear it afterwards.
*/
/*@}*/
/* Copyright (c) 2002, 2004 Marek Michalkiewicz
   Copyright (c) 2005, 2006, 2007 Eric B. Weddington
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
/*
   avr/wdt.h - macros for AVR watchdog timer
 */
/* Copyright (c) 2002,2003,2005,2006,2007 Marek Michalkiewicz, Joerg Wunsch
   Copyright (c) 2007 Eric B. Weddington
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
/** \file */
/** \defgroup avr_io <avr/io.h>: AVR device-specific IO definitions
    \code #include <avr/io.h> \endcode
    This header file includes the apropriate IO definitions for the
    device that has been specified by the <tt>-mmcu=</tt> compiler
    command-line switch.  This is done by diverting to the appropriate
    file <tt>&lt;avr/io</tt><em>XXXX</em><tt>.h&gt;</tt> which should
    never be included directly.  Some register names common to all
    AVR devices are defined directly within <tt>&lt;avr/common.h&gt;</tt>,
    which is included in <tt>&lt;avr/io.h&gt;</tt>,
    but most of the details come from the respective include file.
    Note that this file always includes the following files:
    \code 
    #include <avr/sfr_defs.h>
    #include <avr/portpins.h>
    #include <avr/common.h>
    #include <avr/version.h>
    \endcode
    See \ref avr_sfr for more details about that header file.
    Included are definitions of the IO register set and their
    respective bit values as specified in the Atmel documentation.
    Note that inconsistencies in naming conventions,
    so even identical functions sometimes get different names on
    different devices.
    Also included are the specific names useable for interrupt
    function definitions as documented
    \ref avr_signames "here".
    Finally, the following macros are defined:
    - \b RAMEND
    <br>
    The last on-chip RAM address.
    <br>
    - \b XRAMEND
    <br>
    The last possible RAM location that is addressable. This is equal to 
    RAMEND for devices that do not allow for external RAM. For devices 
    that allow external RAM, this will be larger than RAMEND.
    <br>
    - \b E2END
    <br>
    The last EEPROM address.
    <br>
    - \b FLASHEND
    <br>
    The last byte address in the Flash program space.
    <br>
    - \b SPM_PAGESIZE
    <br>
    For devices with bootloader support, the flash pagesize
    (in bytes) to be used for the \c SPM instruction. 
    - \b E2PAGESIZE
    <br>
    The size of the EEPROM page.
    
*/
/** \file */
/** \defgroup avr_watchdog <avr/wdt.h>: Watchdog timer handling
    \code #include <avr/wdt.h> \endcode
    This header file declares the interface to some inline macros
    handling the watchdog timer present in many AVR devices.  In order
    to prevent the watchdog timer configuration from being
    accidentally altered by a crashing application, a special timed
    sequence is required in order to change it.  The macros within
    this header file handle the required sequence automatically
    before changing any value.  Interrupts will be disabled during
    the manipulation.
    \note Depending on the fuse configuration of the particular
    device, further restrictions might apply, in particular it might
    be disallowed to turn off the watchdog timer.
    Note that for newer devices (ATmega88 and newer, effectively any
    AVR that has the option to also generate interrupts), the watchdog
    timer remains active even after a system reset (except a power-on
    condition), using the fastest prescaler value (approximately 15
    ms).  It is therefore required to turn off the watchdog early
    during program startup, the datasheet recommends a sequence like
    the following:
    \code
    #include <stdint.h>
    #include <avr/wdt.h>
    uint8_t mcusr_mirror __attribute__ ((section (".noinit")));
    void get_mcusr(void)       __attribute__((naked))       __attribute__((section(".init3")));
));
    void get_mcusr(void)
    {
      mcusr_mirror = MCUSR;
      MCUSR = 0;
      wdt_disable();
    }
    \endcode
    Saving the value of MCUSR in \c mcusr_mirror is only needed if the
    application later wants to examine the reset source, but in particular, 
    clearing the watchdog reset flag before disabling the
    watchdog is required, according to the datasheet.
*/
/**
   \ingroup avr_watchdog
   Reset the watchdog timer.  When the watchdog timer is enabled,
   a call to this instruction is required before the timer expires,
   otherwise a watchdog-initiated device reset will occur. 
*/
/**
   \ingroup avr_watchdog
   Enable the watchdog timer, configuring it for expiry after
   \c timeout (which is a combination of the \c WDP0 through
   \c WDP2 bits to write into the \c WDTCR register; For those devices 
   that have a \c WDTCSR register, it uses the combination of the \c WDP0 
   through \c WDP3 bits).
   See also the symbolic constants \c WDTO_15MS et al.
*/
static __inline__
__attribute__ ((__always_inline__))
void wdt_enable (const uint8_t value)
{
 if (!(((uint16_t) &((*(volatile uint8_t *)((0x2F) + 0x20)))) < 0x40 + 0x20) && !(((uint16_t) &((*(volatile uint8_t *)((0x30) + 0x20)))) < 0x40 + 0x20))
 {
  __asm__ __volatile__ (
   "in __tmp_reg__,__SREG__" "\n\t"
   "cli" "\n\t"
   "wdr" "\n\t"
   "sts %[CCPADDRESS],%[SIGNATURE]" "\n\t"
   "sts %[WDTREG],%[WDVALUE]" "\n\t"
   "out __SREG__,__tmp_reg__" "\n\t"
   : /* no outputs */
   : [CCPADDRESS] "n" (((uint16_t) &((*(volatile uint8_t *)((0x2F) + 0x20))))),
   [SIGNATURE] "r" ((uint8_t)0xD8),
   [WDTREG] "n" (((uint16_t) &((*(volatile uint8_t *)((0x30) + 0x20))))),
   [WDVALUE] "r" ((uint8_t)((value & 0x08 ? (1 << (5)) : 0x00)
    | (1 << (3)) | (value & 0x07) ))
   : "r0"
   );
 }
 else if (!(((uint16_t) &((*(volatile uint8_t *)((0x2F) + 0x20)))) < 0x40 + 0x20) && (((uint16_t) &((*(volatile uint8_t *)((0x30) + 0x20)))) < 0x40 + 0x20))
 {
  __asm__ __volatile__ (
   "in __tmp_reg__,__SREG__" "\n\t"
   "cli" "\n\t"
   "wdr" "\n\t"
   "sts %[CCPADDRESS],%[SIGNATURE]" "\n\t"
   "out %[WDTREG],%[WDVALUE]" "\n\t"
   "out __SREG__,__tmp_reg__" "\n\t"
   : /* no outputs */
   : [CCPADDRESS] "n" (((uint16_t) &((*(volatile uint8_t *)((0x2F) + 0x20))))),
   [SIGNATURE] "r" ((uint8_t)0xD8),
   [WDTREG] "I" ((((uint16_t) &((*(volatile uint8_t *)((0x30) + 0x20)))) - 0x20)),
   [WDVALUE] "r" ((uint8_t)((value & 0x08 ? (1 << (5)) : 0x00)
    | (1 << (3)) | (value & 0x07) ))
   : "r0"
   );
 }
 else if ((((uint16_t) &((*(volatile uint8_t *)((0x2F) + 0x20)))) < 0x40 + 0x20) && !(((uint16_t) &((*(volatile uint8_t *)((0x30) + 0x20)))) < 0x40 + 0x20))
 {
  __asm__ __volatile__ (
   "in __tmp_reg__,__SREG__" "\n\t"
   "cli" "\n\t"
   "wdr" "\n\t"
   "out %[CCPADDRESS],%[SIGNATURE]" "\n\t"
   "sts %[WDTREG],%[WDVALUE]" "\n\t"
   "out __SREG__,__tmp_reg__" "\n\t"
   : /* no outputs */
   : [CCPADDRESS] "I" ((((uint16_t) &((*(volatile uint8_t *)((0x2F) + 0x20)))) - 0x20)),
   [SIGNATURE] "r" ((uint8_t)0xD8),
   [WDTREG] "n" (((uint16_t) &((*(volatile uint8_t *)((0x30) + 0x20))))),
   [WDVALUE] "r" ((uint8_t)((value & 0x08 ? (1 << (5)) : 0x00)
    | (1 << (3)) | (value & 0x07) ))
   : "r0"
   );
 }
 else
  {
  __asm__ __volatile__ (
   "in __tmp_reg__,__SREG__" "\n\t"
   "cli" "\n\t"
   "wdr" "\n\t"
   "out %[CCPADDRESS],%[SIGNATURE]" "\n\t"
   "out %[WDTREG],%[WDVALUE]" "\n\t"
   "out __SREG__,__tmp_reg__" "\n\t"
   : /* no outputs */
   : [CCPADDRESS] "I" ((((uint16_t) &((*(volatile uint8_t *)((0x2F) + 0x20)))) - 0x20)),
   [SIGNATURE] "r" ((uint8_t)0xD8),
   [WDTREG] "I" ((((uint16_t) &((*(volatile uint8_t *)((0x30) + 0x20)))) - 0x20)),
   [WDVALUE] "r" ((uint8_t)((value & 0x08 ? (1 << (5)) : 0x00)
    | (1 << (3)) | (value & 0x07) ))
   : "r0"
   );
 }
}
static __inline__
__attribute__ ((__always_inline__))
void wdt_disable (void)
{
 if (!(((uint16_t) &((*(volatile uint8_t *)((0x2F) + 0x20)))) < 0x40 + 0x20) && !(((uint16_t) &((*(volatile uint8_t *)((0x30) + 0x20)))) < 0x40 + 0x20))
 {
        uint8_t temp_wd;
        __asm__ __volatile__ (
    "in __tmp_reg__,__SREG__" "\n\t"
    "cli" "\n\t"
    "wdr" "\n\t"
    "sts %[CCPADDRESS],%[SIGNATURE]" "\n\t"
    "lds %[TEMP_WD],%[WDTREG]" "\n\t"
    "cbr %[TEMP_WD],%[WDVALUE]" "\n\t"
    "sts %[WDTREG],%[TEMP_WD]" "\n\t"
    "out __SREG__,__tmp_reg__" "\n\t"
    : /*no output */
    : [CCPADDRESS] "n" (((uint16_t) &((*(volatile uint8_t *)((0x2F) + 0x20))))),
    [SIGNATURE] "r" ((uint8_t)0xD8),
    [WDTREG] "n" (((uint16_t) &((*(volatile uint8_t *)((0x30) + 0x20))))),
    [TEMP_WD] "d" (temp_wd),
    [WDVALUE] "n" (1 << 3)
    : "r0"
    );
 }
 else if (!(((uint16_t) &((*(volatile uint8_t *)((0x2F) + 0x20)))) < 0x40 + 0x20) && (((uint16_t) &((*(volatile uint8_t *)((0x30) + 0x20)))) < 0x40 + 0x20))
 {
        uint8_t temp_wd;
        __asm__ __volatile__ (
    "in __tmp_reg__,__SREG__" "\n\t"
    "cli" "\n\t"
    "wdr" "\n\t"
    "sts %[CCPADDRESS],%[SIGNATURE]" "\n\t"
    "in %[TEMP_WD],%[WDTREG]" "\n\t"
    "cbr %[TEMP_WD],%[WDVALUE]" "\n\t"
    "out %[WDTREG],%[TEMP_WD]" "\n\t"
    "out __SREG__,__tmp_reg__" "\n\t"
    : /*no output */
    : [CCPADDRESS] "n" (((uint16_t) &((*(volatile uint8_t *)((0x2F) + 0x20))))),
    [SIGNATURE] "r" ((uint8_t)0xD8),
    [WDTREG] "I" ((((uint16_t) &((*(volatile uint8_t *)((0x30) + 0x20)))) - 0x20)),
    [TEMP_WD] "d" (temp_wd),
    [WDVALUE] "n" (1 << 3)
    : "r0"
    );
 }
 else if ((((uint16_t) &((*(volatile uint8_t *)((0x2F) + 0x20)))) < 0x40 + 0x20) && !(((uint16_t) &((*(volatile uint8_t *)((0x30) + 0x20)))) < 0x40 + 0x20))
 {
        uint8_t temp_wd;
        __asm__ __volatile__ (
    "in __tmp_reg__,__SREG__" "\n\t"
    "cli" "\n\t"
    "wdr" "\n\t"
    "out %[CCPADDRESS],%[SIGNATURE]" "\n\t"
    "lds %[TEMP_WD],%[WDTREG]" "\n\t"
    "cbr %[TEMP_WD],%[WDVALUE]" "\n\t"
    "sts %[WDTREG],%[TEMP_WD]" "\n\t"
    "out __SREG__,__tmp_reg__" "\n\t"
    : /*no output */
    : [CCPADDRESS] "I" ((((uint16_t) &((*(volatile uint8_t *)((0x2F) + 0x20)))) - 0x20)),
    [SIGNATURE] "r" ((uint8_t)0xD8),
    [WDTREG] "n" (((uint16_t) &((*(volatile uint8_t *)((0x30) + 0x20))))),
    [TEMP_WD] "d" (temp_wd),
    [WDVALUE] "n" (1 << 3)
    : "r0"
    );
 }
 else
 {
        uint8_t temp_wd;
        __asm__ __volatile__ (
    "in __tmp_reg__,__SREG__" "\n\t"
    "cli" "\n\t"
    "wdr" "\n\t"
    "out %[CCPADDRESS],%[SIGNATURE]" "\n\t"
    "in %[TEMP_WD],%[WDTREG]" "\n\t"
    "cbr %[TEMP_WD],%[WDVALUE]" "\n\t"
    "out %[WDTREG],%[TEMP_WD]" "\n\t"
    "out __SREG__,__tmp_reg__" "\n\t"
    : /*no output */
    : [CCPADDRESS] "I" ((((uint16_t) &((*(volatile uint8_t *)((0x2F) + 0x20)))) - 0x20)),
    [SIGNATURE] "r" ((uint8_t)0xD8),
    [WDTREG] "I" ((((uint16_t) &((*(volatile uint8_t *)((0x30) + 0x20)))) - 0x20)),
    [TEMP_WD] "d" (temp_wd),
    [WDVALUE] "n" (1 << 3)
    : "r0"
    );
 }
}
/**
   \ingroup avr_watchdog
   Symbolic constants for the watchdog timeout.  Since the watchdog
   timer is based on a free-running RC oscillator, the times are
   approximate only and apply to a supply voltage of 5 V.  At lower
   supply voltages, the times will increase.  For older devices, the
   times will be as large as three times when operating at Vcc = 3 V,
   while the newer devices (e. g. ATmega128, ATmega8) only experience
   a negligible change.
   Possible timeout values are: 15 ms, 30 ms, 60 ms, 120 ms, 250 ms,
   500 ms, 1 s, 2 s.  (Some devices also allow for 4 s and 8 s.)
   Symbolic constants are formed by the prefix
   \c WDTO_, followed by the time.
   Example that would select a watchdog timer expiry of approximately
   500 ms:
   \code
   wdt_enable(WDTO_500MS);
   \endcode
*/
/** \ingroup avr_watchdog
    See \c WDTO_15MS */
/** \ingroup avr_watchdog
    See \c WDTO_15MS */
/** \ingroup avr_watchdog
    See \c WDTO_15MS */
/** \ingroup avr_watchdog
    See \c WDTO_15MS */
/** \ingroup avr_watchdog
    See \c WDTO_15MS */
/** \ingroup avr_watchdog
    See \c WDTO_15MS */
/** \ingroup avr_watchdog
    See \c WDTO_15MS */
/** \ingroup avr_watchdog
    See \c WDTO_15MS
    Note: This is only available on the 
    ATtiny2313, 
    ATtiny24, ATtiny44, ATtiny84, ATtiny84A,
    ATtiny25, ATtiny45, ATtiny85, 
    ATtiny261, ATtiny461, ATtiny861, 
    ATmega48, ATmega88, ATmega168,
    ATmega48P, ATmega88P, ATmega168P, ATmega328P,
    ATmega164P, ATmega324P, ATmega644P, ATmega644,
    ATmega640, ATmega1280, ATmega1281, ATmega2560, ATmega2561,
    ATmega8HVA, ATmega16HVA, ATmega32HVB,
    ATmega406, ATmega1284P,
    AT90PWM1, AT90PWM2, AT90PWM2B, AT90PWM3, AT90PWM3B, AT90PWM216, AT90PWM316,
    AT90PWM81, AT90PWM161,
    AT90USB82, AT90USB162,
    AT90USB646, AT90USB647, AT90USB1286, AT90USB1287,
    ATtiny48, ATtiny88.
    Note: This value does <em>not</em> match the bit pattern of the
    respective control register.  It is solely meant to be used together
    with wdt_enable().
    */
/** \ingroup avr_watchdog
    See \c WDTO_15MS
    Note: This is only available on the 
    ATtiny2313, 
    ATtiny24, ATtiny44, ATtiny84, ATtiny84A,
    ATtiny25, ATtiny45, ATtiny85, 
    ATtiny261, ATtiny461, ATtiny861, 
    ATmega48, ATmega48A, ATmega48PA, ATmega88, ATmega168,
    ATmega48P, ATmega88P, ATmega168P, ATmega328P,
    ATmega164P, ATmega324P, ATmega644P, ATmega644,
    ATmega640, ATmega1280, ATmega1281, ATmega2560, ATmega2561,
    ATmega8HVA, ATmega16HVA, ATmega32HVB,
    ATmega406, ATmega1284P,
    ATmega2564RFR2, ATmega256RFR2, ATmega1284RFR2, ATmega128RFR2, ATmega644RFR2, ATmega64RFR2
    AT90PWM1, AT90PWM2, AT90PWM2B, AT90PWM3, AT90PWM3B, AT90PWM216, AT90PWM316,
    AT90PWM81, AT90PWM161,
    AT90USB82, AT90USB162,
    AT90USB646, AT90USB647, AT90USB1286, AT90USB1287,
    ATtiny48, ATtiny88,
    ATxmega16a4u, ATxmega32a4u,
    ATxmega16c4, ATxmega32c4,
    ATxmega128c3, ATxmega192c3, ATxmega256c3.
    Note: This value does <em>not</em> match the bit pattern of the
    respective control register.  It is solely meant to be used together
    with wdt_enable().
    */
// for consistency, ROM_SIZE + EEPROM_SIZE
// tk.h : misc handy stuff
// Copyright (C) 2015-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
/////
// tk.h
// misc tricks which need to be available before other includes,
// but which don't need to be repeated in every source file
////
// AVR GCC has no boolean type by default
// (this isn't native bool, but it's mostly okay)
// create a way to include files defined at the command line,
// like with "gcc -DCONFIGFILE=foo.h"
// use it like this:
//#include incfile(CONFIGFILE)
// cause a build failure if `condition` is true
// (gcc compile trick taken from an old version of include/linux/kernel.h)
// more info here:
// https://scaryreasoner.wordpress.com/2009/02/28/checking-sizeof-at-compile-time/
// cause a build failure if `condition` is false
// arch/attiny1634.h: attiny1634 support header
// Copyright (C) 2014-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
// fill in missing values from Atmel's headers
////////// clock speed / delay stuff //////////
inline void mcu_clock_speed();
///// clock dividers
inline void clock_prescale_set(uint8_t n);
// TODO? allow hwdef to define a base clock speed,
//       and adjust these values accordingly
typedef enum
{
    // datasheet 6.5.2, CLKPR - Clock Prescale Register
    clock_div_1 = 0, // 8 MHz
    clock_div_2 = 1, // 4 MHz
    clock_div_4 = 2, // 2 MHz
    clock_div_8 = 3, // 1 MHz
    clock_div_16 = 4, // 500 kHz
    clock_div_32 = 5, // 250 kHz
    clock_div_64 = 6, // 125 kHz
    clock_div_128 = 7, // 62.5 kHz
    clock_div_256 = 8, // 31.75 kHz
} clock_div_t;
////////// ADC voltage / temperature //////////
//#define VOLTAGE_ADC_DIDR DIDR0  // set this in hwdef
// DS table 19-3, 19-4, 1.1V ref / VCC
// (1 << V_REF) | (THERM_CHANNEL)
// DS table 19-3, 19-4, internal sensor / 1.1V ref
// [refs1, refs0, refen, adc0en, mux3, mux2, mux1, mux0]
// refs=0b10 : internal 1.1V ref
// mux=0b1110 : internal temperature sensor
inline void mcu_set_admux_therm();
inline void mcu_set_admux_voltage();
inline void mcu_adc_sleep_mode();
inline void mcu_adc_start_measurement();
inline void mcu_adc_off();
// NOP because interrupt flag clears itself
inline uint16_t mcu_adc_result();
// return Volts * 50, range 0 to 5.10V
inline uint8_t mcu_vdd_raw2cooked(uint16_t measurement);
inline uint8_t mcu_vdivider_raw2cooked(uint16_t measurement);
// return (temp in Kelvin << 6)
inline uint16_t mcu_temp_raw2cooked(uint16_t measurement);
inline uint8_t mcu_adc_lsb();
////////// WDT //////////
inline void mcu_wdt_active();
inline void mcu_wdt_standby();
inline void mcu_wdt_stop();
// NOP because interrupt flag clears itself
////////// PCINT - pin change interrupt (e-switch) //////////
// set these in hwdef
//#define SWITCH_PORT  PINA
//#define SWITCH_VECT  PCINT0_vect
// NOP because interrupt flag clears itself
inline void mcu_pcint_on();
inline void mcu_pcint_off();
////////// misc //////////
void reboot();
inline void prevent_reboot_loop();
/********* User-configurable options *********/
// config-default.h: Default configuration for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
/*
 * This file specifies the default settings for Anduril.
 *
 * These settings can be overridden per build target, in cfg-*.h files...
 * ... but most are not.  So changing one here will make it change in
 * almost every build target.
 *
 * Some configurable settings are also in other *.h files.
 */
/********* User-configurable options *********/
// low voltage protection (also required for battery check mode)
// overheat protection
// Default value for temperature unit (1 = Celsius, 2 = Fahrenheit)
// Default number output mode (1 = Digits, 2 = Morse Code)
// sloppy temperature sensor needs bigger error margin
// Comment out to disable automatic calibration on factory reset
//   - If so, be sure to set THERM_CAL_OFFSET to the correct calibration offset
//   - Calibration can still be overridden in temperature check mode
// Or uncomment to use the default auto-calibrate on factory reset
//
// To determine THERM_CAL_OFFSET, comment out USE_THERM_AUTOCALIBRATE to
// disable auto-calibration, compile and flash, let flashlight rest at a known
// temperature, then enter temp check mode (do NOT enter calibration mode).
//
// THERM_CAL_OFFSET = known_temperature - temp_check_blinks + THERM_CAL_OFFSET
//
// (include THERM_CAL_OFFSET in sum as it might already be a non-zero number)
// Include a simplified UI for non-enthusiasts?
// a child UI (more limited simple UI and lowered defaults)
///// Ramp mode options /////
// button timing for turning light on/off:
// B_PRESS_T:   activate as soon as button is pressed
// B_RELEASE_T: activate when user lets go of button
// B_TIMEOUT_T: activate when we're sure the user won't double-click
// defaults are release on, timeout off
// default ramp style: 0 = smooth, 1 = stepped
// smooth ramp speed: 1, 2, 3, 4, ...  for 1X speed, 1/2, 1/3rd, 1/4th, ...
// after ramping, how long until the direction resets to "up"?
// add runtime option for whether hold-from-off should ramp or stay at moon
// default to NOT ramp after moon mode
// short blip when crossing from "click" to "hold" from off
// (helps the user hit moon mode exactly, instead of holding too long
//  or too short)
// short blips while ramping
//#define BLINK_AT_RAMP_FLOOR
//#define BLINK_AT_STEPS  // whenever a discrete ramp mode is passed in smooth mode
// Uncomment for Anduril1 "Ramp 2C" behavior:
//   - Ramp 2C goes to turbo (advanced UI) or ceiling (simple UI), like in Anduril1
// Or comment out to use Anduril2 behavior instead:
//   - Ramp 2C goes to ceiling, unless already at ceiling or in simple UI.
//     (Advanced UI ceiling 2C goes to turbo)
//#define USE_2C_MAX_TURBO
// Or uncomment to let the user decide which style they want:
// 0 = no turbo
// 1 = A1 style: Off 2C = ceil, On 2C = turbo
// 2 = A2 style: Off 2C = ceil, On 2C = ceil, Ramped ceil 2C = turbo
// All styles allow momentary turbo in advanced UI
//#define DEFAULT_2C_STYLE 2  // default to Anduril 2 style
//#define DEFAULT_2C_STYLE_SIMPLE 0  // no turbo at all
// make the ramps configurable by the user
// adds a runtime option to switch between automatic memory (default)
// and manual memory (only available if compiled in)
// (manual memory makes 1-click-from-off start at the same level each time)
// (the level can be set explicitly with 10 clicks from on,
// or the user can go back to automatic with 10H)
// if enabled, user can use "hybrid memory"
// The light will use automatic or manual memory level, depending on how long
// the light was off.  Short off = automatic, long off = manual.
// This also remaps 10C/10H:
// - 10C toggles manual mem on/off at current level.
// - 10H configures the timer value.
// enable sunset timer (ramp-down and automatic shutoff)
// timer is available in regular ramp mode and candle mode
// optionally make gradual ticks happen faster
// Affects: thermal regulation speed, sunset mode, maybe other features
// (default is calibrated for 8-bit PWM,
//  but 10-bit should set this value to 4 instead of 1)
///// What to do when power is connected /////
// factory reset function erases user's runtime configuration in eeprom
//#define USE_SOFT_FACTORY_RESET  // only needed on models which can't use hold-button-at-boot
// dual-switch support (second switch is a tail clicky)
// (currently incompatible with factory reset)
//#define START_AT_MEMORIZED_LEVEL
///// extra modes (enable / disable / configure each mode) /////
// include a function to blink out the firmware version
// enable the battery check mode (shows remaining charge) (requires USE_LVP)
// battery readout style (pick one)
// TODO: allow VpT and 4-bar simultaneously,
//       so one can be in "simple mode" and the other in "advanced mode"
//#define BATTCHECK_8bars  // FIXME: breaks build
//#define BATTCHECK_4bars  // FIXME: breaks build
    // battcheck displays 1.25V instead of 1.2V
// allow the user to calibrate the voltage readings?
// (adjust in 0.05V increments from -0.30V to +0.30V)
// (1 = -0.30V, 2 = -0.25V, ... 7 = 0V, ... 13 = +0.30V)
// enable beacon mode
// enable/disable various strobe modes
// boring strobes nobody really likes, but sometimes flashlight companies want
// (these replace the fun strobe group,
//  so don't enable them at the same time as any of the above strobes)
//#define USE_POLICE_STROBE_MODE
//#define USE_SOS_MODE_IN_FF_GROUP  // put SOS in the "boring strobes" mode
// enable a mode for locking the light for safe carry
// should lockout mode function as a momentary moon mode?
// add an optional setting to lock the light after being off for a while
// enable momentary mode
// enable tactical mode
// enable a shortcut for +10 in number entry mode
// (click for +1, hold for +10)
// cut clock speed at very low modes for better efficiency
// (defined here so config files can override it)
// if the aux LEDs oscillate between "full battery" and "empty battery"
// while in "voltage" mode, enable this to reduce the amplitude of
// those oscillations
// if there's tint ramping, allow user to set it smooth or stepped
// Use "smooth steps" to soften on/off and step changes
// on MCUs with enough room for extra stuff like this
// 0 = none, 1 = smooth, 2+ = undefined
// by default, allow user to set the channel for each strobe-group mode
// (but allow disabling this feature per build)
/********* specific settings for known driver types *********/
// Anduril config for Emisar 2ch+FET-joined-into-1-channel
// Copyright (C) 2024 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
// This is mostly just used on the Emisar D4S w/ lighted switch,
// which uses a 2-channel driver but only actually uses 1 set of LEDs
// (so instead of the usual 2ch or 2ch-fet firmware, it needs something else)
// Intl-Outdoor (Hank)'s config options for Anduril
// Copyright (C) 2021-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
// config preferences for Hank Wang of Intl-Outdoor (Emisar, Noctigon)
// RGB aux LEDs should use rainbow cycling mode
// to impress new customers
// (people usually change it to voltage mode later though)
//#define RGB_LED_OFF_DEFAULT 0x18  // low, rainbow
// half a second per color in rainbow mode
//#define RGB_RAINBOW_SPEED 0x03
// Allow 3C (or 6C) in Simple UI (toggle smooth or stepped ramping)
// allow Aux Config and Strobe Modes in Simple UI
// double click while on goes to full-power turbo, not ramp ceiling
// for consistency with KR4 (not otherwise necessary though)
//#undef RGB_SPIN //disable RGB spin mode
// this light has three aux LED channels: R, G, B
// the aux LEDs are front-facing, so turn them off while main LEDs are on
// it also has an independent LED in the button
// enabling this option breaks the button LED
// channel modes...
// CM_CH1      -- linear ch1 only
// CM_CH1_FET  -- linear ch1 + DD FET
// strobes on this light should use the same channel as the ramp
// blink numbers on the main LEDs by default (but allow user to change it)
// Output estimates:
// - linear ch1 only: 2500 lm
// - ch1 + DD FET: 3500 lm
//   (tested on a D4S with Osram W2 LEDs, with a mediocre battery at 3.7V)
//   (LuxWad estimated 6000 lm (uncalibrated) on a full high-amp cell)
//   (I picked 4500 lm as a rough realistic estimate)
// - linear ch2 only: 0 (not connected)
// - moon: 0.7 lm at PWM 1/4096, 0.15 lm at DSM 0/32640
// delta-sigma modulated PWM (0b0HHHHHHHHLLLLLLL = 0, 8xHigh, 7xLow bits)
// (max is (255 << 7), because it's 8-bit PWM plus 7 bits of DSM)
//
// linear ch1 only (copied from noctigon-m44 ramp)
// level_calc.py 5.01 1 150 7135 0 0.2 2000 --pwm 32640
//
// linear+FET linear ch1 segment
// level_calc.py 4.85 2 150 7135 0 0.5 2500 FET 1 10 4500 --pwm 32640
//
// linear+FET DD FET segment
// level_calc.py 4.85 2 150 7135 0 0.5 2500 FET 1 10 4500 --pwm 255
// 10, 30, 50, [70], 90, 110, [130]
// safe limit highest regulated power (no FET or turbo)
// 10, 40, [70], 100, [130]
// stop panicking at ~2500 lm
// use the brightest setting for strobe
// slow down party strobe; this driver can't pulse for less than 1ms
// (in linear-only mode ... but FET mode can pulse a much shorter time)
// the default of 26 looks a bit flat, so increase it
// the power regulator is a bit slow, so push it harder for a quick response from off
// don't blink while ramping
// Emisar 2-channel-plus-FET-joined-into-1-channel
// Copyright (C) 2024 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
/*
 * Pin / Name / Function
 *   1    PA6   ch2 LED PWM (linear) (PWM1B) (unused)
 *   2    PA5   R: red aux LED (PWM0B)
 *   3    PA4   G: green aux LED
 *   4    PA3   B: blue aux LED
 *   5    PA2   button LED
 *   6    PA1   Opamp 2 enable (channel 2 LEDs) (unused)
 *   7    PA0   Opamp 1 enable (channel 1 LEDs)
 *   8    GND   GND
 *   9    VCC   VCC
 *  10    PC5   (none)
 *  11    PC4   (none)
 *  12    PC3   RESET
 *  13    PC2   (none)
 *  14    PC1   SCK
 *  15    PC0   ch1 LED PWM (FET) (PWM0A, 8-bit)
 *  16    PB3   ch1 LED PWM (linear) (PWM1A)
 *  17    PB2   MISO
 *  18    PB1   MOSI / battery voltage (ADC6)
 *  19    PB0   (none)
 *  20    PA7   e-switch (PCINT7)
 *      ADC12   thermal sensor
 *
 * This is used for lights with only 1 set of main LEDs, when using the
 * 2-channel driver internally.  This allows the D4S to have a lighted button.
 * Hank typically connects only linear ch1 and sometimes the DD FET
 * to the main LEDs, leaving linear ch2 completely unused.  Support is
 * included in an extra channel mode in case modders decide to use it.
 * It can raise the maximum regulated level.
 */
// allow using aux LEDs as extra channel modes
// channel modes for RGB aux LEDs
// Copyright (C) 2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
// include / exclude field based on compile options
void set_level_auxred(uint8_t level);
void set_level_auxyel(uint8_t level);
void set_level_auxgrn(uint8_t level);
void set_level_auxcyn(uint8_t level);
void set_level_auxblu(uint8_t level);
void set_level_auxprp(uint8_t level);
void set_level_auxwht(uint8_t level);
uint8_t gradual_tick_null(uint8_t gt);
// channel modes:
// * 0. linear (ch1) only
// * 1. linear (ch1) + DD FET  <-- Hank's primary config, as far as I can tell
// x 2. linear (both) + DD FET (not used)
enum channel_modes_e {
    CM_CH1 = 0,
    CM_CH1_FET, // <-- default
    //CM_BOTH_FET,
    CM_AUXRED, CM_AUXYEL, CM_AUXGRN, CM_AUXCYN, CM_AUXBLU, CM_AUXPRP, CM_AUXWHT
};
// right-most bit first, modes are in fedcba9876543210 order
//#define USE_CHANNEL_MODE_ARGS
// _, _, _, 128=middle CCT, 0=warm-to-cool
//#define CHANNEL_MODE_ARGS     0,0,0,RGB_AUX_CM_ARGS
// linear-only ramp
// linear part of linear+FET ramp
// DD FET part of linear+FET ramp
// PWM parameters of both channels are tied together because they share a counter
// (max is (255 << 7), because it's 8-bit PWM plus 7 bits of DSM)
// timer interrupt for DSM
// main LEDs, linear
uint16_t ch1_dsm_lvl;
uint8_t ch1_pwm, ch1_dsm;
// 2nd LEDs, linear (unused)
// main LEDs, DD FET
// e-switch
// attiny1634 voltage divider common defs
// Copyright (C) 2020-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
// pin to ADC mappings are in DS table 19-4
// DIDR0/DIDR1 mappings are in DS section 19.13.5, 19.13.6
// DS tables 19-3, 19-4
// Bit   7     6     5      4     3    2    1    0
//     REFS1 REFS0 REFEN ADC0EN MUX3 MUX2 MUX1 MUX0
// MUX[3:0] = 0, 1, 1, 0 for ADC6 / PB1
// divided by ...
// REFS[1:0] = 1, 0 for internal 1.1V reference
// other bits reserved
// Raw ADC readings at 4.4V and 2.2V
// calibrate the voltage readout here
// estimated / calculated values are:
//   (voltage - D1) * (R2/(R2+R1) * 1024 / 1.1)
// D1, R1, R2 = 0, 330, 100
//#define ADC_44 (4*981)  // raw value at 4.40V
//#define ADC_22 (4*489)  // raw value at 2.20V
// this light has aux LEDs under the optic
inline void hwdef_setup() {
    // enable output ports
    
   (*(volatile uint8_t *)((0x08) + 0x20)) 
        = (1 << 
                0
                       );
    
   (*(volatile uint8_t *)((0x0C) + 0x20)) 
        = (1 << 
                3
                       );
    
   (*(volatile uint8_t *)((0x10) + 0x20)) 
        = (1 << 
                6
                       )
         | (1 << 
                5
                            )
         | (1 << 
                4
                            )
         | (1 << 
                3
                            )
         | (1 << 
                2
                              )
         | (1 << 
                0
                              )
         | (1 << 
                1
                              )
         ;
    // configure PWM
    // Setup PWM. F_pwm = F_clkio / 2 / N / TOP, where N = prescale factor, TOP = top of counter
    // pre-scale for timer: N = 1
    // Linear opamp PWM for both main and 2nd LEDs (10-bit)
    // WGM1[3:0]: 1,0,1,0: PWM, Phase Correct, adjustable (DS table 12-5)
    // CS1[2:0]:    0,0,1: clk/1 (No prescaling) (DS table 12-6)
    // COM1A[1:0]:    1,0: PWM OC1A in the normal direction (DS table 12-4)
    // COM1B[1:0]:    1,0: PWM OC1B in the normal direction (DS table 12-4)
    
   (*(volatile uint8_t *)(0x72)) 
          = (1<<
                1
                     ) | (0<<
                              0
                                   ) // adjustable PWM (TOP=ICR1) (DS table 12-5)
           | (1<<
                7
                      ) | (0<<
                              6
                                    ) // PWM 1A in normal direction (DS table 12-4)
           | (1<<
                5
                      ) | (0<<
                              4
                                    ) // PWM 1B in normal direction (DS table 12-4)
           ;
    
   (*(volatile uint8_t *)(0x71)) 
          = (0<<
                2
                    ) | (0<<
                              1
                                  ) | (1<<
                                          0
                                              ) // clk/1 (no prescaling) (DS table 12-6)
           | (1<<
                4
                     ) | (0<<
                              3
                                   ) // phase-correct adjustable PWM (DS table 12-5)
           ;
    // FET PWM (8-bit; this channel can't do 10-bit)
    // WGM0[2:0]: 0,0,1: PWM, Phase Correct, 8-bit (DS table 11-8)
    // CS0[2:0]:  0,0,1: clk/1 (No prescaling) (DS table 11-9)
    // COM0A[1:0]:  1,0: PWM OC0A in the normal direction (DS table 11-4)
    // COM0B[1:0]:  1,0: PWM OC0B in the normal direction (DS table 11-7)
    
   (*(volatile uint8_t *)((0x1B) + 0x20)) 
          = (0<<
                1
                     ) | (1<<
                              0
                                   ) // 8-bit (TOP=0xFF) (DS table 11-8)
           | (1<<
                7
                      ) | (0<<
                              6
                                    ) // PWM 0A in normal direction (DS table 11-4)
           //| (1<<COM0B1) | (0<<COM0B0)  // PWM 0B in normal direction (DS table 11-7)
           ;
    
   (*(volatile uint8_t *)((0x1A) + 0x20)) 
          = (0<<
                2
                    ) | (0<<
                              1
                                  ) | (1<<
                                          0
                                              ) // clk/1 (no prescaling) (DS table 11-9)
           | (0<<
                3
                     ) // phase-correct PWM (DS table 11-8)
           ;
    // set PWM resolution
    
   (*(volatile uint16_t *)(0x68)) 
           = 255;
    // set up interrupt for delta-sigma modulation
    // (moved to hwdef.c functions so it can be enabled/disabled based on ramp level)
    //DSM_INTCTRL |= DSM_OVF_bm;  // interrupt once for each timer cycle
    // set up e-switch
    
   (*(volatile uint8_t *)((0x12) + 0x20)) 
              = (1 << 
                      7
                                ); // pull-up for e-switch
    
   (*(volatile uint8_t *)((0x27) + 0x20)) 
                = (1 << 
                        7
                                    ); // enable pin change interrupt
}
/********* Include headers which need to be before FSM *********/
// enable FSM features needed by basic ramping functions
// ramp-mode-fsm.h: FSM config for ramping functions in Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
// enable FSM's ramping features
// do smooth adjustments when compensating for temperature
// brightness to use when no memory is set
// FIXME: this is only here to stop an error in fsm-ramping.c,
//        which should be fixed by using a different symbol instead
//        (like BUTTON_LED_BRIGHT_LEVEL or RAMP_HALFWAY_LEVEL or something)
// requires the ability to measure time while "off"
// ensure the jump start feature gets compiled in if needed
// include an extra config mode for random stuff which doesn't fit elsewhere
// factory-reset-fsm.h: FSM config options to enable factory reset in Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
// battcheck-mode-fsm.h: FSM config for battery check mode in Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
    // show voltage colors for a few seconds after going to standby
        // level at which to switch from low to high aux brightness
// lockout-mode-fsm.h: FSM config for lockout mode in Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
// autolock function requires the ability to measure time while "off"
// enable FSM features needed by strobe modes
// strobe-modes-fsm.h: FSM config for strobe modes in Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
// enable the random number generator if we need it
// party strobe uses really short pulses
// candle mode is basically a bunch of stacked random triangle waves
// the presence of strobe mode(s) affects how many eeprom bytes we need,
// so it's relevant for FSM configuration
// internal numbering for strobe modes
typedef enum {
    party_strobe_e,
    tactical_strobe_e,
    police_color_strobe_e,
    lightning_storm_e,
    candle_mode_e,
    firework_mode_e,
    lighthouse_mode_e,
    broken_fluorescent_mode_e,
    bike_flasher_e,
    strobe_mode_END
} strobe_mode_te;
//const int NUM_STROBES = strobe_mode_END;
// figure out how many bytes of eeprom are needed,
// based on which UI features are enabled
// (include this one last)
// load-save-config-fsm.h: FSM config for eeprom configuration in Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
// load into a custom RAM location instead of FSM's default byte array
// let FSM know this config struct exists
typedef struct Config {
    ///// ramp vars
    uint8_t ramp_style;
        uint8_t ramp_2c_style;
        uint8_t ramp_floors[4];
        uint8_t ramp_ceils [4];
        uint8_t ramp_stepss[4];
        uint8_t simple_ui_active;
            uint8_t ramp_2c_style_simple;
        uint8_t child_ui_active;
        uint8_t child_ui_floor;
        uint8_t child_ui_ceil;
        uint8_t saved_ramp_style;
        uint8_t dont_ramp_after_moon;
        uint8_t manual_memory;
            uint8_t manual_memory_timer;
    ///// channel modes / color modes
        uint8_t channel_mode;
        uint16_t channel_modes_enabled;
            uint8_t manual_memory_channel_mode;
            uint8_t blink_channel;
    ///// Smooth animation between steps, and for on/off
        uint8_t smooth_steps_style;
    ///// strobe / blinky mode settings
        uint8_t strobe_type;
        uint8_t strobe_delays[2];
        uint8_t bike_flasher_brightness;
        uint8_t beacon_seconds;
        uint8_t lightning_busy_factor;
        uint8_t candle_amplitude;
        uint8_t candle_wobble_style;
        uint8_t firework_brightness;
        uint8_t lighthouse_delay;
        uint8_t fluoresent_brightness;
    ///// voltage and temperature
        uint8_t voltage_correction;
        uint8_t therm_ceil;
        int8_t therm_cal_offset;
        int8_t temp_unit; // 1 for Â°C, 2 for Â°F
    ///// aux LEDs
        uint8_t rgb_led_off_mode;
        uint8_t rgb_led_lockout_mode;
            uint8_t post_off_voltage;
    ///// misc other mode settings
        uint8_t autolock_time;
        uint8_t tactical_levels[3];
    ///// Number Format
        uint8_t num_mode;
    ///// hardware config / globals menu
        uint8_t jump_start_level;
} Config;
// auto-detect how many eeprom bytes
// declare this so FSM can see it,
// but define its values in a file which loads later
Config cfg;
/********* bring in FSM / SpaghettiMonster *********/
// spaghetti-monster.h: UI toolkit / microkernel for e-switch flashlights.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
/*
 * SpaghettiMonster: Generic foundation code for e-switch flashlights.
 * Other possible names:
 * - FSM
 * - RoundTable
 * - Mostly Harmless
 * - ...
 */
////////// include all the .h files //////////
// include project definitions to help with recognizing symbols
// fsm-events.h: Event-handling functions for SpaghettiMonster.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
/* Copyright (c) 2002-2007  Marek Michalkiewicz
   Copyright (c) 2006, Carlos Lamas
   Copyright (c) 2009-2010, Jan Waclawek
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
/*
   pgmspace.h
   Contributors:
     Created by Marek Michalkiewicz <marekm@linux.org.pl>
     Eric B. Weddington <eric@ecentral.com>
     Wolfgang Haidinger <wh@vmars.tuwien.ac.at> (pgm_read_dword())
     Ivanov Anton <anton@arc.com.ru> (pgm_read_float())
 */
/** \file */
/** \defgroup avr_pgmspace <avr/pgmspace.h>: Program Space Utilities
    \code
    #include <avr/io.h>
    #include <avr/pgmspace.h>
    \endcode
    The functions in this module provide interfaces for a program to access
    data stored in program space (flash memory) of the device.  In order to
    use these functions, the target device must support either the \c LPM or
    \c ELPM instructions.
    \note These functions are an attempt to provide some compatibility with
    header files that come with IAR C, to make porting applications between
    different compilers easier.  This is not 100% compatibility though (GCC
    does not have full support for multiple address spaces yet).
    \note If you are working with strings which are completely based in ram,
    use the standard string functions described in \ref avr_string.
    \note If possible, put your constant tables in the lower 64 KB and use
    pgm_read_byte_near() or pgm_read_word_near() instead of
    pgm_read_byte_far() or pgm_read_word_far() since it is more efficient that
    way, and you can still use the upper 64K for executable code.
    All functions that are suffixed with a \c _P \e require their
    arguments to be in the lower 64 KB of the flash ROM, as they do
    not use ELPM instructions.  This is normally not a big concern as
    the linker setup arranges any program space constants declared
    using the macros from this header file so they are placed right after
    the interrupt vectors, and in front of any executable code.  However,
    it can become a problem if there are too many of these constants, or
    for bootloaders on devices with more than 64 KB of ROM.
    <em>All these functions will not work in that situation.</em>
    \note For <b>Xmega</b> devices, make sure the NVM controller
    command register (\c NVM.CMD or \c NVM_CMD) is set to 0x00 (NOP)
    before using any of these functions.
*/
/* Copyright (c) 2004,2005,2007,2012 Joerg Wunsch
   Copyright (c) 2005, Carlos Lamas
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
/* Copyright (C) 1989-2015 Free Software Foundation, Inc.
This file is part of GCC.
GCC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3, or (at your option)
any later version.
GCC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
Under Section 7 of GPL version 3, you are granted additional
permissions described in the GCC Runtime Library Exception, version
3.1, as published by the Free Software Foundation.
You should have received a copy of the GNU General Public License and
a copy of the GCC Runtime Library Exception along with this program;
see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
<http://www.gnu.org/licenses/>.  */
/*
 * ISO C Standard:  7.17  Common definitions  <stddef.h>
 */
/* Any one of these symbols __need_* means that GNU libc
   wants us just to define one data type.  So don't define
   the symbols that indicate this file's entire job has been done.  */
/* This avoids lossage on SunOS but only if stdtypes.h comes first.
   There's no way to win with the other order!  Sun lossage.  */
/* On 4.3bsd-net2, make sure ansi.h is included, so we have
   one less case to deal with in the following.  */
/* On FreeBSD 5, machine/ansi.h does not exist anymore... */
/* In 4.3bsd-net2, machine/ansi.h defines these symbols, which are
   defined if the corresponding type is *not* defined.
   FreeBSD-2.1 defines _MACHINE_ANSI_H_ instead of _ANSI_H_.
   NetBSD defines _I386_ANSI_H_ and _X86_64_ANSI_H_ instead of _ANSI_H_ */
/* Sequent's header files use _PTRDIFF_T_ in some conflicting way.
   Just ignore it.  */
/* On VxWorks, <type/vxTypesBase.h> may have defined macros like
   _TYPE_size_t which will typedef size_t.  fixincludes patched the
   vxTypesBase.h so that this macro is only defined if _GCC_SIZE_T is
   not defined, and so that defining this macro defines _GCC_SIZE_T.
   If we find that the macros are still defined at this point, we must
   invoke them so that the type is defined as expected.  */
/* In case nobody has defined these types, but we aren't running under
   GCC 2.00, make sure that __PTRDIFF_TYPE__, __SIZE_TYPE__, and
   __WCHAR_TYPE__ have reasonable values.  This can happen if the
   parts of GCC is compiled by an older compiler, that actually
   include gstddef.h, such as collect2.  */
/* Signed type of difference of two pointers.  */
/* Define this type if we are doing the whole job,
   or if we want this type in particular.  */
/* If this symbol has done its job, get rid of it.  */
/* Unsigned type of `sizeof' something.  */
/* Define this type if we are doing the whole job,
   or if we want this type in particular.  */
/* Wide character type.
   Locale-writers should change this as necessary to
   be big enough to hold unique values not between 0 and 127,
   and not (wchar_t) -1, for each defined multibyte character.  */
/* Define this type if we are doing the whole job,
   or if we want this type in particular.  */
/*  In 4.3bsd-net2, leave these undefined to indicate that size_t, etc.
    are already defined.  */
/*  BSD/OS 3.1 and FreeBSD [23].x require the MACHINE_ANSI_H check here.  */
/*  NetBSD 5 requires the I386_ANSI_H and X86_64_ANSI_H checks here.  */
/* A null pointer constant.  */
/* Offset of member MEMBER in a struct of type TYPE. */
/* Copyright (c) 2002,2003,2005,2006,2007 Marek Michalkiewicz, Joerg Wunsch
   Copyright (c) 2007 Eric B. Weddington
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
/** \file */
/** \defgroup avr_io <avr/io.h>: AVR device-specific IO definitions
    \code #include <avr/io.h> \endcode
    This header file includes the apropriate IO definitions for the
    device that has been specified by the <tt>-mmcu=</tt> compiler
    command-line switch.  This is done by diverting to the appropriate
    file <tt>&lt;avr/io</tt><em>XXXX</em><tt>.h&gt;</tt> which should
    never be included directly.  Some register names common to all
    AVR devices are defined directly within <tt>&lt;avr/common.h&gt;</tt>,
    which is included in <tt>&lt;avr/io.h&gt;</tt>,
    but most of the details come from the respective include file.
    Note that this file always includes the following files:
    \code 
    #include <avr/sfr_defs.h>
    #include <avr/portpins.h>
    #include <avr/common.h>
    #include <avr/version.h>
    \endcode
    See \ref avr_sfr for more details about that header file.
    Included are definitions of the IO register set and their
    respective bit values as specified in the Atmel documentation.
    Note that inconsistencies in naming conventions,
    so even identical functions sometimes get different names on
    different devices.
    Also included are the specific names useable for interrupt
    function definitions as documented
    \ref avr_signames "here".
    Finally, the following macros are defined:
    - \b RAMEND
    <br>
    The last on-chip RAM address.
    <br>
    - \b XRAMEND
    <br>
    The last possible RAM location that is addressable. This is equal to 
    RAMEND for devices that do not allow for external RAM. For devices 
    that allow external RAM, this will be larger than RAMEND.
    <br>
    - \b E2END
    <br>
    The last EEPROM address.
    <br>
    - \b FLASHEND
    <br>
    The last byte address in the Flash program space.
    <br>
    - \b SPM_PAGESIZE
    <br>
    For devices with bootloader support, the flash pagesize
    (in bytes) to be used for the \c SPM instruction. 
    - \b E2PAGESIZE
    <br>
    The size of the EEPROM page.
    
*/
/**
   \ingroup avr_pgmspace
   \def PROGMEM
   Attribute to use in order to declare an object being located in
   flash ROM.
 */
/* Although in C, we can get away with just using __c, it does not work in
   C++. We need to use &__c[0] to avoid the compiler puking. Dave Hylands
   explaned it thusly,
     Let's suppose that we use PSTR("Test"). In this case, the type returned
     by __c is a prog_char[5] and not a prog_char *. While these are
     compatible, they aren't the same thing (especially in C++). The type
     returned by &__c[0] is a prog_char *, which explains why it works
     fine. */
/* The real thing. */
/*
Macro to read data from program memory for avr tiny parts(tiny 4/5/9/10/20/40).
why:
- LPM instruction is not available in AVR_TINY instruction set.
- Programs are executed starting from address 0x0000 in program memory.
But it must be addressed starting from 0x4000 when accessed via data memory.
Reference: TINY device (ATTiny 4,5,9,10,20 and 40) datasheets
Bug: avrtc-536
*/
/** \ingroup avr_pgmspace
    \def pgm_read_byte_near(address_short)
    Read a byte from the program space with a 16-bit (near) address. 
    \note The address is a byte address.
    The address is in the program space. */
/** \ingroup avr_pgmspace
    \def pgm_read_word_near(address_short)
    Read a word from the program space with a 16-bit (near) address. 
    \note The address is a byte address. 
    The address is in the program space. */
/** \ingroup avr_pgmspace
    \def pgm_read_dword_near(address_short)
    Read a double word from the program space with a 16-bit (near) address. 
    \note The address is a byte address. 
    The address is in the program space. */
/** \ingroup avr_pgmspace
    \def pgm_read_float_near(address_short)
    Read a float from the program space with a 16-bit (near) address. 
    \note The address is a byte address. 
    The address is in the program space. */
/** \ingroup avr_pgmspace
    \def pgm_read_ptr_near(address_short)
    Read a pointer from the program space with a 16-bit (near) address. 
    \note The address is a byte address. 
    The address is in the program space. */
/** \ingroup avr_pgmspace
    \def pgm_read_byte(address_short)
    Read a byte from the program space with a 16-bit (near) address. 
    \note The address is a byte address. 
    The address is in the program space. */
/** \ingroup avr_pgmspace
    \def pgm_read_word(address_short)
    Read a word from the program space with a 16-bit (near) address. 
    \note The address is a byte address. 
    The address is in the program space. */
/** \ingroup avr_pgmspace
    \def pgm_read_dword(address_short)
    Read a double word from the program space with a 16-bit (near) address. 
    \note The address is a byte address. 
    The address is in the program space. */
/** \ingroup avr_pgmspace
    \def pgm_read_float(address_short)
    Read a float from the program space with a 16-bit (near) address. 
    \note The address is a byte address. 
    The address is in the program space. */
/** \ingroup avr_pgmspace
    \def pgm_read_ptr(address_short)
    Read a pointer from the program space with a 16-bit (near) address. 
    \note The address is a byte address. 
    The address is in the program space. */
/** \ingroup avr_pgmspace
    \def pgm_get_far_address(var)
   This macro facilitates the obtention of a 32 bit "far" pointer (only 24 bits
   used) to data even passed the 64KB limit for the 16 bit ordinary pointer. It
   is similar to the '&' operator, with some limitations.
   Comments:
   - The overhead is minimal and it's mainly due to the 32 bit size operation.
   - 24 bit sizes guarantees the code compatibility for use in future devices.
   - hh8() is an undocumented feature but seems to give the third significant byte
     of a 32 bit data and accepts symbols, complementing the functionality of hi8()
     and lo8(). There is not an equivalent assembler function to get the high
     significant byte.
   - 'var' has to be resolved at linking time as an existing symbol, i.e, a simple
     type variable name, an array name (not an indexed element of the array, if the
     index is a constant the compiler does not complain but fails to get the address
     if optimization is enabled), a struct name or a struct field name, a function
     identifier, a linker defined identifier,...
   - The returned value is the identifier's VMA (virtual memory address) determined
     by the linker and falls in the corresponding memory region. The AVR Harvard
     architecture requires non overlapping VMA areas for the multiple address spaces
     in the processor: Flash ROM, RAM, and EEPROM. Typical offset for this are
     0x00000000, 0x00800xx0, and 0x00810000 respectively, derived from the linker
     script used and linker options. The value returned can be seen then as a
     universal pointer.
*/
/** \ingroup avr_pgmspace
    \fn const void * memchr_P(const void *s, int val, size_t len)
    \brief Scan flash memory for a character.
    The memchr_P() function scans the first \p len bytes of the flash
    memory area pointed to by \p s for the character \p val.  The first
    byte to match \p val (interpreted as an unsigned character) stops
    the operation.
    \return The memchr_P() function returns a pointer to the matching
    byte or \c NULL if the character does not occur in the given memory
    area.	*/
extern const void * memchr_P(const void *, int __val, size_t __len) __attribute__((__const__));
/** \ingroup avr_pgmspace
    \fn int memcmp_P(const void *s1, const void *s2, size_t len)
    \brief Compare memory areas
    The memcmp_P() function compares the first \p len bytes of the memory
    areas \p s1 and flash \p s2. The comparision is performed using unsigned
    char operations.
    \returns The memcmp_P() function returns an integer less than, equal
    to, or greater than zero if the first \p len bytes of \p s1 is found,
    respectively, to be less than, to match, or be greater than the first
    \p len bytes of \p s2.	*/
extern int memcmp_P(const void *, const void *, size_t) __attribute__((__pure__));
/** \ingroup avr_pgmspace
    \fn void *memccpy_P (void *dest, const void *src, int val, size_t len)
    This function is similar to memccpy() except that \p src is pointer
    to a string in program space.	*/
extern void *memccpy_P(void *, const void *, int __val, size_t);
/** \ingroup avr_pgmspace
    \fn void *memcpy_P(void *dest, const void *src, size_t n)
    The memcpy_P() function is similar to memcpy(), except the src string
    resides in program space.
    \returns The memcpy_P() function returns a pointer to dest.  */
extern void *memcpy_P(void *, const void *, size_t);
/** \ingroup avr_pgmspace
    \fn void *memmem_P(const void *s1, size_t len1, const void *s2, size_t len2)
    The memmem_P() function is similar to memmem() except that \p s2 is
    pointer to a string in program space.	*/
extern void *memmem_P(const void *, size_t, const void *, size_t) __attribute__((__pure__));
/** \ingroup avr_pgmspace
    \fn const void +memrchr_P(const void *src, int val, size_t len)
    The memrchr_P() function is like the memchr_P() function, except
    that it searches backwards from the end of the \p len bytes pointed
    to by \p src instead of forwards from the front. (Glibc, GNU extension.)
    \return The memrchr_P() function returns a pointer to the matching
    byte or \c NULL if the character does not occur in the given memory
    area.	*/
extern const void * memrchr_P(const void *, int __val, size_t __len) __attribute__((__const__));
/** \ingroup avr_pgmspace
    \fn char *strcat_P(char *dest, const char *src)
    The strcat_P() function is similar to strcat() except that the \e src
    string must be located in program space (flash).
    \returns The strcat() function returns a pointer to the resulting string
    \e dest. */
extern char *strcat_P(char *, const char *);
/** \ingroup avr_pgmspace
    \fn const char *strchr_P(const char *s, int val)
    \brief Locate character in program space string.
    The strchr_P() function locates the first occurrence of \p val
    (converted to a char) in the string pointed to by \p s in program
    space. The terminating null character is considered to be part of
    the string.
    The strchr_P() function is similar to strchr() except that \p s is
    pointer to a string in program space.
    \returns The strchr_P() function returns a pointer to the matched
    character or \c NULL if the character is not found. */
extern const char * strchr_P(const char *, int __val) __attribute__((__const__));
/** \ingroup avr_pgmspace
    \fn const char *strchrnul_P(const char *s, int c)
    The strchrnul_P() function is like strchr_P() except that if \p c is
    not found in \p s, then it returns a pointer to the null byte at the
    end of \p s, rather than \c NULL. (Glibc, GNU extension.)
    \return The strchrnul_P() function returns a pointer to the matched
    character, or a pointer to the null byte at the end of \p s (i.e.,
    \c s+strlen(s)) if the character is not found.	*/
extern const char * strchrnul_P(const char *, int __val) __attribute__((__const__));
/** \ingroup avr_pgmspace
    \fn int strcmp_P(const char *s1, const char *s2)
    The strcmp_P() function is similar to strcmp() except that \p s2 is
    pointer to a string in program space.
    \returns The strcmp_P() function returns an integer less than, equal
    to, or greater than zero if \p s1 is found, respectively, to be less
    than, to match, or be greater than \p s2. A consequence of the
    ordering used by strcmp_P() is that if \p s1 is an initial substring
    of \p s2, then \p s1 is considered to be "less than" \p s2. */
extern int strcmp_P(const char *, const char *) __attribute__((__pure__));
/** \ingroup avr_pgmspace
    \fn char *strcpy_P(char *dest, const char *src)
    The strcpy_P() function is similar to strcpy() except that src is a
    pointer to a string in program space.
    \returns The strcpy_P() function returns a pointer to the destination
    string dest. */
extern char *strcpy_P(char *, const char *);
/** \ingroup avr_pgmspace
    \fn int strcasecmp_P(const char *s1, const char *s2)
    \brief Compare two strings ignoring case.
    The strcasecmp_P() function compares the two strings \p s1 and \p s2,
    ignoring the case of the characters.
    \param s1 A pointer to a string in the devices SRAM.
    \param s2 A pointer to a string in the devices Flash.
    \returns The strcasecmp_P() function returns an integer less than,
    equal to, or greater than zero if \p s1 is found, respectively, to
    be less than, to match, or be greater than \p s2. A consequence of
    the ordering used by strcasecmp_P() is that if \p s1 is an initial
    substring of \p s2, then \p s1 is considered to be "less than" \p s2. */
extern int strcasecmp_P(const char *, const char *) __attribute__((__pure__));
/** \ingroup avr_pgmspace
    \fn char *strcasestr_P(const char *s1, const char *s2)
    This funtion is similar to strcasestr() except that \p s2 is pointer
    to a string in program space.	*/
extern char *strcasestr_P(const char *, const char *) __attribute__((__pure__));
/** \ingroup avr_pgmspace
    \fn size_t strcspn_P(const char *s, const char *reject)
    The strcspn_P() function calculates the length of the initial segment
    of \p s which consists entirely of characters not in \p reject. This
    function is similar to strcspn() except that \p reject is a pointer
    to a string in program space.
    \return The strcspn_P() function returns the number of characters in
    the initial segment of \p s which are not in the string \p reject.
    The terminating zero is not considered as a part of string.	*/
extern size_t strcspn_P(const char *__s, const char * __reject) __attribute__((__pure__));
/** \ingroup avr_pgmspace
    \fn size_t strlcat_P(char *dst, const char *src, size_t siz)
    \brief Concatenate two strings.
    The strlcat_P() function is similar to strlcat(), except that the \p src
    string must be located in program space (flash).
    Appends \p src to string \p dst of size \p siz (unlike strncat(),
    \p siz is the full size of \p dst, not space left).  At most \p siz-1
    characters will be copied.  Always NULL terminates (unless \p siz <=
    \p strlen(dst)).
    \returns The strlcat_P() function returns strlen(src) + MIN(siz,
    strlen(initial dst)).  If retval >= siz, truncation occurred.	*/
extern size_t strlcat_P (char *, const char *, size_t );
/** \ingroup avr_pgmspace
    \fn size_t strlcpy_P(char *dst, const char *src, size_t siz)
    \brief Copy a string from progmem to RAM.
    Copy \p src to string \p dst of size \p siz.  At most \p siz-1
    characters will be copied.  Always NULL terminates (unless \p siz == 0).
    The strlcpy_P() function is similar to strlcpy() except that the
    \p src is pointer to a string in memory space.
    \returns The strlcpy_P() function returns strlen(src). If
    retval >= siz, truncation occurred.  */
extern size_t strlcpy_P (char *, const char *, size_t );
/** \ingroup avr_pgmspace
    \fn size_t strnlen_P(const char *src, size_t len)
    \brief Determine the length of a fixed-size string.
    The strnlen_P() function is similar to strnlen(), except that \c src is a
    pointer to a string in program space.
    \returns The strnlen_P function returns strlen_P(src), if that is less than
    \c len, or \c len if there is no '\\0' character among the first \c len
    characters pointed to by \c src. */
extern size_t strnlen_P(const char *, size_t) __attribute__((__const__)); /* program memory can't change */
/** \ingroup avr_pgmspace
    \fn int strncmp_P(const char *s1, const char *s2, size_t n)
    The strncmp_P() function is similar to strcmp_P() except it only compares
    the first (at most) n characters of s1 and s2.
    \returns The strncmp_P() function returns an integer less than, equal to,
    or greater than zero if s1 (or the first n bytes thereof) is found,
    respectively, to be less than, to match, or be greater than s2.  */
extern int strncmp_P(const char *, const char *, size_t) __attribute__((__pure__));
/** \ingroup avr_pgmspace
    \fn int strncasecmp_P(const char *s1, const char *s2, size_t n)
    \brief Compare two strings ignoring case.
    The strncasecmp_P() function is similar to strcasecmp_P(), except it
    only compares the first \p n characters of \p s1.
    \param s1 A pointer to a string in the devices SRAM.
    \param s2 A pointer to a string in the devices Flash.
    \param n The maximum number of bytes to compare.
    \returns The strncasecmp_P() function returns an integer less than,
    equal to, or greater than zero if \p s1 (or the first \p n bytes
    thereof) is found, respectively, to be less than, to match, or be
    greater than \p s2. A consequence of the ordering used by
    strncasecmp_P() is that if \p s1 is an initial substring of \p s2,
    then \p s1 is considered to be "less than" \p s2.  */
extern int strncasecmp_P(const char *, const char *, size_t) __attribute__((__pure__));
/** \ingroup avr_pgmspace
    \fn char *strncat_P(char *dest, const char *src, size_t len)
    \brief Concatenate two strings.
    The strncat_P() function is similar to strncat(), except that the \e src
    string must be located in program space (flash).
    \returns The strncat_P() function returns a pointer to the resulting string
    dest.  */
extern char *strncat_P(char *, const char *, size_t);
/** \ingroup avr_pgmspace
    \fn char *strncpy_P(char *dest, const char *src, size_t n)
    The strncpy_P() function is similar to strcpy_P() except that not more
    than n bytes of src are copied.  Thus, if there is no null byte among the
    first n bytes of src, the result will not be null-terminated.
    In the case where the length of src is less than that of n, the remainder
    of dest will be padded with nulls.
    \returns The strncpy_P() function returns a pointer to the destination
    string dest.  */
extern char *strncpy_P(char *, const char *, size_t);
/** \ingroup avr_pgmspace
    \fn char *strpbrk_P(const char *s, const char *accept)
    The strpbrk_P() function locates the first occurrence in the string
    \p s of any of the characters in the flash string \p accept. This
    function is similar to strpbrk() except that \p accept is a pointer
    to a string in program space.
    \return  The strpbrk_P() function returns a pointer to the character
    in \p s that matches one of the characters in \p accept, or \c NULL
    if no such character is found. The terminating zero is not considered
    as a part of string: if one or both args are empty, the result will
    \c NULL. */
extern char *strpbrk_P(const char *__s, const char * __accept) __attribute__((__pure__));
/** \ingroup avr_pgmspace
    \fn const char *strrchr_P(const char *s, int val)
    \brief Locate character in string.
    The strrchr_P() function returns a pointer to the last occurrence of
    the character \p val in the flash string \p s.
    \return The strrchr_P() function returns a pointer to the matched
    character or \c NULL if the character is not found. */
extern const char * strrchr_P(const char *, int __val) __attribute__((__const__));
/** \ingroup avr_pgmspace
    \fn char *strsep_P(char **sp, const char *delim)
    \brief Parse a string into tokens.
    The strsep_P() function locates, in the string referenced by \p *sp,
    the first occurrence of any character in the string \p delim (or the
    terminating '\\0' character) and replaces it with a '\\0'.  The
    location of the next character after the delimiter character (or \c
    NULL, if the end of the string was reached) is stored in \p *sp. An
    ``empty'' field, i.e. one caused by two adjacent delimiter
    characters, can be detected by comparing the location referenced by
    the pointer returned in \p *sp to '\\0'. This function is similar to
    strsep() except that \p delim is a pointer to a string in program
    space.
    \return The strsep_P() function returns a pointer to the original
    value of \p *sp. If \p *sp is initially \c NULL, strsep_P() returns
    \c NULL. */
extern char *strsep_P(char **__sp, const char * __delim);
/** \ingroup avr_pgmspace
    \fn size_t strspn_P(const char *s, const char *accept)
    The strspn_P() function calculates the length of the initial segment
    of \p s which consists entirely of characters in \p accept. This
    function is similar to strspn() except that \p accept is a pointer
    to a string in program space.
    \return  The strspn_P() function returns the number of characters in
    the initial segment of \p s which consist only of characters from \p
    accept. The terminating zero is not considered as a part of string.	*/
extern size_t strspn_P(const char *__s, const char * __accept) __attribute__((__pure__));
/** \ingroup avr_pgmspace
    \fn char *strstr_P(const char *s1, const char *s2)
    \brief Locate a substring.
    The strstr_P() function finds the first occurrence of the substring
    \p s2 in the string \p s1.  The terminating '\\0' characters are not
    compared. The strstr_P() function is similar to strstr() except that
    \p s2 is pointer to a string in program space.
    \returns The strstr_P() function returns a pointer to the beginning
    of the substring, or NULL if the substring is not found. If \p s2
    points to a string of zero length, the function returns \p s1. */
extern char *strstr_P(const char *, const char *) __attribute__((__pure__));
/** \ingroup avr_pgmspace
    \fn char *strtok_P(char *s, const char * delim)
    \brief Parses the string into tokens.
    strtok_P() parses the string \p s into tokens. The first call to
    strtok_P() should have \p s as its first argument. Subsequent calls
    should have the first argument set to NULL. If a token ends with a
    delimiter, this delimiting character is overwritten with a '\\0' and a
    pointer to the next character is saved for the next call to strtok_P().
    The delimiter string \p delim may be different for each call.
    The strtok_P() function is similar to strtok() except that \p delim
    is pointer to a string in program space.
    \returns The strtok_P() function returns a pointer to the next token or
    NULL when no more tokens are found.
    \note strtok_P() is NOT reentrant. For a reentrant version of this
    function see strtok_rP().
 */
extern char *strtok_P(char *__s, const char * __delim);
/** \ingroup avr_pgmspace
    \fn char *strtok_rP (char *string, const char *delim, char **last)
    \brief Parses string into tokens.
    The strtok_rP() function parses \p string into tokens. The first call to
    strtok_rP() should have string as its first argument. Subsequent calls
    should have the first argument set to NULL. If a token ends with a
    delimiter, this delimiting character is overwritten with a '\\0' and a
    pointer to the next character is saved for the next call to strtok_rP().
    The delimiter string \p delim may be different for each call. \p last is
    a user allocated char* pointer. It must be the same while parsing the
    same string. strtok_rP() is a reentrant version of strtok_P().
    The strtok_rP() function is similar to strtok_r() except that \p delim
    is pointer to a string in program space.
    \returns The strtok_rP() function returns a pointer to the next token or
    NULL when no more tokens are found. */
extern char *strtok_rP(char *__s, const char * __delim, char **__last);
/** \ingroup avr_pgmspace
    \fn size_t strlen_PF(uint_farptr_t s)
    \brief Obtain the length of a string
    The strlen_PF() function is similar to strlen(), except that \e s is a
    far pointer to a string in program space.
    \param s A far pointer to the string in flash
    \returns The strlen_PF() function returns the number of characters in
    \e s. The contents of RAMPZ SFR are undefined when the function returns. */
extern size_t strlen_PF(uint_farptr_t src) __attribute__((__const__)); /* program memory can't change */
/** \ingroup avr_pgmspace
    \fn size_t strnlen_PF(uint_farptr_t s, size_t len)
    \brief Determine the length of a fixed-size string
    The strnlen_PF() function is similar to strnlen(), except that \e s is a
    far pointer to a string in program space.
    \param s A far pointer to the string in Flash
    \param len The maximum number of length to return
    \returns The strnlen_PF function returns strlen_P(\e s), if that is less
    than \e len, or \e len if there is no '\\0' character among the first \e
    len characters pointed to by \e s. The contents of RAMPZ SFR are
    undefined when the function returns. */
extern size_t strnlen_PF(uint_farptr_t src, size_t len) __attribute__((__const__)); /* program memory can't change */
/** \ingroup avr_pgmspace
    \fn void *memcpy_PF(void *dest, uint_farptr_t src, size_t n)
    \brief Copy a memory block from flash to SRAM
    The memcpy_PF() function is similar to memcpy(), except the data
    is copied from the program space and is addressed using a far pointer.
    \param dest A pointer to the destination buffer
    \param src A far pointer to the origin of data in flash memory
    \param n The number of bytes to be copied
    \returns The memcpy_PF() function returns a pointer to \e dst. The contents
    of RAMPZ SFR are undefined when the function returns. */
extern void *memcpy_PF(void *dest, uint_farptr_t src, size_t len);
/** \ingroup avr_pgmspace
    \fn char *strcpy_PF(char *dst, uint_farptr_t src)
    \brief Duplicate a string
    The strcpy_PF() function is similar to strcpy() except that \e src is a far
    pointer to a string in program space.
    \param dst A pointer to the destination string in SRAM
    \param src A far pointer to the source string in Flash
    \returns The strcpy_PF() function returns a pointer to the destination
    string \e dst. The contents of RAMPZ SFR are undefined when the funcion
    returns. */
extern char *strcpy_PF(char *dest, uint_farptr_t src);
/** \ingroup avr_pgmspace
    \fn char *strncpy_PF(char *dst, uint_farptr_t src, size_t n)
    \brief Duplicate a string until a limited length
    The strncpy_PF() function is similar to strcpy_PF() except that not more
    than \e n bytes of \e src are copied.  Thus, if there is no null byte among
    the first \e n bytes of \e src, the result will not be null-terminated.
    In the case where the length of \e src is less than that of \e n, the
    remainder of \e dst will be padded with nulls.
    \param dst A pointer to the destination string in SRAM
    \param src A far pointer to the source string in Flash
    \param n The maximum number of bytes to copy
    \returns The strncpy_PF() function returns a pointer to the destination
    string \e dst. The contents of RAMPZ SFR are undefined when the function
    returns. */
extern char *strncpy_PF(char *dest, uint_farptr_t src, size_t len);
/** \ingroup avr_pgmspace
    \fn char *strcat_PF(char *dst, uint_farptr_t src)
    \brief Concatenates two strings
    The strcat_PF() function is similar to strcat() except that the \e src
    string must be located in program space (flash) and is addressed using
    a far pointer
    \param dst A pointer to the destination string in SRAM
    \param src A far pointer to the string to be appended in Flash
    \returns The strcat_PF() function returns a pointer to the resulting
    string \e dst. The contents of RAMPZ SFR are undefined when the function
    returns */
extern char *strcat_PF(char *dest, uint_farptr_t src);
/** \ingroup avr_pgmspace
    \fn size_t strlcat_PF(char *dst, uint_farptr_t src, size_t n)
    \brief Concatenate two strings
    The strlcat_PF() function is similar to strlcat(), except that the \e src
    string must be located in program space (flash) and is addressed using
    a far pointer.
    Appends src to string dst of size \e n (unlike strncat(), \e n is the
    full size of \e dst, not space left).  At most \e n-1 characters
    will be copied.  Always NULL terminates (unless \e n <= strlen(\e dst)).
    \param dst A pointer to the destination string in SRAM
    \param src A far pointer to the source string in Flash
    \param n The total number of bytes allocated to the destination string
    \returns The strlcat_PF() function returns strlen(\e src) + MIN(\e n,
    strlen(initial \e dst)).  If retval >= \e n, truncation occurred. The
    contents of RAMPZ SFR are undefined when the funcion returns. */
extern size_t strlcat_PF(char *dst, uint_farptr_t src, size_t siz);
/** \ingroup avr_pgmspace
    \fn char *strncat_PF(char *dst, uint_farptr_t src, size_t n)
    \brief Concatenate two strings
    The strncat_PF() function is similar to strncat(), except that the \e src
    string must be located in program space (flash) and is addressed using a
    far pointer.
    \param dst A pointer to the destination string in SRAM
    \param src A far pointer to the source string in Flash
    \param n The maximum number of bytes to append
    \returns The strncat_PF() function returns a pointer to the resulting
    string \e dst. The contents of RAMPZ SFR are undefined when the function
    returns. */
extern char *strncat_PF(char *dest, uint_farptr_t src, size_t len);
/** \ingroup avr_pgmspace
    \fn int strcmp_PF(const char *s1, uint_farptr_t s2)
    \brief Compares two strings
    The strcmp_PF() function is similar to strcmp() except that \e s2 is a far
    pointer to a string in program space.
    \param s1 A pointer to the first string in SRAM
    \param s2 A far pointer to the second string in Flash
    \returns The strcmp_PF() function returns an integer less than, equal to,
    or greater than zero if \e s1 is found, respectively, to be less than, to
    match, or be greater than \e s2. The contents of RAMPZ SFR are undefined
    when the function returns. */
extern int strcmp_PF(const char *s1, uint_farptr_t s2) __attribute__((__pure__));
/** \ingroup avr_pgmspace
    \fn int strncmp_PF(const char *s1, uint_farptr_t s2, size_t n)
    \brief Compare two strings with limited length
    The strncmp_PF() function is similar to strcmp_PF() except it only
    compares the first (at most) \e n characters of \e s1 and \e s2.
    \param s1 A pointer to the first string in SRAM
    \param s2 A far pointer to the second string in Flash
    \param n The maximum number of bytes to compare
    \returns The strncmp_PF() function returns an integer less than, equal
    to, or greater than zero if \e s1 (or the first \e n bytes thereof) is found,
    respectively, to be less than, to match, or be greater than \e s2. The
    contents of RAMPZ SFR are undefined when the function returns. */
extern int strncmp_PF(const char *s1, uint_farptr_t s2, size_t n) __attribute__((__pure__));
/** \ingroup avr_pgmspace
    \fn int strcasecmp_PF(const char *s1, uint_farptr_t s2)
    \brief Compare two strings ignoring case
    The strcasecmp_PF() function compares the two strings \e s1 and \e s2, ignoring
    the case of the characters.
    \param s1 A pointer to the first string in SRAM
    \param s2 A far pointer to the second string in Flash
    \returns The strcasecmp_PF() function returns an integer less than, equal
    to, or greater than zero if \e s1 is found, respectively, to be less than, to
    match, or be greater than \e s2. The contents of RAMPZ SFR are undefined
    when the function returns. */
extern int strcasecmp_PF(const char *s1, uint_farptr_t s2) __attribute__((__pure__));
/** \ingroup avr_pgmspace
    \fn int strncasecmp_PF(const char *s1, uint_farptr_t s2, size_t n)
    \brief Compare two strings ignoring case
    The strncasecmp_PF() function is similar to strcasecmp_PF(), except it
    only compares the first \e n characters of \e s1 and the string in flash is
    addressed using a far pointer.
    \param s1 A pointer to a string in SRAM
    \param s2 A far pointer to a string in Flash
    \param n The maximum number of bytes to compare
    \returns The strncasecmp_PF() function returns an integer less than, equal
    to, or greater than zero if \e s1 (or the first \e n bytes thereof) is found,
    respectively, to be less than, to match, or be greater than \e s2. The
    contents of RAMPZ SFR are undefined when the function returns.  */
extern int strncasecmp_PF(const char *s1, uint_farptr_t s2, size_t n) __attribute__((__pure__));
/** \ingroup avr_pgmspace
    \fn char *strstr_PF(const char *s1, uint_farptr_t s2)
    \brief Locate a substring.
    The strstr_PF() function finds the first occurrence of the substring \c s2
    in the string \c s1.  The terminating '\\0' characters are not
    compared.
    The strstr_PF() function is similar to strstr() except that \c s2 is a
    far pointer to a string in program space.
    \returns The strstr_PF() function returns a pointer to the beginning of the
    substring, or NULL if the substring is not found.
    If \c s2 points to a string of zero length, the function returns \c s1. The
    contents of RAMPZ SFR are undefined when the function returns. */
extern char *strstr_PF(const char *s1, uint_farptr_t s2);
/** \ingroup avr_pgmspace
    \fn size_t strlcpy_PF(char *dst, uint_farptr_t src, size_t siz)
    \brief Copy a string from progmem to RAM.
    Copy src to string dst of size siz.  At most siz-1 characters will be
    copied. Always NULL terminates (unless siz == 0).
    \returns The strlcpy_PF() function returns strlen(src). If retval >= siz,
    truncation occurred.  The contents of RAMPZ SFR are undefined when the
    function returns. */
extern size_t strlcpy_PF(char *dst, uint_farptr_t src, size_t siz);
/** \ingroup avr_pgmspace
    \fn int memcmp_PF(const void *s1, uint_farptr_t s2, size_t len)
    \brief Compare memory areas
    The memcmp_PF() function compares the first \p len bytes of the memory
    areas \p s1 and flash \p s2. The comparision is performed using unsigned
    char operations. It is an equivalent of memcmp_P() function, except
    that it is capable working on all FLASH including the exteded area
    above 64kB.
    \returns The memcmp_PF() function returns an integer less than, equal
    to, or greater than zero if the first \p len bytes of \p s1 is found,
    respectively, to be less than, to match, or be greater than the first
    \p len bytes of \p s2.  */
extern int memcmp_PF(const void *, uint_farptr_t, size_t) __attribute__((__pure__));
extern size_t __strlen_P(const char *) __attribute__((__const__)); /* internal helper function */
__attribute__((__always_inline__)) static __inline__ size_t strlen_P(const char * s);
static __inline__ size_t strlen_P(const char *s) {
  return __builtin_constant_p(__builtin_strlen(s))
     ? __builtin_strlen(s) : __strlen_P(s);
}
// timeout durations in ticks (each tick 1/62th s)
// return codes for Event handlers
// Indicates whether this handler consumed (handled) the Event, or
// if the Event should be sent to the next handler in the stack.
// typedefs
typedef uint8_t Event;
typedef struct Emission {
    Event event;
    uint16_t arg;
} Emission;
Event current_event;
// at 0.016 ms per tick, 255 ticks = 4.08 s
static volatile uint16_t ticks_since_last_event = 0;
// maximum number of events which can be waiting at one time
// (would probably be okay to reduce this to 4, but it's higher to be safe)
// was "volatile" before, changed to regular var since IRQ rewrites seem
// to have removed the need for it to be volatile
// no comment about "volatile emissions"
Emission emissions[16];
void append_emission(Event event, uint16_t arg);
void delete_first_emission();
void process_emissions();
uint8_t emit_now(Event event, uint16_t arg);
void emit(Event event, uint16_t arg);
void emit_current_event(uint16_t arg);
void empty_event_sequence();
uint8_t push_event(uint8_t ev_type); // only for use by PCINT_inner()
// TODO: Maybe move these to their own file...
// ... this probably isn't the right place for delays.
inline void interrupt_nice_delays();
uint8_t nice_delay_ms(uint16_t ms);
//uint8_t nice_delay_s();
void delay_4ms(uint8_t ms);
/* Event structure
 * Bit  7: 1 for a button input event, 0 for all others.
 * If bit 7 is 1:
 *     Bits 0,1,2,3:  Click counter.  Up to 15 clicks.
 *     Bit  4: 1 for a "press" event, 0 for a "release" event.
 *     Bit  5: 1 for a "hold" event, 0 otherwise.
 *     Bit  6: 1 for a "timeout" event, 0 otherwise.
 * If bit 7 is 0:
 *     Sort of ad-hoc, shown in #defines below.
 */
// event masks / bits
// Event types
// Events which aren't button presses
// Button press events
// shouldn't normally happen, but UI might empty_event_sequence() while button
// is down so a release with no recorded prior hold could be possible
// fsm-states.h: State-handling functions for SpaghettiMonster.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
// fsm-adc.h: ADC (voltage, temperature) functions for SpaghettiMonster.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
// voltage is 0.00V to 5.10V in 0.02V steps, from 0 to 255
// so one deci-Volt is 5 steps
// use raw value instead of lowpassed value for the next N measurements
// (2 = 1 for voltage + 1 for temperature)
volatile uint8_t adc_reset = 2;
// default 5 seconds between low-voltage warning events
// low-battery threshold in volts * 50
// battery is low but not critical
// MCU sees voltage 0.X volts lower than actual, add X/2 to readings
void adc_voltage_mode();
volatile uint8_t adc_active_now = 0; // sleep LVP needs a different sleep mode
volatile uint8_t irq_adc = 0; // ADC interrupt happened?
uint8_t adc_sample_count = 0; // skip the first sample; it's junk
uint8_t adc_channel = 0; // 0=voltage, 1=temperature
uint16_t adc_raw[2]; // last ADC measurements (0=voltage, 1=temperature)
uint16_t adc_smooth[2]; // lowpassed ADC measurements (0=voltage, 1=temperature)
// ADC code is split into two parts:
// - ISR: runs immediately at each interrupt, does the bare minimum because time is critical here
// - deferred: the bulk of the logic runs later when time isn't so critical
uint8_t adc_deferred_enable = 0; // stop waiting and run the deferred code
void adc_deferred(); // do the actual ADC-related calculations
static void ADC_voltage_handler();
uint8_t voltage = 0;
void low_voltage();
void battcheck();
// try to keep temperature below 45 C
// don't allow user to set ceiling above 70 C
// Local per-MCU calibration value
// temperature now, in C (ish)
int16_t temperature;
static void ADC_temperature_handler();
inline void ADC_on();
//inline void ADC_off();
//inline void ADC_start_measurement();
// needs a special sleep mode to get accurate measurements quickly 
// ... full power-down ends up using more power overall, and causes 
// some weird issues when the MCU doesn't stay awake enough cycles 
// to complete a reading
//inline void adc_sleep_mode();
// typedefs
typedef uint8_t State(Event event, uint16_t arg);
typedef State * StatePtr;
// top of the stack
volatile StatePtr current_state;
// stack for states, to allow shared utility states like "input a number"
// and such, which return to the previous state after finishing
StatePtr state_stack[8];
uint8_t state_stack_len = 0;
void _set_state(StatePtr new_state, uint16_t arg,
                Event exit_event, Event enter_event);
int8_t push_state(StatePtr new_state, uint16_t arg);
StatePtr pop_state();
uint8_t set_state(StatePtr new_state, uint16_t arg);
// if loop() needs to change state, use this instead of set_state()
// (because this avoids race conditions)
volatile StatePtr deferred_state;
volatile uint16_t deferred_state_arg;
void set_state_deferred(StatePtr new_state, uint16_t arg);
uint8_t default_state(Event event, uint16_t arg);
// fsm-wdt.h: WDT (Watch Dog Timer) functions for SpaghettiMonster.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
//void WDT_on();
//inline void WDT_off();
volatile uint8_t irq_wdt = 0; // WDT interrupt happened?
  // measure battery charge while asleep
// fsm-pcint.h: PCINT (Pin Change Interrupt) functions for SpaghettiMonster.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
volatile uint8_t irq_pcint = 0; // pin change interrupt happened?
//static volatile uint8_t button_was_pressed;
volatile uint8_t button_last_state;
uint8_t button_is_pressed();
//inline void PCINT_on();
//inline void PCINT_off();
void PCINT_inner(uint8_t pressed);
// fsm-standby.h: standby mode functions for SpaghettiMonster.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
// deferred "off" so we won't suspend in a weird state
// (like...  during the middle of a strobe pulse)
// set this to nonzero to enter standby mode next time the system is idle
volatile uint8_t go_to_standby = 0;
/*
 * From the Attiny85 manual:
 * 0: 16 ms
 * 1: 32 ms
 * 2: 64 ms
 * 3: 0.128 s
 * 4: 0.256 s
 * 5: 0.512 s
 * 6: 1.0 s
 * 7: 2.0 s
 * 32: 4.0 s
 * 33: 8.0 s
 * (other values may have unexpected effects; not sure why the final bit is
 *  separated from the others, in the "32" position instead of "8", but that's
 *  how it is)
 */
void sleep_until_eswitch_pressed();
// stops processing until next click or timer tick
// (I think)
void idle_mode();
// fsm-channels.h: Channel mode functions for SpaghettiMonster.
// Copyright (C) 2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
// always enable channel modes, even if there is only one
// typedefs
typedef void SetLevelFunc(uint8_t level);
typedef SetLevelFunc * SetLevelFuncPtr;
typedef uint8_t GradualTickFunc(uint8_t gt);
typedef GradualTickFunc * GradualTickFuncPtr;
// TODO: implement custom 3H handlers
typedef void ChannelArgFunc();
typedef ChannelArgFunc * ChannelArgFuncPtr;
typedef struct Channel {
    SetLevelFuncPtr set_level;
        GradualTickFuncPtr gradual_tick;
} Channel;
Channel channels[]; // values are defined in the hwdef-*.c
// TODO: size-optimize the case with only 1 channel mode?
// (the arrays and stuff shouldn't be needed)
    // current multi-channel mode
    uint8_t channel_mode = CM_CH1_FET;
//#ifdef USE_CHANNEL_MODE_TOGGLES
// user can take unwanted modes out of the rotation
// bitmask
void set_channel_mode(uint8_t mode);
// fsm-ramping.h: Ramping functions for SpaghettiMonster.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
// actual_level: last ramp level set by set_level()
uint8_t actual_level = 0;
// the level used before actual
uint8_t prev_level = 0;
void set_level(uint8_t level);
//void set_level_smooth(uint8_t level);
void set_level_zero(); // implement this in a hwdef
// adjust brightness very smoothly
uint8_t gradual_target;
inline void set_level_gradually(uint8_t lvl);
void gradual_tick();
// reduce repetition with macros
// tick to a specific value
// tick to a specific value, except when immediate 0 to 255 is needed
// tick the top layer of the stack
// tick a base level of the stack
// (with support for special DD FET behavior
//  like "low=0, high=255" --> "low=255, high=254")
// auto-detect the data type for PWM tables
// FIXME: PWM bits and data type should be per PWM table
// FIXME: this whole thing is a mess and should be removed
    // pointer plus 2*y bytes
    //#define PWM_GET(x,y) pgm_read_word(x+(2*y))
    // nope, the compiler was already doing the math correctly
// use UI-defined ramp tables if they exist
__attribute__((__progmem__)) 
       const uint16_t pwm1_levels[] = { 0,1,2,3,4,5,6,7,9,10,12,14,17,19,22,25,28,32,36,41,45,50,56,62,69,76,84,92,101,110,121,132,143,156,169,184,199,215,232,251,270,291,313,336,360,386,414,442,473,505,539,574,612,651,693,736,782,829,880,932,987,1045,1105,1168,1233,1302,1374,1449,1527,1608,1693,1781,1873,1969,2068,2172,2279,2391,2507,2628,2753,2883,3018,3158,3303,3454,3609,3771,3938,4111,4289,4475,4666,4864,5068,5280,5498,5724,5957,6197,6445,6701,6965,7237,7518,7808,8106,8413,8730,9056,9392,9737,10093,10459,10835,11223,11621,12031,12452,12884,13329,13786,14255,14737,15232,15741,16262,16798,17347,17911,18489,19082,19691,20314,20954,21609,22281,22969,23674,24397,25137,25895,26671,27465,28279,29111,29963,30835,31727,32640 };
__attribute__((__progmem__)) 
       const uint16_t pwm2_levels[] = { 0,2,3,5,7,9,11,14,17,20,24,28,33,38,44,50,57,64,72,81,91,101,112,125,138,152,167,184,201,220,241,263,286,311,337,365,395,427,461,497,535,575,618,663,711,761,814,870,929,992,1057,1126,1198,1274,1353,1437,1524,1616,1712,1812,1917,2027,2141,2261,2386,2516,2652,2794,2941,3095,3255,3422,3595,3775,3962,4156,4358,4568,4785,5011,5245,5487,5738,5999,6268,6548,6837,7135,7445,7764,8095,8437,8790,9154,9531,9919,10321,10735,11162,11602,12056,12524,13006,13503,14015,14542,15085,15643,16218,16810,17419,18045,18688,19350,20031,20730,21448,22186,22944,23722,24521,25342,26184,27048,27935,28844,29777,30733,31714,32640,32640,32640,32640,32640,32640,32640,32640,32640,32640,32640,32640,32640,32640,32640,32640,32640,32640,32640,32640,0 };
__attribute__((__progmem__)) 
       const uint8_t pwm3_levels[] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,20,31,42,53,65,76,88,101,113,126,139,152,166,180,194,209,224,239,255 };
// convenience defs for 1 LED with stacked channels
// FIXME: remove this, use pwm1/2/3 instead
// 2 channel CCT blending ramp
// pulse frequency modulation, a.k.a. dynamic PWM
// (different ceiling / frequency at each ramp level)
// FIXME: dynamic PWM should be a per-channel option, not global
// FIXME: jump start should be per channel / channel mode
// RAMP_SIZE / MAX_LVL
// cfg-*.h should define RAMP_SIZE
//#define RAMP_SIZE (sizeof(stacked_pwm1_levels)/sizeof(STACKED_PWM_DATATYPE))
// fsm-random.h: Random number generator for SpaghettiMonster.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
uint8_t pseudo_rand();
// TODO: test without "volatile", in case it's not needed
volatile uint8_t pseudo_rand_seed = 0;
// fsm-eeprom.h: EEPROM API for SpaghettiMonster.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
/* Copyright (c) 2002, 2003, 2004, 2007 Marek Michalkiewicz
   Copyright (c) 2005, 2006 Bjoern Haase
   Copyright (c) 2008 Atmel Corporation
   Copyright (c) 2008 Wouter van Gulik
   Copyright (c) 2009 Dmitry Xmelkov
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
// set this higher to enable normal eeprom functions
// TODO: rename to EEPROM_BYTES_NEEDED or similar, to make purpose clearer
// set this higher to enable wear-levelled eeprom functions
// TODO: rename to EEPROM_WL_BYTES_NEEDED or similar, to make purpose clearer
        // use entire eeprom
        __attribute__((unused)) static void eep_data_fits() { ((void)sizeof(char[1 - 2*!(sizeof(Config) <= 256)])); };
        uint8_t *eeprom;
    uint8_t load_eeprom(); // returns 1 for success, 0 for no data found
    void save_eeprom();
// if this marker isn't found, the eeprom is assumed to be blank
// wait a few ms before eeprom operations, to wait for power to stabilize
// (otherwise reads or writes can get corrupt data)
// (not necessary on some hardware,
//  but enabled by default when there's space)
// fsm-misc.h: Miscellaneous function for SpaghettiMonster.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
void auto_clock_speed();
// shortest time (in ms) the light should blink for to indicate a zero
    uint8_t blink_digit(uint8_t num);
//#define USE_BLINK
uint8_t blink_num(uint8_t num);
/*
uint8_t blink(uint8_t num, uint8_t speed);
*/
uint8_t button_led_off = 0;
// lvl: 0=off, 1=low, 2=high
void button_led_set(uint8_t lvl);
// if any type of aux LEDs exist, define a shorthand flag for it
// value: 0b00BBGGRR
// each pair of bits: 0=off, 1=low, 2=high
void rgb_led_set(uint8_t value);
uint8_t triangle_wave(uint8_t phase);
// fsm-main.h: main() function for SpaghettiMonster.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
int main();
// needs to run frequently to execute the logic for WDT and ADC and stuff
void handle_deferred_interrupts();
// delay.h: Smaller, more flexible _delay_ms() functions.
// Copyright (C) 2015-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
/* Copyright (c) 2002, Marek Michalkiewicz
   Copyright (c) 2007 Joerg Wunsch
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
/* Copyright (c) 2004,2005,2007,2012 Joerg Wunsch
   Copyright (c) 2005, Carlos Lamas
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
static __inline__ void _delay_loop_1(uint8_t __count) __attribute__((__always_inline__));
static __inline__ void _delay_loop_2(uint16_t __count) __attribute__((__always_inline__));
/** \file */
/** \defgroup util_delay_basic <util/delay_basic.h>: Basic busy-wait delay loops
    \code
    #include <util/delay_basic.h>
    \endcode
    The functions in this header file implement simple delay loops
    that perform a busy-waiting.  They are typically used to
    facilitate short delays in the program execution.  They are
    implemented as count-down loops with a well-known CPU cycle
    count per loop iteration.  As such, no other processing can
    occur simultaneously.  It should be kept in mind that the
    functions described here do not disable interrupts.
    In general, for long delays, the use of hardware timers is
    much preferrable, as they free the CPU, and allow for
    concurrent processing of other events while the timer is
    running.  However, in particular for very short delays, the
    overhead of setting up a hardware timer is too much compared
    to the overall delay time.
    Two inline functions are provided for the actual delay algorithms.
*/
/** \ingroup util_delay_basic
    Delay loop using an 8-bit counter \c __count, so up to 256
    iterations are possible.  (The value 256 would have to be passed
    as 0.)  The loop executes three CPU cycles per iteration, not
    including the overhead the compiler needs to setup the counter
    register.
    Thus, at a CPU speed of 1 MHz, delays of up to 768 microseconds
    can be achieved.
*/
void
_delay_loop_1(uint8_t __count)
{
 __asm__ volatile (
  "1: dec %0" "\n\t"
  "brne 1b"
  : "=r" (__count)
  : "0" (__count)
 );
}
/** \ingroup util_delay_basic
    Delay loop using a 16-bit counter \c __count, so up to 65536
    iterations are possible.  (The value 65536 would have to be
    passed as 0.)  The loop executes four CPU cycles per iteration,
    not including the overhead the compiler requires to setup the
    counter register pair.
    Thus, at a CPU speed of 1 MHz, delays of up to about 262.1
    milliseconds can be achieved.
 */
void
_delay_loop_2(uint16_t __count)
{
 __asm__ volatile (
  "1: sbiw %0,1" "\n\t"
  "brne 1b"
  : "=w" (__count)
  : "0" (__count)
 );
}
void _delay_zero() {
    //_delay_loop_2((BOGOMIPS/3) & 0xff00);
    _delay_loop_2(1020);
}
////////// include all the .c files //////////
// arch/mcu.c: Attiny portability header.
// Copyright (C) 2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
// arch/attiny1634.c: attiny85 support functions
// Copyright (C) 2014-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
////////// clock speed / delay stuff //////////
inline void mcu_clock_speed() {
    // TODO?
    // (or not; clock speed is set by the fuses)
    // attiny1634 datasheet 6.5
    // CLKSR = [OSCRDY, CSTR, CKOUT_IO, SUT, CKSEL3/2/1/0]
    // default 8MHz calibrated internal clock: SUT=0, CKSEL=0b0010
}
///// clock dividers
inline void clock_prescale_set(uint8_t n) {
    
   __asm__ __volatile__ ("cli" ::: "memory")
        ;
    // _PROTECTED_WRITE(CLKPR, n);
    
   (*(volatile uint8_t *)((0x2F) + 0x20)) 
       = 0xD8;
    
   (*(volatile uint8_t *)((0x33) + 0x20)) 
         = n;
    
   __asm__ __volatile__ ("sei" ::: "memory")
        ;
}
////////// default hw_setup() //////////
////////// ADC voltage / temperature //////////
inline void mcu_set_admux_therm() {
    // put the ADC in temperature mode
    // DS table 19-3, 19-4, internal sensor / 1.1V ref
    // [refs1, refs0, refen, adc0en, mux3, mux2, mux1, mux0]
    // refs=0b10 : internal 1.1V ref
    // mux=0b1110 : internal temperature sensor
    //#define ADMUX_THERM 0b10001110
    
   (*(volatile uint8_t *)((0x04) + 0x20)) 
         = 0b10001110;
    // other stuff is already set, so no need to re-set it
}
inline void mcu_set_admux_voltage() {
    // put the ADC in battery voltage measurement mode
    // TODO: avr datasheet references
        
       (*(volatile uint8_t *)((0x04) + 0x20)) 
             = 0b10000110;
        // disable digital input on divider pin to reduce power consumption
        // TODO: this should be in hwdef init, not here
        
       (*(volatile uint8_t *)(0x61)) 
                        |= (1 << 
                                 1
                                            );
    //ACSRA |= (1 << ACD);  // turn off analog comparator to save power
    // ADCSRB: [VDEN, VDPD, -, -, ADLAR, ADTS2, ADTS1, ADTS0]
    
   (*(volatile uint8_t *)((0x02) + 0x20)) 
          = (1 << 
                  3
                       ); // left-adjust, free-running
    //ADCSRB = 0;  // right-adjust, free-running
}
inline void mcu_adc_sleep_mode() {
    
   do { (*(volatile uint8_t *)((0x36) + 0x20)) = (((*(volatile uint8_t *)((0x36) + 0x20)) & ~((1 << (5)) | (1 << (6)))) | ((0x01<<5))); } while(0)
                                 ;
}
inline void mcu_adc_start_measurement() {
    // [ADEN, ADSC, ADATE, adif, ADIE, ADPS2, ADPS1, ADPS0]
    
   (*(volatile uint8_t *)((0x03) + 0x20)) 
          = (1 << 
                  7
                      ) // enable
           | (1 << 
                  6
                      ) // start
           | (1 << 
                  5
                       ) // auto-retrigger
           | (1 << 
                  3
                      ) // interrupt enable
           | 0x07; // prescale
}
inline void mcu_adc_off() {
    
   (*(volatile uint8_t *)((0x03) + 0x20)) 
          &= ~(1<<
                  7
                      ); //ADC off
}
// left-adjusted mode:
inline uint16_t mcu_adc_result() { return 
                                         (*(volatile uint16_t *)((0x00) + 0x20))
                                            ; }
//inline uint16_t mcu_adc_result() { return (uint16_t)(ADCL | (ADCH << 8)); }
// right-adjusted mode:
/*
inline uint16_t mcu_adc_result() {
    uint16_t result = (ADCL | (ADCH << 8)) << 6;
    return result;
}
*/
inline uint8_t mcu_vdd_raw2cooked(uint16_t measurement) {
    // In : 65535 * 1.1 / Vbat
    // Out: uint8_t: Vbat * 50
    // 1.1 = ADC Vref
    // ... spend the extra 84 bytes of ROM for better precision
    // 4096 = how much ADC resolution we're using (12 bits)
    uint8_t vbat = (uint32_t)(10 * 5 * 1.1 * 4096) / (measurement >> 4);
    return vbat;
}
inline uint8_t mcu_vdivider_raw2cooked(uint16_t measurement) {
    // In : 4095 * Vdiv / 1.1V
    // Out: uint8_t: Vbat * 50
    // Vdiv = Vbat / 4.3  (typically)
    // 1.1 = ADC Vref
    const uint16_t adc_per_volt =
            (((uint16_t)(4*967) << 4) - ((uint16_t)(4*482) << 4))
            / (5 * (44-22));
    uint8_t result = measurement / adc_per_volt;
    return result;
}
inline uint16_t mcu_temp_raw2cooked(uint16_t measurement) {
    // convert raw ADC values to calibrated temperature
    // In: ADC raw temperature (16-bit, or left-aligned)
    // Out: Kelvin << 6
    // Precision: 1/64th Kelvin (but noisy)
    // attiny1634 datasheet section 19.12
    // nothing to do; input value is already "cooked"
    return measurement;
}
inline uint8_t mcu_adc_lsb() {
    // left-adjusted mode:
    return (
           (*(volatile uint8_t *)((0x00) + 0x20)) 
                >> 6) + (
                         (*(volatile uint8_t *)((0x01) + 0x20)) 
                              << 2);
    // right-adjusted mode:
    // datasheet 19.13.3.2:
    // "When ADCL is read, the ADC Data Register is not updated
    //  until ADCH is read. ... ADCL must be read first, then ADCH."
    // So... gotta read it even if not needed?
    // (the value doesn't matter here, the lower bits are only used
    //  for generating some random seed data)
    //return ADCL + ADCH;
}
////////// WDT //////////
inline void mcu_wdt_active() {
    
   __asm__ __volatile__ ("wdr")
              ; // Reset the WDT
    
   (*(volatile uint8_t *)((0x30) + 0x20)) 
          = (1<<
                6
                    ); // Enable interrupt every 16ms
}
inline void mcu_wdt_standby() {
    
   __asm__ __volatile__ ("wdr")
              ; // Reset the WDT
    
   (*(volatile uint8_t *)((0x30) + 0x20)) 
          = (1<<
                6
                    ) | 3;
}
inline void mcu_wdt_stop() {
    
   __asm__ __volatile__ ("cli" ::: "memory")
        ; // needed because CCP, below
    
   __asm__ __volatile__ ("wdr")
              ; // Reset the WDT
    
   (*(volatile uint8_t *)((0x35) + 0x20)) 
         &= ~(1<<
                 3
                     ); // clear watchdog reset flag
    // _PROTECTED_WRITE(WDTCSR, 0);
    
   (*(volatile uint8_t *)((0x2F) + 0x20)) 
       = 0xD8; // enable config changes
    
   (*(volatile uint8_t *)((0x30) + 0x20)) 
          = 0; // disable and clear all WDT settings
    
   __asm__ __volatile__ ("sei" ::: "memory")
        ;
}
////////// PCINT - pin change interrupt (e-switch) //////////
inline void mcu_pcint_on() {
    // enable pin change interrupt
    
   (*(volatile uint8_t *)((0x3C) + 0x20)) 
         |= (1 << 
                  3
                             );
}
inline void mcu_pcint_off() {
    // disable all pin-change interrupts
    
   (*(volatile uint8_t *)((0x3C) + 0x20)) 
         &= ~(1 << 
                   3
                              );
}
////////// misc //////////
void reboot() {
    // put the WDT in hard reset mode, then trigger it
    
   __asm__ __volatile__ ("cli" ::: "memory")
        ;
    // _PROTECTED_WRITE(WDTCSR, 0b10001000);
    // allow protected configuration changes for next 4 clock cycles
    
   (*(volatile uint8_t *)((0x2F) + 0x20)) 
       = 0xD8; // magic number
    // reset (WDIF + WDE), no WDIE, fastest (16ms) timing (0000)
    // (DS section 8.5.2 and table 8-4)
    
   (*(volatile uint8_t *)((0x30) + 0x20)) 
          = 0b10001000;
    
   __asm__ __volatile__ ("sei" ::: "memory")
        ;
    
   __asm__ __volatile__ ("wdr")
              ;
    while (1) {}
}
inline void prevent_reboot_loop() {
    // prevent WDT from rebooting MCU again
    
   (*(volatile uint8_t *)((0x35) + 0x20)) 
         &= ~(1<<
                 3
                     ); // reset status flag
    wdt_disable(); // from avr/wdt.h
}
// Define these in your SpaghettiMonster recipe
// boot-time tasks
void setup();
// single loop iteration, runs continuously
void loop();
// include executable functions too, for easier compiling
// fsm-states.c: State-handling functions for SpaghettiMonster.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
// TODO: if callback doesn't handle current event,
//       pass event to next state on stack?
//       Callback return values:
//       0: event handled normally
//       1: event not handled
//       255: error (not sure what this would even mean though, or what difference it would make)
// TODO: function to call stacked callbacks until one returns "handled"
void _set_state(StatePtr new_state, uint16_t arg,
                Event exit_event, Event enter_event) {
    // call old state-exit hook (don't use stack)
    if (current_state != 
                        ((void *)0)
                            ) current_state(exit_event, arg);
    // set new state
    current_state = new_state;
    // call new state-enter hook (don't use stack)
    if (new_state != 
                    ((void *)0)
                        ) current_state(enter_event, arg);
    // since state changed, stop any animation in progress
    interrupt_nice_delays();
}
int8_t push_state(StatePtr new_state, uint16_t arg) {
    if (state_stack_len < 8) {
        // TODO: call old state's exit hook?
        //       new hook for non-exit recursion into child?
        state_stack[state_stack_len] = new_state;
        state_stack_len ++;
        // FIXME: use EV_stacked_state?
        _set_state(new_state, arg, (0b00000000|0b00001001), (0b00000000|0b00001000));
        return state_stack_len;
    } else {
        // TODO: um...  how is a flashlight supposed to handle a recursion depth error?
        return -1;
    }
}
StatePtr pop_state() {
    // TODO: how to handle pop from empty stack?
    StatePtr old_state = 
                        ((void *)0)
                            ;
    StatePtr new_state = 
                        ((void *)0)
                            ;
    if (state_stack_len > 0) {
        state_stack_len --;
        old_state = state_stack[state_stack_len];
    }
    if (state_stack_len > 0) {
        new_state = state_stack[state_stack_len-1];
    }
    // FIXME: what should 'arg' be?  (maybe re-entry should be entry with arg+1?)
    _set_state(new_state, 0, (0b00000000|0b00001001), (0b00000000|0b00001010));
    return old_state;
}
uint8_t set_state(StatePtr new_state, uint16_t arg) {
    // FIXME: this calls exit/enter hooks it shouldn't
    //        (for the layer underneath the top)
    pop_state();
    return push_state(new_state, arg);
}
void set_state_deferred(StatePtr new_state, uint16_t arg) {
    deferred_state = new_state;
    deferred_state_arg = arg;
}
// bottom state on stack
// handles default actions for LVP, thermal regulation, etc
uint8_t default_state(Event event, uint16_t arg) {
    if (0) {} // this should get compiled out
    else if (event == (0b00000000|0b00000100)) {
        low_voltage();
        return 0;
    }
    // event not handled
    return 1;
}
// fsm-events.c: Event-handling functions for SpaghettiMonster.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
/* Copyright (c) 2002, Marek Michalkiewicz
   Copyright (c) 2007 Joerg Wunsch
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
void append_emission(Event event, uint16_t arg) {
    uint8_t i;
    // find last entry
    for(i=0;
        (i<16) && (emissions[i].event != 0);
        i++) { }
    // add new entry
    if (i < 16) {
        emissions[i].event = event;
        emissions[i].arg = arg;
    } else {
        // TODO: if queue full, what should we do?
    }
}
void delete_first_emission() {
    uint8_t i;
    for(i=0; i<16 -1; i++) {
        emissions[i].event = emissions[i+1].event;
        emissions[i].arg = emissions[i+1].arg;
    }
    emissions[i].event = 0;
    emissions[i].arg = 0;
}
void process_emissions() {
    while (emissions[0].event != 0) {
        emit_now(emissions[0].event, emissions[0].arg);
        delete_first_emission();
    }
}
// Call stacked callbacks for the given event until one handles it.
uint8_t emit_now(Event event, uint16_t arg) {
    for(int8_t i=state_stack_len-1; i>=0; i--) {
        uint8_t err = state_stack[i](event, arg);
        if (! err) return 0;
    }
    return 1; // event not handled
}
void emit(Event event, uint16_t arg) {
    // add this event to the queue for later,
    // so we won't use too much time during an interrupt
    append_emission(event, arg);
}
void emit_current_event(uint16_t arg) {
    emit(current_event, arg);
}
void empty_event_sequence() {
    current_event = 0;
    ticks_since_last_event = 0;
    // when the user completes an input sequence, interrupt any running timers
    // to cancel any delays currently in progress
    // This eliminates a whole bunch of extra code:
    //   before: if (! nice_delay_ms(ms)) {break;}
    //   after: nice_delay_ms(ms);
    interrupt_nice_delays();
}
uint8_t push_event(uint8_t ev_type) { // only for use by PCINT_inner()
    // don't do this here; do it in PCINT_inner() instead
    //ticks_since_last_event = 0;  // something happened
    // only click events are sent to this function
    current_event |= 0b10000000;
    // handle button presses
    if (ev_type == 0b00010000) {
        // set press flag
        current_event |= 0b00010000;
        // increase click counter
        if ((current_event & 0b00001111) < (0b00001111)) {
            current_event ++;
        }
        return 1; // event pushed, even if max clicks already reached
                   // (will just repeat the max over and over)
    }
    // handle button releases
    else if (ev_type == 0b00000000) {
        // clear the press flag
        current_event &= (~0b00010000);
        // if a "hold" event just ended, set the timeout flag
        // to indicate that the event is done and can be cleared
        if (current_event & 0b00100000) { current_event |= 0b01000000; }
        return 1; // event pushed
    }
    return 0; // unexpected event type
}
// explicitly interrupt these "nice" delays
volatile uint8_t nice_delay_interrupt = 0;
inline void interrupt_nice_delays() { nice_delay_interrupt = 1; }
// like delay_ms, except it aborts on state change
// return value:
//   0: state changed
//   1: normal completion
uint8_t nice_delay_ms(uint16_t ms) {
    /*  // delay_zero() implementation
    if (ms == 0) {
        CLKPR = 1<<CLKPCE; CLKPR = 0;  // full speed
        _delay_loop_2(BOGOMIPS*95/100/3);
        return 1;
    }
    */
    while(ms-- > 0) {
        if (nice_delay_interrupt) {
            return 0;
        }
        uint8_t level = actual_level; // volatile, avoid repeat access
        if (level < 10) {
            clock_prescale_set(clock_div_4);
            _delay_loop_2((8000000UL/4000)*90/100/4);
        }
        //else if (level < HALFSPEED_LEVEL) {
        //    clock_prescale_set(clock_div_2);
        //    _delay_loop_2(BOGOMIPS*95/100/2);
        //}
        else {
            clock_prescale_set(clock_div_1);
            _delay_loop_2((8000000UL/4000)*90/100);
        }
        // restore regular clock speed
        clock_prescale_set(clock_div_1);
        // run pending system processes while we wait
        handle_deferred_interrupts();
        // handle events only afterward, so that any collapsed delays will
        // finish running the UI's loop() code before taking any further actions
        // (this helps make sure code runs in the correct order)
        // (otherwise, a new state's EV_enter runs before the old state's
        //  loop() has finished, and things can get weird)
        process_emissions();
    }
    return 1;
}
void delay_4ms(uint8_t ms) {
    while(ms-- > 0) {
        // underclock MCU to save power
        clock_prescale_set(clock_div_4);
        // wait
        _delay_loop_2((8000000UL/4000)*98/100);
        // restore regular clock speed
        clock_prescale_set(clock_div_1);
    }
}
/*
uint8_t nice_delay_4ms(uint8_t ms) {
    return nice_delay_ms((uint16_t)ms << 2);
}
*/
/*
uint8_t nice_delay_s() {
    return nice_delay_4ms(250);
}
*/
// fsm-adc.c: ADC (voltage, temperature) functions for SpaghettiMonster.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
// override onboard temperature sensor definition, if relevant
/* Copyright (c) 2002, 2004 Theodore A. Roth
   Copyright (c) 2004, 2007, 2008 Eric B. Weddington
   Copyright (c) 2005, 2006, 2007 Joerg Wunsch
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
static inline void adc_therm_mode() {
    mcu_set_admux_therm();
    adc_channel = 1;
    adc_sample_count = 0; // first result is unstable
    mcu_adc_start_measurement();
}
void adc_voltage_mode() {
    mcu_set_admux_voltage();
    adc_channel = 0;
    adc_sample_count = 0; // first result is unstable
    mcu_adc_start_measurement();
}
inline void ADC_on() {
    if (go_to_standby && adc_channel == 1)
        adc_therm_mode();
    else
        adc_voltage_mode();
}
// Each full cycle runs ~2X per second with just voltage enabled,
// or ~1X per second with voltage and temperature.
// happens every time the ADC sampler finishes a measurement
void __vector_14 (void) __attribute__ ((signal,used, externally_visible)) ; void __vector_14 (void) 
             {
    // clear the interrupt flag
    ;
    if (adc_sample_count) {
        uint16_t m; // latest measurement
        uint16_t s; // smoothed measurement
        uint8_t channel = adc_channel;
        // update the latest value
            m = mcu_adc_result();
        adc_raw[channel] = m;
        // lowpass the value
        //s = adc_smooth[channel];  // easier to read
        uint16_t *v = adc_smooth + channel; // compiles smaller
        s = *v;
        if (m > s) { s++; }
        if (m < s) { s--; }
        //adc_smooth[channel] = s;
        *v = s;
        // track what woke us up, and enable deferred logic
        irq_adc = 1;
    }
    // the next measurement isn't the first
    adc_sample_count = 1;
    // rollover doesn't really matter
    //adc_sample_count ++;
}
void adc_deferred() {
    irq_adc = 0; // event handled
    // real-world entropy makes this a true random, not pseudo
    // Why here instead of the ISR?  Because it makes the time-critical ISR
    // code a few cycles faster and we don't need crypto-grade randomness.
    pseudo_rand_seed += mcu_adc_lsb();
    // the ADC triggers repeatedly when it's on, but we only need to run the
    // voltage and temperature regulation stuff once in a while...so disable
    // this after each activation, until it's manually enabled again
    if (! adc_deferred_enable) return;
    // disable after one iteration
    adc_deferred_enable = 0;
    // what is being measured? 0 = battery voltage, 1 = temperature
    uint8_t adc_step;
    // do whichever one is currently active
    adc_step = adc_channel;
        // in sleep mode, turn off after just one measurement
        // (having the ADC on raises standby power by about 250 uA)
        // (and the usual standby level is only ~20 uA)
        if (go_to_standby) {
            mcu_adc_off();
            // if any measurements were in progress, they're done now
            adc_active_now = 0;
            // also, check both battery and temperature while asleep
            adc_channel = !adc_channel;
        }
    if (0) {} // placeholder for easier syntax
    else if (0 == adc_step) { // voltage
        ADC_voltage_handler();
        // set the correct type of measurement for next time
        if (! go_to_standby) adc_therm_mode();
    }
    else if (1 == adc_step) { // temperature
        ADC_temperature_handler();
        // set the correct type of measurement for next time
        if (! go_to_standby) adc_voltage_mode();
    }
    if (adc_reset) adc_reset --;
}
static void ADC_voltage_handler() {
    // rate-limit low-voltage warnings to a max of 1 per N seconds
    static uint8_t lvp_timer = 0;
    uint16_t measurement;
    // latest ADC value
    if (adc_reset) { // just after waking, don't lowpass
        measurement = adc_raw[0];
        adc_smooth[0] = measurement; // no lowpass, just use the latest value
    }
    else if (go_to_standby) { // weaker lowpass while asleep
        // occasionally the aux LED color can oscillate during standby,
        // while using "voltage" mode ... so try to reduce the oscillation
        uint16_t r = adc_raw[0];
        uint16_t s = adc_smooth[0];
        // 1/8th proportional lowpass, faster but less stable
        int16_t diff = (r/8) - (s/8);
        s += diff;
        adc_smooth[0] = s;
        measurement = s;
    }
    else measurement = adc_smooth[0];
    // convert raw ADC value to FSM voltage units: Volts * 50
    // 0 .. 250 = 0.0V .. 5.0V
    voltage = mcu_vdivider_raw2cooked(measurement)
              + (0 << 1)
                 + ((cfg.voltage_correction - 7) << 1)
              ;
    // if low, callback EV_voltage_low / EV_voltage_critical
    //         (but only if it has been more than N seconds since last call)
    if (lvp_timer) {
        lvp_timer --;
    } else { // it has been long enough since the last warning
        if (voltage < (29*5)) {
            // send out a warning
            emit((0b00000000|0b00000100), 0);
            // reset rate-limit counter
            lvp_timer = (5*1);
        }
    }
}
// generally happens once per second while awake
static void ADC_temperature_handler() {
    // coarse adjustment
    // reduce frequency of minor warnings
    // fine-grained adjustment
    // how proportional should the adjustments be?
    // acceptable temperature window size in C
    // TODO? make this configurable per build target?
    //       (shorter time for hosts with a lower power-to-mass ratio)
    //       (because then it'll have smaller responses)
    static uint8_t history_step = 0;
    static uint16_t temperature_history[8];
    static int8_t warning_threshold = 0;
    // when we are in standby always use the raw measurement
    if (adc_reset || go_to_standby) adc_smooth[1] = adc_raw[1];
    // latest 16-bit ADC reading
    // convert raw ADC value to Kelvin << 6
    // 0 .. 65535 = 0 K .. 1024 K
    uint16_t measurement = mcu_temp_raw2cooked(adc_smooth[1]);
    // let the UI see the current temperature in C
    // (Kelvin << 6) to Celsius
    // Why 275?  Because Atmel's docs use 275 instead of 273.
    temperature = (measurement>>6) + 5 + (int16_t)cfg.therm_cal_offset - 275;
    // instead of (K << 6), use (K << 1) now
    // TODO: use more precision, if it can be done without overflow in 16 bits
    //       (and still work on attiny85 without increasing ROM size)
    measurement = measurement >> 5;
    if (adc_reset) { // wipe out old data after waking up
        // forget any past measurements
        for(uint8_t i=0; i<8; i++)
            temperature_history[i] = measurement;
    }
    // if we are in standby, don't do the rest since we've got the current temperature now
    if (go_to_standby) return;
    // how much has the temperature changed between now and a few seconds ago?
    int16_t diff;
    diff = measurement - temperature_history[history_step];
    // update / rotate the temperature history
    temperature_history[history_step] = measurement;
    history_step = (history_step + 1) & (8 -1);
    // PI[D]: guess what the temperature will be in a few seconds
    uint16_t pt; // predicted temperature
    pt = measurement + (diff * 4);
    // convert temperature limit from C to raw 16-bit ADC units
    // C = (ADC>>6) - 275 + THERM_CAL_OFFSET + TH_CAL;
    // ... so ...
    // (C + 275 - THERM_CAL_OFFSET - TH_CAL) << 6 = ADC;
    uint16_t ceil = (cfg.therm_ceil + 275 - cfg.therm_cal_offset - 5) << 1;
    int16_t offset = pt - ceil;
    // bias small errors toward zero, while leaving large errors mostly unaffected
    // (a diff of 1 C is 2 ADC units, * 4 for therm lookahead, so it becomes 8)
    // (but a diff of 1 C should only send a warning of magnitude 1)
    // (this also makes it only respond to small errors at the time the error
    // happened, not after the temperature has stabilized)
    for(uint8_t foo=0; foo<3; foo++) {
        if (offset > 0) {
            offset --;
        } else if (offset < 0) {
            offset ++;
        }
    }
    // Too hot?
    // (if it's too hot and not getting cooler...)
    if ((offset > 0) && (diff > -1)) {
        // accumulated error isn't big enough yet to send a warning
        if (warning_threshold > 0) {
            warning_threshold -= offset;
        } else { // error is big enough; send a warning
            // how far above the ceiling?
            // original method works, but is too slow on some small hosts:
            // (and typically has a minimum response magnitude of 2 instead of 1)
            //   int16_t howmuch = offset;
            // ... so increase the amount, except for small values
            // (for example, 1:1, 2:1, 3:3, 4:5, 6:9, 8:13, 10:17, 40:77)
            // ... and let us tune the response per build target if desired
            int16_t howmuch = (offset + offset - 3) * 64 / 128;
            if (howmuch < 1) howmuch = 1;
            warning_threshold = 24 - (uint8_t)howmuch;
            // send a warning
            emit((0b00000000|0b00000101), howmuch);
        }
    }
    // Too cold?
    // (if it's too cold and still getting colder...)
    // the temperature is this far below the floor:
    else if (((offset + (2<<1)) < 0) && (diff < 0)) {
        // accumulated error isn't big enough yet to send a warning
        if (warning_threshold < 0) {
            warning_threshold -= (offset + (2<<1));
        } else { // error is big enough; send a warning
            warning_threshold = (-24) - (offset + (2<<1));
            // how far below the floor?
            // int16_t howmuch = ((-BELOW) >> 1) * THERM_RESPONSE_MAGNITUDE / 128;
            int16_t howmuch = (-(offset + (2<<1))) >> 1;
            // send a notification (unless voltage is low)
            // (LVP and underheat warnings fight each other)
            if (voltage > ((29*5) + 1))
                emit((0b00000000|0b00000110), howmuch);
        }
    }
    // Goldilocks?
    // (temperature is within target window, or at least heading toward it)
    else {
        // send a notification (unless voltage is low)
        // (LVP and temp-okay events fight each other)
        if (voltage > (29*5))
            emit((0b00000000|0b00000111), 0);
    }
}
void battcheck() {
        blink_num(voltage / 5);
            // 0.02V precision, 0 1 2 3 4 remainder -> .00 .02 .04 .06 .08V
            blink_num((voltage % 5) * (10/5));
}
// fsm-wdt.c: WDT (Watch Dog Timer) functions for SpaghettiMonster.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
/* Copyright (c) 2002,2005,2007 Marek Michalkiewicz
   Copyright (c) 2007, Dean Camera
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
/* Copyright (c) 2002, 2004 Marek Michalkiewicz
   Copyright (c) 2005, 2006, 2007 Eric B. Weddington
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
/*
   avr/wdt.h - macros for AVR watchdog timer
 */
// clock tick -- this runs every 16ms (62.5 fps)
void __vector_5 (void) __attribute__ ((signal,used, externally_visible)) ; void __vector_5 (void) 
             {
    ;
    irq_wdt = 1; // WDT event happened
}
void WDT_inner() {
    irq_wdt = 0; // WDT event handled; reset flag
    static uint8_t adc_trigger = 0;
    // cache this here to reduce ROM size, because it's volatile
    uint16_t ticks_since_last = ticks_since_last_event;
    // increment, but loop from max back to half
    ticks_since_last = (ticks_since_last + 1)
                     | (ticks_since_last & 0x8000);
    // copy back to the original
    ticks_since_last_event = ticks_since_last;
    // detect and emit button change events (even during standby)
    uint8_t was_pressed = button_last_state;
    uint8_t pressed = button_is_pressed();
    if (was_pressed != pressed) {
        go_to_standby = 0;
        PCINT_inner(pressed);
    }
    // cache again, in case the value changed
    ticks_since_last = ticks_since_last_event;
    // handle standby mode specially
    if (go_to_standby) {
        // emit a sleep tick, and process it
        emit((0b00000000|0b00000011), ticks_since_last);
        process_emissions();
        // stop here, usually...  except during the first few seconds asleep, 
        // and once in a while afterward for sleep LVP
        if ((ticks_since_last > (8 * 8))
            && (0 != (ticks_since_last & 0x0f))) return;
        adc_trigger = 0; // make sure a measurement will happen
        adc_active_now = 1; // use ADC noise reduction sleep mode
        ADC_on(); // enable ADC voltage/temperature measurement functions temporarily
    }
    else { // button handling should only happen while awake
    // if time since last event exceeds timeout,
    // append timeout to current event sequence, then
    // send event to current state callback
    // callback on each timer tick
    if ((current_event & 0b11110000) == (0b10000000 | 0b00100000 | 0b00010000)) {
        emit((0b00000000|0b00000001), 0); // override tick counter while holding button
    }
    else {
        emit((0b00000000|0b00000001), ticks_since_last);
    }
    // user held button long enough to count as a long click?
    if (current_event & 0b00010000) {
        // during a "hold", send a hold event each tick, with a timer
        if (current_event & 0b00100000) {
            emit_current_event(ticks_since_last);
        }
        // has button been down long enough to become a "hold"?
        // (first frame of a "hold" event)
        else {
            if (ticks_since_last >= 24) {
                ticks_since_last_event = 0;
                current_event |= 0b00100000;
                emit_current_event(0);
            }
        }
    }
    // event in progress, but button not currently down
    else if (current_event) {
        // "hold" event just ended
        // no timeout required when releasing a long-press
        if (current_event & 0b00100000) {
            //emit_current_event(ticks_since_last);  // should have been emitted by PCINT_inner()
            empty_event_sequence();
        }
        // end and clear event after release timeout
        else if (ticks_since_last >= 18) {
            current_event |= 0b01000000;
            emit_current_event(0);
            empty_event_sequence();
        }
    }
    }
    // enable the deferred ADC handler once in a while
    if (! adc_trigger) {
        mcu_adc_start_measurement();
        adc_deferred_enable = 1;
    }
    // timing for the ADC handler is every 32 ticks (~2Hz)
    adc_trigger = (adc_trigger + 1) & 31;
}
// fsm-pcint.c: PCINT (Pin Change Interrupt) functions for SpaghettiMonster.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
/* Copyright (c) 2002,2005,2007 Marek Michalkiewicz
   Copyright (c) 2007, Dean Camera
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
/* Copyright (c) 2002, Marek Michalkiewicz
   Copyright (c) 2007 Joerg Wunsch
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
uint8_t button_is_pressed() {
    uint8_t value = ((
                     (*(volatile uint8_t *)((0x0F) + 0x20)) 
                                 & (1<<
                                       7
                                                 )) == 0);
    button_last_state = value;
    return value;
}
void __vector_2 (void) __attribute__ ((signal,used, externally_visible)) ; void __vector_2 (void) 
                {
    ;
    irq_pcint = 1; // let deferred code know an interrupt happened
    //DEBUG_FLASH;
    // as it turns out, it's more reliable to detect pin changes from WDT
    // because PCINT itself tends to double-tap when connected to a
    // noisy / bouncy switch (so the content of this function has been
    // moved to a separate function, called from WDT only)
    // PCINT_inner(button_is_pressed());
}
// should only be called from PCINT and/or WDT
// (is a separate function to reduce code duplication)
void PCINT_inner(uint8_t pressed) {
    button_last_state = pressed;
    // register the change, and send event to the current state callback
    if (pressed) { // user pressed button
        push_event(0b00010000);
        emit_current_event(0);
    } else { // user released button
        // how long was the button held?
        push_event(0b00000000);
        emit_current_event(ticks_since_last_event);
    }
    ticks_since_last_event = 0;
}
// fsm-standby.c: standby mode functions for SpaghettiMonster.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
/* Copyright (c) 2002,2005,2007 Marek Michalkiewicz
   Copyright (c) 2007, Dean Camera
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
/* Copyright (c) 2002, 2004 Theodore A. Roth
   Copyright (c) 2004, 2007, 2008 Eric B. Weddington
   Copyright (c) 2005, 2006, 2007 Joerg Wunsch
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
// low-power standby mode used while off but power still connected
void sleep_until_eswitch_pressed()
{
    mcu_wdt_standby();
    mcu_adc_off();
    // make sure switch isn't currently pressed
    while (button_is_pressed()) {}
    empty_event_sequence(); // cancel pending input on suspend
    mcu_pcint_on(); // wake on e-switch event
    // detect which type of event caused a wake-up
    irq_adc = 0;
    irq_wdt = 0;
    irq_pcint = 0;
    while (go_to_standby) {
        // configure sleep mode
            // needs a special sleep mode during measurements
            if (adc_active_now) mcu_adc_sleep_mode();
            else
        
       do { (*(volatile uint8_t *)((0x36) + 0x20)) = (((*(volatile uint8_t *)((0x36) + 0x20)) & ~((1 << (5)) | (1 << (6)))) | ((0x02<<5))); } while(0)
                                          ;
        
       do { (*(volatile uint8_t *)((0x36) + 0x20)) |= (uint8_t)(1 << (4)); } while(0)
                     ;
        
       do { __asm__ __volatile__ ( "sleep" "\n\t" :: ); } while(0)
                  ; // wait here
        // something happened; wake up
        
       do { (*(volatile uint8_t *)((0x36) + 0x20)) &= (uint8_t)(~(1 << (4))); } while(0)
                      ;
        // determine what woke us up...
        if (irq_pcint) { // button pressed; wake up
            go_to_standby = 0;
        }
        if (irq_adc) { // ADC done measuring
            adc_deferred_enable = 1;
            adc_deferred();
            //ADC_off();  // takes care of itself
            //irq_adc = 0;  // takes care of itself
        }
        if (irq_wdt) { // generate a sleep tick
            WDT_inner();
        }
    }
    // don't lowpass immediately after waking
    // also, reset thermal history
    adc_reset = 2;
    // go back to normal running mode
    // PCINT not needed any more, and can cause problems if on
    // (occasional reboots on wakeup-by-button-press)
    mcu_pcint_off();
    // restore normal awake-mode interrupts
    ADC_on();
    mcu_wdt_active();
}
void idle_mode()
{
    // configure sleep mode
    
   do { (*(volatile uint8_t *)((0x36) + 0x20)) = (((*(volatile uint8_t *)((0x36) + 0x20)) & ~((1 << (5)) | (1 << (6)))) | ((0x00<<5))); } while(0)
                                  ;
    
   do { (*(volatile uint8_t *)((0x36) + 0x20)) |= (uint8_t)(1 << (4)); } while(0)
                 ;
    
   do { __asm__ __volatile__ ( "sleep" "\n\t" :: ); } while(0)
              ; // wait here
    // something happened; wake up
    
   do { (*(volatile uint8_t *)((0x36) + 0x20)) &= (uint8_t)(~(1 << (4))); } while(0)
                  ;
}
// fsm-channels.c: Channel mode functions for SpaghettiMonster.
// Copyright (C) 2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
void set_channel_mode(uint8_t mode) {
    if (mode == channel_mode) return; // abort if nothing to do
    uint8_t cur_level = actual_level;
    // turn off old LEDs before changing channel
    set_level(0);
    // change the channel
    channel_mode = mode;
    // update the LEDs
    set_level(cur_level);
}
///// Common set_level_*() functions shared by multiple lights /////
// (unique lights should use their own,
//  but these common versions cover most of the common hardware designs)
// TODO: upgrade some older lights to dynamic PWM
// TODO: 1ch w/ dynamic PWM
// TODO: 1ch w/ dynamic PWM and opamp enable pins?
// TODO: 2ch stacked w/ dynamic PWM
// TODO: 2ch stacked w/ dynamic PWM and opamp enable pins?
// fsm-ramping.c: Ramping functions for SpaghettiMonster.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
inline void set_level_aux_leds(uint8_t level) {
        if (! go_to_standby) {
                rgb_led_set(0);
                    button_led_set((level > 0) + (level > 70));
        }
}
void set_level(uint8_t level) {
    // maybe "jump start" the engine, if it's prone to slow starts
    // (pulse the output high for a moment to wake up the power regulator)
    // (only do this when starting from off and going to a low level)
    // TODO: allow different jump start behavior per channel mode
    // FIXME: don't jump-start during factory reset
    //        (it seems to cause some eeprom issues on KR4
    //         when doing a click with a loose tailcap)
    if ((! actual_level)
            && level
            && (level < cfg.jump_start_level)) {
        set_level(cfg.jump_start_level);
        delay_4ms(8/4);
    }
    set_level_aux_leds(level);
    if (0 == level) {
        set_level_zero();
    } else {
        // call the relevant hardware-specific set_level_*()
        SetLevelFuncPtr set_level_func = channels[channel_mode].set_level;
        set_level_func(level - 1);
    }
    if (actual_level != level) prev_level = actual_level;
    actual_level = level;
    gradual_target = level;
    auto_clock_speed();
}
inline void set_level_gradually(uint8_t lvl) {
    gradual_target = lvl;
}
// call this every frame or every few frames to change brightness very smoothly
void gradual_tick() {
    uint8_t gt = gradual_target;
    if (gt < actual_level) gt = actual_level - 1;
    else if (gt > actual_level) gt = actual_level + 1;
    // call the relevant hardware-specific function
    GradualTickFuncPtr gradual_tick_func = channels[channel_mode].gradual_tick;
    uint8_t done = gradual_tick_func(gt - 1);
    if (done) {
        uint8_t orig = gradual_target;
        set_level(gt);
        gradual_target = orig;
    }
}
// fsm-random.c: Random number generator for SpaghettiMonster.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
uint8_t pseudo_rand() {
    static uint16_t offset = 1024;
    // loop from 1024 to 4095
    offset = ((offset + 1) & 0x0fff) | 0x0400;
    pseudo_rand_seed += 0b01010101; // 85
    return 
          (__extension__({ uint16_t __addr16 = (uint16_t)((uint16_t)(
          offset
          )); uint8_t __result; __asm__ __volatile__ ( "lpm %0, Z" "\n\t" : "=r" (__result) : "z" (__addr16) ); __result; })) 
                                + pseudo_rand_seed;
}
// fsm-eeprom.c: EEPROM API for SpaghettiMonster.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
uint8_t *eeprom;
uint8_t load_eeprom() {
    delay_4ms(2); // wait for power to stabilize
    
   __asm__ __volatile__ ("cli" ::: "memory")
        ;
    // check if eeprom has been initialized; abort if it hasn't
    uint8_t marker = eeprom_read_byte((uint8_t *)0);
    if (marker != 0b10100101) { 
                               __asm__ __volatile__ ("sei" ::: "memory")
                                    ; return 0; }
    // load the actual data
    for(uint8_t i=0; i<sizeof(Config); i++) {
        eeprom[i] = eeprom_read_byte((uint8_t *)(0 +1+i));
    }
    
   __asm__ __volatile__ ("sei" ::: "memory")
        ;
    return 1;
}
void save_eeprom() {
    delay_4ms(2); // wait for power to stabilize
    
   __asm__ __volatile__ ("cli" ::: "memory")
        ;
    // save the actual data
    for(uint8_t i=0; i<sizeof(Config); i++) {
        eeprom_update_byte((uint8_t *)(0 +1+i), eeprom[i]);
    }
    // save the marker last, to indicate the transaction is complete
    eeprom_update_byte((uint8_t *)0, 0b10100101);
    
   __asm__ __volatile__ ("sei" ::: "memory")
        ;
}
// fsm-misc.c: Miscellaneous function for SpaghettiMonster.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
void auto_clock_speed() {
    uint8_t level = actual_level; // volatile, avoid repeat access
    if (level < 10) {
        // run at quarter speed
        // note: this only works when executed as two consecutive instructions
        // (don't try to combine them or put other stuff between)
        clock_prescale_set(clock_div_4);
    }
    else if (level < 20) {
        // run at half speed
        clock_prescale_set(clock_div_2);
    } else {
        // run at full speed
        clock_prescale_set(clock_div_1);
    }
}
uint8_t blink_digit(uint8_t num) {
    //StatePtr old_state = current_state;
    // "zero" digit gets a single short blink
    uint8_t ontime = 1000 * 2 / 12;
    if (!num) { ontime = 12; num ++; }
    // channel is set per blink, to prevent issues
    // if another mode interrupts us (like a config menu)
    uint8_t old_channel = channel_mode;
    for (; num>0; num--) {
        // TODO: allow setting a blink channel mode per build target
            set_channel_mode(cfg.blink_channel);
        set_level(45);
            channel_mode = old_channel;
        nice_delay_ms(ontime);
            set_channel_mode(cfg.blink_channel);
        set_level(0);
            channel_mode = old_channel;
        nice_delay_ms(1000 * 3 / 12);
    }
    set_channel_mode(old_channel);
    return nice_delay_ms(1000 * 8 / 12);
}
void morse_blink(char *morse_code, uint8_t level) {
    for (char *p = morse_code; *p; p++) {
        if (*p == '.') {
            set_level(level);
            nice_delay_ms(200);
            set_level(0);
        } else if (*p == '-') {
            set_level(level);
            nice_delay_ms(200 * 3);
            set_level(0);
        }
        // Space between elements of the same letter
        nice_delay_ms(200);
    }
    // Space between letters
    nice_delay_ms(200 * 2);
}
void blink_digit_in_morse(uint8_t digit, uint8_t level) {
    // Define the Morse code for each digit
    static const char *morse_map[] = {
        "-----", // 0
        ".----", // 1
        "..---", // 2
        "...--", // 3
        "....-", // 4
        ".....", // 5
        "-....", // 6
        "--...", // 7
        "---..", // 8
        "----." // 9
    };
    morse_blink((char *)morse_map[digit], level);
}
uint8_t blink_num(uint8_t num) {
    uint8_t level = 15; //  TODO: make this configurable under 9H
    // Check the value of cfg.num_mode
    if (cfg.num_mode == 1) {
        // Original decimal blinking functionality
        uint8_t hundreds = num / 100;
        num = num % 100;
        uint8_t tens = num / 10;
        num = num % 10;
        if (hundreds) blink_digit(hundreds);
        if (hundreds || tens) blink_digit(tens);
        return blink_digit(num);
    }
    else if (cfg.num_mode == 2) {
        // Morse code blinking functionality
        uint8_t hundreds = num / 100;
        num = num % 100;
        uint8_t tens = num / 10;
        num = num % 10;
        if (hundreds) blink_digit_in_morse(hundreds, level);
        if (hundreds || tens) blink_digit_in_morse(tens, level);
        blink_digit_in_morse(num, level);
        // Return the last digit or another appropriate value
        return num;
    }
    return 0; // Default return value (if cfg.num_mode is not 1 or 2)
}
// TODO: Refactor this and RGB LED function to merge code and save space
void button_led_set(uint8_t lvl) {
    if (button_led_off) lvl = 0;
    switch (lvl) {
        // FIXME: move this logic to arch/*
        case 0: // LED off
            
           (*(volatile uint8_t *)((0x10) + 0x20)) 
                           &= 0xff ^ (1 << 
                                           2
                                                         );
            
           (*(volatile uint8_t *)((0x12) + 0x20)) 
                           &= 0xff ^ (1 << 
                                           2
                                                         );
            
           (*(volatile uint8_t *)((0x11) + 0x20)) 
                           &= 0xff ^ (1 << 
                                           2
                                                         );
            break;
        case 1: // LED low
            
           (*(volatile uint8_t *)((0x10) + 0x20)) 
                           &= 0xff ^ (1 << 
                                           2
                                                         );
            
           (*(volatile uint8_t *)((0x12) + 0x20)) 
                           |= (1 << 
                                    2
                                                  );
            
           (*(volatile uint8_t *)((0x11) + 0x20)) 
                           |= (1 << 
                                    2
                                                  );
            break;
        default: // LED high
            
           (*(volatile uint8_t *)((0x10) + 0x20)) 
                           |= (1 << 
                                    2
                                                  );
            
           (*(volatile uint8_t *)((0x12) + 0x20)) 
                           |= (1 << 
                                    2
                                                  );
            
           (*(volatile uint8_t *)((0x11) + 0x20)) 
                           |= (1 << 
                                    2
                                                  );
            break;
    }
}
void rgb_led_set(uint8_t value) {
    // value: 0b00BBGGRR
    uint8_t pins[] = { 
                      5
                                  , 
                                    4
                                                , 
                                                  3 
                                                               };
    for (uint8_t i=0; i<3; i++) {
        uint8_t lvl = (value >> (i<<1)) & 0x03;
        uint8_t pin = pins[i];
        switch (lvl) {
            // FIXME: move this logic to arch/*
            case 0: // LED off
                
               (*(volatile uint8_t *)((0x10) + 0x20)) 
                               &= 0xff ^ (1 << pin);
                
               (*(volatile uint8_t *)((0x12) + 0x20)) 
                               &= 0xff ^ (1 << pin);
                
               (*(volatile uint8_t *)((0x11) + 0x20)) 
                               &= 0xff ^ (1 << pin);
                break;
            case 1: // LED low
                
               (*(volatile uint8_t *)((0x10) + 0x20)) 
                               &= 0xff ^ (1 << pin);
                
               (*(volatile uint8_t *)((0x12) + 0x20)) 
                               |= (1 << pin);
                
               (*(volatile uint8_t *)((0x11) + 0x20)) 
                               |= (1 << pin);
                break;
            default: // LED high
                
               (*(volatile uint8_t *)((0x10) + 0x20)) 
                               |= (1 << pin);
                
               (*(volatile uint8_t *)((0x12) + 0x20)) 
                               |= (1 << pin);
                
               (*(volatile uint8_t *)((0x11) + 0x20)) 
                               |= (1 << pin);
                break;
        }
    }
}
uint8_t triangle_wave(uint8_t phase) {
    uint8_t result = phase << 1;
    if (phase > 127) result = 255 - result;
    return result;
}
// fsm-main.c: main() function for SpaghettiMonster.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
int main() {
    // Don't allow interrupts while booting
    
   __asm__ __volatile__ ("cli" ::: "memory")
        ;
    // prevents cycling after a crash,
    // whether intentional (like factory reset) or not (bugs)
    prevent_reboot_loop();
    hwdef_setup();
    // all booted -- turn interrupts back on
    mcu_pcint_on();
    // FIXME: support both WDT *and* RTC PIT on newer devices
    // (WDT to recover from crashes, PIT for task scheduling)
    // (old AVR had only WDT, newer ones split it into WDT, RTC, and PIT)
    mcu_wdt_active();
    ADC_on();
    
   __asm__ __volatile__ ("sei" ::: "memory")
        ;
    // in case any spurious button presses were detected at boot
    delay_4ms(1);
    // fallback for handling a few things
    push_state(default_state, 0);
    nice_delay_interrupt = 0;
    // call recipe's setup
    setup();
    // main loop
    while (1) {
        // if event queue not empty, empty it
        process_emissions();
        // if loop() tried to change state, process that now
        StatePtr df = deferred_state;
        if (df) {
            set_state(df, deferred_state_arg);
            deferred_state = 
                            ((void *)0)
                                ;
            //deferred_state_arg = 0;  // unnecessary
        }
        // enter standby mode if requested
        // (works better if deferred like this)
        if (go_to_standby) {
            set_level(0);
            sleep_until_eswitch_pressed();
        }
        // catch up on interrupts
        handle_deferred_interrupts();
        // turn delays back on, if they were off
        nice_delay_interrupt = 0;
        // give the recipe some time slices
        loop();
    }
}
void handle_deferred_interrupts() {
    /*
    if (irq_pcint) {  // button pressed or released
        // nothing to do here
        // (PCINT only matters during standby)
    }
    */
    if (irq_adc) { // ADC done measuring
        adc_deferred();
        // irq_adc = 0;  // takes care of itself
    }
    if (irq_wdt) { // the clock ticked
        WDT_inner();
        // irq_wdt = 0;  // takes care of itself
    }
}
/********* does this build target have special code to include? *********/
// Emisar 2-channel-plus-FET-joined-into-1-channel
// Copyright (C) 2024 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
// channel modes for RGB aux LEDs
// Copyright (C) 2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
void set_level_auxred(uint8_t level) {
    rgb_led_set(0b000001 << !(!(level))); // red, high (level > 0) or low
}
void set_level_auxyel(uint8_t level) {
    rgb_led_set(0b000101 << !(!(level))); // red+green, high (level > 0) or low
}
void set_level_auxgrn(uint8_t level) {
    rgb_led_set(0b000100 << !(!(level))); // green, high (level > 0) or low
}
void set_level_auxcyn(uint8_t level) {
    rgb_led_set(0b010100 << !(!(level))); // green+blue, high (level > 0) or low
}
void set_level_auxblu(uint8_t level) {
    rgb_led_set(0b010000 << !(!(level))); // blue, high (level > 0) or low
}
void set_level_auxprp(uint8_t level) {
    rgb_led_set(0b010001 << !(!(level))); // red+blue, high (level > 0) or low
}
void set_level_auxwht(uint8_t level) {
    rgb_led_set(0b010101 << !(!(level))); // red+green+blue, high (level > 0) or low
}
uint8_t gradual_tick_null(uint8_t gt) { return 1; } // do nothing
void set_level_zero();
void set_level_ch1(uint8_t level);
void set_level_ch1_fet(uint8_t level);
uint8_t gradual_tick_ch1(uint8_t gt);
uint8_t gradual_tick_ch1_fet(uint8_t gt);
Channel channels[] = {
    { // channel 1 only
        .set_level = set_level_ch1,
        .gradual_tick = gradual_tick_ch1,
        // .has_args     = 0
    },
    { // channel 1 + DD FET
        .set_level = set_level_ch1_fet,
        .gradual_tick = gradual_tick_ch1_fet,
        // .has_args     = 0
    },
    { .set_level = set_level_auxred, .gradual_tick = gradual_tick_null }, { .set_level = set_level_auxyel, .gradual_tick = gradual_tick_null }, { .set_level = set_level_auxgrn, .gradual_tick = gradual_tick_null }, { .set_level = set_level_auxcyn, .gradual_tick = gradual_tick_null }, { .set_level = set_level_auxblu, .gradual_tick = gradual_tick_null }, { .set_level = set_level_auxprp, .gradual_tick = gradual_tick_null }, { .set_level = set_level_auxwht, .gradual_tick = gradual_tick_null }
};
void set_level_zero() {
    // disable timer overflow interrupt
    // (helps improve button press handling from Off state)
    
   (*(volatile uint8_t *)((0x3A) + 0x20)) 
               &= ~(1<<
                   7
                   );
    // turn off all LEDs
    ch1_dsm_lvl = 0;
    //ch2_dsm_lvl = 0;
    
   (*(volatile uint16_t *)(0x6C)) 
               = 0;
    
   (*(volatile uint16_t *)(0x6A)) 
               = 0;
    
   (*(volatile uint8_t *)((0x18) + 0x20)) 
               = 0;
    
   (*(volatile uint16_t *)(0x6E)) 
               = 0; // reset phase
    
   (*(volatile uint8_t *)((0x11) + 0x20)) 
                   &= ~(1 << 
                             0
                                           ); // disable opamp
    
   (*(volatile uint8_t *)((0x11) + 0x20)) 
                   &= ~(1 << 
                             1
                                           ); // disable opamp
}
// wrap setting the dsm vars, to get a faster response
// (just setting *_dsm_lvl doesn't work well for strobes)
// set new values for both channels,
// handling any possible combination
// and any before/after state
void set_hw_levels(uint16_t ch1,
                   //PWM2_DATATYPE ch2,
                   uint8_t ch3
                   //, bool ch1_on, bool ch2_on
                   ) {
    //bool was_on = (CH1_PWM>0) || (CH2_PWM>0)
    //            || ( CH1_ENABLE_PORT & (1 << CH1_ENABLE_PIN) )
    //            || ( CH2_ENABLE_PORT & (1 << CH2_ENABLE_PIN) );
    //if (ch1 || ch1_on)
        
       (*(volatile uint8_t *)((0x11) + 0x20)) 
                       |= (1 << 
                                0
                                              ); // enable opamp
    //else
    //    CH1_ENABLE_PORT &= ~(1 << CH1_ENABLE_PIN);  // disable opamp
    //if (ch2 || ch2_on)
    //    CH2_ENABLE_PORT |= (1 << CH2_ENABLE_PIN);  // enable opamp
    //else
    //    CH2_ENABLE_PORT &= ~(1 << CH2_ENABLE_PIN);  // disable opamp
    // set delta-sigma soft levels
    ch1_dsm_lvl = ch1;
    //ch2_dsm_lvl = ch2;
    // set hardware PWM levels and init dsm loop
    
   (*(volatile uint16_t *)(0x6C)) 
           = ch1_pwm = ch1 >> 7;
    //CH2_PWM = ch2_pwm = ch2 >> 7;
    
   (*(volatile uint8_t *)((0x18) + 0x20)) 
           = ch3;
    // enable timer overflow interrupt so DSM can work
    
   (*(volatile uint8_t *)((0x3A) + 0x20)) 
               |= (1<<
                  7
                  );
    // reset phase when turning on
    if (! prev_level) 
                     (*(volatile uint16_t *)(0x6E)) 
                             = 0;
}
// delta-sigma modulation of PWM outputs
// happens on each Timer overflow (every 512 cpu clock cycles)
// uses 8-bit pwm w/ 7-bit dsm (0b 0PPP PPPP PDDD DDDD)
void __vector_9 (void) __attribute__ ((signal,used, externally_visible)) ; void __vector_9 (void) 
             {
    // set new hardware values first,
    // for best timing (reduce effect of interrupt jitter)
    
   (*(volatile uint16_t *)(0x6C)) 
           = ch1_pwm;
    //CH2_PWM = ch2_pwm;
    // calculate next values, now that timing matters less
    // accumulate error
    ch1_dsm += (ch1_dsm_lvl & 0x007f);
    // next PWM = base PWM value + carry bit
    ch1_pwm = (ch1_dsm_lvl >> 7) + (ch1_dsm > 0x7f);
    // clear carry bit
    ch1_dsm &= 0x7f;
    // repeat for other channels
    //ch2_dsm += (ch2_dsm_lvl & 0x007f);
    //ch2_pwm  = (ch2_dsm_lvl >> 7) + (ch2_dsm > 0x7f);
    //ch2_dsm &= 0x7f;
}
void set_level_ch1(uint8_t level) {
    uint16_t pwm1 = 
                        (__extension__({ uint16_t __addr16 = (uint16_t)((uint16_t)(
                        pwm1_levels+level
                        )); uint16_t __result; __asm__ __volatile__ ( "lpm %A0, Z+" "\n\t" "lpm %B0, Z" "\n\t" : "=r" (__result), "=z" (__addr16) : "1" (__addr16) ); __result; }))
                                       ;
    set_hw_levels(pwm1, 0);
}
void set_level_ch1_fet(uint8_t level) {
    uint16_t pwm2 = 
                        (__extension__({ uint16_t __addr16 = (uint16_t)((uint16_t)(
                        pwm2_levels+level
                        )); uint16_t __result; __asm__ __volatile__ ( "lpm %A0, Z+" "\n\t" "lpm %B0, Z" "\n\t" : "=r" (__result), "=z" (__addr16) : "1" (__addr16) ); __result; }))
                                       ;
    uint8_t pwm3 = 
                        (__extension__({ uint16_t __addr16 = (uint16_t)((uint16_t)(
                        pwm3_levels+level
                        )); uint8_t __result; __asm__ __volatile__ ( "lpm %0, Z" "\n\t" : "=r" (__result) : "z" (__addr16) ); __result; }))
                                       ;
    set_hw_levels(pwm2, pwm3);
}
///// bump each channel toward a target value /////
uint8_t gradual_adjust(uint16_t ch1,
                    //PWM2_DATATYPE ch2,
                    uint8_t ch3) {
    // instant 0 to TOP change, and TOP to 0
    if ((((255<<7) == ch1_dsm_lvl) && (0 == ch1)) ||
        (((255<<7) == ch1) && (0 == ch1_dsm_lvl)))
        ch1_dsm_lvl = ch1;
    // bump the DD FET multiple steps
    // (it only has 255 steps, but the effect is small
    //  compared to the linear channel it's stacked on,
    //  so smaller steps tend to overheat on turbo)
    for (uint8_t i=0; i<4; i++)
        if (
       (*(volatile uint8_t *)((0x18) + 0x20)) 
       < ch3) 
       (*(volatile uint8_t *)((0x18) + 0x20)) 
       ++; else if (
       (*(volatile uint8_t *)((0x18) + 0x20)) 
       > ch3) 
       (*(volatile uint8_t *)((0x18) + 0x20)) 
       --;;
    // if DSM changed by less than 100%,
    // adjust multiple times based on current brightness
    // (so it adjusts faster/coarser when bright, slower/finer when dim)
    // higher shift = slower/finer adjustments
    const uint8_t shift = 9; // ((255 << 7) >> 9) = 63 max
    uint8_t steps;
    steps = ch1_dsm_lvl >> shift;
    for (uint8_t i=0; i<=steps; i++)
        if (ch1_dsm_lvl < ch1) ch1_dsm_lvl ++; else if (ch1_dsm_lvl > ch1) ch1_dsm_lvl --;;
    //steps = ch2_dsm_lvl  >> shift;
    ////for (uint8_t i=0; i<=steps; i++)
    ////    GRADUAL_ADJUST_SIMPLE(ch2, ch2_dsm_lvl);
    if ((ch1 == ch1_dsm_lvl)
     //&& (ch2 == ch2_dsm_lvl)
     && (ch3 == 
               (*(volatile uint8_t *)((0x18) + 0x20))
                      ) ) {
        return 1; // done
    }
    return 0; // not done yet
}
uint8_t gradual_tick_ch1(uint8_t gt) {
    uint16_t pwm1 = 
                        (__extension__({ uint16_t __addr16 = (uint16_t)((uint16_t)(
                        pwm1_levels+gt
                        )); uint16_t __result; __asm__ __volatile__ ( "lpm %A0, Z+" "\n\t" "lpm %B0, Z" "\n\t" : "=r" (__result), "=z" (__addr16) : "1" (__addr16) ); __result; }))
                                    ;
    return gradual_adjust(pwm1, 0);
}
uint8_t gradual_tick_ch1_fet(uint8_t gt) {
    uint16_t pwm2 = 
                        (__extension__({ uint16_t __addr16 = (uint16_t)((uint16_t)(
                        pwm2_levels+gt
                        )); uint16_t __result; __asm__ __volatile__ ( "lpm %A0, Z+" "\n\t" "lpm %B0, Z" "\n\t" : "=r" (__result), "=z" (__addr16) : "1" (__addr16) ); __result; }))
                                    ;
    uint8_t pwm3 = 
                        (__extension__({ uint16_t __addr16 = (uint16_t)((uint16_t)(
                        pwm3_levels+gt
                        )); uint8_t __result; __asm__ __volatile__ ( "lpm %0, Z" "\n\t" : "=r" (__result) : "z" (__addr16) ); __result; }))
                                    ;
    return gradual_adjust(pwm2, pwm3);
}
/********* Include all the regular app headers *********/
// off-mode.h: "Off" mode for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
// was the light in an "on" mode within the past second or so?
uint8_t ticks_since_on = 0;
// when the light is "off" or in standby
uint8_t off_state(Event event, uint16_t arg);
// ramp-mode.h: Ramping functions for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
       
// config-mode.h: Config mode base functions for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
// menus can use 2 colors
// when true, changes the channel mode for each config step
uint8_t config_color_per_step = 0;
// config menu
uint8_t config_state_base(
    Event event,
    uint16_t arg,
    uint8_t num_config_steps,
    void (*savefunc)(uint8_t step, uint8_t value)
    );
typedef enum {
    globals_cfg_zero = 0,
    jump_start_config_step,
    num_mode_config_step,
    globals_config_num_steps
} globals_config_steps_e;
//void globals_config_save(uint8_t step, uint8_t value);
//uint8_t globals_config_state(Event event, uint16_t arg);
void globals_config_save(uint8_t step, uint8_t value) {
    if (0) {}
    else if (step == jump_start_config_step) { cfg.jump_start_level = value; }
    else if (step == num_mode_config_step) { cfg.num_mode = value; }
}
uint8_t globals_config_state(Event event, uint16_t arg) {
    return config_state_base(event, arg,
                             globals_config_num_steps - 1,
                             globals_config_save);
}
// TODO: Replace MAX_Xx7135 with MAX_CH1, MAX_CH2, MAX_REGULATED, etc
// thermal properties, if not defined per-driver
// TODO: Move these settings to config-default.h?
// start in the simple UI after each factory reset?
// configure the timing of turning on/off in regular ramp mode
// press: react as soon as the button is pressed
// release: react as soon as the button is released
// timeout: react as soon as we're sure the user isn't doing a double-click
// defaults are release on, timeout off
// default ramp options if not overridden earlier per-driver
// mile marker(s) partway up the ramp
// default: blink only at border between regulated and FET
// ramping mode and its related config mode
uint8_t steady_state(Event event, uint16_t arg);
uint8_t ramp_config_state(Event event, uint16_t arg);
void ramp_config_save(uint8_t step, uint8_t value);
uint8_t simple_ui_config_state(Event event, uint16_t arg);
uint8_t child_ui_config_state(Event event, uint16_t arg);
uint8_t ramp_extras_config_state(Event event, uint16_t arg);
// calculate the nearest ramp level which would be valid at the moment
// (is a no-op for smooth ramp, but limits discrete ramp to only the
// correct levels for the user's config)
uint8_t nearest_level(int16_t target);
// ensure ramp globals are correct
void ramp_update_config();
// brightness before thermal step-down
uint8_t target_level = 0;
void set_level_and_therm_target(uint8_t level);
// brightness control
uint8_t memorized_level = 70;
    void manual_memory_restore();
    void manual_memory_save();
// current values, regardless of style
uint8_t ramp_floor = 1;
uint8_t ramp_ceil = 150;
uint8_t ramp_discrete_step_size; // don't set this
uint8_t sunset_timer_orig_level = 0;
void reset_sunset_timer();
typedef enum {
    ramp_extras_cfg_zero = 0,
    manual_memory_config_step,
    manual_memory_timer_config_step,
    dont_ramp_after_moon_config_step,
    ramp_2c_style_config_step,
    smooth_steps_style_config_step,
    ramp_extras_config_num_steps
} ramp_extras_config_steps_e;
// aux-leds.h: Aux LED functions for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
uint8_t setting_rgb_mode_now = 0;
void rgb_led_update(uint8_t mode, uint16_t arg);
void rgb_led_voltage_readout(uint8_t bright);
/*
 * 0: R
 * 1: RG
 * 2:  G
 * 3:  GB
 * 4:   B
 * 5: R B
 * 6: RGB
 * 7: rainbow
 * 8: voltage
 */
const 
     __attribute__((__progmem__)) 
             uint8_t rgb_led_colors[] = {
    0b00000000, // 0: black
    0b00000001, // 1: red
    0b00000101, // 2: yellow
    0b00000100, // 3: green
    0b00010100, // 4: cyan
    0b00010000, // 5: blue
    0b00010001, // 6: purple
    0b00010101, // 7: white
};
// intentionally 1 higher than total modes, to make "voltage" easier to reach
// (at Hank's request)
//#define RGB_LED_LOCKOUT_DEFAULT 0x39  // blinking, voltage
//#define RGB_LED_LOCKOUT_DEFAULT 0x37  // blinking, disco
//#define USE_OLD_BLINKING_INDICATOR
//#define USE_FANCIER_BLINKING_INDICATOR
// misc.h: Misc extra functions for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
//void blink_confirm(uint8_t num);  // no longer used
void blink_once();
void blink_some(uint8_t times);
void blip();
void blip_ms(uint8_t ms);
// sunset-timer.h: Sunset / candle auto-shutoff functions for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
// how many minutes to add each time the user "bumps" the timer?
// automatic shutoff timer
uint8_t sunset_timer = 0; // minutes remaining in countdown
uint8_t sunset_timer_peak = 0; // total minutes in countdown
uint16_t sunset_ticks = 0; // counts from 0 to TICKS_PER_MINUTE, then repeats
uint8_t sunset_timer_state(Event event, uint16_t arg);
// version-check-mode.h: Version check mode for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
const 
     __attribute__((__progmem__)) 
             uint8_t version_number[] = "0137" "." "2023-12-03+119#1";
uint8_t version_check_state(Event event, uint16_t arg);
inline void version_check_iter();
// battcheck-mode.h: Battery check mode for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
uint8_t battcheck_state(Event event, uint16_t arg);
void voltage_config_save(uint8_t step, uint8_t value);
uint8_t voltage_config_state(Event event, uint16_t arg);
// beacon-mode.h: Beacon mode for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
// beacon mode
uint8_t beacon_state(Event event, uint16_t arg);
inline void beacon_mode_iter();
// tempcheck-mode.h: Temperature check mode for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
uint8_t tempcheck_state(Event event, uint16_t arg);
uint8_t thermal_config_state(Event event, uint16_t arg);
void thermal_config_save(uint8_t step, uint8_t value);
// lockout-mode.h: Lockout mode for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
// soft lockout
uint8_t lockout_state(Event event, uint16_t arg);
uint8_t autolock_config_state(Event event, uint16_t arg);
// momentary-mode.h: Momentary mode for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
// momentary / signalling mode
uint8_t momentary_state(Event event, uint16_t arg);
uint8_t momentary_mode = 0; // 0 = ramping, 1 = strobe
uint8_t momentary_active = 0; // boolean, true if active *right now*
// tactical-mode.h: Tactical mode for Anduril.
// Copyright (C) 2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
// tactical(ish) mode
uint8_t tactical_state(Event event, uint16_t arg);
uint8_t tactical_config_state(Event event, uint16_t arg);
// allow the channel mode handler even when only 1 mode
// (so a tint ramp light could still use 3H even if there's no other mode)
// channel-modes.h: Multi-channel functions for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
// not actually a mode, more of a fallback under other modes
uint8_t channel_mode_state(Event event, uint16_t arg);
uint8_t channel_mode_config_state(Event event, uint16_t arg);
// factory-reset.h: Factory reset functions for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
void factory_reset();
// this one detects its own enable/disable settings
// strobe-modes.h: Strobe modes for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
strobe_mode_te current_strobe_type;
// which strobe mode is active?
// full FET strobe can be a bit much...  use max regulated level instead,
// if there's a bright enough regulated level
// some drivers need to keep the regulator chip on between pulses,
// so set this to 1 to keep the light on at moon mode between pulses,
// and thus keep the regulator powered up for the next flash
// party and tactical strobes
uint8_t strobe_state(Event event, uint16_t arg);
inline void strobe_state_iter();
inline void party_tactical_strobe_mode_iter(uint8_t st);
inline void police_color_strobe_iter();
inline void lightning_storm_iter();
// bike mode config options
    inline void bike_flasher_iter();
inline void firework_iter();
uint8_t lighthouse_phase = 0;
inline void lighthouse_iter();
uint8_t fluoresent_flicker_random = 1;
uint8_t fluoresent_flicker_index = 0;
uint8_t fluoresent_ramp_up_increment = 0;
inline void bad_fluorescent_iter();
// candle-mode.h: Candle mode for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
uint8_t candle_mode_state(Event event, uint16_t arg);
// moved to fsm-misc.c because it's also used for tint ramping power correction
//uint8_t triangle_wave(uint8_t phase);
typedef enum {
    candle_wobble_e,
    fireplace_slow_wobble_e,
    fireplace_fast_wobble_e,
    wobble_mode_END
} wobble_mode_te;
const int NUM_WOBBLE = wobble_mode_END;
wobble_mode_te wobble_style;
// sos-mode.h: SOS mode for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
// automatic SOS emergency signal
uint8_t sos_state(Event event, uint16_t arg);
// smooth-steps.h: Smooth step adjustments for Anduril.
// Copyright (C) 2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
uint8_t smooth_steps_start;
uint8_t smooth_steps_target;
uint8_t smooth_steps_in_progress;
uint8_t smooth_steps_speed;
void smooth_steps_iter();
void set_level_smooth(uint8_t level, uint8_t speed);
// this should be last, so other headers have a chance to declare values
// load-save-config.h: Load/save/eeprom functions for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
// remember stuff even after battery was changed
void load_config();
void save_config();
// a struct to hold config values
Config cfg = {
    ///// ramp vars
    // smooth vs discrete ramping
    .ramp_style = 0, // 0 = smooth, 1 = discrete
        // 1 = A1 style, 2 = A2 style
        .ramp_2c_style = 1,
    // settings for each ramp (smooth, stepped, simple UI)
        .ramp_floors = {
            1,
            10,
                10,
                10,
            },
        .ramp_ceils = {
            150,
            130,
                130,
                (150/3),
            },
        .ramp_stepss = {
            1,
            7,
                5,
                2,
            },
        // whether to enable the simplified interface or not
        .simple_ui_active = 0,
            // 0 = no turbo, 1 = A1 style, 2 = A2 style
            .ramp_2c_style_simple = 0,
            .child_ui_active = 0,
            .child_ui_floor = 10,
            .child_ui_ceil = (150/3),
            .saved_ramp_style = 0,
        .dont_ramp_after_moon = 0,
        .manual_memory = 0,
            .manual_memory_timer = 0,
    ///// channel modes / color modes
        // current multi-channel mode
        .channel_mode = CM_CH1_FET,
        // user can take unwanted modes out of the rotation (bitmask)
        .channel_modes_enabled = 0b0000000000000010,
            // reset w/ manual memory
            .manual_memory_channel_mode = CM_CH1_FET,
            // blink numbers in a specific channel (user configurable)
            .blink_channel = CM_CH1_FET,
    ///// Smooth animation between steps, and for on/off
        .smooth_steps_style = 1,
    ///// strobe / blinky mode settings
        .strobe_type = candle_mode_e,
        // party / tactical strobe timing
        // party strobe 24 Hz, tactical strobe 10 Hz
        .strobe_delays = { 41, 67 },
        .bike_flasher_brightness = (150/3),
        // beacon timing
        .beacon_seconds = 2,
        .lightning_busy_factor = 14,
        .candle_amplitude = 33,
        .candle_wobble_style = 0,
        .firework_brightness = 150,
        .lighthouse_delay = 5,
        .fluoresent_brightness = 70,
    ///// voltage and temperature
        // same 0.05V units as fudge factor,
        // but 7 is neutral, and the expected range is from 1 to 13
        .voltage_correction = 7,
        .therm_ceil = 45,
        .therm_cal_offset = -3,
    ///// aux LEDs
        .rgb_led_off_mode = 0x2C,
        .rgb_led_lockout_mode = 0x5B,
            // display voltage readout for a while after turning off?
            .post_off_voltage = 4,
    ///// misc other mode settings
        .autolock_time = 2,
        .tactical_levels = { 130,30,(150 +3) },
    ///// hardware config / globals menu
        .jump_start_level = 22,
        .num_mode = 2,
        .temp_unit = 2,
        .dont_ramp_after_moon = 1,
};
/********* Include all the app logic source files *********/
// (is a bit weird to do things this way,
//  but it saves a lot of space by letting us use the -fwhole-program flag)
// off-mode.c: "Off" mode for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
// set level smooth maybe
void off_state_set_level(uint8_t level);
uint8_t off_state(Event event, uint16_t arg) {
    // turn emitter off when entering state
    if (event == (0b00000000|0b00001000)) {
        // turn off
        off_state_set_level(0);
        button_led_off = 0;
            // don't go to sleep while animating
            arg |= smooth_steps_in_progress;
        ticks_since_on = 0;
            // reset to ramp mode's channel when light turns off
            channel_mode = cfg.channel_mode;
        // redundant, sleep tick does the same thing
        //rgb_led_update(cfg.rgb_led_off_mode, 0);
        sunset_timer = 0; // needs a reset in case previous timer was aborted
        // sleep while off  (lower power use)
        // (unless delay requested; give the ADC some time to catch up)
        if (! arg) { go_to_standby = 1; }
        return 0;
    }
    // go back to sleep eventually if we got bumped but didn't leave "off" state
    else if (event == (0b00000000|0b00000001)) {
        if (arg > 24
                && (! smooth_steps_in_progress)
            ) {
            go_to_standby = 1;
            // redundant, sleep tick does the same thing
            //rgb_led_update(cfg.rgb_led_off_mode, arg);
        }
        return 0;
    }
    // blink the indicator LED, maybe
    else if (event == (0b00000000|0b00000011)) {
        if (ticks_since_on < 255) ticks_since_on ++;
        // reset to manual memory level when timer expires
        if (cfg.manual_memory &&
                (arg >= (cfg.manual_memory_timer * 450))) {
            manual_memory_restore();
        }
        if (voltage < (33*5))
            rgb_led_update(0|(4<<4), arg);
        else
            rgb_led_update(cfg.rgb_led_off_mode, arg);
            // lock the light after being off for N minutes
            uint16_t ticks = cfg.autolock_time * 450;
            if ((cfg.autolock_time > 0) && (arg > ticks)) {
                set_state(lockout_state, 0);
            }
        return 0;
    }
    // hold: go to lowest level
    else if (event == (0b10000000|0b00100000|0b00010000|1)) {
        off_state_set_level(nearest_level(1));
        if (cfg.dont_ramp_after_moon) {
            return 0;
        }
        // don't start ramping immediately;
        // give the user time to release at moon level
        //if (arg >= HOLD_TIMEOUT) {  // smaller
        if (arg >= (!cfg.ramp_style) * 24) { // more consistent
            set_state(steady_state, 1);
        }
        return 0;
    }
    // hold, release quickly: go to lowest level (floor)
    else if (event == (0b10000000|0b00100000|0b00000000|0b01000000|1)) {
        set_state(steady_state, 1);
        return 0;
    }
    // 1 click (before timeout): go to memorized level, but allow abort for double click
    else if (event == (0b10000000|0b00000000|1)) {
        off_state_set_level(nearest_level(memorized_level));
        return 0;
    }
    // 1 click: regular mode
    else if (event == (0b10000000|0b01000000|1)) {
        set_state(steady_state, memorized_level);
        return 0;
    }
    // click, hold: momentary at ceiling or turbo
    else if (event == (0b10000000|0b00100000|0b00010000|2)) {
        ticks_since_on = 0; // momentary turbo is definitely "on"
        uint8_t turbo_level; // how bright is "turbo"?
            uint8_t style_2c = cfg.ramp_2c_style;
            // simple UI has its own turbo config
            if (cfg.simple_ui_active) style_2c = cfg.ramp_2c_style_simple;
            // 0  = ceiling
            // 1+ = full power
            if (0 == style_2c) turbo_level = nearest_level(150);
            else turbo_level = 150;
        off_state_set_level(turbo_level);
        return 0;
    }
    else if (event == (0b10000000|0b00100000|0b00000000|0b01000000|2)) {
        off_state_set_level(0);
        return 0;
    }
    // 2 clicks: highest mode (ceiling)
    else if (event == (0b10000000|0b01000000|2)) {
        set_state(steady_state, 150);
        return 0;
    }
    // 3 clicks (initial press): off, to prep for later events
    else if (event == (0b10000000|0b00010000|3)) {
            // immediately cancel any animations in progress
            smooth_steps_in_progress = 0;
        off_state_set_level(0);
        return 0;
    }
    // 3 clicks: battcheck mode / blinky mode group 1
    else if (event == (0b10000000|0b01000000|3)) {
        set_state(battcheck_state, 0);
        return 0;
    }
    // 4 clicks: soft lockout
    else if (event == (0b10000000|0b01000000|4)) {
        blink_once();
        set_state(lockout_state, 0);
        return 0;
    }
    // 13 clicks and hold the last click: invoke factory reset (reboot)
    else if (event == (0b10000000|0b00100000|0b00010000|13)) {
        reboot();
        return 0;
    }
    // 15+ clicks: show the version number
    else if (event == (0b10000000|0b01000000|15)) {
        set_state(version_check_state, 0);
        return 0;
    }
    else if ((event == (0b10000000|0b00100000|0b00010000|12)) && (!arg)) {
        if (cfg.child_ui_active) { // turn off child UI, meaning go back to adv mode
            blink_some(3);
            cfg.simple_ui_active = cfg.child_ui_active = 0;
            // restore original ramp style (smooth or discrete)
            cfg.ramp_style = cfg.saved_ramp_style;
            save_config();
        } else { // configure child UI ramp
            push_state(child_ui_config_state, 0);
        }
        return 0;
    }
    // every action below is blocked in Child UI
    if (cfg.child_ui_active) {
        return 1;
    }
    else if (event == (0b10000000|0b01000000|12)) {
        blink_some(2);
        // use simple UI variant: child UI
        cfg.simple_ui_active = cfg.child_ui_active = 1;
        // setting ramp style
        cfg.saved_ramp_style = cfg.ramp_style;
        cfg.ramp_style = 1;
        save_config();
        return 0;
    }
    // 10 clicks, but hold last click: turn simple UI off (or configure it)
    else if ((event == (0b10000000|0b00100000|0b00010000|10)) && (!arg)) {
        if (cfg.simple_ui_active) { // turn off simple UI
            blink_once();
            cfg.simple_ui_active = 0;
            save_config();
        }
        else { // configure simple UI ramp
            push_state(simple_ui_config_state, 0);
        }
        return 0;
    }
    ////////// Every action below here is blocked in the (non-Extended) Simple UI //////////
    // click, click, long-click: strobe mode
    else if (event == (0b10000000|0b00100000|0b00010000|3)) {
        set_state(strobe_state, 0);
        return 0;
    }
    // 7 clicks: change RGB aux LED pattern
    else if (event == (0b10000000|0b01000000|7)) {
        uint8_t mode = (cfg.rgb_led_off_mode >> 4) + 1;
        mode = mode % 6;
        cfg.rgb_led_off_mode = (mode << 4) | (cfg.rgb_led_off_mode & 0x0f);
        rgb_led_update(cfg.rgb_led_off_mode, 0);
        save_config();
        blink_once();
        return 0;
    }
    // 7 clicks (hold last): change RGB aux LED color
    else if (event == (0b10000000|0b00100000|0b00010000|7)) {
        setting_rgb_mode_now = 1;
        if (0 == (arg & 0x3f)) {
            uint8_t mode = (cfg.rgb_led_off_mode & 0x0f) + 1;
            mode = mode % 13;
            cfg.rgb_led_off_mode = mode | (cfg.rgb_led_off_mode & 0xf0);
            //save_config();
        }
        rgb_led_update(cfg.rgb_led_off_mode, arg);
        return 0;
    }
    else if (event == (0b10000000|0b00100000|0b00000000|0b01000000|7)) {
        setting_rgb_mode_now = 0;
        save_config();
        return 0;
    }
    ////////// Every action below here is blocked in the Extended Simple UI //////////
    if (cfg.simple_ui_active) {
        return 1;
    }
    // 10 clicks: enable simple UI
    else if (event == (0b10000000|0b01000000|10)) {
        blink_once();
        cfg.simple_ui_active = 1;
        save_config();
        return 0;
    }
    // 5 clicks: momentary mode
    else if (event == (0b10000000|0b01000000|5)) {
        blink_once();
        set_state(momentary_state, 0);
        return 0;
    }
    // 6 clicks: tactical mode
    else if (event == (0b10000000|0b01000000|6)) {
        blink_once();
        set_state(tactical_state, 0);
        return 0;
    }
    // 9 clicks, but hold last click: configure misc global settings
    else if ((event == (0b10000000|0b00100000|0b00010000|9)) && (!arg)) {
        push_state(globals_config_state, 0);
        return 0;
    }
    return 1;
}
void off_state_set_level(uint8_t level) {
    // this pattern gets used a few times, so reduce duplication
        if (cfg.smooth_steps_style) set_level_smooth(level, 8);
        else
    set_level(level);
}
// ramp-mode.c: Ramping functions for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
uint8_t steady_state(Event event, uint16_t arg) {
    static int8_t ramp_direction = 1;
        channel_mode = cfg.channel_mode;
    // make sure ramp globals are correct...
    // ... but they already are; no need to do it here
    //ramp_update_config();
    //nearest_level(1);  // same effect, takes less space
    uint8_t mode_min = ramp_floor;
    uint8_t mode_max = ramp_ceil;
    uint8_t step_size;
    if (cfg.ramp_style) { step_size = ramp_discrete_step_size; }
    else { step_size = 1; }
    // how bright is "turbo"?
    uint8_t turbo_level;
        uint8_t style_2c = cfg.ramp_2c_style;
        // simple UI has its own turbo config
        if (cfg.simple_ui_active) style_2c = cfg.ramp_2c_style_simple;
        // 0 = no turbo
        // 1 = Anduril 1 direct to turbo
        // 2 = Anduril 2 direct to ceiling, or turbo if already at ceiling
        if (0 == style_2c) turbo_level = mode_max;
        else if (1 == style_2c) turbo_level = 150;
        else {
            if (memorized_level < mode_max) { turbo_level = mode_max; }
            else { turbo_level = 150; }
        }
    // handle the shutoff timer first
    uint8_t sunset_active = sunset_timer; // save for comparison
    // clock tick
    sunset_timer_state(event, arg);
    // if the timer was just turned on
    if (sunset_timer && (! sunset_active)) {
        sunset_timer_orig_level = actual_level;
    }
    // if the timer just expired, shut off
    else if (sunset_active && (! sunset_timer)) {
        set_state(off_state, 0);
        return 0;
    }
    // turn LED on when we first enter the mode
    if ((event == (0b00000000|0b00001000)) || (event == (0b00000000|0b00001010))) {
        momentary_mode = 0; // 0 = ramping, 1 = strobes
        // if we just got back from config mode, go back to memorized level
        if (event == (0b00000000|0b00001010)) {
            arg = memorized_level;
        }
        // remember this level, unless it's moon or turbo
        if ((arg > mode_min) && (arg < mode_max))
            memorized_level = arg;
        // use the requested level even if not memorized
        arg = nearest_level(arg);
        set_level_and_therm_target(arg);
        ramp_direction = 1;
        return 0;
    }
    // 1 click: off
    else if (event == (0b10000000|0b01000000|1)) {
        set_state(off_state, 0);
        return 0;
    }
    // 2 clicks: go to/from highest level
    else if (event == (0b10000000|0b01000000|2)) {
        if (actual_level < turbo_level) {
            set_level_and_therm_target(turbo_level);
        }
        else {
            set_level_and_therm_target(memorized_level);
        }
        reset_sunset_timer();
        return 0;
    }
    // 4 clicks: shortcut to lockout mode
    else if (event == (0b10000000|0b01000000|4)) {
        set_level(0);
        set_state(lockout_state, 0);
        return 0;
    }
    // hold: change brightness (brighter, dimmer)
    // click, hold: change brightness (dimmer)
    else if ((event == (0b10000000|0b00100000|0b00010000|1)) || (event == (0b10000000|0b00100000|0b00010000|2))) {
        // ramp infrequently in stepped mode
        if (cfg.ramp_style && (arg % 24 != 0))
            return 0;
            // ramp slower if user configured things that way
            if ((! cfg.ramp_style) && (arg % (cfg.ramp_stepss[0])))
                return 0;
            // if a brightness transition is already happening,
            // don't interrupt it
            // (like 2C for full turbo then 1H to smooth ramp down
            //  ... without this clause, it flickers because it trips
            //  the "blink at ramp ceil" clause below, over and over)
            if (smooth_steps_in_progress) return 0;
        // fix ramp direction on first frame if necessary
        if (!arg) {
            // click, hold should always go down if possible
            if (event == (0b10000000|0b00100000|0b00010000|2)) { ramp_direction = -1; }
            // make it ramp down instead, if already at max
            else if (actual_level >= mode_max) { ramp_direction = -1; }
            // make it ramp up if already at min
            // (off->hold->stepped_min->release causes this state)
            else if (actual_level <= mode_min) { ramp_direction = 1; }
        }
        // if the button is stuck, err on the side of safety and ramp down
        else if ((arg > 62 * 5
                    // FIXME: count from time actual_level hits mode_max,
                    //   not from beginning of button hold
                    * (cfg.ramp_stepss[0])
                    ) && (actual_level >= mode_max)) {
            ramp_direction = -1;
        }
        // if the button is still stuck, lock the light
        else if ((arg > 62 * 10
                    // FIXME: count from time actual_level hits mode_min,
                    //   not from beginning of button hold
                    * (cfg.ramp_stepss[0])
                    ) && (actual_level <= mode_min)) {
            blink_once();
            set_state(lockout_state, 0);
        }
        memorized_level = nearest_level((int16_t)actual_level
                          + (step_size * ramp_direction));
        // only blink once for each threshold
        // FIXME: blinks at beginning of smooth_steps animation instead
        // of the end, so it should blink when actual_level reaches a
        // threshold, instead of when memorized_level does
        // (one possible fix is to just remove mid-ramp blinks entirely,
        //  and just blink only when it hits the top while going up)
        if ((memorized_level != actual_level) && (
                0 // for easier syntax below
                || (memorized_level == 75)
                || (memorized_level == 75)
                // FIXME: only blink at top when going up, not down
                || (memorized_level == mode_max)
                )) {
            blip();
        }
        set_level_and_therm_target(memorized_level);
        reset_sunset_timer();
        return 0;
    }
    // reverse ramp direction on hold release
    else if ((event == (0b10000000|0b00100000|0b00000000|0b01000000|1))
             || (event == (0b10000000|0b00100000|0b00000000|0b01000000|2))) {
        ramp_direction = -ramp_direction;
        return 0;
    }
    else if (event == (0b00000000|0b00000001)) {
        // un-reverse after 1 second
        if (arg == (62 * 2 / 3)) ramp_direction = 1;
        // reduce output if shutoff timer is active
        if (sunset_timer) {
            uint8_t dimmed_level = sunset_timer_orig_level * sunset_timer / sunset_timer_peak;
            uint8_t dimmed_level_next = sunset_timer_orig_level * (sunset_timer-1) / sunset_timer_peak;
            uint8_t dimmed_level_delta = dimmed_level - dimmed_level_next;
            dimmed_level -= dimmed_level_delta * (sunset_ticks/62) / 60;
            if (dimmed_level < 1) dimmed_level = 1;
            set_level_gradually(dimmed_level);
            target_level = dimmed_level;
        }
        int16_t diff = gradual_target - actual_level;
        static uint16_t ticks_since_adjust = 0;
        ticks_since_adjust++;
        if (diff) {
            uint16_t ticks_per_adjust = 256 / 1;
            if (diff < 0) {
                //diff = -diff;
                if (actual_level > 130) {
                    ticks_per_adjust >>= 2;
                }
            } else {
                // rise at half speed
                ticks_per_adjust <<= 1;
            }
            while (diff) {
                ticks_per_adjust >>= 1;
                //diff >>= 1;
                diff /= 2; // because shifting produces weird behavior
            }
            if (ticks_since_adjust > ticks_per_adjust)
            {
                gradual_tick();
                ticks_since_adjust = 0;
            }
        }
        if (voltage < (33*5)) {
            // turn on button and/or rgb aux briefly on high every ~3 seconds
            arg %= (62*3);
            if (arg == 0) {
                button_led_set(2);
                rgb_led_voltage_readout(1);
            } else if (arg == 3) {
                button_led_set(0);
                rgb_led_set(0);
            }
        }
        return 0;
    }
    // overheating: drop by an amount proportional to how far we are above the ceiling
    else if (event == (0b00000000|0b00000101)) {
        if (actual_level > 50) {
            int16_t stepdown = actual_level - arg;
            if (stepdown < 50) stepdown = 50;
            else if (stepdown > 150) stepdown = 150;
            set_level_gradually(stepdown);
        }
        return 0;
    }
    // underheating: increase slowly if we're lower than the target
    //               (proportional to how low we are)
    else if (event == (0b00000000|0b00000110)) {
        if (actual_level < target_level) {
            //int16_t stepup = actual_level + (arg>>1);
            int16_t stepup = actual_level + arg;
            if (stepup > target_level) stepup = target_level;
            else if (stepup < 50) stepup = 50;
            set_level_gradually(stepup);
        }
        return 0;
    }
    // temperature is within target window
    // (so stop trying to adjust output)
    else if (event == (0b00000000|0b00000111)) {
        // if we're still adjusting output...  stop after the current step
        if (gradual_target > actual_level)
            gradual_target = actual_level + 1;
        else if (gradual_target < actual_level)
            gradual_target = actual_level - 1;
        return 0;
    }
    ////////// Every action below here is blocked in the simple UI //////////
    // That is, unless we specifically want to enable 3C for smooth/stepped selection in Simple UI
    // 3 clicks: toggle smooth vs discrete ramping
    // (and/or 6 clicks when there are multiple channel modes)
    // (handle 3C here anyway, when all but 1 mode is disabled)
    else if ((event == (0b10000000|0b01000000|3))
             || (event == (0b10000000|0b01000000|6))
        ) {
            // detect if > 1 channel mode is enabled,
            // and if so, fall through so channel mode code can handle it
            // otherwise, change the ramp style
            if (event == (0b10000000|0b01000000|3)) {
                uint8_t enabled = 0;
                for (uint8_t m=0; m<(2 + 7); m++)
                    enabled += ((cfg.channel_modes_enabled >> m) & 1);
                if (enabled > 1)
                    return 1;
            }
        cfg.ramp_style = !cfg.ramp_style;
        save_config();
        blip();
        memorized_level = nearest_level(actual_level);
        set_level_and_therm_target(memorized_level);
        reset_sunset_timer();
        return 0;
    }
    // If we allowed 3C in Simple UI, now block further actions
    if (cfg.simple_ui_active) {
        return 1;
    }
    // 3H: momentary turbo (on lights with no tint ramping)
    // (or 4H when tint ramping is available)
    else if ((event == (0b10000000|0b00100000|0b00010000|3))
        ) {
        if (! arg) { // first frame only, to allow thermal regulation to work
            uint8_t tl = style_2c ? 150 : turbo_level;
            set_level_and_therm_target(tl);
        }
        return 0;
    }
    else if ((event == (0b10000000|0b00100000|0b00000000|0b01000000|3))
        ) {
        set_level_and_therm_target(memorized_level);
        return 0;
    }
    // 5 clicks: shortcut to momentary mode
    else if (event == (0b10000000|0b01000000|5)) {
        memorized_level = actual_level; // allow turbo in momentary mode
        set_level(0);
        set_state(momentary_state, 0);
        return 0;
    }
    // 7C: temporarily turn off button LED. Will reset when entering off/lockout
    else if (event == (0b10000000|0b01000000|7)) {
        button_led_off = !button_led_off;
        blink_once();
    }
    // 7H: configure this ramp mode
    else if (event == (0b10000000|0b00100000|0b00010000|7)) {
        push_state(ramp_config_state, 0);
        return 0;
    }
    else if (event == (0b10000000|0b01000000|10)) {
        // turn on manual memory and save current brightness
        manual_memory_save();
        save_config();
        blink_once();
        return 0;
    }
    else if (event == (0b10000000|0b00100000|0b00010000|10)) {
        // let user configure a bunch of extra ramp options
        push_state(ramp_extras_config_state, 0);
        return 0;
    }
    return 1;
}
void ramp_config_save(uint8_t step, uint8_t value) {
    // 0 = smooth ramp, 1 = stepped ramp, 2 = simple UI's ramp
    uint8_t style = cfg.ramp_style;
    if (current_state == simple_ui_config_state) style = 2;
    else if (current_state == child_ui_config_state) style = 3;
    // simple UI config is weird...
    // has some ramp extras after floor/ceil/steps
    if (4 == step) {
        cfg.ramp_2c_style_simple = value;
    }
    else
    // save adjusted value to the correct slot
    if (value) {
        // ceiling value is inverted
        if (step == 2) value = 150 + 1 - value;
        // which option are we configuring?
        // TODO? maybe rearrange definitions to avoid the need for this table
        //       (move all ramp values into a single array?)
        uint8_t *steps[] = { cfg.ramp_floors, cfg.ramp_ceils, cfg.ramp_stepss };
        uint8_t *option;
        option = steps[step-1];
        option[style] = value;
    }
}
uint8_t ramp_config_state(Event event, uint16_t arg) {
    const uint8_t num_config_steps = 3;
    return config_state_base(event, arg,
                             num_config_steps, ramp_config_save);
}
uint8_t simple_ui_config_state(Event event, uint16_t arg) {
    return config_state_base(event, arg,
                             4,
                             ramp_config_save);
}
uint8_t child_ui_config_state(Event event, uint16_t arg) {
    return config_state_base(event, arg,
                             2, // only floor and ceil settings
                             ramp_config_save);
}
void ramp_extras_config_save(uint8_t step, uint8_t value) {
    if (0) {}
    // item 1: disable manual memory, go back to automatic
    else if (manual_memory_config_step == step) {
        cfg.manual_memory = 0;
    }
    // item 2: set manual memory timer duration
    // FIXME: should be limited to (65535 / SLEEP_TICKS_PER_MINUTE)
    //   to avoid overflows or impossibly long timeouts
    //   (by default, the effective limit is 145, but it allows up to 255)
    else if (manual_memory_timer_config_step == step) {
        cfg.manual_memory_timer = value;
    }
    // item 3: ramp up after hold-from-off for moon?
    // 0 = yes, ramp after moon
    // 1+ = no, stay at moon
    else if (dont_ramp_after_moon_config_step == step) {
        cfg.dont_ramp_after_moon = value;
    }
    // item 4: Anduril 1 2C turbo, or Anduril 2 2C ceiling?
    // 1 = Anduril 1, 2C turbo
    // 2+ = Anduril 2, 2C ceiling
    else if (ramp_2c_style_config_step == step) {
        cfg.ramp_2c_style = value;
    }
    else if (smooth_steps_style_config_step == step) {
        cfg.smooth_steps_style = value;
    }
}
uint8_t ramp_extras_config_state(Event event, uint16_t arg) {
    return config_state_base(event, arg,
        ramp_extras_config_num_steps - 1,
        ramp_extras_config_save);
}
// find the ramp level closest to the target,
// using only the levels which are allowed in the current state
uint8_t nearest_level(int16_t target) {
    // using int16_t here saves us a bunch of logic elsewhere,
    // by allowing us to correct for numbers < 0 or > 255 in one central place
    // ensure all globals are correct
    ramp_update_config();
    // bounds check
    uint8_t mode_min = ramp_floor;
    uint8_t mode_max = ramp_ceil;
    uint8_t num_steps = cfg.ramp_stepss[1
        + cfg.simple_ui_active
        + cfg.child_ui_active
        ];
    // special case for 1-step ramp... use halfway point between floor and ceiling
    if (cfg.ramp_style && (1 == num_steps)) {
        uint8_t mid = (mode_max + mode_min) >> 1;
        return mid;
    }
    if (target < mode_min) return mode_min;
    if (target > mode_max) return mode_max;
    // the rest isn't relevant for smooth ramping
    if (! cfg.ramp_style) return target;
    uint8_t ramp_range = mode_max - mode_min;
    ramp_discrete_step_size = ramp_range / (num_steps-1);
    uint8_t this_level = mode_min;
    for(uint8_t i=0; i<num_steps; i++) {
        this_level = mode_min + (i * (uint16_t)ramp_range / (num_steps-1));
        int16_t diff = target - this_level;
        if (diff < 0) diff = -diff;
        if (diff <= (ramp_discrete_step_size>>1))
            return this_level;
    }
    return this_level;
}
// ensure ramp globals are correct
void ramp_update_config() {
    uint8_t which = cfg.ramp_style;
    if (cfg.simple_ui_active) { which = 2; }
    if (cfg.child_ui_active) { which = 3; }
    ramp_floor = cfg.ramp_floors[which];
    ramp_ceil = cfg.ramp_ceils[which];
}
void set_level_and_therm_target(uint8_t level) {
    target_level = level;
        // if adjusting by more than 1 ramp level,
        // animate the step change (if smooth steps enabled)
        uint8_t diff = (level > actual_level)
            ? (level - actual_level) : (actual_level - level);
        if (smooth_steps_in_progress
            || (cfg.smooth_steps_style && (diff > 1)))
            set_level_smooth(level, 4);
        else
    set_level(level);
}
void manual_memory_restore() {
    memorized_level = cfg.manual_memory;
        channel_mode = cfg.channel_mode = cfg.manual_memory_channel_mode;
}
void manual_memory_save() {
    cfg.manual_memory = actual_level;
        cfg.manual_memory_channel_mode = channel_mode;
}
void reset_sunset_timer() {
    if (sunset_timer) {
        sunset_timer_orig_level = actual_level;
        sunset_timer_peak = sunset_timer;
        sunset_ticks = 0;
    }
}
// load-save-config.c: Load/save/eeprom functions for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
void load_config() {
    eeprom = (uint8_t *)&cfg;
    if (! load_eeprom()) return;
}
void save_config() {
    eeprom = (uint8_t *)&cfg;
    save_eeprom();
}
// config-mode.c: Config mode base functions for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
// general helper function for config modes
uint8_t number_entry_state(Event event, uint16_t arg);
// return value from number_entry_state()
volatile uint8_t number_entry_value;
// TODO: promote this to fsm-channels.c ?
void set_chan_if(uint8_t cond, uint8_t chan) {
    if ((cond) && (chan != channel_mode))
        set_channel_mode(chan);
}
// allow the user to set a new value for a config option
// can be called two ways:
//   - with a "click" action: Configures first menu item only.
//   - with a "hold" action: Sets user select a menu item and then
//     choose a new value for it.  User should hold button until light
//     blinks N times, to choose menu item N.  Then let go, and light
//     should give a buzzing prompt to enter a number.  Click N times
//     at the prompt to set the new value to N.
// after completing this process, config state calls the savefunc callback
// and then returns to caller/parent state
uint8_t config_state_base(
        Event event,
        uint16_t arg,
        uint8_t num_config_steps,
        void (*savefunc)(uint8_t step, uint8_t value)) {
    static uint8_t config_step;
    static uint8_t orig_channel;
    if (event == (0b00000000|0b00001000)) {
        orig_channel = channel_mode;
        config_step = 0;
        set_level(0);
        // if button isn't held, configure first menu item
        if (! button_last_state) {
            config_step ++;
            push_state(number_entry_state, 0);
        }
    }
    // if initial "hold" event still active
    // blink while holding to indicate option number
    else if ((event & (0b10000000|0b00100000|0b00010000|0b00000000|0b01000000)) == (0b10000000|0b00100000|0b00010000)) {
        if (config_step <= num_config_steps) {
                uint8_t chan = config_step - 1;
                if (chan < (2 + 7))
                    set_chan_if(config_color_per_step, chan);
            if ((62/10) == (arg % (62*3/2))) {
                config_step ++;
                // blink when config step advances
                if (config_step <= num_config_steps) {
                    set_level(150 * 3 / 8);
                }
            }
            else {
                // stay on at a low level to indicate menu is active
                set_level(150 * 1 / 8);
            }
        } else {
            // turn off when end of menu is reached
            set_level(0);
        }
    }
    // button release: activate number entry for one menu item
    else if ((event & (0b10000000|0b00100000|0b00010000|0b00000000|0b01000000)) == (0b10000000|0b00100000|0b00000000|0b01000000)) {
        // ask the user for a number, if they selected a menu item
        if (config_step && config_step <= num_config_steps) {
                // put the colors back how they were
                set_channel_mode(orig_channel);
            push_state(number_entry_state, 0);
        }
        // exit after falling out of end of menu
        else {
            pop_state();
        }
    }
    // an option was set (return from number_entry_state)
    else if (event == (0b00000000|0b00001010)) {
        // process value with parent's callback
        savefunc(config_step, number_entry_value);
        // make changes persist in eeprom
        save_config();
        pop_state();
    }
    else if (event == (0b00000000|0b00001001)) {
        // put the colors back how they were
        set_channel_mode(orig_channel);
    }
    // eat all other events; don't pass any through to parent
    return 0;
}
uint8_t number_entry_state(Event event, uint16_t arg) {
    static uint8_t entry_step;
    if (event == (0b00000000|0b00001000)) {
        number_entry_value = 0;
        entry_step = 0;
        set_level(0); // initial pause should be dark
    }
    // advance through the process:
    // 0: wait a moment
    // 1: "buzz" while counting clicks
    // 2: save and exit
    else if (event == (0b00000000|0b00000001)) {
        // wait a moment
        if (entry_step == 0) {
            if (arg > 62/2) {
                entry_step ++;
                empty_event_sequence(); // reset tick counter to 0
            }
        }
        // buzz while waiting for a number to be entered
        else if (entry_step == 1) {
            // time out and exit after 3 seconds
            if (arg > 62*3) {
                entry_step ++;
                set_level(0);
            }
            // buzz for N seconds after last event
            // (flicker every other frame,
            //  except first frame (so we can see flashes after each click))
            else if (arg) {
                set_level( (150/8)
                           + ((arg&2)<<2) );
            }
        }
        // all done, save result and return to parent state
        else {
            pop_state();
        }
        return 0;
    }
    // count clicks: click = +1, hold = +10
    else if ((event == (0b10000000|0b00000000|1))
            || (event == (0b10000000|0b00100000|0b00000000|0b01000000|1))
            ) {
        entry_step = 1; // in case user clicked during initial delay
            if (event == (0b10000000|0b00100000|0b00000000|0b01000000|1)) number_entry_value += 10;
            else
        number_entry_value ++; // update the result
        empty_event_sequence(); // reset FSM's click count
        set_level(150/2); // flash briefly
        return 0;
    }
    // eat all other events; don't pass any through to parent
    return 0;
}
// aux-leds.c: Aux LED functions for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
uint8_t voltage_to_rgb() {
    static const uint8_t levels[] = {
    // voltage, color
            0, 0, // black
        // li-ion voltages
        29*5, 1, // R
        33*5, 2, // R+G
        35*5, 3, //   G
        37*5, 4, //   G+B
        39*5, 5, //     B
        41*5, 6, // R + B
        44*5, 7, // R+G+B  // skip; looks too similar to G+B
          255, 7, // R+G+B
    };
    uint8_t volts = voltage;
    //if (volts < VOLTAGE_LOW) return 0;
    uint8_t i;
    for (i = 0; volts >= levels[i]; i += 2) {}
    uint8_t color_num = levels[(i - 2) + 1];
    return 
          (__extension__({ uint16_t __addr16 = (uint16_t)((uint16_t)(
          rgb_led_colors + color_num
          )); uint8_t __result; __asm__ __volatile__ ( "lpm %0, Z" "\n\t" : "=r" (__result) : "z" (__addr16) ); __result; }))
                                                   ;
}
uint8_t temperature_to_rgb() {
    static const uint8_t temp_levels[] = {
    // temperature in Celsius, color
          0, 6, // R + B => pink/purple  <=50 F
         10, 5, //     B                 (50,60] F
         16, 4, //   G+B => cyan         (60,70] F
         21, 3, //   G                   (70,80] F
         27, 2, // R+G   => yellow       (80,90] F
         32, 1, // R                     >90 F
        255, 1, // R
    };
    int16_t temps = temperature;
    if (temps < 0) return 0;
    uint8_t i;
    for (i = 0; temps >= temp_levels[i]; i += 2) {}
    uint8_t color_num = temp_levels[(i - 2) + 1];
    return 
          (__extension__({ uint16_t __addr16 = (uint16_t)((uint16_t)(
          rgb_led_colors + color_num
          )); uint8_t __result; __asm__ __volatile__ ( "lpm %0, Z" "\n\t" : "=r" (__result) : "z" (__addr16) ); __result; }))
                                                   ;
}
// do fancy stuff with the RGB aux LEDs
// mode: 0bPPPPCCCC where PPPP is the pattern and CCCC is the color
// arg: time slice number
void rgb_led_update(uint8_t mode, uint16_t arg) {
    static uint8_t rainbow = 0; // track state of rainbow mode
    static uint8_t frame = 0; // track state of animation mode
        static uint8_t spin_step = 0; // track state of spinning RGB mode
    // turn off aux LEDs when battery is empty
    // (but if voltage==0, that means we just booted and don't know yet)
    uint8_t volts = voltage; // save a few bytes by caching volatile value
    if ((volts) && (volts < (29*5))) {
        rgb_led_set(0);
        button_led_set(0);
        return;
    }
    uint8_t pattern = (mode>>4); // off, low, high, blinking, breathing
    uint8_t button_pattern = pattern;
    uint8_t color = mode & 0x0f;
    // always preview in high mode
    if (setting_rgb_mode_now) { pattern = 2; }
    // use voltage high mode for a few seconds after initial poweroff
    // (but not after changing aux LED settings and other similar actions)
    else if ((arg < (cfg.post_off_voltage * 8))
          && (ticks_since_on < (cfg.post_off_voltage * 8))
          && (ticks_since_on > 0) // don't blink red on 1st frame
        ) {
        // use high mode if regular aux level is high or prev level was high
        pattern = 1 + ((2 == pattern) | (prev_level >= (150/10)));
        // voltage mode
        color = 9;
    }
    const uint8_t *colors = rgb_led_colors + 1;
    uint8_t actual_color = 0;
    if (color < 7) { // normal color
        actual_color = 
                      (__extension__({ uint16_t __addr16 = (uint16_t)((uint16_t)(
                      colors + color
                      )); uint8_t __result; __asm__ __volatile__ ( "lpm %0, Z" "\n\t" : "=r" (__result) : "z" (__addr16) ); __result; }))
                                                   ;
    }
    else if (color == 7) { // disco
        rainbow = (rainbow + 1 + pseudo_rand() % 5) % 6;
        actual_color = 
                      (__extension__({ uint16_t __addr16 = (uint16_t)((uint16_t)(
                      colors + rainbow
                      )); uint8_t __result; __asm__ __volatile__ ( "lpm %0, Z" "\n\t" : "=r" (__result) : "z" (__addr16) ); __result; }))
                                                     ;
    }
    else if (color == 8) { // rainbow
        uint8_t speed = 0x03; // awake speed
        if (go_to_standby) speed = 0x0F; // asleep speed
        if (0 == (arg & speed)) {
            rainbow = (rainbow + 1) % 6;
        }
        actual_color = 
                      (__extension__({ uint16_t __addr16 = (uint16_t)((uint16_t)(
                      colors + rainbow
                      )); uint8_t __result; __asm__ __volatile__ ( "lpm %0, Z" "\n\t" : "=r" (__result) : "z" (__addr16) ); __result; }))
                                                     ;
    }
    else if (color == 9) { // voltage
        // show actual voltage while asleep...
        if (go_to_standby) {
            // choose a color based on battery voltage
            actual_color = voltage_to_rgb();
        }
        // ... but during preview, cycle colors quickly
        else {
            actual_color = 
                          (__extension__({ uint16_t __addr16 = (uint16_t)((uint16_t)(
                          colors + (((arg>>1) % 3) << 1)
                          )); uint8_t __result; __asm__ __volatile__ ( "lpm %0, Z" "\n\t" : "=r" (__result) : "z" (__addr16) ); __result; }))
                                                                       ;
        }
    }
    else if (color == 11) { // splat
        uint8_t speed = 0x01; // awake speed
        if (go_to_standby) speed = 0x04; // asleep speed
        if (0 == (arg & speed)) {
            rainbow = (rainbow + 1) % 7;
        }
        actual_color = 
                      (__extension__({ uint16_t __addr16 = (uint16_t)((uint16_t)(
                      colors + rainbow
                      )); uint8_t __result; __asm__ __volatile__ ( "lpm %0, Z" "\n\t" : "=r" (__result) : "z" (__addr16) ); __result; }))
                                                     ;
    }
// Handle the spinning RGB pattern
else if (color == 12) { //rgb spin
    static uint8_t custom_speed_counter = 0;
    uint8_t desired_speed = 2; // Set this to control how many ticks before advancing
    custom_speed_counter++;
    if (custom_speed_counter >= desired_speed) {
        spin_step = (spin_step + 1) % 3; // cycle through 0, 1, 2
        custom_speed_counter = 0;
    }
    switch (spin_step) {
        case 0:
            actual_color = 
                          (__extension__({ uint16_t __addr16 = (uint16_t)((uint16_t)(
                          rgb_led_colors + 5
                          )); uint8_t __result; __asm__ __volatile__ ( "lpm %0, Z" "\n\t" : "=r" (__result) : "z" (__addr16) ); __result; }))
                                                           ; // Blue
            break;
        case 1:
            actual_color = 
                          (__extension__({ uint16_t __addr16 = (uint16_t)((uint16_t)(
                          rgb_led_colors + 1
                          )); uint8_t __result; __asm__ __volatile__ ( "lpm %0, Z" "\n\t" : "=r" (__result) : "z" (__addr16) ); __result; }))
                                                           ; // Red
            break;
        case 2:
            actual_color = 
                          (__extension__({ uint16_t __addr16 = (uint16_t)((uint16_t)(
                          rgb_led_colors + 3
                          )); uint8_t __result; __asm__ __volatile__ ( "lpm %0, Z" "\n\t" : "=r" (__result) : "z" (__addr16) ); __result; }))
                                                           ; // Green
            break;
    }
}
    else { // temperature
        actual_color = temperature_to_rgb();
        if (!go_to_standby) {
            // during preview, flash current temperature's colors quickly
            pattern = (arg >> 1) % 3;
        }
    }
    // uses an odd length to avoid lining up with rainbow loop
    static const uint8_t animation[] = {2, 1, 0, 0, 0, 0, 0, 0, 0,
                                        1, 0, 0, 0, 0, 0, 0, 0, 0, 1};
    static const uint8_t animation_breath[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 2,
                                               2, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    static const uint8_t animation_pulse[] = {1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2,
                                               2, 2, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1};
    // pick a brightness from the animation sequence
    uint8_t blink_animation_done = 0;
    // pick a brightness from the animation sequence
    if (pattern == 3) {
        frame = (frame + 1) % sizeof(animation);
        pattern = animation[frame];
        blink_animation_done = 1;
    } else if (pattern == 4) {
        frame = (frame + 1) % sizeof(animation_breath);
        pattern = animation_breath[frame];
        blink_animation_done = 1;
    } else if (pattern == 5) {
        frame = (frame + 1) % sizeof(animation_pulse);
        pattern = animation_pulse[frame];
        blink_animation_done = 1;
    }
    if (button_pattern == 3) {
        if (blink_animation_done) {
            button_pattern = pattern;
        } else {
            frame = (frame + 1) % sizeof(animation);
            button_pattern = animation[frame];
        }
    } else if (button_pattern == 4) {
        if (blink_animation_done) {
            button_pattern = pattern;
        } else {
            frame = (frame + 1) % sizeof(animation_breath);
            button_pattern = animation_breath[frame];
        }
    }
    uint8_t result;
    switch (pattern) {
        case 0: // off
            result = 0;
            break;
        case 1: // low
            result = actual_color;
            break;
        default: // high
            result = (actual_color << 1);
            break;
    }
    rgb_led_set(result);
    // separate button LED logic here because the button LED may blink while AUX LED doesn't
    button_led_set((button_pattern > 1) ? 2 : button_pattern);
}
void rgb_led_voltage_readout(uint8_t bright) {
    uint8_t color = voltage_to_rgb();
    if (bright) color = color << 1;
    rgb_led_set(color);
}
// misc.c: Misc extra functions for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
/* no longer used
void blink_confirm(uint8_t num) {
    uint8_t brightness = actual_level;
    uint8_t bump = actual_level + BLINK_BRIGHTNESS;
    if (bump > MAX_LEVEL) bump = 0;
    for (; num>0; num--) {
        set_level(bump);
        delay_4ms(10/4);
        set_level(brightness);
        if (num > 1) { delay_4ms(100/4); }
    }
}
*/
// make a short, visible pulse
// (either brighter or darker, depending on current brightness)
void blink_once() {
    uint8_t brightness = actual_level;
    uint8_t bump = brightness + 45;
    if (bump > 150) bump = 0;
    set_level(bump);
    delay_4ms(12/4);
    set_level(brightness);
}
void blink_some(uint8_t times) {
    blink_once();
    for (uint8_t i = 1; i < times; i++) {
        delay_4ms(100); //about 0.4s
        blink_once();
    }
}
// Just go dark for a moment to indicate to user that something happened
void blip() {
    blip_ms(12);
}
// ms must be multiples of 4
void blip_ms(uint8_t ms) {
    uint8_t temp = actual_level;
    set_level(0);
    delay_4ms(ms/4);
    set_level(temp);
}
// sunset-timer.c: Sunset / candle auto-shutoff functions for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
uint8_t sunset_timer_state(Event event, uint16_t arg) {
    // reset on start
    if (event == (0b00000000|0b00001000)) {
        sunset_timer = 0;
        sunset_ticks = 0;
        return 0;
    }
    // hold: maybe "bump" the timer if it's active and almost expired
    else if (event == (0b10000000|0b00100000|0b00010000|1)) {
        // ramping up should "bump" the timer to extend the deadline a bit
        if ((sunset_timer > 0) && (sunset_timer < 4)) {
            sunset_timer = 3; // 3 minutes
            sunset_timer_peak = 3;
            sunset_ticks = 0; // re-start current "minute"
        }
    }
    // 5H: add 5m to timer, per second, until released
    else if (event == (0b10000000|0b00100000|0b00010000|5)) {
        if (0 == (arg % 62)) {
            if (sunset_timer < (255 - 5)) {
                // add a few minutes to the timer
                sunset_timer += 5;
                sunset_timer_peak = sunset_timer; // reset ceiling
                sunset_ticks = 0; // reset phase
                // let the user know something happened
                blink_once();
            }
        }
        return 0;
    }
    // tick: count down until time expires
    else if (event == (0b00000000|0b00000001)) {
        // time passed
        sunset_ticks ++;
        // did we reach a minute mark?
        if (sunset_ticks >= (62*60)) {
            sunset_ticks = 0;
            if (sunset_timer > 0) {
                sunset_timer --;
            }
        }
        return 0;
    }
    return 1;
}
// version-check-mode.c: Version check mode for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
// empty state; logic is handled in FSM loop() instead
uint8_t version_check_state(Event event, uint16_t arg) {
    return 1;
}
// this happens in FSM loop()
inline void version_check_iter() {
    for (uint8_t i=0; i<sizeof(version_number)-1; i++) {
        uint8_t digit = 
                       (__extension__({ uint16_t __addr16 = (uint16_t)((uint16_t)(
                       version_number + i
                       )); uint8_t __result; __asm__ __volatile__ ( "lpm %0, Z" "\n\t" : "=r" (__result) : "z" (__addr16) ); __result; })) 
                                                         - '0';
        //       digits: 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
        //   hex digits: 0 1 2 3 4 5 6 7 8 9  a  b  c  d  e  f
        // 'model' file: 0 1 2 3 4 5 6 7 8 9  :  ;  <  =  >  ?
        if (digit < 16) blink_digit(digit);
        else { // "buzz" for non-numeric characters
            for(uint8_t frame=0; frame<25; frame++) {
                set_level((frame&1) << 5);
                nice_delay_ms(16);
            }
            nice_delay_ms(1000 * 8 / 12);
        }
        nice_delay_ms(300);
    }
    set_state_deferred(off_state, 0);
}
// battcheck-mode.c: Battery check mode for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
uint8_t battcheck_state(Event event, uint16_t arg) {
    ////////// Every action below here is blocked in the simple UI //////////
    if (cfg.simple_ui_active) {
        return 1;
    }
    // 1 click: off
    if (event == (0b10000000|0b01000000|1)) {
        set_state(off_state, 0);
        return 0;
    }
    // 2 clicks: next blinky mode
    else if (event == (0b10000000|0b01000000|2)) {
        set_state(tempcheck_state, 0);
        return 0;
    }
    // 3 clicks: next channel mode (specific to number blinky modes)
    else if (event == (0b10000000|0b01000000|3)) {
        cfg.blink_channel = (cfg.blink_channel + 1) % (2 + 7);
        save_config();
        return 0;
    }
    // 7H: voltage config mode
    else if (event == (0b10000000|0b00100000|0b00010000|7)) {
        push_state(voltage_config_state, 0);
        return 0;
    }
    return 1;
}
// the user can adjust the battery measurements... on a scale of 1 to 13
// 1 = subtract 0.30V
// 2 = subtract 0.25V
// ...
// 7 = no effect (add 0V)
// 8 = add 0.05V
// ...
// 13 = add 0.30V
void voltage_config_save(uint8_t step, uint8_t value) {
        if (2 == step) cfg.post_off_voltage = value;
        else
    if (value) cfg.voltage_correction = value;
}
uint8_t voltage_config_state(Event event, uint16_t arg) {
    return config_state_base(event, arg,
                             2,
                             voltage_config_save);
}
// beacon-mode.c: Beacon mode for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
inline void beacon_mode_iter() {
    // one iteration of main loop()
    if (! button_last_state) {
        set_level(memorized_level);
        nice_delay_ms(100);
        set_level(0);
        nice_delay_ms(((cfg.beacon_seconds) * 1000) - 100);
    }
}
uint8_t beacon_state(Event event, uint16_t arg) {
    // 1 click: off
    if (event == (0b10000000|0b01000000|1)) {
        set_state(off_state, 0);
        return 0;
    }
    // TODO: use sleep ticks to measure time between pulses,
    //       to save power
    // 2 clicks: next blinky mode
    else if (event == (0b10000000|0b01000000|2)) {
        set_state(sos_state, 0);
        return 0;
    }
    // hold: configure beacon timing
    else if (event == (0b10000000|0b00100000|0b00010000|1)) {
        if (0 == (arg % 62)) {
            blink_once();
        }
        return 0;
    }
    // release hold: save new timing
    else if (event == (0b10000000|0b00100000|0b00000000|0b01000000|1)) {
        cfg.beacon_seconds = 1 + (arg / 62);
        save_config();
        return 0;
    }
    return 1;
}
// tempcheck-mode.c: Temperature check mode for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
uint8_t tempcheck_state(Event event, uint16_t arg) {
    // 1 click: off
    if (event == (0b10000000|0b01000000|1)) {
        set_state(off_state, 0);
        return 0;
    }
    // 2 clicks: next blinky mode
    else if (event == (0b10000000|0b01000000|2)) {
        set_state(beacon_state, 0);
        return 0;
    }
    // 7H: thermal config mode
    else if (event == (0b10000000|0b00100000|0b00010000|7)) {
        push_state(thermal_config_state, 0);
        return 0;
    }
    return 1;
}
void thermal_config_save(uint8_t step, uint8_t value) {
    if (value) {
        // item 1: calibrate room temperature
        if (step == 1) {
            int8_t rawtemp = temperature - cfg.therm_cal_offset;
            cfg.therm_cal_offset = value - rawtemp;
            adc_reset = 2; // invalidate all recent temperature data
        }
        // item 2: set maximum heat limit
        else if (step == 2) {
            cfg.therm_ceil = 30 + value - 1;
        }
        // item 3: toggle temperature unit (Celsius or Fahrenheit)
        else if (step == 3) {
            cfg.temp_unit = value; // 1 for Â°C, 2 for Â°F
        }
    }
    if (cfg.therm_ceil > 70) cfg.therm_ceil = 70;
}
uint8_t thermal_config_state(Event event, uint16_t arg) {
    return config_state_base(event, arg,
                             3, thermal_config_save); // 3 steps now
}
// lockout-mode.c: Lockout mode for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
uint8_t lockout_state(Event event, uint16_t arg) {
    // momentary(ish) moon mode during lockout
    // button is being held
    // don't turn on during RGB aux LED configuration
    if (event == (0b10000000|0b00100000|0b00010000|7)) { set_level(0); } else
    if ((event & (0b10000000 | 0b00010000)) == (0b10000000 | 0b00010000)) {
        // hold: lowest floor
        // click, hold: highest floor (or manual mem level)
        uint8_t lvl = cfg.ramp_floors[0];
        if (1 == (event & 0x0f)) { // first click
            if (cfg.ramp_floors[1] < lvl) lvl = cfg.ramp_floors[1];
        } else { // 2nd click or later
            if (cfg.ramp_floors[1] > lvl) lvl = cfg.ramp_floors[1];
            if (cfg.manual_memory) lvl = cfg.manual_memory;
        }
        off_state_set_level(lvl);
    }
    // button was released
    else if ((event & (0b10000000 | 0b00010000)) == (0b10000000)) {
        off_state_set_level(0);
    }
    // regular event handling
    // conserve power while locked out
    // (allow staying awake long enough to exit, but otherwise
    //  be persistent about going back to sleep every few seconds
    //  even if the user keeps pressing the button)
    if (event == (0b00000000|0b00001000)) {
        ticks_since_on = 0;
            rgb_led_update(cfg.rgb_led_lockout_mode, 0);
        button_led_off = 0;
    }
    else if (event == (0b00000000|0b00000001)) {
        if (arg > 24) {
            go_to_standby = 1;
            rgb_led_update(cfg.rgb_led_lockout_mode, arg);
        }
        return 0;
    }
    else if (event == (0b00000000|0b00000011)) {
        if (ticks_since_on < 255) ticks_since_on ++;
        // reset to manual memory level when timer expires
        if (cfg.manual_memory &&
                (arg >= (cfg.manual_memory_timer * 450))) {
            manual_memory_restore();
        }
        if (voltage < (33*5))
            rgb_led_update(0|(4<<4), arg);
        else
            rgb_led_update(cfg.rgb_led_lockout_mode, arg);
        return 0;
    }
    // 3 clicks: exit and turn off
    else if (event == (0b10000000|0b01000000|3)) {
        blink_once();
        set_state(off_state, 0);
        return 0;
    }
    // 4 clicks: exit and turn on
    else if (event == (0b10000000|0b01000000|4)) {
        set_state(steady_state, memorized_level);
        return 0;
    }
    // 4 clicks, but hold last: exit and start at floor
    else if (event == (0b10000000|0b00100000|0b00010000|4)) {
        //blink_once();
        blip();
        // reset button sequence to avoid activating anything in ramp mode
        current_event = 0;
        // ... and back to ramp mode
        set_state(steady_state, 1);
        return 0;
    }
    // 5 clicks: exit and turn on at mid level
    else if (event == (0b10000000|0b01000000|5)) {
        //set_state(steady_state, MAX_LEVEL);
        set_state(steady_state, 75);
        return 0;
    }
        // 5 clicks and hold: momentary mid
    else if (event == (0b10000000|0b00100000|0b00010000|5)) {
        // Set to middle level (75/150) when the button is held
        //set_level(steady_state, 75);
        off_state_set_level(75);
        //off_state_set_level(memorized_level);
        return 0;
    }
    // Release after 5 clicks and hold: return to lockout
    else if (event == (0b10000000|0b00100000|0b00000000|0b01000000|5)) {
        // Turn off the light and return to lockout mode
        //set_level(0);
        off_state_set_level(0);
        return 0;
    }
    // 6 clicks: exit and turn on at ceiling level
    else if (event == (0b10000000|0b01000000|6)) {
        //set_state(steady_state, MAX_LEVEL);
        off_state_set_level(150);
        return 0;
    }
        // 5 clicks and hold: momentary turbo
    else if (event == (0b10000000|0b00100000|0b00010000|6)) {
        // Set to maximum level (turbo) when the button is held
        //set_level(MAX_LEVEL);
        off_state_set_level(150);
        return 0;
    }
    // Release after 6 clicks and hold: return to lockout
    else if (event == (0b10000000|0b00100000|0b00000000|0b01000000|6)) {
        // Turn off the light and return to lockout mode
        //set_level(0);
        off_state_set_level(0);
        return 0;
    }
    // 3H: next channel mode
    else if (event == (0b10000000|0b00100000|0b00010000|3)) {
        if (0 == (arg % 62)) {
            // pretend the user clicked 3 times to change channels
            return channel_mode_state((0b10000000|0b01000000|3), 0);
        }
    }
    ////////// Every action below here is blocked in the (non-Extended) Simple UI //////////
    // 7 clicks: change RGB aux LED pattern
    else if (event == (0b10000000|0b01000000|7)) {
        uint8_t mode = (cfg.rgb_led_lockout_mode >> 4) + 1;
        mode = mode % 6;
        cfg.rgb_led_lockout_mode = (mode << 4) | (cfg.rgb_led_lockout_mode & 0x0f);
        rgb_led_update(cfg.rgb_led_lockout_mode, 0);
        save_config();
        blink_once();
        return 0;
    }
    // 7H: change RGB aux LED color
    else if (event == (0b10000000|0b00100000|0b00010000|7)) {
        setting_rgb_mode_now = 1;
        if (0 == (arg & 0x3f)) {
            uint8_t mode = (cfg.rgb_led_lockout_mode & 0x0f) + 1;
            mode = mode % 13;
            cfg.rgb_led_lockout_mode = mode | (cfg.rgb_led_lockout_mode & 0xf0);
            //save_config();
        }
        rgb_led_update(cfg.rgb_led_lockout_mode, arg);
        return 0;
    }
    // 7H, release: save new color
    else if (event == (0b10000000|0b00100000|0b00000000|0b01000000|7)) {
        setting_rgb_mode_now = 0;
        save_config();
        return 0;
    }
    ////////// Every action below here is blocked in the Extended Simple UI //////////
    if (cfg.simple_ui_active) {
        return 1;
    }
    // 10H: configure the autolock option
    else if (event == (0b10000000|0b00100000|0b00010000|10)) {
        push_state(autolock_config_state, 0);
        return 0;
    }
    return 1;
}
// set the auto-lock timer to N minutes, where N is the number of clicks
void autolock_config_save(uint8_t step, uint8_t value) {
    cfg.autolock_time = value;
}
uint8_t autolock_config_state(Event event, uint16_t arg) {
    return config_state_base(event, arg, 1, autolock_config_save);
}
// momentary-mode.c: Momentary mode for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
uint8_t momentary_state(Event event, uint16_t arg) {
    // init strobe mode, if relevant
    if ((event == (0b00000000|0b00001000)) && (momentary_mode != 0)) {
        strobe_state(event, arg);
    }
    // light up when the button is pressed; go dark otherwise
    // button is being held
    if ((event & (0b10000000 | 0b00010000)) == (0b10000000 | 0b00010000)) {
        momentary_active = 1;
        // 0 = ramping, 1 = strobes
        if (momentary_mode == 0) {
            set_level(memorized_level);
        }
        return 0;
    }
    // button was released
    else if ((event & (0b10000000 | 0b00010000)) == (0b10000000)) {
        momentary_active = 0;
        set_level(0);
        //go_to_standby = 1;  // sleep while light is off
        return 0;
    }
    // Sleep, dammit!  (but wait a few seconds first)
    // (because standby mode uses such little power that it can interfere
    //  with exiting via tailcap loosen+tighten unless you leave power
    //  disconnected for several seconds, so we want to be awake when that
    //  happens to speed up the process)
    else if (event == (0b00000000|0b00000001)) {
        if (momentary_active) {
            // 0 = ramping, non-zero = strobes
            if (momentary_mode != 0) {
                return strobe_state(event, arg);
            }
        }
        else {
            // turn off lighted button
                rgb_led_set(0);
                button_led_set(0);
            if (arg > 62*5) { // sleep after 5 seconds
                go_to_standby = 1; // sleep while light is off
            }
        }
        return 0;
    }
    return 1;
}
// tactical-mode.c: Tactical (ish) mode for Anduril.
// Copyright (C) 2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
uint8_t tactical_state(Event event, uint16_t arg) {
    // momentary(ish) tactical mode
    uint8_t mem_lvl = memorized_level; // save this to restore it later
    uint8_t ret = 1;
    // button is being held
    if ((event & (0b10000000 | 0b00010000)) == (0b10000000 | 0b00010000)) {
        // 1H: 1st level
        // 2H: 2nd level
        // 3H: 3rd level
        // 4+: nothing
        momentary_active = 0;
        ret = 0;
        uint8_t click = event & 0x0f; // click number
        if (click <= 3) {
            momentary_active = 1;
            uint8_t lvl;
            lvl = cfg.tactical_levels[click-1];
            if ((1 <= lvl) && (lvl <= 150)) { // steady output
                memorized_level = lvl;
                momentary_mode = 0;
                    // use ramp mode's channel
                    channel_mode = cfg.channel_mode;
            } else { // momentary strobe mode
                momentary_mode = 1;
                if (lvl > 150) {
                    current_strobe_type = (lvl - 150 - 1) % strobe_mode_END;
                }
            }
        }
    }
    // button was released
    else if ((event & (0b10000000 | 0b00010000)) == (0b10000000)) {
        momentary_active = 0;
        set_level(0);
        interrupt_nice_delays(); // stop animations in progress
    }
    // delegate to momentary mode while button is pressed
    if (momentary_active) {
        momentary_state(event, arg);
    }
    memorized_level = mem_lvl; // restore temporarily overridden mem level
    // copy lockout mode's aux LED and sleep behaviors
    if (event == (0b00000000|0b00001000)) {
        lockout_state(event, arg);
    }
    else if (event == (0b00000000|0b00000001)) {
        if (! momentary_active) {
            return lockout_state(event, arg);
        }
        return 0;
    }
    else if (event == (0b00000000|0b00000011)) {
        return lockout_state(event, arg);
    }
    // handle 3C here to prevent changing channel modes unintentionally
    if (event == (0b10000000|0b01000000|3)) {
        return 0;
    }
    // 6 clicks: exit and turn off
    else if (event == (0b10000000|0b01000000|6)) {
        blink_once();
        set_state(off_state, 0);
        return 0;
    }
    ////////// Every action below here is blocked in the simple UI //////////
    // (unnecessary since this entire mode is blocked in simple UI)
    /*
    #ifdef USE_SIMPLE_UI
    if (cfg.simple_ui_active) {
        return EVENT_NOT_HANDLED;
    }
    #endif
    */
    // 7H: configure tactical mode
    else if (event == (0b10000000|0b00100000|0b00010000|7)) {
        push_state(tactical_config_state, 0);
        return 0;
    }
    return ret;
}
void tactical_config_save(uint8_t step, uint8_t value) {
    // update tac mode values
    // 3 values
    // each value is 1 to 150, or other:
    // - 1..150 is a ramp level
    // - other means "strobe mode"
    cfg.tactical_levels[step - 1] = value;
}
uint8_t tactical_config_state(Event event, uint16_t arg) {
    return config_state_base(event, arg, 3, tactical_config_save);
}
// channel-modes.c: Multi-channel functions for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
uint8_t channel_mode_state(Event event, uint16_t arg) {
    if (0) {}
    // it's possible that a light may need 3H but not 3C,
    // so try to detect if 3C is needed
    // 3 clicks: next channel mode
    else if (event == (0b10000000|0b01000000|3)) {
        uint8_t next = channel_mode;
        // go to next channel mode until we find one which is enabled
        // (and don't do any infinite loops if the user disabled them all)
        uint8_t count = 0;
        do {
            count ++;
            next = (next + 1) % (2 + 7);
        } while ((! ((cfg.channel_modes_enabled >> next) & 1)) && count < (2 + 7));
        //} while ((! channel_modes_enabled[next]) && count < NUM_CHANNEL_MODES);
        // undo change if infinite loop detected (redundant?)
        //if (NUM_CHANNEL_MODES == count) next = channel_mode;
        // if mode hasn't changed, abort
        if (channel_mode == next)
            return 1;
        set_channel_mode(next);
        // remember after battery changes
        cfg.channel_mode = channel_mode;
        save_config();
        return 0;
    }
    // remaining mappings aren't "simple", so stop here
    else if (cfg.simple_ui_active) {
        return 1;
    }
    // channel toggle menu on ... 9H?
    else if (event == (0b10000000|0b00100000|0b00010000|9)) {
        push_state(channel_mode_config_state, 0);
        return 0;
    }
    return 1;
}
void channel_mode_config_save(uint8_t step, uint8_t value) {
    // 1 menu item per channel mode, to enable or disable that mode
    step --; // step is 1-based, channel modes are 0-based
    if (value) cfg.channel_modes_enabled |= (1 << step);
    else cfg.channel_modes_enabled &= ((1 << step) ^ 0xff);
}
uint8_t channel_mode_config_state(Event event, uint16_t arg) {
    uint8_t ret;
    // make config steps match channel modes
    config_color_per_step = 1;
    // 1 menu item per channel mode, to enable or disable that mode
    ret = config_state_base(
        event, arg,
        (2 + 7),
        channel_mode_config_save
        );
    // no other menu needs this
    config_color_per_step = 0;
    return ret;
}
// factory-reset.c: Factory reset functions for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
// allows setting channel mode per animation stage,
// so it can ramp up in red then explode in white (as one example)
void factory_reset() {
    // display a warning for a few seconds before doing the actual reset,
    // so the user has time to abort if they want
    uint8_t bright;
    uint8_t reset = 1;
    // wind up to an explosion
    for (bright=0; bright<64; bright++) {
        set_level(bright);
        nice_delay_ms((2500/64)/2);
        set_level(bright>>1);
        nice_delay_ms((2500/64)/2);
        if (! button_is_pressed()) {
            reset = 0;
            break;
        }
    }
    // explode, if button pressed long enough
    if (reset) {
        // auto-calibrate temperature
        // AVR 1-Series has factory calibrated thermal sensor, always remove the offset on reset
        // assume current temperature is 21 C
        thermal_config_save(1, 21);
        thermal_config_save(3, 2);
        // Reset number output mode
        globals_config_save(num_mode_config_step, 2);
        // save all settings to eeprom
        // (assuming they're all at default because we haven't loaded them yet)
        save_config();
        // explosion animation
        bright = 150;
        for (; bright > 0; bright--) {
            set_level(bright);
            nice_delay_ms((2500/64)/8);
        }
    }
    // explosion cancelled, fade away
    else {
        for (; bright > 0; bright--) {
            set_level(bright);
            nice_delay_ms((2500/64)/3);
        }
    }
}
// strobe-modes.c: Strobe modes for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
uint8_t strobe_state(Event event, uint16_t arg) {
    static int8_t ramp_direction = 1;
    // 'st' reduces ROM size slightly
    strobe_mode_te st = current_strobe_type;
    momentary_mode = 1; // 0 = ramping, 1 = strobes
    // pass all events to candle mode, when it's active
    // (the code is in its own pseudo-state to keep things cleaner)
    if (st == candle_mode_e) {
        candle_mode_state(event, arg);
    }
    if (0) {} // placeholder
    // init anything which needs to be initialized
    else if (event == (0b00000000|0b00001000)) {
        current_strobe_type = cfg.strobe_type;
        ramp_direction = 1;
        return 0;
    }
    // 1 click: off
    else if (event == (0b10000000|0b01000000|1)) {
        set_state(off_state, 0);
        return 0;
    }
    // 2 clicks: rotate through strobe/flasher modes
    else if (event == (0b10000000|0b01000000|2)) {
        current_strobe_type = cfg.strobe_type = (st + 1) % strobe_mode_END;
        save_config();
        return 0;
    }
    // 4 clicks: rotate backward through strobe/flasher modes
    else if (event == (0b10000000|0b01000000|4)) {
        current_strobe_type = cfg.strobe_type = (st - 1 + strobe_mode_END) % strobe_mode_END;
        save_config();
        return 0;
    }
    // hold: change speed (go faster)
    //       or change brightness (brighter)
    else if (event == (0b10000000|0b00100000|0b00010000|1)) {
        if (0) {} // placeholder
        // party / tactical strobe faster
        else if (st <= tactical_strobe_e) {
            if ((arg & 1) == 0) {
                uint8_t d = cfg.strobe_delays[st];
                d -= ramp_direction;
                if (d < 8) d = 8;
                else if (d > 254) d = 254;
                cfg.strobe_delays[st] = d;
            }
        }
        // lightning has no adjustments
        //else if (st == lightning_storm_e) {}
        // biking mode brighter
        else if (st == bike_flasher_e) {
            cfg.bike_flasher_brightness += ramp_direction;
            if (cfg.bike_flasher_brightness < 2) cfg.bike_flasher_brightness = 2;
            else if (cfg.bike_flasher_brightness > 120) cfg.bike_flasher_brightness = 120;
            set_level(cfg.bike_flasher_brightness);
        }
        else if (st == broken_fluorescent_mode_e) {
            cfg.fluoresent_brightness += ramp_direction;
            if (cfg.fluoresent_brightness < 1) cfg.fluoresent_brightness = 1;
            else if (cfg.fluoresent_brightness > 150) cfg.fluoresent_brightness = 150;
        }
        return 0;
    }
    // reverse ramp direction on hold release
    // ... and save new strobe settings
    else if (event == (0b10000000|0b00100000|0b00000000|0b01000000|1)) {
        ramp_direction = -ramp_direction;
        save_config();
        return 0;
    }
    // click, hold: change speed (go slower)
    //       or change brightness (dimmer)
    else if (event == (0b10000000|0b00100000|0b00010000|2)) {
        ramp_direction = 1;
        if (0) {} // placeholder
        // party / tactical strobe slower
        else if (st <= tactical_strobe_e) {
            if ((arg & 1) == 0) {
                if (cfg.strobe_delays[st] < 255) cfg.strobe_delays[st] ++;
            }
        }
        // lightning has no adjustments
        //else if (st == lightning_storm_e) {}
        // biking mode dimmer
        else if (st == bike_flasher_e) {
            if (cfg.bike_flasher_brightness > 2)
                cfg.bike_flasher_brightness --;
            set_level(cfg.bike_flasher_brightness);
        }
        else if (st == broken_fluorescent_mode_e) {
            if (cfg.fluoresent_brightness > 1)
                cfg.fluoresent_brightness--;
        }
        return 0;
    }
    // release hold: save new strobe settings
    else if (event == (0b10000000|0b00100000|0b00000000|0b01000000|2)) {
        save_config();
        return 0;
    }
    // 5 clicks: go to momentary mode (momentary strobe)
    else if (event == (0b10000000|0b01000000|5)) {
        set_state(momentary_state, 0);
        set_level(0);
        return 0;
    }
    // clock tick: bump the random seed
    else if (event == (0b00000000|0b00000001)) {
        // un-reverse after 1 second
        if (arg == (62 * 2 / 3)) ramp_direction = 1;
        pseudo_rand_seed += arg;
        return 0;
    }
    // 6C: turning down busy factor (less busy) of lightning mode,
    //  or turning down firework brightness by 12,
    //  or decrease lighthouse delay by 1 sec
    else if (event == (0b10000000|0b01000000|6)) {
        if (0) {} // placeholder
        else if (st == lightning_storm_e) {
            cfg.lightning_busy_factor++;
            if (cfg.lightning_busy_factor > 16)
                cfg.lightning_busy_factor = 16;
            save_config();
            blink_once();
        }
        else if (st == firework_mode_e) {
            cfg.firework_brightness -= 12;
            if (cfg.firework_brightness < 70)
                cfg.firework_brightness = 70;
            save_config();
            blink_once();
        }
        else if (st == lighthouse_mode_e) {
            if (cfg.lighthouse_delay > 0)
                cfg.lighthouse_delay--;
            save_config();
            blink_once();
        }
        return 0;
    }
    // 7C: turning up busy factor (busier) of lightning mode,
    //  or turning up firework brightness by 12,
    //  or increasing lighthouse delay by 1 sec
    else if (event == (0b10000000|0b01000000|7)) {
        if (0) {} // placeholder
        else if (st == lightning_storm_e) {
            cfg.lightning_busy_factor--;
            if (cfg.lightning_busy_factor < 12)
                cfg.lightning_busy_factor = 12;
            save_config();
            blink_once();
        }
        else if (st == firework_mode_e) {
            cfg.firework_brightness += 12;
            if (cfg.firework_brightness > 150)
                cfg.firework_brightness = 150;
            save_config();
            blink_once();
        }
        else if (st == lighthouse_mode_e) {
            if (cfg.lighthouse_delay < 30)
                cfg.lighthouse_delay++;
            save_config();
            blink_once();
        }
        return 0;
    }
    // 8C: reset lightning busy factor to default,
    //  or reset firework brightness to default
    //  or reset lighthouse delay to default
    else if (event == (0b10000000|0b01000000|8)) {
        if (0) {} // placeholder
        else if (st == lightning_storm_e) {
            cfg.lightning_busy_factor = 14;
            save_config();
            blink_once();
        }
        else if (st == firework_mode_e) {
            cfg.firework_brightness = 150;
        }
        else if (st == lighthouse_mode_e) {
            cfg.lighthouse_delay = 5;
        }
        return 0;
    }
    return 1;
}
// runs repeatedly in FSM loop() whenever UI is in strobe_state or momentary strobe
inline void strobe_state_iter() {
    uint8_t st = current_strobe_type; // can't use switch() on an enum
    switch(st) {
        case party_strobe_e:
        case tactical_strobe_e:
            party_tactical_strobe_mode_iter(st);
            break;
        case police_color_strobe_e:
            police_color_strobe_iter();
            break;
        case lightning_storm_e:
            lightning_storm_iter();
            break;
        case bike_flasher_e:
            bike_flasher_iter();
            break;
        case firework_mode_e:
            firework_iter();
            break;
        case lighthouse_mode_e:
            lighthouse_iter();
            break;
        case broken_fluorescent_mode_e:
            bad_fluorescent_iter();
            break;
    }
}
inline void party_tactical_strobe_mode_iter(uint8_t st) {
    // one iteration of main loop()
    uint8_t del = cfg.strobe_delays[st];
    // TODO: make tac strobe brightness configurable?
    set_level(150);
    if (0) {} // placeholder
    else if (st == party_strobe_e) { // party strobe
        nice_delay_ms(1);
    }
    else { //tactical strobe
        nice_delay_ms(del >> 1);
    }
    set_level(0);
    nice_delay_ms(del); // no return check necessary on final delay
}
inline void police_color_strobe_iter() {
    // one iteration of main loop()
    uint8_t del = 66;
    // TODO: make police strobe brightness configurable
    uint8_t bright = memorized_level;
    //uint8_t channel = channel_mode;
    for (uint8_t i=0; i<10; i++) {
        if (0 == i) set_channel_mode(CM_AUXRED);
        else if (5 == i) set_channel_mode(CM_AUXBLU);
        set_level(bright);
        nice_delay_ms(del >> 1);
        set_level(0);
        nice_delay_ms(del);
    }
    // restore the channel when done
    //set_channel_mode(channel);
    channel_mode = cfg.channel_mode;
}
inline void lightning_storm_iter() {
    // one iteration of main loop()
    int16_t brightness;
    uint16_t rand_time;
    // turn the emitter on at a random level,
    // for a random amount of time between 1ms and 32ms
    //rand_time = 1 << (pseudo_rand() % 7);
    rand_time = pseudo_rand() & 63;
    brightness = 1 << (pseudo_rand() % 7); // 1, 2, 4, 8, 16, 32, 64
    brightness += 1 << (pseudo_rand() % 5); // 2 to 80 now
    brightness += pseudo_rand() % brightness; // 2 to 159 now (w/ low bias)
    if (brightness > 150) brightness = 150;
    set_level(brightness);
    nice_delay_ms(rand_time);
    // decrease the brightness somewhat more gradually, like lightning
    uint8_t stepdown = brightness >> 3;
    if (stepdown < 1) stepdown = 1;
    while(brightness > 1) {
        nice_delay_ms(rand_time);
        brightness -= stepdown;
        if (brightness < 0) brightness = 0;
        set_level(brightness);
        /*
           if ((brightness < MAX_LEVEL/2) && (! (pseudo_rand() & 15))) {
           brightness <<= 1;
           set_level(brightness);
           }
           */
        if (! (pseudo_rand() & 3)) {
            nice_delay_ms(rand_time);
            set_level(brightness>>1);
        }
    }
    // turn the emitter off,
    // for a random amount of time between 1ms and 8192ms (default busy factor)
    // (with a low bias)
    rand_time = 1 << (pseudo_rand() % cfg.lightning_busy_factor);
    rand_time += pseudo_rand() % rand_time;
    set_level(0);
    nice_delay_ms(rand_time); // no return check necessary on final delay
}
inline void bike_flasher_iter() {
    // one iteration of main loop()
    uint8_t burst = cfg.bike_flasher_brightness << 1;
    if (burst > 150) burst = 150;
    for(uint8_t i=0; i<4; i++) {
        set_level(burst);
        nice_delay_ms(5 + 0);
        set_level(cfg.bike_flasher_brightness);
        nice_delay_ms(65);
    }
    nice_delay_ms(720); // no return check necessary on final delay
    set_level(0);
}
uint8_t firework_stage = 0;
uint8_t firework_stage_count = 64;
uint8_t step_interval = (2500/64);
// code is copied and modified from factory-reset.c
inline void firework_iter() {
    if (firework_stage == firework_stage_count) {
        // explode, and reset stage
        firework_stage = 0;
        for (uint8_t brightness = cfg.firework_brightness; brightness > 0; brightness--) {
            set_level(brightness);
            nice_delay_ms(step_interval/4);
            set_level((uint16_t)brightness*7/8);
            nice_delay_ms(step_interval/(1+(pseudo_rand()%5)));
        }
        // off for 1 to 5 seconds
        set_level(0);
        nice_delay_ms(1000 + (pseudo_rand() % 5) * 1000);
        // set next stage count (16 to 64 in increment of 8)
        firework_stage_count = 16 + 8 * (pseudo_rand() % 7);
        return;
    }
    // wind up to explode
    set_level(firework_stage);
    nice_delay_ms(step_interval/3);
    set_level((uint16_t)firework_stage*2/3);
    nice_delay_ms(step_interval/3);
    firework_stage++;
    // we've reached our max brightness for firework mode, let's explode in the next iteration
    if (firework_stage > cfg.firework_brightness)
        firework_stage = firework_stage_count;
}
// phase is between 0~255, returns MAX_LEVEL at 128 and 1 at both ends
uint8_t lighthouse_intensity(uint8_t phase) {
    if (phase > 127)
        phase = 256 - phase;
    const uint64_t maxOutput = 150 - 1;
    // power of 4 (quartic function)
    return (uint8_t)(maxOutput * phase / 128 * phase / 128 * phase / 128 * phase / 128) + 1;
}
inline void lighthouse_iter() {
    uint8_t brightness = lighthouse_intensity(lighthouse_phase++);
    set_level(brightness);
    if (lighthouse_phase == 0) {
        set_level(0);
        nice_delay_ms(1000 * cfg.lighthouse_delay);
    } else
        nice_delay_ms(10 + cfg.lighthouse_delay);
}
inline void bad_fluorescent_iter() {
    // broken fluorescent
    // even index: light off, odd index: light on
    // unit: 10ms or -1 means random number (10~500ms) generated at boot
    static const int8_t fluorescent_pattern[] = {1,4, -1,2, 5,3, -1,5, 7,27, 1,5, 3,10, -1,20, 3,-1, 2,-1, 10,-1, -1,-1, 1};
    fluoresent_ramp_up_increment++;
    if ((fluorescent_pattern[fluoresent_flicker_index] == -1 && fluoresent_ramp_up_increment == fluoresent_flicker_random) ||
        (fluorescent_pattern[fluoresent_flicker_index] == fluoresent_ramp_up_increment)) {
        fluoresent_flicker_index++;
        fluoresent_ramp_up_increment = 0;
        set_level(fluoresent_flicker_index & 1 ? cfg.fluoresent_brightness >> (pseudo_rand()&1): 0);
    }
    if (fluoresent_flicker_index == sizeof(fluorescent_pattern)) {
        fluoresent_flicker_index = 0;
        fluoresent_flicker_random = pseudo_rand()%50 + 1;
    }
    nice_delay_ms(10);
}
// candle-mode.c: Candle mode for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
static uint8_t max_candle_level = (150 -33 -15);
// these should add up to 100
static uint8_t candle_wave1_maxdepth = 30;
static uint8_t candle_wave2_maxdepth = 45;
static uint8_t candle_wave3_maxdepth = 25;
static uint8_t candle_wave1_depth;
static uint8_t candle_wave2_depth;
static uint8_t candle_wave3_depth;
static inline void reset_parameters() {
    max_candle_level = 150 -cfg.candle_amplitude-15;
    switch (wobble_style) {
    case fireplace_slow_wobble_e:
        //use wave1/wave2 only
        candle_wave3_depth = candle_wave3_maxdepth = 0;
        candle_wave1_maxdepth = 50;
        candle_wave2_maxdepth = 50;
        candle_wave1_depth = candle_wave1_maxdepth * cfg.candle_amplitude / 100;
        candle_wave2_depth = candle_wave2_maxdepth * cfg.candle_amplitude / 100;
        // #ifdef USE_AUX_RGB_LEDS
        // rgb_led_update(RGB_RED|RGB_HIGH, 0);
        // #endif
        break;
    case fireplace_fast_wobble_e:
        //use wave2/wave3 only
        candle_wave1_depth = candle_wave1_maxdepth = 0;
        candle_wave2_maxdepth = 20;
        candle_wave3_maxdepth = 80;
        candle_wave2_depth = candle_wave2_maxdepth * cfg.candle_amplitude / 100;
        candle_wave3_depth = candle_wave3_maxdepth * cfg.candle_amplitude / 100;
        // #ifdef USE_AUX_RGB_LEDS
        // rgb_led_update(RGB_YELLOW|RGB_HIGH, 0);
        // #endif
        break;
    default:
        candle_wave1_maxdepth = 30;
        candle_wave2_maxdepth = 45;
        candle_wave3_maxdepth = 25;
        candle_wave1_depth = candle_wave1_maxdepth * cfg.candle_amplitude / 100;
        candle_wave2_depth = candle_wave2_maxdepth * cfg.candle_amplitude / 100;
        candle_wave3_depth = candle_wave3_maxdepth * cfg.candle_amplitude / 100;
        // #ifdef USE_AUX_RGB_LEDS
        // rgb_led_update(RGB_OFF, 0);
        // #endif
    }
}
uint8_t candle_mode_state(Event event, uint16_t arg) {
    static int8_t ramp_direction = 1;
    static uint8_t candle_wave1 = 0;
    static uint8_t candle_wave2 = 0;
    static uint8_t candle_wave3 = 0;
    static uint8_t candle_wave2_speed = 0;
    static uint8_t candle_mode_brightness = 24;
    // let the candle "burn out" and shut itself off
    // if the user told it to
    // cache this in case it changes when the timer is called
    uint8_t sunset_active = sunset_timer;
    // clock tick
    sunset_timer_state(event, arg);
    // if the timer just expired, shut off
    if (sunset_active && (! sunset_timer)) {
        set_state(off_state, 0);
        return 0;
    }
    if (event == (0b00000000|0b00001000)) {
        wobble_style = cfg.candle_wobble_style;
        ramp_direction = 1;
        reset_parameters();
        return 0;
    }
    // 2 clicks: cancel timer
    else if (event == (0b10000000|0b01000000|2)) {
        // parent state just rotated through strobe/flasher modes,
        // so cancel timer...  in case any time was left over from earlier
        sunset_timer = 0;
        return 0;
    }
    // hold: change brightness (brighter)
    else if (event == (0b10000000|0b00100000|0b00010000|1)) {
        // ramp away from extremes
        if (! arg) {
            if (candle_mode_brightness >= max_candle_level) { ramp_direction = -1; }
            else if (candle_mode_brightness <= 1) { ramp_direction = 1; }
        }
        // change brightness, but not too far
        candle_mode_brightness += ramp_direction;
        if (candle_mode_brightness < 1) candle_mode_brightness = 1;
        else if (candle_mode_brightness > max_candle_level) candle_mode_brightness = max_candle_level;
        return 0;
    }
    // reverse ramp direction on hold release
    else if (event == (0b10000000|0b00100000|0b00000000|0b01000000|1)) {
        ramp_direction = -ramp_direction;
        return 0;
    }
    // click, hold: change brightness (dimmer)
    else if (event == (0b10000000|0b00100000|0b00010000|2)) {
        ramp_direction = 1;
        // difference of level 2 and 3 is huge. Avoid going too low or the candle will wobble too much
        if (candle_mode_brightness > 3)
            candle_mode_brightness --;
        return 0;
    }
    // 4H: set wobble style
    else if (event == (0b10000000|0b00100000|0b00010000|4)) {
        if (0 == (arg & 0x3f)) {
            wobble_style = cfg.candle_wobble_style = (wobble_style + 1) % NUM_WOBBLE;
            reset_parameters();
            if (wobble_style == candle_wobble_e)
                blip_ms(12);
            else if (wobble_style == fireplace_slow_wobble_e)
                blip_ms(96);
            else if (wobble_style == fireplace_fast_wobble_e)
                blip_ms(192);
        }
        return 0;
    }
    else if (event == (0b10000000|0b00100000|0b00000000|0b01000000|4)) {
        save_config();
        return 0;
    }
    // 6C: making candle amplitude smaller (candle in sort of stillness)
    else if (event == (0b10000000|0b01000000|6)) {
        cfg.candle_amplitude -= 3;
        if (cfg.candle_amplitude < 10)
            cfg.candle_amplitude = 10;
        reset_parameters();
        save_config();
        blip();
        return 0;
    }
    // 7C: making candle amplitude bigger (candle in the wind)
    else if (event == (0b10000000|0b01000000|7)) {
        cfg.candle_amplitude += 3;
        if (cfg.candle_amplitude > 60)
            cfg.candle_amplitude = 60;
        reset_parameters();
        save_config();
        blip();
        return 0;
    }
    // 8C: reset candle amplitude
    else if (event == (0b10000000|0b01000000|8)) {
        cfg.candle_amplitude = 33;
        reset_parameters();
        save_config();
        blink_once();
        blip();
        return 0;
    }
    // clock tick: animate candle brightness
    else if (event == (0b00000000|0b00000001)) {
        // un-reverse after 1 second
        if (arg == (62 * 2 / 3)) ramp_direction = 1;
        // 3-oscillator synth for a relatively organic pattern
        uint8_t add;
        add = ((triangle_wave(candle_wave1) * candle_wave1_depth) >> 8)
            + ((triangle_wave(candle_wave2) * candle_wave2_depth) >> 8)
            + ((triangle_wave(candle_wave3) * candle_wave3_depth) >> 8);
// limit add if we are on lower level because brightness varies a lot
        // when we use lower level
        if (add > candle_mode_brightness/2) add >>= 1;
        if (wobble_style == fireplace_fast_wobble_e) add >>=1; // cut the add in half
        uint16_t brightness = candle_mode_brightness + add;
        // self-timer dims the light during the final minute
        if (1 == sunset_timer) {
            brightness = brightness
                         * (((62*60)>>5) - (sunset_ticks>>5))
                         / ((62*60)>>5);
        }
        set_level(brightness);
        // wave1: slow random LFO
        // TODO: make wave slower and more erratic?
        if (wobble_style != fireplace_fast_wobble_e){
            if ((arg & 1) == 0) candle_wave1 += pseudo_rand() & 1;
        }
        // wave2: medium-speed erratic LFO
        candle_wave2 += candle_wave2_speed;
        // wave3: erratic fast wave
        if (wobble_style == fireplace_fast_wobble_e)
            candle_wave3 += pseudo_rand() % 31; //slightly slower
        else
            candle_wave3 += pseudo_rand() % 37;
        // S&H on wave2 frequency to make it more erratic
        if ((pseudo_rand() & 0b00111111) == 0)
            candle_wave2_speed = pseudo_rand() % 13;
        // downward sawtooth on wave2 depth to simulate stabilizing
        if ((candle_wave2_depth > 0) && ((pseudo_rand() & 0b00111111) == 0))
            candle_wave2_depth --;
        // less random factor when we are in fireplace wobble mode
        if (wobble_style > candle_wobble_e) {
            if (0 == (arg & 0x7f))
                reset_parameters();
            return 0;
        }
        // random sawtooth retrigger
        if (pseudo_rand() == 0) {
            // random amplitude
            //candle_wave2_depth = 2 + (pseudo_rand() % ((CANDLE_WAVE2_MAXDEPTH * cfg.candle_amplitude / 100) - 2));
            candle_wave2_depth = pseudo_rand() % (candle_wave2_maxdepth * cfg.candle_amplitude / 100);
            //candle_wave3_depth = 5;
            candle_wave2 = 0;
        }
        // downward sawtooth on wave3 depth to simulate stabilizing
        if ((candle_wave3_depth > 2) && ((pseudo_rand() & 0b00011111) == 0))
            candle_wave3_depth --;
        if ((pseudo_rand() & 0b01111111) == 0)
            // random amplitude
            //candle_wave3_depth = 2 + (pseudo_rand() % ((CANDLE_WAVE3_MAXDEPTH * cfg.candle_amplitude / 100) - 2));
            candle_wave3_depth = pseudo_rand() % (candle_wave3_maxdepth * cfg.candle_amplitude / 100);
        return 0;
    }
    return 1;
}
// sos-mode.c: SOS mode for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
uint8_t sos_state(Event event, uint16_t arg) {
    // 1 click: off
    if (event == (0b10000000|0b01000000|1)) {
        set_state(off_state, 0);
        return 0;
    }
    // 2 clicks: next blinky mode
    else if (event == (0b10000000|0b01000000|2)) {
        set_state(battcheck_state, 0);
        return 0;
    }
    return 1;
}
void sos_blink(uint8_t num, uint8_t dah) {
    for (; num > 0; num--) {
        set_level(memorized_level);
        nice_delay_ms(200);
        if (dah) { // dah is 3X as long as a dit
            nice_delay_ms(200*2);
        }
        set_level(0);
        // one "off" dit between blinks
        nice_delay_ms(200);
    }
    // three "off" dits (or one "dah") between letters
    nice_delay_ms(200*2);
}
inline void sos_mode_iter() {
    // Spell "I LUV U" in Morse code
    // I: ..
    sos_blink(2, 0); // I
    nice_delay_ms(2000);
    // L: .-..
    sos_blink(1, 0); // .
    sos_blink(1, 1); // -
    sos_blink(2, 0); // ..
    nice_delay_ms(2000);
    // U: ..-
    sos_blink(2, 0); // ..
    sos_blink(1, 1); // -
    nice_delay_ms(2000);
    // V: ...-
    sos_blink(3, 0); // ...
    sos_blink(1, 1); // -
    nice_delay_ms(2000);
    // U: ..-
    sos_blink(2, 0); // ..
    sos_blink(1, 1); // -
    nice_delay_ms(2000);
}
// smooth-steps.c: Smooth step adjustments for Anduril.
// Copyright (C) 2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
// one iteration of main loop()
void smooth_steps_iter() {
    if (actual_level == smooth_steps_target) {
        set_level(smooth_steps_target);
        smooth_steps_in_progress = 0;
        // restore prev_level when animation ends
        prev_level = smooth_steps_start;
    }
    else if (smooth_steps_target > actual_level) {
        // power-linear(ish) ascent
        // (jump by ~20% of remaining distance on each frame)
        uint8_t diff = smooth_steps_target - actual_level;
        uint8_t this = diff / smooth_steps_speed;
        if (!this) this = 1;
        set_level(actual_level + this);
        nice_delay_ms(10);
    } else {
        // ramp-linear descent
        // (jump by 1 on each frame, frame rate gives constant total time)
        uint8_t diff = smooth_steps_start - smooth_steps_target;
        uint16_t delay = 1 + (30 * smooth_steps_speed / diff);
        set_level(actual_level - 1);
        // TODO? if delay < one PWM cycle, this can look a little weird
        nice_delay_ms(delay);
    }
}
void set_level_smooth(uint8_t level, uint8_t speed) {
    smooth_steps_target = level;
    smooth_steps_speed = speed; // higher = slower
    smooth_steps_in_progress = 1;
    // for setting prev_level after animation ends
    smooth_steps_start = actual_level;
}
// runs one time at boot, when power is connected
void setup() {
        // regular e-switch light, no hard clicky power button
            // blink at power-on to let user know power is connected
            blink_once();
        if (button_is_pressed())
            factory_reset();
        load_config();
        // without this, initial boot-up brightness is wrong
        // when manual mem is enabled with a non-zero timer
        if (cfg.manual_memory) manual_memory_restore();
        // add channel mode functions underneath every other state
        push_state(channel_mode_state, 0);
        push_state(off_state, 1);
}
// runs repeatedly whenever light is "on" (not in standby)
void loop() {
    // "current_state" is volatile, so cache it to reduce code size
    StatePtr state = current_state;
    if (0) {} // placeholder
    else if (state == version_check_state) {
        version_check_iter();
    }
    else if ((state == strobe_state)
         // also handle momentary strobes
         || ((0
              || (state == momentary_state)
              || (state == tactical_state)
             )
             && (momentary_mode == 1) && (momentary_active))
         ) {
        strobe_state_iter();
    }
    else if (state == battcheck_state) {
        nice_delay_ms(1000); // wait a moment for a more accurate reading
        battcheck();
        // in simple mode, turn off after one readout
        // FIXME: can eat the next button press
        //        (state changes in loop() act weird)
        if (cfg.simple_ui_active) set_state_deferred(off_state, 0);
        else nice_delay_ms(1000);
    }
    // TODO: blink out therm_ceil during thermal_config_state?
    else if (state == tempcheck_state) {
        if (cfg.temp_unit == 2) {
            temperature = temperature * 9 / 5 + 32; // convert to F
            }
        blink_num(temperature);
        nice_delay_ms(1000);
    }
    else if (state == beacon_state) {
        beacon_mode_iter();
    }
    else if (state == sos_state) {
        sos_mode_iter();
    }
    else if (cfg.smooth_steps_style && smooth_steps_in_progress) {
        smooth_steps_iter();
    }
    else {
        // doze until next clock tick
        idle_mode();
    }
}
// instead of handling EV_low_voltage in each mode,
// it's handled globally here to make the code smaller and simpler
void low_voltage() {
    // "current_state" is volatile, so cache it to reduce code size
    StatePtr state = current_state;
    // turn off aux LED(s) when power is really low
    button_led_set(0);
    rgb_led_set(0);
    if (0) {} // placeholder
    // "step down" from strobe to something low
    else if (state == strobe_state) {
        set_state(steady_state, 150/6);
    }
    // in normal mode, step down or turn off
    else if (state == steady_state) {
        if (actual_level > 1) {
            uint8_t lvl = (actual_level >> 1) + (actual_level >> 2);
            set_level_and_therm_target(lvl);
        }
        else {
            set_state(off_state, 0);
        }
    }
    // all other modes, just turn off when voltage is low
    else {
        set_state(off_state, 0);
    }
}
