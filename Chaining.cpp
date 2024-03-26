#include "Chaining.h"

Chaining::Chaining(){
    bankStorage2d.resize(tablesize);
}

void Chaining::createAccount(std::string id, int count) {
    int index=hash(id);
    if(doesExist(id)==false){
        Account newaccount;
        newaccount.id=id;
        newaccount.balance=count;
        bankStorage2d[index].push_back(newaccount);
    }
    size+=1;
}

void Chaining::merge(std::vector<int>& arr, int left, int middle, int right){
    int n1=middle-left+1;
    int n2=right-middle;
    std::vector<int> leftArray(n1);
    std::vector<int> rightArray(n2);
    for (int i = 0; i < n1; i++) {
        leftArray[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        rightArray[j] = arr[middle + 1 + j];
    }
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArray[i] >= rightArray[j]) {
            arr[k] = leftArray[i];
            i++;
        } else {
            arr[k] = rightArray[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = leftArray[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = rightArray[j];
        j++;
        k++;
    }
}

void Chaining:: mergesort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;
        mergesort(arr, left, middle);
        mergesort(arr, middle + 1, right);
        merge(arr, left, middle, right);
    }
}

std::vector<int> Chaining::getTopK(int k) {
    std::vector<int> answer;
    for (const std::vector<Account>& accounts : bankStorage2d) {
        for (const Account& account : accounts) {
            answer.push_back(account.balance);
        }
    }
    mergesort(answer,0,answer.size()-1);
    if(k<answer.size()){
            answer.resize(k);
        }
    return answer; 
}

int Chaining::getBalance(std::string id) {
    int index=hash(id);
    for(Account &account:bankStorage2d[index]){
        if(account.id==id){
            return account.balance;
        }
    }
    return -1; // Placeholder return value
}

void Chaining::addTransaction(std::string id, int count) {
    std::vector<int> answer;
    int index=hash(id);
    for(Account &account:bankStorage2d[index]){
        if(account.id==id){
            account.balance+=count;
            return;
        }
    }
    Account newaccount;
    newaccount.id=id;
    newaccount.balance=count;
    bankStorage2d[index].push_back(newaccount);
    size+=1;
}

bool Chaining::doesExist(std::string id) {
    int index=hash(id);
    for(Account &account:bankStorage2d[index]){
        if(account.id==id){
            return true;
        }
    }
    return false; 
}

bool Chaining::deleteAccount(std::string id) {
    int index=hash(id);
    int index1=-1;
    for(auto it=bankStorage2d[index].begin(); it!=bankStorage2d[index].end();++it){
        if(it->id==id){
            bankStorage2d[index].erase(it);
            size-=1;
            return true;
        }
    }
    return false; 
}
int Chaining::databaseSize() {
    return size;
}

int Chaining::hash(std::string id) {
    std::string hashid=id.substr(0, 4);
    std::string hashid2=id.substr(5,11);
    std::string hashid3=id.substr(12);
    int hashvalue = 0;
    for (char c : hashid) {
        hashvalue = (hashvalue*31+static_cast<int>(c))%150001;
    }
    for (char c:hashid2){
        hashvalue=(hashvalue*13+static_cast<int>(c))%150001;
    }
    for (char c:hashid3){
        hashvalue=(hashvalue*17+static_cast<int>(c))%150001;
    }
    hashvalue %= 131071;
    return hashvalue;
}
