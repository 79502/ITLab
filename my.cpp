#include <iostream>

void Tree(E* my) {
    int father[n];
    bool component[n];
    E thr[n];
    for (int i = 0; i < n; i++) {
        thr[i].a = n;
        thr[i].b = n;
        thr[i].sz = 0;
    }

    for (int i = 0; i < n; i++) {
        father[i] = i;
        component[i] = 1;
    }

    E temp[n];
    int Edge = 0; // счётчик количества рёбер записанных в дерево
    int col = 0; // 

    while (Edge != n - 1) {
        col = 0;
        for (int j = 0; j < n; j++) { // цикл для каждой компоненты связности
            if (component[j] != 0) {
                int tmp = MAX_SIZE + 1;
                int p = 0;
                for (int i = 0; i < m; i++) {
                    if (my[i].sz != 0.0 && ((father[my[i].a] == j) || (father[my[i].b] == j)) && my[i].sz < tmp) { // поиск наименьшего ребра
                        tmp = my[i].sz;                                                                         // 'p' - номер оптимального ребра для компоненты 
                        p = i;
                    }
                }
                temp[col].a = my[p].a;
                temp[col].b = my[p].b;
                temp[col].sz = my[p].sz;
                col++;
            }
        }
        for (int i = 0; i < col; i++) { // объеденение компонент (цикл для оптимаьного ребра каждой компоненты)
            int a = father[temp[i].a];
            int b = father[temp[i].b];
            if (a != b) {               // если ребро не лежит целиком в одной компоненте
                thr[Edge] = temp[i];
                Edge++;

                for (int k = 0; k < n; k++)
                    if (father[k] == b)
                        father[k] = a;
                component[b] = 0; // удаляем одну их компонент

                for (int ij = 0; ij < m; ij++)
                    if (father[my[ij].a] == a && father[my[ij].b] == a)
                        my[ij].sz = 0.0;                                 // удаляем ребра внутри одной компоненты
            }
        }

    }
}
