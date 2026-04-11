#include <stdio.h>
#include <string.h>
#include "dynamicArray/dynamicArray.h"
#include "fieldinfo/fieldinfo.h"
#include "person/person.h"
#include "robot/robot.h"
#include "ui.h"

#ifdef _WIN32
#include <windows.h>
#endif

static DynamicArray* students;
static DynamicArray* temp_result;

void ui_init(void) {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
#endif
    
    students = dynamicArrayCreate(getStudentFieldInfo(), 10);
    temp_result = dynamicArrayCreate(getStudentFieldInfo(), 10);
    
    dynamicArrayAppend(students, personCreate("Ivan", "Alekseevich", "Starovoytov", 1, 123, 1998));
    dynamicArrayAppend(students, personCreate("Maria", NULL, "Sharapova", 2, 456, 2002));
    dynamicArrayAppend(students, personCreate("Petr", "Olegovich", "Medvedev", 1, 789, 1995));
}

// Предикаты
static bool series1(const void* p) { 
    return ((Person*)p)->id.series == 1; 
}
static bool young(const void* p) { 
    return (2026 - ((Person*)p)->birthYear) < 25; 
}
static bool nameI(const void* p) { 
    return ((Person*)p)->firstName[0] == 'I'; 
}

void ui_run(void) {
    int choice;
    
    while (1) {
        printf("\n=== ВЕКТОР СТУДЕНТОВ (Эл: %zu) ===\n", students->size);
        printf("1. Показать всех\n");
        printf("2. 1-я серия\n");
        printf("3. Младше 25\n");
        printf("4. Имя на I\n");
        printf("5. Конкатенация\n");
        printf("6. Добавить\n");
        printf("0. Выход\n");
        printf("➤ ");
        
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            continue;
        }
        getchar();
        
        switch (choice) {
            case 1: dynamicArrayPrint(students, "Студенты"); break;
            case 2: dynamicArrayWhere(students, series1, temp_result); dynamicArrayPrint(temp_result, "1-я серия"); break;
            case 3: dynamicArrayWhere(students, young, temp_result); dynamicArrayPrint(temp_result, "Младше 25"); break;
            case 4: dynamicArrayWhere(students, nameI, temp_result); dynamicArrayPrint(temp_result, "Имя на I"); break;
            case 5: {
                DynamicArray* copy = dynamicArrayConcat(students, students);
                dynamicArrayPrint(copy, "Конкатенация");
                dynamicArrayDestroy(copy);
                break;
            }
            case 6: {
                char first[30], middle[30], last[30]; int s, n, y;
                printf("Полное ФИО Серия Номер Год (Alexey Igorevich Lobanov 1 123 2007): ");
                

                char line[100];
                fgets(line, sizeof(line), stdin);
                line[strcspn(line, "\n")] = 0;
                
                if (sscanf(line, "%29s %29s %29s %d %d %d", first, middle, last, &s, &n, &y) >= 5) {
                    dynamicArrayAppend(students, personCreate(first, strlen(middle) ? middle : NULL, last, s, n, y));
                    printf("%s %s %s добавлен!\n", first, strlen(middle) ? middle : "", last);
                } else {
                    printf("Формат: Имя Отчество Фамилия Серия Номер Год\n");
                }
                break;
            }

            case 0: goto end;
            default: printf("0-6!\n");
        }
        printf("\n[Enter для меню]");
        getchar();
    }
end:
    dynamicArrayDestroy(students);
    dynamicArrayDestroy(temp_result);
    printf("До свидания!\n");
}