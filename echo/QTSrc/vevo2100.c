#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXCHARS 100
#define MAXNAME 30

struct Dest {
		int str;
		int size;
};

void getName(const char *srcStr, struct Dest *arg);
void getDigit(const char *srcStr, struct Dest *arg);
void getDigit2(const char *srcStr, struct Dest *arg);
void splitName(const char *name, char *name1, char *name2);

int deal(const char *inputName, const char *outputName){
		FILE *fo;
		FILE *fw;
		char string[MAXCHARS];
		char name[MAXNAME];
		char name1[MAXNAME];
		char name2[MAXNAME];
		double num;
        struct Dest *arg = (struct Dest *)malloc(sizeof(struct Dest));
		arg->str = 0;
		arg->size = 0;

		fo = fopen(inputName, "r");
		fw = fopen(outputName, "w");
		if (!fo) {
                fprintf(stderr, "Cannot open %s, enter a valid file name.\n", inputName);
				exit(2);
		}
		if (!fw) {
                fprintf(stderr, "Cannot make %s file.\n", outputName);
				exit(3);
		}
		fprintf(fw, "Series_name,Group1,Group2,LVAW_d,Units,LVAW_s,Units,LVID_d,Units,LVID_s,Units,LVPW_d,Units,LVPW_s,Units,EF,Units,FS,Units,LV_Mass_Aw(cr),Units,LV_Vol_d,Units,LV_Vol_s,Units\n");
		while (fgets(string, MAXCHARS, fo)) {
				if (strstr(string, "Series Name")) {
						getName(string, arg);
						strncpy(name, string + arg->str, (arg->size));
						name[arg->size] = '\0';
						if (strstr(name, "+")) {
								splitName(name, name1, name2);
								fprintf(fw, "%s,%s,%s,", name, name1, name2);
						}
						else
								fprintf(fw, "%s, , ,", name);
				}
				if (strstr(string, "No measurements found")) {
						fprintf(fw, "\n");
						continue;
				}
				if (strstr(string, "LVAW;d") || strstr(string, "LVAW;s") || strstr(string, "LVID;d") || strstr(string, "LVID;s") || strstr(string, "LVPW;d") || strstr(string, "LVPW;s")) {
						getDigit(string, arg);
						strncpy(name, string + arg->str, (arg->size));
						name[arg->size] = '\0';
						fprintf(fw, "%s,mm,", name);
				}
				if (strstr(string, "EF") || strstr(string, "FS")) {
						getDigit2(string, arg);
						strncpy(name, string + arg->str, (arg->size));
						name[arg->size] = '\0';
						fprintf(fw, "%s,%%,", name);
				}
				if (strstr(string,"LV Mass AW (Corrected)")) {
						getDigit2(string, arg);
						strncpy(name, string + arg->str, (arg->size));
						name[arg->size] = '\0';
						fprintf(fw, "%s,mg,", name);
				}
				if (strstr(string, "LV Vol;d")) {
						getDigit2(string, arg);
						strncpy(name, string + arg->str, (arg->size));
						name[arg->size] = '\0';
						fprintf(fw, "%s,uL,", name);
				}
				if (strstr(string, "LV Vol;s")) {
						getDigit2(string, arg);
						strncpy(name, string + arg->str, (arg->size));
						name[arg->size] = '\0';
						fprintf(fw, "%s,uL\n", name);
				}
		}
	fclose(fo);
	fclose(fw);
	free(arg);

	return 0;
}

void getName(const char *srcStr, struct Dest *arg) {
		int i;
		int len = strlen(srcStr);

		for (i = 0; i < len;) {
				if (srcStr[i++] == ',')
						break;
		}
		arg->str = ++i;
		while (srcStr[++i] != '\"')
				continue;
		arg->size = i - arg->str;
}

void getDigit(const char *srcStr, struct Dest *arg) {
		int i;
		double num;
		int count = 0;
		int len = strlen(srcStr);

		for (i = 0; count < 4;) {
				if (srcStr[i++] == ',')
						++count;
		}
		arg->str = ++i;
		while (srcStr[++i] != '\"')
				continue;
		arg->size = i - arg->str;
}

void getDigit2(const char *srcStr, struct Dest *arg) {
		int i;
		int count = 0;
		int len = strlen(srcStr);

		for (i = 0; count < 3;) {
				if (srcStr[i++] == ',')
						++count;
		}
		arg->str = i;
		while (srcStr[++i] != ',')
				continue;
		arg->size = i - arg->str;
}

void splitName(const char *name, char *name1, char *name2) {
		// split by '+'
		int i, len, tempPoint;

		len = strlen(name);
		for (i = 0; i < len; ++i) {
				if (name[i] == '+')
						break;
		}
		tempPoint = i;
		strncpy(name1, name, tempPoint);
		name1[tempPoint] = '\0';
		for (;i < len; ++i) {
				if (name[i] == ' ')
						break;
		}
		strncpy(name2, name + tempPoint + 1, i - tempPoint - 1);
		name2[i - tempPoint - 1] = '\0';
}

