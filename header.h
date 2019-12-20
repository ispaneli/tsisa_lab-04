// Copyright 2019 Ilya <ilia.bezverzhenko@mail.ru>

#ifndef __LAB5_HEADER_H
#define __LAB5_HEADER_H

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cmath>

void cout_task_info(const std::vector<double>& vec) {
    std::cout << "1) Цена за 1 м^3: . . . . . ";
    std::cout << vec[0] << std::endl;

    std::cout << "2) Легкость обработки:. . . ";
    std::cout << vec[1] << std::endl;

    std::cout << "3) Долговечность: . . . . . ";
    std::cout << vec[2] << std::endl;

    std::cout << "4) Водостойкость: . . . . . ";
    std::cout << vec[3] << std::endl << std::endl;
}

void print(const std::vector<double>& vec) {
    std::cout << "{";

    for (size_t i = 0; i < vec.size(); ++i) {

        if (i != vec.size() - 1) {
            std::cout << std::setprecision(3) << vec[i] << ", ";
        } else {
            std::cout << vec[i];
        }
    }

    std::cout << "}." << std::endl << std::endl;
}

void normalization(std::vector<double>& vec) {
    double sum = 0;

    for (auto& i : vec) {
        sum += i;
    }

    for (auto& i : vec) {
        i /= sum;
    }

    std::cout << "Вектор после нормирования: ";

    print(vec);
}

void print(std::vector<std::vector<double>>& mat) {
    std::cout << "|___|___1___|___2___|___3___|___4___|" << std::endl;

    std::vector<char> letters = {'A', 'B', 'C', 'D'};

    for (size_t i = 0; i < 4; ++i) {
        std::cout << "| " << letters[i] << " |";

        for (size_t j = 0; j < 4; ++j) {
            std::cout << std::setw(5) << int(mat[i][j] * 100 + 0.5) / 100.0 << "  |";
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;
}

void print2(std::vector<std::vector<double>>& mat) {
    std::cout << "|___|___1___|___2___|___3___|___4___|" << std::endl;

    std::vector<char> letters = {'1', '2', '3', '4'};

    for (size_t i = 0; i < 4; ++i) {
        std::cout << "| " << letters[i] << " |";

        for (size_t j = 0; j < 4; ++j) {
            std::cout << std::setw(5) << int(mat[i][j] * 100 + 0.5) / 100.0 << "  |";
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;
}

void get_answer(size_t index) {
    if (index == 0) {
        std::cout << "A)Береза.";
    } else if (index == 1) {
        std::cout << "B)Сосна.";
    } else if (index == 2) {
        std::cout << "C)Дуб.";
    } else if (index == 3) {
        std::cout << "D)Лиственница.";
    }
}

void create_matrix(std::vector<std::vector<double>>& Matrix) {
    Matrix = {{7, 7, 2, 2},
              {5, 4, 3, 6},
              {2, 3, 5, 3},
              {4, 2, 6, 7}};

    std::cout << "Составленная матрица оценок:" << std::endl;

    print(Matrix);
}


/// Метод 1: "Метод замены критериев ограничениями".
void replacing_criteria(std::vector<std::vector<double>> Matrix) {
    std::cout << "Главный критерий - дешевизна (т.е. обратное цене)." << std::endl << std::endl;
    std::cout << "Минимально допустимые уровни для остальных критериев:" << std::endl;
    std::cout << "а) Легкость обработки >= 0.4×A_max2, т.е. >= 2.8" << std::endl;
    std::cout << "б) Долговечность      >= 0.2×A_max3, т.е. >= 1.2" << std::endl;
    std::cout << "в) Водостойкость      >= 0.2×A_max4, т.е. >= 1.4" << std::endl << std::endl;

    std::vector<double> A_max, A_min;


    for (size_t i = 1; i < 4; ++i) {
        double tmp_max = Matrix[0][i],
                tmp_min = Matrix[0][i];

        for (size_t j = 1; j < 4; ++j) {

            if (tmp_max < Matrix[j][i]) {
                tmp_max = Matrix[j][i];
            }

            if (tmp_min > Matrix[j][i]) {
                tmp_min = Matrix[j][i];
            }
        }

        A_max.push_back(tmp_max);
        A_min.push_back(tmp_min);
    }

    for (size_t i = 1; i < 4; ++i) {

        for (size_t j = 0; j < 4; ++j) {
            Matrix[j][i] = (Matrix[j][i] - A_min[i - 1]) / (A_max[i - 1] - A_min[i - 1]);
        }
    }

    std::cout << "Составленная матрица оценок после нормирования:" << std::endl;

    print(Matrix);

    std::vector<double> result(4);

    for (size_t i = 0; i < 4; ++i) {

        for (size_t j = 0; j < 4; ++j) {

            if (j != 0) {

                result[i] += Matrix[i][j];
            } else {

                result[i] += (10 - Matrix[i][j]);
            }
        }
    }

    std::cout << "Приемлемый вариант: ";

    get_answer(std::distance(result.begin(), std::min_element(result.begin(), result.end())));

    std::cout << std::endl << std::endl;
}

/// Метод 2: "Формирование и сужение множества Парето".
void Pareto_set(std::vector<std::vector<double>> Matrix) {
    std::cout << "Главные критерии: Дешевизна и Долговечность." << std::endl << std::endl;
    std::vector<std::pair<double, double>> main;

    for (auto& i : Matrix) {
        main.emplace_back(i[0], i[2]);
    }

    std::pair<double, double> utopia;
    utopia.first = 0;
    utopia.second = 10;

    std::cout << "Точка утопии: (" << utopia.first << ";" << utopia.second << ")." << std::endl;

    std::vector<double> radii;

    for (auto& i : main) {
        i.first =  std::abs(utopia.first - i.first);
        i.second = std::abs(utopia.second - i.second);
    }

    for (auto& i : main) {
        radii.push_back(i.first + i.second);
    }

    std::cout << "Вектор Манхэттенских расстояний: ";
    print(radii);

    std::cout << std::endl << "Приемлемый вариант: ";

    get_answer(std::distance(radii.begin(), std::min_element(radii.begin(), radii.end())));

    std::cout << std::endl << std::endl;
}

/// Метод 3: "Взвешивание и объединение критериев".
void weighing(std::vector<std::vector<double>> Matrix) {
    std::vector<double> tmp(4);

    for (auto& i : Matrix) {
        for (size_t j = 0; j < i.size(); ++j) {
            tmp[j] += i[j];
        }
    }

    for (auto& i : Matrix) {
        for (size_t j = 0; j < i.size(); ++j) {
            i[j] /= tmp[j];
        }
    }

    print(Matrix);

    std::vector<double> experts_12_13_14_23_24_34 = {1, 0.5, 1, 0, 0.5, 1};
    std::cout << "Вектор экспертных оценок критериев: ";
    print(experts_12_13_14_23_24_34);

    std::vector<double> WeightCriteria = {1 + 0.5 + 1, 0 + 0 + 0.5, 0.5 + 1 + 1, 0 + 0.5 + 0};
    std::cout << "Вектор весов критериев: ";
    print(WeightCriteria);
    normalization(WeightCriteria);

    std::cout << "Умножим нормализованную матрицу на" << std::endl;
    std::cout << "нормализованный вектор весов критериев." << std::endl;
    std::cout << "Таким образом получим значения объединенного" << std::endl; ;
    std::cout << "критерия для всех альтернатив: ";
    std::vector<double> result = {0, 0, 0, 0};

    for (size_t i = 0; i < Matrix.size(); ++i) {

        for (size_t j = 0; j < Matrix[i].size(); ++j) {

            result[i] += Matrix[i][j] * WeightCriteria[j];
        }
    }

    print(result);

    std::cout << "Приемлемый вариант: ";

    get_answer(std::distance(result.begin(), std::max_element(result.begin(), result.end())));
    std::cout << std::endl << std::endl;
}

std::vector<double> sum_line(const std::vector<std::vector<double>>& Matrix) {
    std::vector<double> result = {0, 0, 0, 0};

    for (size_t i = 0; i < Matrix.size(); ++i) {
        for (size_t j = 0; j < Matrix[i].size(); ++j) {
            result[i] += Matrix[i][j];
        }
    }

    print(result);

    return result;
}

void add_vector(std::vector<std::vector<double>>& Matrix, const std::vector<double>& vec) {

    for (size_t i = 0; i < Matrix.size(); ++i) {
        Matrix[i].push_back(vec[i]);
    }
}

void search_coefficient(std::vector<std::vector<double>>& Matrix) {
    std::vector<double> a(4);

    for (size_t i = 0; i < 4; ++i) {
        double tmp = 1;

        for (size_t j = 0; j < 4; ++j) {
            tmp *= Matrix[i][j];
        }

        a[i] = std::pow(tmp, 0.25);
    }

    double sum_a = a[0] + a[1] + a[2] + a[3];

    std::vector<double> NWP(4);

    for(size_t i = 0; i < 4; ++i) {
        NWP[i] = a[i] / sum_a;
    }

    double lymbda = 0;

    for (size_t i = 0; i < 4; ++i) {
        double tmp = 0;

        for (size_t j = 0; j < 4; ++j) {
            tmp += Matrix[j][i];
        }

        lymbda += tmp * NWP[i];
    }

    double IS = (lymbda - 4) / 3;

    std::cout << "Отношение согласованности данной матрицы: " << IS / 0.9 << std::endl;
}

void hierarchy_analysis() {
    std::vector<std::vector<double>> PriceMatrix = {{1,     3,     7, 5    },
                                                    {0.333, 1,     5, 3    },
                                                    {0.143, 0.2,   1, 0.333},
                                                    {0.2,   0.333, 3, 1    }};

    std::vector<std::vector<double>> ProcessingMatrix = {{1,     3,     5,     7},
                                                         {0.333, 1,     5,     7},
                                                         {0.2,   0.2,   1,     3},
                                                         {0.143, 0.143, 0.333, 1}};

    std::vector<std::vector<double>> DurabilityMatrix = {{1, 0.333, 0.2, 0.143},
                                                         {3, 1,     0.2, 0.143},
                                                         {5, 5,     1,   0.333},
                                                         {7, 7,     3,   1    }};

    std::vector<std::vector<double>> WaterResistanceMatrix = {{1, 0.5, 0.25, 0.143},
                                                              {2, 1,   0.2,  0.2  },
                                                              {4, 5,   1,    0.333},
                                                              {7, 5,   3,    1    }};

    print2(PriceMatrix);
    search_coefficient(PriceMatrix);
    std::cout << "Сумма по строке: ";
    std::vector<double> SumPrice = sum_line(PriceMatrix);
    normalization(SumPrice);

    print2(ProcessingMatrix);
    search_coefficient(ProcessingMatrix);
    std::cout << "Сумма по строке: ";
    std::vector<double> SumProcessing = sum_line(ProcessingMatrix);
    normalization(SumProcessing);

    print2(DurabilityMatrix);
    search_coefficient(DurabilityMatrix);
    std::cout << "Сумма по строке: ";
    std::vector<double> SumDurability = sum_line(DurabilityMatrix);
    normalization(SumDurability);

    print2(WaterResistanceMatrix);
    search_coefficient(WaterResistanceMatrix);
    std::cout << "Сумма по строке: ";
    std::vector<double> SumWaterResistance = sum_line(WaterResistanceMatrix);
    normalization(SumWaterResistance);

    std::vector<std::vector<double>> Matrix(4);
    add_vector(Matrix, SumPrice);
    add_vector(Matrix, SumProcessing);
    add_vector(Matrix, SumDurability);
    add_vector(Matrix, SumWaterResistance);

    std::vector<std::vector<double>> PrioritizationMatrix = {{1,     7, 3,     5    },
                                                             {0.143, 1, 0.2,   0.333},
                                                             {0.333, 5, 1,     3    },
                                                             {0.2,   3, 0.333, 1    }};

    print2(PrioritizationMatrix);
    std::cout << "Сумма по строке: ";
    std::vector<double> SumPrioritization = sum_line(PrioritizationMatrix);
    normalization(SumPrioritization);

    std::vector<double> result = {0, 0, 0, 0};

    for (size_t i = 0; i < Matrix.size(); ++i) {

        for (size_t j = 0; j < Matrix[i].size(); ++j) {

            result[i] += Matrix[i][j] * SumPrioritization[j];
        }
    }

    std::cout << "Результат-вектор алгоритма: ";
    print(result);

    std::cout << "Приемлемый вариант: ";

    get_answer(std::distance(result.begin(), std::max_element(result.begin(), result.end())));
    std::cout << std::endl << std::endl;
}

#endif //__LAB5_HEADER_H
