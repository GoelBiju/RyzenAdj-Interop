/* SPDX-License-Identifier: LGPL */
/* Copyright (C) 2019 Jiaxun Yang <jiaxun.yang@flygoat.com> */
/* RyzenAdj API */

#ifndef RYZENADJ_H
#define RYZENADJ_H

#ifdef __cplusplus
extern "C" {
#endif

#include  "nb_smu_ops.h"

typedef struct {
    nb_t nb;
    pci_obj_t pci_obj;
    smu_t mp1_smu;
    smu_t psmu;
} *ryzen_access;


// Only internal.
ryzen_access __stdcall _init_ryzenadj();
void __stdcall _cleanup_ryzenadj(ryzen_access ry);


// Functions that can be called from the DLL.
_declspec(dllexport) bool __stdcall init_ryzenadj_library();
_declspec(dllexport) void __stdcall cleanup_ryzenadj_library();

__declspec(dllexport) int __stdcall set_stapm_limit(uint32_t value);
__declspec(dllexport) int __stdcall set_fast_limit(uint32_t value);
__declspec(dllexport) int __stdcall set_slow_limit(uint32_t value);
__declspec(dllexport) int __stdcall set_slow_time(uint32_t value);
__declspec(dllexport) int __stdcall set_stapm_time(uint32_t value);
__declspec(dllexport) int __stdcall set_tctl_temp(uint32_t value);
__declspec(dllexport) int __stdcall set_vrm_current(uint32_t value);
__declspec(dllexport) int __stdcall set_vrmsoc_current(uint32_t value);
__declspec(dllexport) int __stdcall set_vrmmax_current(uint32_t value);
__declspec(dllexport) int __stdcall set_vrmsocmax_current(uint32_t value);
__declspec(dllexport) int __stdcall set_psi0_current(uint32_t value);
__declspec(dllexport) int __stdcall set_psi0soc_current(uint32_t value);

#ifdef __cplusplus
}
#endif
#endif
