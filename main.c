#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void removeSubstr(char* string, char* sub) {
	char substring[6] = " ";
	strcat(substring, sub);
	char* match;
	int len = strlen(substring);
	match = strstr(string, substring);
	if (match != NULL) {
		*match = '\0';
		strcat(string, match + len - 1);
	}
	else {
		printf("Error: Could not remove province ID from original file.\n\n");
	}	
}


int main() {
	printf("Welcome to Glorwyn's State Template Creation tool!\n\n\n");
	while (1) {
		printf("Enter file name (with .txt, 0 to exit):\n");
		char fileName[40];
		gets(fileName);
		if (fileName[0] == '0') {
			break;
		}
		printf("\n");
		printf("Enter state name:\n");
		char stateName[40];
		gets(stateName);
		printf("\n");
		printf("Enter state ID:\n");
		int stateID = -1;
		scanf_s("%d", &stateID);
		FILE* newState = fopen(fileName, "w");
		fprintf(newState, "state={\n\tid=%d\n\tname=\"%s\"\n\tprovinces={\n\t\t", stateID, stateName);

		//load up data from 1-State_1.txt so we can remove IDs
		FILE* stateOne = fopen("1-State_1.txt", "r");
		char* stateOneData = calloc(1000, sizeof(char));
		int totalSpace = 1000;
		int currentChar = 0;
		while (1) {
			int cChar = fgetc(stateOne);
			if (cChar == EOF) {
				stateOneData[currentChar] = '\0';
				break;
			}
			else {
				if (currentChar < totalSpace) {
					stateOneData[currentChar] = cChar;
					currentChar++;
				}
				else {
					totalSpace += 1000;
					stateOneData = realloc(stateOneData, totalSpace);
					stateOneData[currentChar] = cChar;
					currentChar++;
				}
			}
		}


		
		char provinceID[5];
		gets(provinceID);
		while (1) {
			printf("Province IDs to add (0 to cancel):\n");
			gets(provinceID);
			if (provinceID[0] == '0') {
				break;
			}
			strcat(provinceID, " ");
			fprintf(newState, "%s", provinceID);

			removeSubstr(stateOneData, provinceID);
		}

		fprintf(newState, "\n\t}\n\tmanpower = 110\n\tbuildings_max_level_factor=1.000\n}");
		fclose(newState);

		fclose(stateOne);
		stateOne = fopen("1-State_1.txt", "w");
		int length = strlen(stateOneData);
		for (int currentChar = 0; currentChar < length; currentChar++) {
			fprintf(stateOne, "%c", stateOneData[currentChar]);
		}
		fclose(stateOne);
		printf("\n\n\n\n");
	}

	printf("\n\n\nThank you for using Glorwyn's State Template Creation tool! :3");
}