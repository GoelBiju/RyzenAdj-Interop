// RyzenAdjDLL.cpp : Defines the exported functions for the DLL application.
//

// SPDX-License-Identifier: LGPL
/* Copyright (C) 2018-2019 Jiaxun Yang <jiaxun.yang@flygoat.com> */
/* Modified for Interop with C#*/

/* RyzenAdj API */

#include "ryzenadj.h"

extern "C"
{
	// Initialise ryzen access.
	ryzen_access ry;

	__declspec(dllexport) bool __stdcall init_ryzenadj_library()
	{
		bool initialised = false;

		// Call the main initialised method.
		ry = _init_ryzenadj();
		if (!ry) {
			printf("Unable to initialise RyzenAdj.\n");
		}
		else {
			printf("Initialised RyzenAdj Library.\n");
			initialised = true;
		}

		return initialised;
	}

	__declspec(dllexport) void __stdcall cleanup_ryzenadj_library()
	{
		// Free up space from the objects we used.
		_cleanup_ryzenadj(ry);
		printf("Cleaned RyzenAdj.");
	}

	ryzen_access __stdcall _init_ryzenadj() {
		smu_service_args_t args = { 0, 0, 0, 0, 0, 0 };
		ryzen_access ry;

		ry = (ryzen_access)malloc((sizeof(*ry)));

		ry->pci_obj = init_pci_obj();
		if (!ry->pci_obj) {
			printf("Unable to get PCI Obj\n");
			return NULL;
		}

		ry->nb = get_nb(ry->pci_obj);
		if (!ry->nb) {
			printf("Unable to get NB Obj\n");
			goto out_free_pci_obj;
		}

		ry->mp1_smu = get_smu(ry->nb, TYPE_MP1);
		if (!ry->mp1_smu) {
			goto out_free_nb;
		}

		ry->psmu = get_smu(ry->nb, TYPE_PSMU);
		if (!ry->psmu) {
			goto out_free_mp1_smu;
		}

		smu_service_req(ry->mp1_smu, 0x3, &args);
		if (args.arg0 != 0x5 && args.arg0 != 0x6) {
			printf("Not a Ryzen NB SMU, BIOS Interface Ver: 0x%x", args.arg0);
			goto out_err;
		}

		return ry;

	out_err:
		free_smu(ry->psmu);
	out_free_mp1_smu:
		free_smu(ry->mp1_smu);
	out_free_nb:
		free_nb(ry->nb);
	out_free_pci_obj:
		free_pci_obj(ry->pci_obj);
		free(ry);
		return NULL;
	}

	void __stdcall _cleanup_ryzenadj(ryzen_access ry) {
		free_smu(ry->psmu);
		free_smu(ry->mp1_smu);
		free_nb(ry->nb);
		free_pci_obj(ry->pci_obj);
		free(ry);
	}

#define _do_adjust(OPT) \
	do{ \
			smu_service_args_t args = {0, 0, 0, 0, 0, 0};    \
			args.arg0 = value; \
			if(smu_service_req(ry->mp1_smu, OPT, &args) == 0x1){   \
				return 0;   \
			} else {    \
				return -1;  \
			} \
	}while(0);

	__declspec(dllexport) int __stdcall set_stapm_limit(uint32_t value) {
		_do_adjust(0x1a);
		printf("Adjusted STAPM Limit.\n");
	}

	__declspec(dllexport) int __stdcall set_fast_limit(uint32_t value) {
		_do_adjust(0x1b);
		printf("Adjusted PPT Fast Limit.\n");
	}

	__declspec(dllexport) int __stdcall set_slow_limit(uint32_t value) {
		_do_adjust(0x1c);
		printf("Adjusted PPT Slow Limit.\n");
	}

	__declspec(dllexport) int __stdcall set_slow_time(uint32_t value) {
		_do_adjust(0x1d);
		printf("Adjusted PPT Slow Time.\n");
	}

	__declspec(dllexport) int __stdcall set_stapm_time(uint32_t value) {
		_do_adjust(0x1e);
		printf("Adjusted STAPM Time.\n");
	}

	__declspec(dllexport) int __stdcall set_tctl_temp(uint32_t value) {
		_do_adjust(0x1f);
		printf("Adjusted Temperature Limit.\n");
	}

	__declspec(dllexport) int __stdcall set_vrm_current(uint32_t value) {
		_do_adjust(0x20);
		printf("Adjusted VRM Current.\n");
	}

	__declspec(dllexport) int __stdcall set_vrmsoc_current(uint32_t value) {
		_do_adjust(0x21);
		printf("Adjusted VRM SoC Current.\n");
	}

	__declspec(dllexport) int __stdcall set_vrmmax_current(uint32_t value) {
		_do_adjust(0x22);
		printf("Adjusted VRM Max Current.\n");
	}

	__declspec(dllexport) int __stdcall set_vrmsocmax_current(uint32_t value) {
		_do_adjust(0x23);
		printf("Adjusted VRM SoC Max Current.\n");
	}

	__declspec(dllexport) int __stdcall set_psi0_current(uint32_t value) {
		_do_adjust(0x24);
		printf("Adjusted PSI0 Current.\n");
	}

	__declspec(dllexport) int __stdcall set_psi0soc_current(uint32_t value) {
		_do_adjust(0x25);
		printf("Adjusted PSI0 SoC Current.\n");
	}
}