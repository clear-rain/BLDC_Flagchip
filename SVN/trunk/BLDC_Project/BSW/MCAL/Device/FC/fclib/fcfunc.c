/**
 * @file module_fcfunc.c
 * @author Flagchip
 * @brief include fcfunc file
 * @version 0.2.1
 * @date 2022-02-20
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 */
#include "fcfunc.h"

/**
 * @brief Personnal memcpy function,avoid building target file too large because of include <string.h>--memcpy()
 *
 * @param pDest pSource  u32Count   wdogTriggerFunc
 */
void* FCFUNC_FcOwnMemcpy(uint8_t *pDest, const uint8_t *pSource, uint32_t u32Count,  void_functype wdogTriggerFunc )
{
   uint8_t* plocalDest;
   const uint8_t* plocalSource;
   uint32_t u32Index;

   /* Initialize variables */
   plocalDest = (uint8_t*)pDest;
   plocalSource = (uint8_t const *)pSource;

   for (u32Index = 0u; u32Index < u32Count; u32Index++)
   {
      if ((u32Index & 0x3Fu) == 0u)
      {
          if(wdogTriggerFunc!=NULL)
          {
              (void)wdogTriggerFunc();
          }
      }
      plocalDest[u32Index] = plocalSource[u32Index];
   }

   return pDest;
}


void* FC_OwnMemcpy(void *pDest, const void *pSource, uint32_t u32Count)
{
   uint8_t* plocalDest;
   const uint8_t* plocalSource;
   uint32_t u32Index;

   /* Initialize variables */
   plocalDest = (uint8_t*)pDest;
   plocalSource = (const uint8_t*)pSource;

   for (u32Index = 0u; u32Index < u32Count; u32Index++)
   {
      plocalDest[u32Index] = plocalSource[u32Index];
   }

   return pDest;
}



void* FC_OwnMemcpyWithWdg(void *pDest, const void *pSource, uint32_t u32Count,  void_functype wdogTriggerFunc, uint32_t u32CallBackCnt)
{
   uint8_t* plocalDest;
   const uint8_t* plocalSource;
   uint32_t u32Index;

   /* Initialize variables */
   plocalDest = (uint8_t*)pDest;
   plocalSource = (const uint8_t*)pSource;

   for (u32Index = 0u; u32Index < u32Count; u32Index++)
   {
      if ((u32Index % u32CallBackCnt) == 0u)
      {
          if(wdogTriggerFunc!=NULL)
          {
              (void)wdogTriggerFunc();
          }
      }
      plocalDest[u32Index] = plocalSource[u32Index];
   }

   return pDest;
}

