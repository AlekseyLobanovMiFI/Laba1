#include <stdio.h>
#include "ui.h"
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#ifdef _WIN32
#include <windows.h>
#endif

#include "person/person.h"
#include "robot/robot.h"
#include "fieldinfo/fieldinfo.h"
#include "dynamicArray/dynamicArray.h"
#include "test/test.h"
#include <stdio.h>

static void print_menu(void) {
    puts("=== ГЛАВНОЕ МЕНЮ ===");
    puts("1 — запустить все тесты");
    puts("2 — запустить UI‑интерфейс");
    puts("0 — выход");
    printf("Выберите режим: ");
}



int main(void) {
    int choice;
    print_menu();

    while (scanf("%d", &choice) == 1) {
        switch (choice) {
            case 1:
                printf("\n=== ЗАПУСК ТЕСТОВ ===\n\n");
                test_dynamic_array_basic();
                test_dynamic_array_person();
                test_dynamic_array_robot();
                test_person_robot();
                test_fieldinfo();
                break;

            case 2:
                printf("\n=== ЗАПУСК UI‑ИНТЕРФЕЙСА СТУДЕНТОВ ===\n\n");
                ui_init();
                ui_run();
                break;

            case 0:
                printf("Выход.\n");
                return 0;

            default:
                printf("0–2!\n");
                break;
        }

        puts("");
        print_menu();
    }

    return 0;
}


