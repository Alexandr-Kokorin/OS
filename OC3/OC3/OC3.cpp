#include <iostream>

char** strings;
int* sizes;
int count, iteration, quant;
int* processTime;
int* timeLeft;
int* executionTime;
int* prior;
int* timeReceipt;
bool* isDid;

void input() {
    printf("Введите квант: ");
    scanf_s("%d", &quant);
    printf("Введите кол-во процессов: ");
    scanf_s("%d", &count);
    processTime = (int*)malloc(count * sizeof(int));
    printf("Введите времена процессов: ");
    for (int i = 0; i < count; i++) {
        scanf_s("%d", &processTime[i]);
    }
    strings = (char**)malloc((count + 1) * sizeof(char*));
    for (int i = 0; i <= count; i++) {
        strings[i] = (char*)malloc(256 * sizeof(char));
    }
    sizes = (int*)malloc((count + 1) * sizeof(int));
    timeLeft = (int*)malloc(count * sizeof(int));
    executionTime = (int*)malloc(count * sizeof(int));
    prior = (int*)malloc(count * sizeof(int));
    timeReceipt = (int*)malloc(count * sizeof(int));
    isDid = (bool*)malloc(count * sizeof(bool));
    for (int i = 0; i < count; i++) {
        timeReceipt[i] = 0;
    }
}

void init() {
    for (int i = 0; i <= count; i++) {
        for (int j = 0; j < 256; j++) {
            strings[i][j] = '\0';
        }
    }
    strings[0][0] = '|';
    strings[0][1] = ' ';
    strings[0][2] = ' ';
    strings[0][3] = '|';
    for (int i = 1; i <= count; i++) {
        strings[i][0] = '|';
        if (i <= 9) {
            strings[i][1] = (char)('0' + i);
            strings[i][2] = ' ';
        }
        else {
            strings[i][1] = (char)('0' + i / 10);
            strings[i][2] = (char)('0' + i % 10);
        }
        strings[i][3] = '|';
    }
    for (int i = 0; i <= count; i++) {
        sizes[i] = 4;
    }
    iteration = 1;
    for (int i = 0; i < count; i++) {
        timeLeft[i] = processTime[i];
    }
    for (int i = 0; i < count; i++) {
        executionTime[i] = 0;
    }
    for (int i = 0; i < count; i++) {
        prior[i] = 0;
    }
    for (int i = 0; i < count; i++) {
        isDid[i] = false;
    }
}

void addToLine(int index) {
    if (iteration <= 9) {
        strings[0][sizes[0]] = (char)('0' + iteration);
        strings[0][sizes[0] + 1] = ' ';
    }
    else {
        strings[0][sizes[0]] = (char)('0' + iteration / 10);
        strings[0][sizes[0] + 1] = (char)('0' + iteration % 10);
    }
    strings[0][sizes[0] + 2] = '|';
    sizes[0] += 3;
    for (int i = 1; i <= count; i++) {
        if (timeLeft[i-1] <= 0 || timeReceipt[i-1] >= iteration) {
            strings[i][sizes[i]] = ' ';
        }
        else {
            if (i == index) strings[i][sizes[i]] = 'и';
            else strings[i][sizes[i]] = 'г';
            executionTime[i - 1]++;
        }
        strings[i][sizes[i] + 1] = ' ';
        strings[i][sizes[i] + 2] = '|';
        sizes[i] += 3;
    }
    iteration++;
}

void printTable() {
    char* str = (char*)malloc((sizes[0]+1) * sizeof(char));
    for (int i = 0; i < sizes[0]; i++) {
        str[i] = '-';
    }
    str[sizes[0]] = '\0';
    printf("%s\n", str);
    for (int i = 0; i <= count; i++) {
        printf("%s\n", strings[i]);
        printf("%s\n", str);
    }
}

void printAddTable() {
    int sumExTime = 0, sumWaitTime = 0;
    int size = 18 + 3 * count + 8;
    char* str = (char*)malloc((size + 1) * sizeof(char));
    for (int i = 0; i < size; i++) {
        str[i] = '-';
    }
    str[size] = '\0';
    printf("%s\n", str);
    printf("|      № процесса|");
    for (int i = 0; i < count; i++) {
        if (i <= 9) printf("%d |", i+1);
        else printf("%d|", i+1);
    }
    printf("       |\n");
    printf("%s\n", str);
    printf("|Время выполнения|");
    for (int i = 0; i < count; i++) {
        if (executionTime[i] <= 9) printf("%d |", executionTime[i]);
        else printf("%d|", executionTime[i]);
        sumExTime += executionTime[i];
    }
    if (sumExTime <= 9) printf("S = %d  |\n", sumExTime);
    else if (sumExTime > 9 && sumExTime <= 99) printf("S = %d |\n", sumExTime);
    else printf("S = %d|\n", sumExTime);
    printf("%s\n", str);
    printf("|Время ожидания  |");
    for (int i = 0; i < count; i++) {
        if (executionTime[i] - processTime[i] <= 9) printf("%d |", executionTime[i]-processTime[i]);
        else printf("%d|", executionTime[i] - processTime[i]);
        sumWaitTime += executionTime[i] - processTime[i];
    }
    if (sumWaitTime <= 9) printf("S = %d  |\n", sumWaitTime);
    else if (sumWaitTime > 9 && sumWaitTime <= 99) printf("S = %d |\n", sumWaitTime);
    else printf("S = %d|\n", sumWaitTime);
    printf("%s\n", str);
    printf("Среднее время выполнения %d/%d = %0.1f\n", sumExTime, count, (float)sumExTime / count);
    printf("Среднее время ожидания   %d/%d = %0.1f\n", sumWaitTime, count, (float)sumWaitTime / count);
}

void FCFS1() {
    printf("\nАлгоритм FCFS (без прерывания процесса)\n");
    for (int i = 0; i < count; i++) {
        while (timeLeft[i] > 0) {
            addToLine(i+1);
            timeLeft[i]--;
        }
    }
}

void SJF1() {
    printf("\nАлгоритм SJF (без прерывания процесса)\n");
    for (int i = 0; i < count; i++) {
        int min = 0, index = 0;
        while (index < count && timeLeft[index] <= 0) {
            index++;
        }
        if (index != count) min = timeLeft[index];
        for (int j = index; j < count; j++) {
            if (timeLeft[j] < min && timeLeft[j] > 0) {
                min = timeLeft[j];
                index = j;
            }
        }
        while (timeLeft[index] > 0) {
            addToLine(index + 1);
            timeLeft[index]--;
        }
    }
}

void FCFS2() {
    printf("\nАлгоритм FCFS (c прерыванием процесса)\n");
    int rTime = quant;
    bool flag = true;
    while (flag) {
        for (int i = 0; i < count; i++) {
            while (timeLeft[i] > 0 && rTime > 0) {
                addToLine(i + 1);
                timeLeft[i]--;
                rTime--;
            }
            rTime = quant;
        }
        flag = false;
        for (int i = 0; i < count; i++) {
            if (timeLeft[i] > 0) flag = true;
        }
    }
}

void SJF2() {
    printf("\nАлгоритм SJF (c прерыванием процесса)\n");
    int rTime = quant;
    bool flag = true;
    while (flag) {
        int min = 0, index = 0;
        while (index < count && timeLeft[index] <= 0 || prior[index] == 1) {
            index++;
        }
        if (index != count) min = timeLeft[index];
        for (int j = index; j < count; j++) {
            if (timeLeft[j] < min && timeLeft[j] > 0 && prior[j] == 0) {
                min = timeLeft[j];
                index = j;
            }
        }
        while (timeLeft[index] > 0 && rTime > 0) {
            addToLine(index + 1);
            timeLeft[index]--;
            rTime--;
        }
        for (int i = 0; i < count; i++) {
            prior[i] = 0;
        }
        prior[index] = 1;
        rTime = quant;
        flag = false;
        for (int i = 0; i < count; i++) {
            if (timeLeft[i] > 0) flag = true;
        }
    }
}

void SJF2_1() {
    printf("\nВведите времена поступления процессов: ");
    for (int i = 0; i < count; i++) {
        scanf_s("%d", &timeReceipt[i]);
    }
    printf("\nАлгоритм SJF (c прерыванием процесса и учетом времени поступления)\n");
    bool flag = true;
    while (flag) {
        int min = 0, index = 0;
        while (index < count && timeLeft[index] <= 0 || timeReceipt[index] >= iteration) {
            index++;
        }
        if (index != count) min = timeLeft[index];
        for (int j = index; j < count; j++) {
            if ((timeLeft[j] < min || (timeLeft[j] <= min && prior[j] > prior[index])) && timeLeft[j] > 0 && timeReceipt[j] < iteration) {
                min = timeLeft[j];
                index = j;
            }
        }
        if (timeLeft[index] > 0 && timeReceipt[index] < iteration) {
            addToLine(index + 1);
            timeLeft[index]--;
            prior[index]++;
        }
        flag = false;
        for (int i = 0; i < count; i++) {
            if (timeLeft[i] > 0) flag = true;
        }
    }
}

void SJF3_1() {
    printf("\nВведите приоритеты процессов: ");
    for (int i = 0; i < count; i++) {
        scanf_s("%d", &prior[i]);
    }
    printf("\nАлгоритм SJF (c прерыванием процесса, учетом времени поступления и приоритета)\n");
    bool flag = true;
    while (flag) {
        int min = 0, index = 0;
        while (index < count && timeLeft[index] <= 0 || timeReceipt[index] >= iteration) {
            index++;
        }
        if (index != count) min = timeLeft[index];
        for (int j = index; j < count; j++) {
            if ((((timeLeft[j] < min || (timeLeft[j] >= min && isDid[j] && !isDid[index])) && prior[j] == prior[index]) || prior[j] < prior[index]) && timeLeft[j] > 0 && timeReceipt[j] < iteration) {
                min = timeLeft[j];
                index = j;
            }
        }
        if (timeLeft[index] > 0 && timeReceipt[index] < iteration) {
            addToLine(index + 1);
            timeLeft[index]--;
            isDid[index] = true;
        }
        flag = false;
        for (int i = 0; i < count; i++) {
            if (timeLeft[i] > 0) flag = true;
        }
    }
}

int main() {
    setlocale(LC_ALL, "Rus");
    input();
    init();
    FCFS1();
    printTable();
    printAddTable();
    init();
    SJF1();
    printTable();
    printAddTable();
    init();
    FCFS2();
    printTable();
    printAddTable();
    init();
    SJF2();
    printTable();
    printAddTable();
    init();
    SJF2_1();
    printTable();
    printAddTable();
    init();
    SJF3_1();
    printTable();
    printAddTable();
}