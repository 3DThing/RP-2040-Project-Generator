/*
Функции micros,millis,seconds - это переменные считающие время от старта микроконтроллера. 
Для реализации многозадачности необходимо объявить переменную при которой будет считатся время и если 
времени прошло больше или равно чем нам нужно то выполняется условие. Пример ниже. Аналогично эти функции работают 
в ардуино!

        int time;
        uint64_t tmr1;
        if (seconds() - tmr1 >= 60) {
            tmr1 = seconds();
            time++;
            printf("NOW Lost %ds \n", time);
        }

*/

    unsigned long micros(){ //таймер в микросекундах
        return (to_us_since_boot(get_absolute_time()));
    }
    unsigned long millis(){ //таймер в милисекундах
        return (to_ms_since_boot(get_absolute_time()));
    }
    unsigned long seconds(){ //таймер в секундах
        int time = to_ms_since_boot(get_absolute_time());
        return (time/1000);
    }
