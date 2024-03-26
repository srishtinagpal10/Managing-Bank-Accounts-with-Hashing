#include "QuadraticProbing.h"

QuadraticProbing:: QuadraticProbing(){
    bankStorage1d.resize(tablesize);
    size=0;
};
void QuadraticProbing::createAccount(std::string id, int count) {
    if (size>=tablesize*0.7){
        resizetable();
    }
    int index = hash(id);
    int originalindex=hash(id);
    int i=1;
    while(bankStorage1d[index].id != "" && bankStorage1d[index].id!=deletedflag){
        index = (originalindex + i * i) % tablesize;
        i++;
    }
    bankStorage1d[index].id = id;
    bankStorage1d[index].balance = count;
    size += 1;
}
void QuadraticProbing::merge(std::vector<int>& arr, int left, int middle, int right){
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

void QuadraticProbing:: mergesort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;
        mergesort(arr, left, middle);
        mergesort(arr, middle + 1, right);
        merge(arr, left, middle, right);
    }
}
std::vector<int> QuadraticProbing::getTopK(int k) {
    std::vector<int> answer;
    for (int i = 0; i < tablesize; i++) {
        if (bankStorage1d[i].id != "" && bankStorage1d[i].id!=deletedflag) {
            answer.push_back(bankStorage1d[i].balance);
            }
        }
    mergesort(answer,0,answer.size()-1);
    if (k < answer.size()) {
        answer.resize(k);
    }
    return answer;
}

int QuadraticProbing::getBalance(std::string id) {
    int index = hash(id);
    int originalindex=hash(id);
    int i = 1;
    while (bankStorage1d[index].id != "") {
        if (bankStorage1d[index].id == id) {
            return bankStorage1d[index].balance;
        }
        index = (originalindex + i * i) % tablesize;
        i++;
        if (index==originalindex){
            break;
        }
    }
    return -1;
}

void QuadraticProbing::addTransaction(std::string id, int count) {
    int index = hash(id);
    int originalindex=hash(id);
    int i = 1;
    while (bankStorage1d[index].id != "" ) {
        if (bankStorage1d[index].id == id) {
            bankStorage1d[index].balance += count;
            return;
        }
        index = (originalindex + i * i) % tablesize;
        i++;
        if (index==originalindex){
            break;
        }
    }
    bankStorage1d[index].id = id;
    bankStorage1d[index].balance = count;
    size += 1;
}

bool QuadraticProbing::doesExist(std::string id) {
    int index = hash(id);
    int originalindex=hash(id);
    int i = 1;
    while (bankStorage1d[index].id != "" ) {
        if (bankStorage1d[index].id == id) {
            return true;
        }
        index = (originalindex + i * i) % tablesize;
        i++;
        if (index==originalindex){
            break;
        }
    }
    return false;
}

bool QuadraticProbing::deleteAccount(std::string id) {
    int index = hash(id);
    int originalindex=hash(id);
    int i = 1;
    while (bankStorage1d[index].id != "" ) {
        if (bankStorage1d[index].id == id) {
            bankStorage1d[index].id = deletedflag;
            bankStorage1d[index].balance = 0;
            size--;
            return true;
        }
        index = (originalindex + i * i) % tablesize;
        i++;
        if (index==originalindex){
            break;
        }
    }
    return false;
}

int QuadraticProbing::databaseSize() {
    return size;
}

int QuadraticProbing::hash(std::string id) {
    std::string hashid=id.substr(0, 4);
    std::string hashid2=id.substr(5,11);
    std::string hashid3=id.substr(12);
    int hashvalue = 0;
    for (char c : hashid) {
        hashvalue = (hashvalue*31+static_cast<int>(c))%131071;
    }
    for (char c:hashid2){
        hashvalue=(hashvalue*13+static_cast<int>(c))%131071;
    }
    for (char c:hashid3){
        hashvalue=(hashvalue*17+static_cast<int>(c))%131071;
    }
    hashvalue %= 131071;
    return hashvalue;
}

void QuadraticProbing::resizetable() {
    int newtablesize = tablesize * 2;
    std::vector<Account> newBankStorage(newtablesize);

    for (int i = 0; i < tablesize; i++) {
        if (bankStorage1d[i].id != "" && bankStorage1d[i].id != deletedflag){
            // Rehash the existing accounts into the new table
            int newIndex = hash(bankStorage1d[i].id);
            int originalindex=hash(bankStorage1d[i].id);
            while (newBankStorage[newIndex].id != "") {
                newIndex = (newIndex + 1) % newtablesize;
                if (newIndex==originalindex){
                    return;
                }
            }
            newBankStorage[newIndex] = bankStorage1d[i];
        }
    }

    // Update the class variables with the new table and size
    bankStorage1d = newBankStorage;
    tablesize = newtablesize;
}