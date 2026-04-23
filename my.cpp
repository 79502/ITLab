//n - число вершин
//m - число ребер
struct E {
    int a;
    int b;
    long double sz;
};

void sort_with_pivot(E* arr, double pivot, int last_index) {
    int left = 0;
    int right = last_index;

    while (left <= right) {

        while (left <= right && arr[left].sz < pivot) {
            left++;
        }

        while (left <= right && arr[right].sz >= pivot) {
            right--;
        }

        if (left < right) {
            swap(arr[left], arr[right]);
            left++;
            right--;
        }
    }
}

void Boruvka_filter(E* my) { //передаем массив ребер

    int* father = new int[n];
    bool* component = new bool[n];// массив оставшихся компонент
    E* thr = new E[n - 1];
    int Edge = 0; // счётчик количества рёбер записанных в дерево

    list<int>borders; //лист с границами разделений массива
    borders.push_front(m - 1);
    int start = 0;
    int finish = m;

    random_device rd;
    mt19937 gen(rd());
    int random_;
    long double sum = 0.0;
    long double pivot;
    uniform_int_distribution<int> int_dist; // функция рандома

    for (int i = 0; i < n; i++) {
        father[i] = i;
        component[i] = 1;
    }

    //---------------------------------------------------------
    // разделение массива

    while (borders.front() > 1 * n) {
        sum = 0.0;
        int_dist = uniform_int_distribution<int>(0, borders.front());

        for (int i = 0; i < 10; i++) {
            random_ = int_dist(gen);
            sum += my[random_].sz;
        }
        pivot = sum * 0.1;

        sort_with_pivot(my, pivot, borders.front()); // сортировка относительно опорного

        for (int j = 0; j < m; j++) { //поиск места опорного элемента
            if (pivot <= my[j].sz) {
                borders.push_front(j);
                break;
            }
        }
    }
    borders.push_front(0);

    //--------------------------------------------------------

    cout << "Sort is ended" << endl;

    start = borders.front();
    borders.pop_front();
    finish = borders.front();

    while (Edge != n - 1) {

        int* best_edge = new int[n];
        for (int i = 0; i < n; i++) best_edge[i] = -1;

        for (int i = start; i < finish; i++) {
            int comp_a = father[my[i].a];
            int comp_b = father[my[i].b];

            if (comp_a != comp_b) {
                // Проверяем для компоненты A
                if (best_edge[comp_a] == -1 || my[i].sz < my[best_edge[comp_a]].sz) {
                    best_edge[comp_a] = i;
                }
                // Проверяем для компоненты B
                if (best_edge[comp_b] == -1 || my[i].sz < my[best_edge[comp_b]].sz) {
                    best_edge[comp_b] = i;
                }
            }
        }

        //добавляем найденные рёбра в MST
        int added = 0;
        for (int comp = 0; comp < n; comp++) {
            if (best_edge[comp] != -1 && component[comp]) {  // comp существует

                int edge_idx = best_edge[comp];
                int a = father[my[edge_idx].a];
                int b = father[my[edge_idx].b];

                if (a != b) {  //разные компоненты
                    thr[Edge++] = my[edge_idx];
                    added++;

                    // Объединяем компоненты
                    for (int k = 0; k < n; k++) {
                        if (father[k] == b) father[k] = a;
                    }
                    component[b] = 0;  // компонента b больше не существует
                }
            }
        }

        delete[] best_edge;

        if (added == 0) {
            start = borders.front();
            borders.pop_front();
            if (borders.size() == 0) {
                cout << "Graph is not connected" << endl;
                break;
            }
            finish = borders.front();
        }

    }

    delete[] thr;
    delete[] father;
    delete[] component;

}
