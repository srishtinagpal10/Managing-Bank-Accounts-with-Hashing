#ifndef QUADRATICPROBING_H
#define QUADRATICPROBING_H

#include "BaseClass.h"
#include <iostream>

class QuadraticProbing : public BaseClass {
public:
    void createAccount(std::string id, int count) override;
    std::vector<int> getTopK(int k) override;
    int getBalance(std::string id) override;
    void addTransaction(std::string id, int count) override;
    bool doesExist(std::string id) override;
    bool deleteAccount(std::string id) override;
    int databaseSize() override;
    int hash(std::string id) override;
    QuadraticProbing();

private:
    int tablesize=131071;
    int size=0;
    std::string deletedflag="deleted";
    void merge(std::vector<int>& arr, int left, int middle, int right);
    void mergesort(std::vector<int>& arr, int left, int right);
    void resizetable();
};

#endif // QUADRATICPROBING_H