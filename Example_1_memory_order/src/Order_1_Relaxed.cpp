#include <atomic>
#include <thread>
#include <assert.h>

std::atomic<bool> x, y;
std::atomic<int> z;


// Сначала выставляем true в X, затем в Y
void write_x_then_y() {
    x.store(true, std::memory_order_relaxed);
    y.store(true, std::memory_order_relaxed);
}

void read_y_then_x() {
    // Ждем, пока не выставится Y в True
    while(!y.load(std::memory_order_relaxed)){
    }
    // Так как X в потоке выставляется всегда перед Y, то вроде бы
    // все должно быть верно, но по факту - из-за memory_order_relaxed (слабый порядок обновления значений),
    // другой поток может не увидеть обновления значения и x все еще будет false
    // Как результат - Z будет больше 0
    if(x.load(std::memory_order_relaxed) == false){
        ++z;
    }
}

int main() {
    do {
        x = false;
        y = false;
        z = 0;
        std::thread a(write_x_then_y);
        std::thread b(read_y_then_x);
        a.join();
        b.join();
        if (z.load() != 0) {
            printf("Z == %d\n", z.load());
        }
        assert(z.load() == 0);
    }while(z.load() == 0);
    
    if (z.load() != 0) {
        printf("Z == %d\n", z.load());
    }
}
