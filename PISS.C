/*Plant Information Storage System using C language with the concept of file handling.
This program allows users to add, view, edit, and delete plant information. The data is stored in a text file.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

// Structure to represent a plant
struct Plant {
    char botanical_name[100];
    char common_name[100];
    char description[500];
    char image_url[200];
    char growing_conditions[200];
    char geographical_data[200];
    char medical_uses[200];
    char culinary_uses[200];
    char seasonal_info[200];
    char conservation_status[100];
};

// Function declarations
void displayMenu();
void addPlant();
void viewPlants();
void editPlant();
void deletePlant();

void header();
void welcome();

int main() {
    int choice;
    textbackground(2);
    clrscr();

    do {
	displayMenu();
	printf("Enter your choice: ");
	scanf("%d", &choice);

	switch (choice) {
	    case 1:
		addPlant();
		break;
	    case 2:
		viewPlants();
		break;
	    case 3:
		editPlant();
		break;
	    case 4:
		deletePlant();
		break;
	    case 5:
		printf("Exiting the program. Goodbye!\n");
		break;
	    default:
		clrscr();
		header();
		printf("Invalid choice. Please enter a valid option.\n");
		header();
	}

    } while (choice != 5);

    return 0;
}

void displayMenu() {
    printf("\n====================++ Plant Information Storage System ++====================\n");
    printf("1. Add a Plant\n");
    printf("2. View Plants\n");
    printf("3. Edit a Plant\n");
    printf("4. Delete a Plant\n");
    printf("5. Exit\n");
}

void addPlant() {
    FILE *file = fopen("plant_data.txt", "a");
    struct Plant plant;

    printf("Enter Botanical Name: ");
    scanf(" %[^\n]", plant.botanical_name);

    printf("Enter Common Name: ");
    scanf(" %[^\n]", plant.common_name);

    printf("Enter Description: ");
    scanf(" %[^\n]", plant.description);

    printf("Enter Geographical Data: ");
    scanf(" %[^\n]", plant.geographical_data);

    printf("Enter Seasonal Info: ");
    scanf(" %[^\n]", plant.seasonal_info);
    // Add other fields as needed

    fprintf(file, "%s|%s|%s|%s|%s|%s|%s|%s|%s|%s\n",
	    plant.botanical_name, plant.common_name,
	    plant.description, plant.image_url,
	    plant.growing_conditions, plant.geographical_data,
	    plant.medical_uses, plant.culinary_uses,
	    plant.seasonal_info, plant.conservation_status);

    fclose(file);
    clrscr();
    printf("Plant added successfully!\n");
}

void viewPlants() {
    FILE *file = fopen("plant_data.txt", "r");
    struct Plant plant;

    if (!file) {
	clrscr();
	printf("No plants found.\n");
	return;
    }


    while (fscanf(file, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%s\n",
		  plant.botanical_name, plant.common_name,
		  plant.description, plant.image_url,
		  plant.growing_conditions, plant.geographical_data,
		  plant.medical_uses, plant.culinary_uses,
		  plant.seasonal_info, plant.conservation_status) != EOF) {

    clrscr();
    welcome();
    printf("\nPlants:\n");

    printf("--------------------------------------------------------------------------------\n");
    printf(" Botanical Name | Common Name | Description | Geographical Data | Seasonal Info\n");
    printf("--------------------------------------------------------------------------------\n");


	printf(" |Scientific Name: %-15s\n\n |Common Name: %-11s\n\n |Description: %-11s\n\n |Geographical Data: %-17s\n\n |Seasonal Info: %-14s\n\n",
	       plant.botanical_name, plant.common_name,
	       plant.description,
	       plant.geographical_data,
	       plant.seasonal_info);
	       printf("Press Enter to Continue!");
	       getch();
	       clrscr();
    }

    fclose(file);
   // printf("This is the End of the List !");
   // getch();
    clrscr();
}

void editPlant() {
    FILE *file = fopen("plant_data.txt", "r");
    FILE *tempFile = fopen("temp_data.txt", "w");
    struct Plant plant;

    char editBotanicalName[100];
    int found = 0;
    clrscr();
    welcome();
    printf("\n\nEnter the Botanical Name of the plant to edit: ");
    scanf(" %[^\n]", editBotanicalName);

    while (fscanf(file, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%s\n",
		  plant.botanical_name, plant.common_name,
		  plant.description, plant.image_url,
		  plant.growing_conditions, plant.geographical_data,
		  plant.medical_uses, plant.culinary_uses,
		  plant.seasonal_info, plant.conservation_status) != EOF) {
	if (strcmp(plant.botanical_name, editBotanicalName) == 0) {
	    found = 1;

	    printf("\nEnter updated Botanical Name: ");
	    scanf(" %[^\n]", plant.botanical_name);

	    printf("\nEnter updated Common Name: ");
	    scanf(" %[^\n]", plant.common_name);

	    printf("\nEnter Description: ");

	    scanf(" %[^\n]", plant.description);

	    printf("\nEnter Geographical Data: ");
	    scanf(" %[^\n]", plant.geographical_data);

	    printf("\nEnter Seasonal Info: ");
	    scanf(" %[^\n]", plant.seasonal_info);

	    // Update other fields as needed

	    fprintf(tempFile, "%s|%s|%s|%s|%s|%s|%s|%s|%s|%s\n",
		    plant.botanical_name, plant.common_name,
		    plant.description, plant.image_url,
		    plant.growing_conditions, plant.geographical_data,
		    plant.medical_uses, plant.culinary_uses,
		    plant.seasonal_info, plant.conservation_status);
	    clrscr();
	    header();
	    printf("Plant updated successfully!\n");
	    header();
	} else {
	    fprintf(tempFile, "%s|%s|%s|%s|%s|%s|%s|%s|%s|%s\n",
		    plant.botanical_name, plant.common_name,
		    plant.description, plant.image_url,
		    plant.growing_conditions, plant.geographical_data,
		    plant.medical_uses, plant.culinary_uses,
		    plant.seasonal_info, plant.conservation_status);
	}
    }

    fclose(file);
    fclose(tempFile);

    remove("plant_data.txt");
    rename("temp_data.txt", "plant_data.txt");

    if (!found) {
	clrscr();
	header();
	printf("Plant not found.\n");
	header();
    }
}

void deletePlant() {
    FILE *file = fopen("plant_data.txt", "r");
    FILE *tempFile = fopen("temp_data.txt", "w");
    struct Plant plant;

    char deleteBotanicalName[100];
    int found = 0;
     clrscr();
     welcome();
    printf("\nEnter the Botanical Name of the plant to delete: ");
    scanf(" %[^\n]", deleteBotanicalName);

    while (fscanf(file, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%s\n",
		  plant.botanical_name, plant.common_name,
		  plant.description, plant.image_url,
		  plant.growing_conditions, plant.geographical_data,
		  plant.medical_uses, plant.culinary_uses,
		  plant.seasonal_info, plant.conservation_status) != EOF) {
	if (strcmp(plant.botanical_name, deleteBotanicalName) == 0) {
	    found = 1;
	    clrscr();
	    header();
	    printf("Plant deleted successfully!\n");
	    header();
	} else {
	    fprintf(tempFile, "%s|%s|%s|%s|%s|%s|%s|%s|%s|%s\n",
		    plant.botanical_name, plant.common_name,
		    plant.description, plant.image_url,
		    plant.growing_conditions, plant.geographical_data,
		    plant.medical_uses, plant.culinary_uses,
		    plant.seasonal_info, plant.conservation_status);
	}
    }

    fclose(file);
    fclose(tempFile);

    remove("plant_data.txt");
    rename("temp_data.txt", "plant_data.txt");

    if (!found) {
	clrscr();
	header();
	printf("Plant not found.\n");
	header();
    }
}
void welcome(){
    printf("\n====================++ Plant Information Storage System ++====================\n");
}
void header(){
printf("##################################################\n");
}