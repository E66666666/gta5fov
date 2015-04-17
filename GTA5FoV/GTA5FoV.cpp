#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <Windows.h>
#include <Psapi.h>

#include "patches.h"

FILE *logfile;
BOOL haveLog;

char *applyPatch(patch_t *patch, const char *modOffset)
{
	if (haveLog) fprintf(logfile, "Applying patch: %s\r\n", patch->name);
	char *patchLoc, *codeLoc, *patchTemp = NULL;
	DWORD oldProtect;

	for (size_t i = (size_t)modOffset; i < UINT64_MAX; i++)
	{
		for (size_t j = 0; j < patch->signatureLength; j++)
		{
			if (patch->signature[j] != *(char*)(i + j))
				break;

			if (j == patch->signatureLength - 1)
			{
				patchLoc = (char *)i;
				goto endloops;
			}
		}
	}

endloops:
	if (haveLog) fprintf(logfile, "Signature search complete\r\n");
	if (patchLoc == NULL)
	{
		if (haveLog) fprintf(logfile, "Patch failed\r\n");
		return NULL;
	}
	if (haveLog) fprintf(logfile, "Signature found at %llx\r\n", patchLoc);

	codeLoc = (char *)malloc(patch->codeLength);
	VirtualProtect(codeLoc, patch->codeLength, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy(codeLoc, patch->code, patch->codeLength);
	// jump is 13 bytes, return after jump and nops
	char *afterPatchLoc = patchLoc + patch->jumpOffset + 13 + patch->nopCount;
	memcpy(codeLoc + patch->jumpBackAddrOffset, &afterPatchLoc, 8);
	if (haveLog) fprintf(logfile, "Code written\r\n");

	patchTemp = (char *)malloc(13 + patch->nopCount);
	memcpy(patchTemp, patchTemplate, 13);
	memcpy(patchTemp + 2, &codeLoc, 8);
	for (size_t i = 0; i < patch->nopCount; i++)
	{
		*(char*)(patchTemp + 13 + i) = 0x90;
	}

	VirtualProtect(patchLoc + patch->jumpOffset, 13 + patch->nopCount, PAGE_EXECUTE_READWRITE, &oldProtect);
	if (haveLog) fprintf(logfile, "Game code made RWX\r\n");
	memcpy(patchLoc + patch->jumpOffset, patchTemp, 13 + patch->nopCount);
	if (haveLog) fprintf(logfile, "Game code patched\r\n");
	VirtualProtect(patchLoc + patch->jumpOffset, 13 + patch->nopCount, oldProtect, &oldProtect);
	if (haveLog) fprintf(logfile, "Game code memory protection restored\r\n");

	free(patchTemp);

	return codeLoc;
}

bool setPatchParameter(patch_t *patch, char *location, const char *paramName, const char *paramValue)
{
	if (haveLog) fprintf(logfile, "Setting parameter %s on patch %s\r\n", paramName, patch->name);
	patch_parameter_t *param = NULL;

	for (size_t i = 0; i < patch->paramCount; i++) 
	{
		if (strcmp(patch->parameters[i].name, paramName) == 0)
		{
			param = &patch->parameters[i];
			break;
		}
	}

	if (param == NULL)
	{
		if (haveLog) fprintf(logfile, "No such parameter\r\n");
		return false;
	}

	memcpy(location + param->offset, paramValue, param->length);

	if (haveLog) fprintf(logfile, "Parameter set\r\n");
	return true;
}

bool iniReadFloat(const char *section, const char *name, float default, float *out)
{
	char buffer[100], defaultStr[100];
	_snprintf_s(defaultStr, 100, "%f", default);
	GetPrivateProfileString(section, name, defaultStr, buffer, 100, ".\\fov.ini");
	*out = strtof(buffer, NULL);
	return (*out != HUGE_VALF && *out != -HUGE_VALF);
}

DWORD WINAPI fovfix(LPVOID lpParameter)
{
	Sleep(30 * 1000);

	if (fopen_s(&logfile, "fov-log.txt", "w") == EINVAL || logfile == NULL) haveLog = false;
	else haveLog = true;
	if (haveLog) fprintf(logfile, "Logging initialised\r\n");

	float fov;
	if (!iniReadFloat("FirstPerson", "Walking", 68, &fov)) goto err;
	if (haveLog) fprintf(logfile, "Target FoV is %f\r\n", fov);

	MODULEINFO modinfo;
	HMODULE hModule = GetModuleHandle("GTA5.exe");
	if (hModule == 0) goto err;
	if (haveLog) fprintf(logfile, "Module handle found\r\n");
	GetModuleInformation(GetCurrentProcess(), hModule, &modinfo, sizeof(MODULEINFO));
	char *modOffset = (char *)(modinfo.lpBaseOfDll);
	if (haveLog) fprintf(logfile, "lpBaseOfDll: %llx\r\n", modinfo.lpBaseOfDll);

	char *codeLoc = applyPatch(&fovPatches[0], (char*)modOffset);
	if (codeLoc == NULL) goto err;

	if (!setPatchParameter(&fovPatches[0], codeLoc, "fov", (char*)&fov)) goto err;

	goto exit;

err:
	MessageBoxA(NULL, "FOV Fix has encountered an issue", NULL, MB_OK | MB_ICONWARNING);
exit:
	if (logfile) fclose(logfile);
	return 0;
}