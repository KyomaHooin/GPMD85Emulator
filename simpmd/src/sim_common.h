/*

SIM_COMMON.H

Copyright 2008 Petr Tuma

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

*/

#include <atomic>


//--------------------------------------------------------------------------
// Types

typedef unsigned int    uint;

typedef uint8_t         byte;
typedef uint16_t        word;

typedef uint32_t        uint32;
typedef uint64_t        uint64;


//--------------------------------------------------------------------------
// Macros

/// Returns the smaller one of two arguments.
#define MIN(A,B) ((A) < (B) ? (A) : (B))
/// Returns the greater one of two arguments.
#define MAX(A,B) ((A) > (B) ? (A) : (B))

/// Returns the nearest higher power of two.
#define POT(X) ({ uint O = 1; uint H = (X); while (H > 1) { H >>= 1; O <<= 1; }; O; })

//--------------------------------------------------------------------------
// System Related Constants

/// Invalid handle value.
#define INVALID_HANDLE          -1

/// No option to parse.
#define POPT_NO_NEXT_OPT        -1


//--------------------------------------------------------------------------
// Simulator Related Constants

/// Simulated processor clock rate
#define PMD_CLOCK       (18432000 / 9)

/// Model PMD 85-1
#define PMD_MODEL_1     1
/// Model PMD 85-2
#define PMD_MODEL_2     2

/// Reasonable alignment to prevent cache line ping pong.
#define SAFE_ALIGNMENT          64


//--------------------------------------------------------------------------
// Atomicity

class atomic_int
{
  private:
    std::atomic<int> iValue __attribute__ ((aligned (SAFE_ALIGNMENT)));
    int iPadding __attribute__ ((aligned (SAFE_ALIGNMENT)));
  public:
    atomic_int () : iValue (0) { }
    atomic_int (int iInitial) : iValue (iInitial) { }
    inline operator int () { return (iValue.load (std::memory_order_relaxed)); }
    inline void operator = (int iAssignment) { iValue.store (iAssignment, std::memory_order_relaxed); }
    inline void operator += (int iIncrement) { iValue.fetch_add (iIncrement, std::memory_order_relaxed); }
    inline void operator -= (int iDecrement) { iValue.fetch_sub (iDecrement, std::memory_order_relaxed); }
};


//--------------------------------------------------------------------------
// Globals

extern byte MemData [65536];
extern bool MemMask [65536];

extern atomic_int Clock;

extern struct poptOption asDSPOptions [];
extern struct poptOption asSNDOptions [];
extern struct poptOption asTAPOptions [];
extern struct poptOption asTIMOptions [];

//--------------------------------------------------------------------------
// Externals

int CPUThread (void *);
void CPUInitialize ();
void CPUShutdown ();

void DSPPaintHandler ();
void DSPResizeHandler (const SDL_ResizeEvent *);
void DSPInitialize ();
void DSPShutdown ();

byte KBDReadRow ();
byte KBDReadColumn ();
void KBDWriteColumn (byte iData);
void KBDEventHandler (const SDL_KeyboardEvent *);
void KBDInitialize ();
void KBDShutdown ();

void SNDSynchronize ();
void SNDWriteSpeaker (byte iData);
void SNDInitialize ();
void SNDShutdown ();

byte TAPReadData ();
void TAPWriteData (byte iData);
byte TAPReadStatus ();
void TAPInitialize ();
void TAPShutdown ();

void TIMSynchronize ();
void TIMAdvance (int);
void TIMInitialize ();
void TIMShutdown ();


//--------------------------------------------------------------------------
// Debugging

/// Displays a message with a terminating newline.
#define DEBUG_LOG(X) std::cout << X << std::endl
/// Displays a message without a terminating newline.
#define DEBUG_LOG_PARTIAL(X) std::cout << X
/// Displays the terminating newline.
#define DEBUG_LOG_NEWLINE std::cout << std::endl

/// Display instructions while executing.
#undef DEBUG_CPU_TRACE_INSTRUCTIONS
/// Display registers while executing.
#undef DEBUG_CPU_TRACE_REGISTERS

/// Executes an SDL function and makes sure it returned 0.
#define SDL_CheckZero(X) if (X) { DEBUG_LOG (SDL_GetError ()); assert (false); }
/// Executes an SDL function and makes sure it did not return NULL.
#define SDL_CheckNotNull(X) if ((X) == NULL) { DEBUG_LOG (SDL_GetError ()); assert (false); }

//--------------------------------------------------------------------------

