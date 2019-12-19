// Copyright 2019 Ilya <ilia.bezverzhenko@mail.ru>

#include "header.h"

int main() {
    std::cout << std::endl;

    std::vector<double> WT = {6, 2, 8, 4};

    cout_task_info(WT);
    normalization(WT);

    std::vector<std::vector<double>> Matrix;
    create_matrix(Matrix);

    std::cout << std::endl << "======МЕТОД №1. Метод замены критериев ограничениями.======" << std::endl << std::endl;
    replacing_criteria(Matrix);

    std::cout << std::endl << "======МЕТОД №2. Формирование и сужение множества Парето.======" << std::endl << std::endl;
    Pareto_set(Matrix);

    std::cout << std::endl << "======МЕТОД №3. Взвешивание и объединение критериев.======" << std::endl << std::endl;
    weighing(Matrix);

    std::cout << std::endl << "======МЕТОД №4. Метод анализа иерархий.======" << std::endl << std::endl;
    hierarchy_analysis();

    return 0;
}


