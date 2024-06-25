//=========================================================================================
// Types definitions
//=========================================================================================
typedef struct
{
  unsigned long  sourceAddr;  /* Source Address (section in ROM memory) */
  unsigned long  targetAddr;  /* Target Address (section in RAM memory) */
  unsigned long  size;        /* length of section (bytes)              */
} runtimeCopyTable_t;

typedef struct
{
  unsigned long  addr;  /* Source Address (section in RAM memory) */
  unsigned long  size;  /* Length of section (bytes)              */
} runtimeClearTable_t;

//=========================================================================================
// Linker variables
//=========================================================================================
extern const runtimeCopyTable_t __RUNTIME_COPY_TABLE[];
extern const runtimeClearTable_t __RUNTIME_CLEAR_TABLE[];

//=========================================================================================
// Defines
//=========================================================================================
#define __STARTUP_RUNTIME_COPYTABLE   (runtimeCopyTable_t*)(&__RUNTIME_COPY_TABLE[0])
#define __STARTUP_RUNTIME_CLEARTABLE  (runtimeClearTable_t*)(&__RUNTIME_CLEAR_TABLE[0])

void Startup_InitRam(void)
{
  unsigned long ClearTableIdx = 0;
  unsigned long CopyTableIdx  = 0;

  /* Clear Table */
  while((__STARTUP_RUNTIME_CLEARTABLE)[ClearTableIdx].addr != (unsigned long)-1 && (__STARTUP_RUNTIME_CLEARTABLE)[ClearTableIdx].size != (unsigned long)-1)
  {
    for(unsigned long idx = 0; idx < ((unsigned long)((__STARTUP_RUNTIME_CLEARTABLE)[ClearTableIdx].size) / 4); idx++)
    {
     ((unsigned long*)((__STARTUP_RUNTIME_CLEARTABLE)[ClearTableIdx].addr))[idx] = 0;
    }

    ClearTableIdx++;
  }

  /* Copy Table */
  while((__STARTUP_RUNTIME_COPYTABLE)[CopyTableIdx].sourceAddr != (unsigned long)-1 &&
        (__STARTUP_RUNTIME_COPYTABLE)[CopyTableIdx].targetAddr != (unsigned long)-1 &&
        (__STARTUP_RUNTIME_COPYTABLE)[CopyTableIdx].size       != (unsigned long)-1
       )
  {
    for(unsigned long idx = 0; idx < ((unsigned long)((__STARTUP_RUNTIME_COPYTABLE)[CopyTableIdx].size) / 4); idx++)
    {
     ((unsigned long*)((__STARTUP_RUNTIME_COPYTABLE)[CopyTableIdx].targetAddr))[idx] = 
     ((unsigned long*)((__STARTUP_RUNTIME_COPYTABLE)[CopyTableIdx].sourceAddr))[idx];
    }

    CopyTableIdx++;
  }
}

