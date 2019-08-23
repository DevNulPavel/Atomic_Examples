#include <atomic>
#include <thread>
#include <assert.h>

std::atomic<bool> x, y;
std::atomic<int> z;

void write_x() {
    // Записываем true значение в X, release - значит барьер на записи, acquire - значит барьер на чтении
    x.store(true, std::memory_order_release);
}

void write_y() {
    // Записываем true значение в Y, release - значит барьер на записи, acquire - значит барьер на чтении
    y.store(true, std::memory_order_release);
}

void write_x_then_y() {
    // Записываем true значение в Y, release - значит барьер на записи, acquire - значит барьер на чтении
    x.store(true, std::memory_order_release);
    y.store(true, std::memory_order_release);
}

void read_x_then_y() {
    // Ждем, пока X не станет true
    while(x.load(std::memory_order_acquire) == false){
    }
    // Если Y == false, тогда мы увеличиваем Z
    if(y.load(std::memory_order_acquire) == false){
        ++z;
    }
}

void read_y_then_x() {
    // Ждем, пока Y не станет true
    while(y.load(std::memory_order_acquire) == false){
    }
    // Если X == false, тогда мы увеличиваем Z
    if(x.load(std::memory_order_acquire) == false){
        ++z;
    }
}

int main() {
    x = false;
    y = false;
    z = 0;
    std::thread a(write_x_then_y);
    //std::thread b(write_y);
    //std::thread c(read_x_then_y);
    std::thread d(read_y_then_x);
    a.join();
    //b.join();
    //c.join();
    d.join();
    
    // Если все работает правильно, то Z == 0
    printf("Z = %d\n", z.load());
    assert(z.load() == 0);
}
