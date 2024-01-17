/*
 Points to remember
 1. There should be only one instance of the class. 
 2. Use of =, () should be not allowed. 
 3. To make it thread-safe we use mutex lock, but it is expensive. So, we add a double-check.

*/


#include<bits/stdc++.h>

using namespace std;

class cacheService
{
private:
    static cacheService *serviceInstance;
    map<string, int> mp;
    static int cnt; // to check how many instances are created.
    static mutex mtx;
    cacheService(){
        cnt++;
        cout << "count of Instances = " << cnt << endl;
    } // this function is added here so that, any other object can't be instantiated. 
    
     // to avoide use of = operator and assignment , so that copy/clone of object is not created.
    cacheService operator=(const cacheService &); 
    cacheService(const cacheService &);   

public:
   
    void addToCache(string name, int cnt){
        mp[name] = cnt;
    }

    int getCache(string name){
        return mp[name];
    }

    static cacheService* getInstance(){
        if(serviceInstance == NULL) // Double check, to make it less expensive
        { // Now lock will be used only one the first instance creation.
            mtx.lock();
            if(serviceInstance == NULL){
                serviceInstance = new cacheService();
            }
            mtx.unlock();
        }
            
        return serviceInstance;
    }

};

cacheService* cacheService::serviceInstance = NULL;
int cacheService::cnt = 0;
mutex cacheService::mtx;

void fun1(){
    cacheService *service1 = cacheService::getInstance();

    service1->addToCache("vipin", 1);
}

void fun2(){
    cacheService *service2 = cacheService::getInstance();

    cout << service2->getCache("vipin") << endl;
}

void fun3(){
    cacheService *service3 = cacheService::getInstance();

    cout << service3->getCache("nitin") << endl;
}

int main(){
    
    thread t1(fun1);
    thread t2(fun2);
    thread t3(fun3);

    t1.join();
    t2.join();
    t3.join();
    
    
    
    // it will show error.
    //cacheService service4 = *service2;
}

