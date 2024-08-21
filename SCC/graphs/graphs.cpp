#include "iostream";
#include "Header.h"

int main() {
    setlocale(LC_ALL, "ru");
    Graph g(5);
    g.addEdge(1, 0);
    g.addEdge(0, 2);
    g.addEdge(2, 1);
    g.addEdge(0, 3);
    g.addEdge(3, 4);

    cout << "Сильно связанные компоненты:\n";
    g.SCC();
    g.printSCCs();

    return 0;
}