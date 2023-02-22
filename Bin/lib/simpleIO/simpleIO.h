
#include "pico/stdlib.h"
#include "hardware/pwm.h"

class simpleIO{

    public:
        void initall(){
            stdio_init_all();
        }
        
        void pinOut(uint8_t pin){
            gpio_init(pin);
            gpio_set_dir(pin, GPIO_OUT);
        }

        void pinPWM(uint8_t pin){
            gpio_set_function(pin, GPIO_FUNC_PWM);
            uint slice_num = pwm_gpio_to_slice_num(pin);
            pwm_set_wrap(slice_num, 255);
            pwm_set_chan_level(slice_num, PWM_CHAN_A, 1);
            pwm_set_chan_level(slice_num, PWM_CHAN_B, 255);
            pwm_set_enabled(slice_num, true);
        }


        void pinWrite(uint8_t pin, bool state){
            if(state==true){
                gpio_put(pin, 1);
            } else {
                gpio_put(pin, 0);
            }
        }

        void setPWM(uint8_t pin, int pwm){
            pwm_set_gpio_level(pin, pwm);
        }

};