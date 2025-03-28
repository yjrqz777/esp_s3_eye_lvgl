/**
 * @file lv_port_indev_templ.c
 *
 */

/*Copy this file as "lv_port_indev.c" and set this value to "1" to enable content*/
#if 1

/*********************
 *      INCLUDES
 *********************/
#include "lv_port_indev.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_log.h"
// #include "../../lvgl.h"

#include "ui.h"
#include "ui_helpers.h"
#include "test_ui.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void touchpad_init(void);
static void touchpad_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);
static bool touchpad_is_pressed(void);
static void touchpad_get_xy(lv_coord_t * x, lv_coord_t * y);

static void mouse_init(void);
static void mouse_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);
static bool mouse_is_pressed(void);
static void mouse_get_xy(lv_coord_t * x, lv_coord_t * y);

static void keypad_init(void);
static void keypad_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);
static uint32_t keypad_get_key(void);

static void encoder_init(void);
static void encoder_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);
static void encoder_handler(void);

static void button_init(void);
static void button_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);
static int8_t button_get_pressed_id(void);
static bool button_is_pressed(uint8_t id);

/**********************
 *  STATIC VARIABLES
 **********************/
lv_indev_t * indev_touchpad;
lv_indev_t * indev_mouse;
lv_indev_t * indev_keypad;
lv_indev_t * indev_encoder;
lv_indev_t * indev_button;

static int32_t encoder_diff;
static lv_indev_state_t encoder_state;

/**********************
 *      MACROS
 **********************/
lv_group_t* group1;
lv_group_t* group2;
lv_group_t* group3;
lv_group_t* group4;
lv_group_t* group5;
/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_port_indev_init(void)
{
    /**
     * Here you will find example implementation of input devices supported by LittelvGL:
     *  - Touchpad
     *  - Mouse (with cursor support)
     *  - Keypad (supports GUI usage only with key)
     *  - Encoder (supports GUI usage only with: left, right, push)
     *  - Button (external buttons to press points on the screen)
     *
     *  The `..._read()` function are only examples.
     *  You should shape them according to your hardware
     */

    static lv_indev_drv_t indev_drv;

    /*------------------
     * Touchpad
     * -----------------*/

    /*Initialize your touchpad if you have*/
    // touchpad_init();

    // /*Register a touchpad input device*/
    // lv_indev_drv_init(&indev_drv);
    // indev_drv.type = LV_INDEV_TYPE_POINTER;
    // indev_drv.read_cb = touchpad_read;
    // indev_touchpad = lv_indev_drv_register(&indev_drv);

    /*------------------
     * Mouse
     * -----------------*/

    /*Initialize your mouse if you have*/
    // mouse_init();

    // /*Register a mouse input device*/
    // lv_indev_drv_init(&indev_drv);
    // indev_drv.type = LV_INDEV_TYPE_POINTER;
    // indev_drv.read_cb = mouse_read;
    // indev_mouse = lv_indev_drv_register(&indev_drv);

    // /*Set cursor. For simplicity set a HOME symbol now.*/
    // lv_obj_t * mouse_cursor = lv_img_create(lv_scr_act());
    // lv_img_set_src(mouse_cursor, LV_SYMBOL_HOME);
    // lv_indev_set_cursor(indev_mouse, mouse_cursor);

    /*------------------
     * Keypad
     * -----------------*/
    
    /*Initialize your keypad or keyboard if you have*/
    keypad_init();

    /*Register a keypad input device*/
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_KEYPAD;
    indev_drv.read_cb = keypad_read;
    indev_keypad = lv_indev_drv_register(&indev_drv);


    group1 = lv_group_create();
    group2 = lv_group_create();
    group3 = lv_group_create();
    group4 = lv_group_create();
    group5 = lv_group_create();
	// lv_group_set_default(group1);
    lv_indev_set_group(indev_keypad, group1);
    
    //运行demo
    





// SCREEN: ui_Screen2
// lv_obj_t *ui_manbtn;
// lv_obj_t *ui_Label3;
// lv_obj_t *ui_scanbtn;
// lv_obj_t *ui_Label4;
// lv_obj_t *ui_Switch2;
// lv_obj_t *ui_testbtn;
// lv_obj_t *ui_Label6;
// lv_obj_t *ui_wifiname;
// lv_obj_t *ui_Dropdown1;
// lv_obj_t *ui_TextArea2;
// lv_obj_t *ui_conbtn;
// lv_obj_t *ui_Label7;
// lv_obj_t *ui_TextArea3;


    
    lv_group_add_obj(group1,ui_wifibtn);
    lv_group_add_obj(group1,ui_Roller1);

    // lv_indev_set_group(indev_keypad, group1);
    lv_group_focus_obj(ui_wifibtn);



    lv_group_add_obj(group2,ui_backbtn2);
    lv_group_add_obj(group2,ui_nextbtn2);
    lv_group_add_obj(group2,ui_Switch1);

    lv_group_add_obj(group2,ui_scanbtn);
    lv_group_add_obj(group2,ui_wifiname);
    lv_group_add_obj(group2,ui_conbtn);

    lv_group_add_obj(group2,ui_Dropdown1);
    lv_group_add_obj(group2,ui_Switch2);
    // lv_group_add_obj(group2,ui_TextArea2);

    lv_group_add_obj(group3,ui_backbtn3);
    lv_group_add_obj(group3,ui_nextbtn3);
    lv_group_add_obj(group3,ui_scanbtn2);
    lv_group_add_obj(group3,ui_Switch3);
    lv_group_add_obj(group3,ui_TextArea3);
    lv_group_add_obj(group3,ui_Keyboard1);

    lv_group_add_obj(group4,ui_backbtn4);
    lv_group_add_obj(group4,ui_nextbtn4);

    lv_group_add_obj(group5,ui_backbtn5);
    lv_group_add_obj(group5,ui_nextbtn5);


    // lv_group_add_obj(group4,list);
    // lv_group_add_obj(group3,ui_scanbtn2);

    /*Later you should create group(s) with `lv_group_t * group = lv_group_create()`,
     *add objects to the group with `lv_group_add_obj(group, obj)`
     *and assign this input device to group to navigate in it:
     *`lv_indev_set_group(indev_keypad, group);`*/

    /*------------------
     * Encoder
     * -----------------*/

    /*Initialize your encoder if you have*/
    // encoder_init();

    // /*Register a encoder input device*/
    // lv_indev_drv_init(&indev_drv);
    // indev_drv.type = LV_INDEV_TYPE_ENCODER;
    // indev_drv.read_cb = encoder_read;
    // indev_encoder = lv_indev_drv_register(&indev_drv);

    /*Later you should create group(s) with `lv_group_t * group = lv_group_create()`,
     *add objects to the group with `lv_group_add_obj(group, obj)`
     *and assign this input device to group to navigate in it:
     *`lv_indev_set_group(indev_encoder, group);`*/

    /*------------------
     * Button
     * -----------------*/

    /*Initialize your button if you have*/
    // button_init();

    // /*Register a button input device*/
    // lv_indev_drv_init(&indev_drv);
    // indev_drv.type = LV_INDEV_TYPE_BUTTON;
    // indev_drv.read_cb = button_read;
    // indev_button = lv_indev_drv_register(&indev_drv);

    // /*Assign buttons to points on the screen*/
    // static const lv_point_t btn_points[2] = {
    //     {10, 10},   /*Button 0 -> x:10; y:10*/
    //     {40, 100},  /*Button 1 -> x:40; y:100*/
    // };
    // lv_indev_set_button_points(indev_button, btn_points);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/*------------------
 * Touchpad
 * -----------------*/

/*Initialize your touchpad*/
static void touchpad_init(void)
{
    /*Your code comes here*/
}

/*Will be called by the library to read the touchpad*/
static void touchpad_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{
    static lv_coord_t last_x = 0;
    static lv_coord_t last_y = 0;

    /*Save the pressed coordinates and the state*/
    if(touchpad_is_pressed()) {
        touchpad_get_xy(&last_x, &last_y);
        data->state = LV_INDEV_STATE_PR;
    }
    else {
        data->state = LV_INDEV_STATE_REL;
    }

    /*Set the last pressed coordinates*/
    data->point.x = last_x;
    data->point.y = last_y;
}

/*Return true is the touchpad is pressed*/
static bool touchpad_is_pressed(void)
{
    /*Your code comes here*/

    return false;
}

/*Get the x and y coordinates if the touchpad is pressed*/
static void touchpad_get_xy(lv_coord_t * x, lv_coord_t * y)
{
    /*Your code comes here*/

    (*x) = 0;
    (*y) = 0;
}

/*------------------
 * Mouse
 * -----------------*/

/*Initialize your mouse*/
static void mouse_init(void)
{
    /*Your code comes here*/
}

/*Will be called by the library to read the mouse*/
static void mouse_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{
    /*Get the current x and y coordinates*/
    mouse_get_xy(&data->point.x, &data->point.y);

    /*Get whether the mouse button is pressed or released*/
    if(mouse_is_pressed()) {
        data->state = LV_INDEV_STATE_PR;
    }
    else {
        data->state = LV_INDEV_STATE_REL;
    }
}

/*Return true is the mouse button is pressed*/
static bool mouse_is_pressed(void)
{
    /*Your code comes here*/

    return false;
}

/*Get the x and y coordinates if the mouse is pressed*/
static void mouse_get_xy(lv_coord_t * x, lv_coord_t * y)
{
    /*Your code comes here*/

    (*x) = 0;
    (*y) = 0;
}

/*------------------
 * Keypad
 * -----------------*/

/*Initialize your keypad*/
static void keypad_init(void)
{
    /*Your code comes here*/
}

/*Will be called by the library to read the mouse*/
static void keypad_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{
    static uint32_t last_key = 0;

    /*Get the current x and y coordinates*/
    mouse_get_xy(&data->point.x, &data->point.y);

    /*Get whether the a key is pressed and save the pressed key*/
    uint32_t act_key = keypad_get_key();
    if(act_key != 0) {
        data->state = LV_INDEV_STATE_PR;


    // LV_KEY_UP        = 17,  /*0x11*/
    // LV_KEY_DOWN      = 18,  /*0x12*/
    // LV_KEY_RIGHT     = 19,  /*0x13*/
    // LV_KEY_LEFT      = 20,  /*0x14*/
    // LV_KEY_ESC       = 27,  /*0x1B*/
    // LV_KEY_DEL       = 127, /*0x7F*/
    // LV_KEY_BACKSPACE = 8,   /*0x08*/
    // LV_KEY_ENTER     = 10,  /*0x0A, '\n'*/
    // LV_KEY_NEXT      = 9,   /*0x09, '\t'*/
    // LV_KEY_PREV      = 11,  /*0x0B, '*/
    // LV_KEY_HOME      = 2,   /*0x02, STX*/
    // LV_KEY_END       = 3,   /*0x03, ETX*/

        /*Translate the keys to LVGL control characters according to your key definitions*/
        switch(act_key) {
            case 1:
                act_key = LV_KEY_RIGHT;
                break;
            // case 2:
            //     act_key = LV_KEY_PREV;
            //     break;
            case 3:
                act_key = LV_KEY_PREV;
                break;
            case 4:
                act_key = LV_KEY_NEXT;
                break;
            case 5:
                act_key = LV_KEY_ENTER;
                break;
        }

        last_key = act_key;
    }
    else {
        data->state = LV_INDEV_STATE_REL;
    }

    data->key = last_key;
}

/*Get the currently being pressed key.  0 if no key is pressed*/
#include "key.hpp"

static uint32_t keypad_get_key(void)
{
    /*Your code comes here*/
    unsigned char button_flag = 0;
    int p=0;
    ESP_ERROR_CHECK(adc_oneshot_read(adc_handle_with_oneshot,ADC_CHANNEL_0,&p));
    // ESP_LOGI("keypad_get_key","p = %d\n",p);
    // voltage = p *3.3/4096;
    if (p> 300 && p < 500)
    {
        button_flag = 1;
        ESP_LOGI("keypad_get_key = LV_KEY_RIGHT","p = %d\n",button_flag);
    }
    else if (p > 850 && p < 1050)
    {
        button_flag = 4;
        ESP_LOGI("keypad_get_key = LV_KEY_NEXT","p = %d\n",button_flag);
    }
    else if (p > 2250 && p < 2450)
    {
        button_flag = 3;
        ESP_LOGI("keypad_get_key = LV_KEY_PREV","p = %d\n",button_flag);
    }
    else if (p > 2800 && p < 3000)
    {
        button_flag = 5;
        ESP_LOGI("keypad_get_key = LV_KEY_ENTER","p = %d\n",button_flag);
    }
    else
    {
        button_flag = 0;
    }
    // if(button_flag)
    //     ESP_LOGI("keypad_get_key","p = %d\n",button_flag);

    return button_flag;
}

/*------------------
 * Encoder
 * -----------------*/

/*Initialize your keypad*/
static void encoder_init(void)
{
    /*Your code comes here*/
}

/*Will be called by the library to read the encoder*/
static void encoder_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{

    data->enc_diff = encoder_diff;
    data->state = encoder_state;
}

/*Call this function in an interrupt to process encoder events (turn, press)*/
static void encoder_handler(void)
{
    /*Your code comes here*/

    encoder_diff += 0;
    encoder_state = LV_INDEV_STATE_REL;
}

/*------------------
 * Button
 * -----------------*/

/*Initialize your buttons*/
static void button_init(void)
{
    /*Your code comes here*/
}

/*Will be called by the library to read the button*/
static void button_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{

    static uint8_t last_btn = 0;

    /*Get the pressed button's ID*/
    int8_t btn_act = button_get_pressed_id();

    if(btn_act >= 0) {
        data->state = LV_INDEV_STATE_PR;
        last_btn = btn_act;
    }
    else {
        data->state = LV_INDEV_STATE_REL;
    }

    /*Save the last pressed button's ID*/
    data->btn_id = last_btn;
}

/*Get ID  (0, 1, 2 ..) of the pressed button*/
static int8_t button_get_pressed_id(void)
{
    uint8_t i;

    /*Check to buttons see which is being pressed (assume there are 2 buttons)*/
    for(i = 0; i < 2; i++) {
        /*Return the pressed button's ID*/
        if(button_is_pressed(i)) {
            return i;
        }
    }

    /*No button pressed*/
    return -1;
}

/*Test if `id` button is pressed or not*/
static bool button_is_pressed(uint8_t id)
{

    /*Your code comes here*/

    return false;
}

#else /*Enable this file at the top*/

/*This dummy typedef exists purely to silence -Wpedantic.*/
typedef int keep_pedantic_happy;
#endif
