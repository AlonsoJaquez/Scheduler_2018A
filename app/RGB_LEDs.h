/****************************************************************************
 * Project developed as a simple Blink the LED's to 
 * demonstrate basic CodeWarrior functionality and capability.
 * Borrowed from Freedom Example Projects: Blinky
 * 
 * Date: 11 Sept 2012
 * Author: M. Ruthenbeck
 * Revision Level 1.0
 */
#ifndef RGB_LEDS_H                       /* To avoid double inclusion */
#define RGB_LEDS_H


extern void init_pins(void);
extern void app_rgb_led(void);
extern void app_rgb_led_fsm(void);

extern void pin4_on();
extern void pin4_off();
extern void pin5_on();
extern void pin5_off();

extern void set_pins_inputs(void);
extern void reinit_pins(void);

#endif /* RGB_LEDS_H */
