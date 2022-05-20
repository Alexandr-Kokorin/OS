#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <locale.h>

struct Process {
    int id;
    int time;
};

int count;
Process* processes;
FILE* file;

void readFile() {
    FILE* file;
    char str[256];
    file = fopen("test.txt", "r");
    fscanf(file, "%[^\n]\n", str);
    count = atoi(str);
    processes = (Process*)malloc(count * sizeof(Process));
    printf("Кол-во процессов: %d\n", count);
    fscanf(file, "%[^\n]\n", str);
    fclose(file);
    int i = 0, j = 0, index = 0;
    char number[16] = "";
    printf("Время исполнения: ");
    while (str[i] != '\0') {
        if (str[i] >= '0' && str[i] <= '9') {
            number[j] = str[i];
            j++;
            number[j] = '\0';
        }
        else {
            processes[index].time = atoi(number);
            processes[index].id = index + 1;
            printf("%d ", processes[index].time);
            index++;
            j = 0;
            number[j] = '\0';
        }
        i++;
    }
    processes[index].time = atoi(number);
    processes[index].id = index + 1;
    printf("%d\n", processes[index].time);
}

void readConsole() {
    printf("Введите кол-во процессов: ");
    scanf_s("%d", &count);
    processes = (Process*)malloc(count * sizeof(Process));
    printf("Введите время исполнения: ");
    for (int i = 0; i < count; i++)
    {
        scanf_s("%d", &processes[i].time);
        processes[i].id = i + 1;
    }
}

void readRandom() {
    printf("Введите кол-во процессов: ");
    scanf_s("%d", &count);
    processes = (Process*)malloc(count * sizeof(Process));
    printf("Время исполнения: ");
    for (int i = 0; i < count; i++)
    {
        processes[i].time = 1 + rand() % 50;
        processes[i].id = i + 1;
        printf("%d ", processes[i].time);
    }
    printf("\n");
}

void PrintConsoleAdd(int n) {
    printf(" %d", n);
    if (n < 10) printf("           |");
    if (n >= 10 && n < 100) printf("          |");
    if (n >= 100 && n < 1000) printf("         |");
}

void PrintFileAdd(int n) {
    fprintf(file, " %d", n);
    if (n < 10) fprintf(file, "           |");
    if (n >= 10 && n < 100) fprintf(file, "          |");
    if (n >= 100 && n < 1000) fprintf(file, "         |");
}

void PrintConsole() {
    int index = 0, sum = 0, min, quant = 0, id;
    printf("-------------------------------------------------------------------------------------\n");
    printf("| Номер       | Квант       | Суммарное   | Номер       | Время       | Оставшееся  |\n");
    printf("| итерации    | времени ЦП  | доступное   | выбранного  | выбранного  | время ЦП    |\n");
    printf("|             |             | время ЦП    | процесса    | процесса    |             |\n");
    printf("-------------------------------------------------------------------------------------\n");
    while (count > 0) {
        printf("|");
        min = processes[0].time;
        for (int i = 1; i < count; i++)
        {
            if (processes[i].time < min) min = processes[i].time;
        }
        if (sum < min) {
            quant = 1 + rand() % 50;
            index++;
            PrintConsoleAdd(index);
            PrintConsoleAdd(quant);
            sum += quant;
        }
        else printf("             |             |");
        PrintConsoleAdd(sum);
        id = 0;
        min = sum;
        for (int i = 0; i < count; i++)
        {
            if (sum - processes[i].time >= 0 && sum - processes[i].time < min) {
                min = sum - processes[i].time;
                id = i;
            }
        }
        if (min != sum) {
            PrintConsoleAdd(processes[id].id);
            PrintConsoleAdd(processes[id].time);
            sum = min;
            count--;
            processes[id] = processes[count];
            processes = (Process*)realloc(processes, count * sizeof(Process));
        }
        else printf(" -           | -           |");
        PrintConsoleAdd(sum);
        printf("\n");
        printf("-------------------------------------------------------------------------------------\n");
    }
}

void PrintFile() {
    file = fopen("data.txt", "w");
    int index = 0, sum = 0, min, quant = 0, id;
    fprintf(file, "-------------------------------------------------------------------------------------\n");
    fprintf(file, "| Номер       | Квант       | Суммарное   | Номер       | Время       | Оставшееся  |\n");
    fprintf(file, "| итерации    | времени ЦП  | доступное   | выбранного  | выбранного  | время ЦП    |\n");
    fprintf(file, "|             |             | время ЦП    | процесса    | процесса    |             |\n");
    fprintf(file, "-------------------------------------------------------------------------------------\n");
    while (count > 0) {
        fprintf(file, "|");
        min = processes[0].time;
        for (int i = 1; i < count; i++)
        {
            if (processes[i].time < min) min = processes[i].time;
        }
        if (sum < min) {
            quant = 1 + rand() % 50;
            index++;
            PrintFileAdd(index);
            PrintFileAdd(quant);
            sum += quant;
        }
        else fprintf(file, "             |             |");
        PrintFileAdd(sum);
        id = 0;
        min = sum;
        for (int i = 0; i < count; i++)
        {
            if (sum - processes[i].time >= 0 && sum - processes[i].time < min) {
                min = sum - processes[i].time;
                id = i;
            }
        }
        if (min != sum) {
            PrintFileAdd(processes[id].id);
            PrintFileAdd(processes[id].time);
            sum = min;
            count--;
            processes[id] = processes[count];
            processes = (Process*)realloc(processes, count * sizeof(Process));
        }
        else fprintf(file, " -           | -           |");
        PrintFileAdd(sum);
        fprintf(file, "\n");
        fprintf(file, "-------------------------------------------------------------------------------------\n");
    }
    fclose(file);
}

int main()
{
    setlocale(LC_ALL, "Rus");
    srand(time(NULL));
    int choice;
    printf("Выберите вариант ввода:\n");
    printf("1. Ввод с клавиатуры\n");
    printf("2. Генерация случайным образом\n");
    printf("3. Чтение из файла\n");
    printf("Ваш выбор: ");
    scanf_s("%d", &choice);
    switch (choice) {
    case 1:
        readConsole();
        break;
    case 2:
        readRandom();
        break;
    case 3:
        readFile();
        break;
    default:
        break;
    }
    if (count >= 21) {
        PrintFile();
        printf("Данные были выведены в файл\n");
    }
    else {
        PrintConsole();
    }
}