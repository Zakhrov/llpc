/*
 ***********************************************************************************************************************
 *
 *  Copyright (c) 2016-2019 Advanced Micro Devices, Inc. All Rights Reserved.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 *
 **********************************************************************************************************************/
/**
 ***********************************************************************************************************************
 * @file  llpcDebug.h
 * @brief LLPC header file: contains definitions of LLPC debug utilities.
 ***********************************************************************************************************************
 */
#pragma once

#include <stdint.h>

#define LLPC_UNUSED(a) (void(a))

#if PAL_ENABLE_PRINTS_ASSERTS || !defined(NDEBUG)
#include <cassert>

// Debug assertion: generic
#define LLPC_ASSERT(...)        assert(__VA_ARGS__)
// Debug assertion: not implemented
#define LLPC_NOT_IMPLEMENTED()  assert(0 && "Not implemented!")
// Debug assertion: should never be called
#define LLPC_NEVER_CALLED()     assert(0 && "Should never be called!")
// Debug assertion: not tested
#define LLPC_NOT_TESTED()       assert(0 && "Not tested!")

#else

#define LLPC_ASSERT(...)              ((void)0)
#define LLPC_NOT_IMPLEMENTED()        ((void)0)
#define LLPC_NEVER_CALLED()           ((void)0)
#define LLPC_NOT_TESTED()             ((void)0)

#endif

// Output error message
#define LLPC_ERRS(_msg) { if (EnableErrs()) { outs() << "ERROR: " << _msg; outs().flush(); } }

// Output general message
#define LLPC_OUTS(_msg) { if (EnableOuts()) { outs() << _msg; } }

// Disallow the use of the default constructor for a class
#define LLPC_DISALLOW_DEFAULT_CTOR(_typename)       \
    _typename();

// Disallow the use of the copy constructor and assignment operator for a class
#define LLPC_DISALLOW_COPY_AND_ASSIGN(_typename)    \
    _typename(const _typename&);                    \
    _typename& operator =(const _typename&);

namespace llvm { class raw_ostream; }
namespace llvm { class raw_fd_ostream; }

namespace MetroHash { struct Hash; };

namespace Llpc
{

struct ComputePipelineBuildInfo;
struct GraphicsPipelineBuildInfo;
struct BinaryData;
struct Elf64;
struct Elf32;
struct GfxIpVersion;

template<class Elf> class ElfReader;

// Gets the value of option "enable-outs"
bool EnableOuts();

// Gets the value of option "enable-errs"
bool EnableErrs();

// Dumps ELF package to out stream
template<class OStream, class Elf>
OStream& operator<<(
    OStream&         out,
    ElfReader<Elf>&  reader);

// Redirects the output of logs, It affects the behavior of llvm::outs(), dbgs() and errs().
void RedirectLogOutput(
    bool              restoreToDefault,
    uint32_t          optionCount,
    const char*const* pOptions);

// Enable/disable the output for debugging.
void EnableDebugOutput(bool restore);

} // Llpc
