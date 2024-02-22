/*
 * @Author: YJRQZ777 
 * @Date: 2024-02-21 18:20:15 
 * @Last Modified by: YJRQZ777
 * @Last Modified time: 2024-02-21 19:52:26
 */

#include "key.hpp"
#include "main_cpp.hpp"

int main_cpp()
{
    Button *key = new Button();
    key->adc_init_with_oneshot();
    // key->run_with_oneshot();
    return 0;
}