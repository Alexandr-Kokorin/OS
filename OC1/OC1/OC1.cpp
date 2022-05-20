#include <iostream>

struct Process {
    int id;
    int time;
};

int main()
{
    setlocale(LC_ALL, "Rus");
    Process* processes = NULL;
    int count;
    printf("Введите кол-во процессов: ");
    scanf_s("%d", &count);
    processes = (Process*)malloc(count * sizeof(Process));
    for (int i = 0; i < count; i++) {
        printf("Введите время выполнения %d-го процесса: ", i+1);
        processes[i].id = i+1;
        scanf_s("%d", &processes[i].time);
    }
    bool flag = true;
    while (flag) {
        flag = false;
        for (int i = 0; i < count-1; i++) {
            if (processes[i].time < processes[i + 1].time) {
                Process temp = processes[i];
                processes[i] = processes[i + 1];
                processes[i + 1] = temp;
                flag = true;
            }
        }
    }
    int sumProc1 = 0, sumProc2 = 0;
    int countProc1 = 0, countProc2 = 0;
    Process* processor1 = NULL;
    Process* processor2 = NULL;
    for (int i = 0; i < count; i++) {
        if (sumProc1 <= sumProc2) {
            processor1 = (Process*)realloc(processor1, (countProc1+1) * sizeof(Process));
            processor1[countProc1] = processes[i];
            countProc1++;
            sumProc1 += processes[i].time;
        }
        else {
            processor2 = (Process*)realloc(processor2, (countProc2 + 1) * sizeof(Process));
            processor2[countProc2] = processes[i];
            countProc2++;
            sumProc2 += processes[i].time;
        }
    }
    printf("1 процессор: ");
    for (int i = 0; i < countProc1; i++) {
        printf("%d ", processor1[i].id);
    }
    printf("\n2 процессор: ");
    for (int i = 0; i < countProc2; i++) {
        printf("%d ", processor2[i].id);
    }
}